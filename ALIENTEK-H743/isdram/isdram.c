/**
 * @file isdram.c
 * @author SHUAIWEN CUI (shuaiwencui AT gmail DOT com)
 * @brief This file is the source file for the isdram.c file
 * @version 1.0
 * @date 2024-07-16
 * @ref https://blog.csdn.net/Believeziwo/article/details/131372421
 */

#include "isdram.h"
#include "fmc.h"

/**
 * @name SDRAM Initialization Sequence
 * @brief SDRAM initialization sequence
 * @param None
 * @retval None
 * !NOTE: to use sdram, the frequency can not be too high, otherwise the sdram will not work properly. This is the core for SDRAM initialization. CubeMX will do FMC initialization, then we need this function to do SDRAM initialization. After that, we can use SDRAM in the application layer.
 * 
 */
void SDRAM_Initialization_Sequence(void)
{
  uint32_t temp = 0;

  // After the SDRAM controller initialization, the SDRAM still needs to be initialized in the following order

  /* Step 1 ----------------------------------------------------------------*/
  /* enable the clock for SDRAM */
  SDRAM_Send_Cmd(0, FMC_SDRAM_CMD_CLK_ENABLE, 1, 0);

  /* Step 2 ----------------------------------------------------------------*/
  /* delay for a while, at least 200us */
  HAL_Delay(1);

  /* Step 3 ----------------------------------------------------------------*/
  /* precharge all memory areas */
  SDRAM_Send_Cmd(0, FMC_SDRAM_CMD_PALL, 1, 0);             

  /* Step 4 ----------------------------------------------------------------*/
  /* set auto refresh times */
  SDRAM_Send_Cmd(0, FMC_SDRAM_CMD_AUTOREFRESH_MODE, 8, 0); // Set auto-refresh times

  /* Step 5 ----------------------------------------------------------------*/
  /* configure SDRAM register */
  // Configure the mode register, bit0~bit2 of SDRAM specify the burst access length,
  // bit3 specifies the burst access type, bit4~bit6 specify the CAS value, bit7 and bit8 specify the operation mode
  // bit9 specifies the write burst mode, bit10 and bit11 are reserved
  temp = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1 |      // Set burst length: 1 (can be 1/2/4/8)
         SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |         // Set burst type: sequential (can be sequential/interleaved)
         SDRAM_MODEREG_CAS_LATENCY_3 |                 // Set CAS value: 3 (can be 2/3)
         SDRAM_MODEREG_OPERATING_MODE_STANDARD |       // Set operation mode: 0, standard mode
         SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;         // Set write burst mode: 1, single point access
  SDRAM_Send_Cmd(0, FMC_SDRAM_CMD_LOAD_MODE, 1, temp); // Set the mode register of SDRAM

  /* Step 6 ----------------------------------------------------------------*/
  /* configure refresh rate */
  // Refresh rate counter (count in SDCLK frequency), calculation method:
  // COUNT = SDRAM refresh cycle / number of rows - 20 = SDRAM refresh cycle (us) * SDCLK frequency (MHz) / number of rows
  // The SDRAM refresh cycle we use is 64ms, SDCLK = 200/2 = 100MHz, the number of rows is 8192 (2^13).
  // So, COUNT = 64 * 1000 * 100 / 8192 - 20 = 761
  HAL_SDRAM_ProgramRefreshRate(&hsdram1, 761);
}

/**
 * @name SDRAM Send Command
 * @brief Send command to SDRAM
 * @param bankx: 0, send command to SDRAM on BANK5; 1, send command to SDRAM on BANK6
 * @param cmd: command (0, normal mode / 1, clock configuration enable / 2, precharge all memory areas / 3, auto-refresh / 4, load mode register / 5, self-refresh / 6, power-down)
 * @param refresh: auto-refresh times
 * @param regval: definition of mode register
 * @retval 0, normal; 1, fail.
 */
uint8_t SDRAM_Send_Cmd(uint8_t bankx, uint8_t cmd, uint8_t refresh, uint16_t regval)
{
  uint32_t target_bank = 0;
  FMC_SDRAM_CommandTypeDef Command;

  if (bankx == 0)
  {
    target_bank = FMC_SDRAM_CMD_TARGET_BANK1;
  }
  else if (bankx == 1)
  {
    target_bank = FMC_SDRAM_CMD_TARGET_BANK2;
  }
  Command.CommandMode = cmd;                                       // Command
  Command.CommandTarget = target_bank;                             // Target SDRAM memory area
  Command.AutoRefreshNumber = refresh;                             // Auto-refresh times
  Command.ModeRegisterDefinition = regval;                         // Value to write to mode register
  if (HAL_SDRAM_SendCommand(&hsdram1, &Command, 0XFFFF) == HAL_OK) // Send command to SDRAM
  {
    return 0;
  }
  else
    return 1;
}

/**
 * @name SDRAM_Test
 * @brief This function is used to test the SDRAM, write data to SDRAM, read data from SDRAM, and compare the data.
 * @param None
 * @retval 0, normal; others, fail.
 */
uint32_t SDRAM_Test(void)
{
  uint32_t i;
  uint32_t *pSRAM;
  uint8_t *pBytes;
  uint32_t err;
  const uint8_t ByteBuf[4] = {0x55, 0xA5, 0x5A, 0xAA};

  /* Write to SDRAM */
  pSRAM = (uint32_t *)EXT_SDRAM_ADDR;
  for (i = 0; i < EXT_SDRAM_SIZE / 4; i++)
  {
    *pSRAM++ = i;
  }

  /* Read from SDRAM */
  err = 0;
  pSRAM = (uint32_t *)EXT_SDRAM_ADDR;
  for (i = 0; i < EXT_SDRAM_SIZE / 4; i++)
  {
    if (*pSRAM++ != i)
    {
      err++;
    }
  }

  if (err > 0)
  {
    return (4 * err);
  }

  /* Invert data in SDRAM and write */
  pSRAM = (uint32_t *)EXT_SDRAM_ADDR;
  for (i = 0; i < EXT_SDRAM_SIZE / 4; i++)
  {
    *pSRAM = ~*pSRAM;
    pSRAM++;
  }

  /* Compare SDRAM data again */
  err = 0;
  pSRAM = (uint32_t *)EXT_SDRAM_ADDR;
  for (i = 0; i < EXT_SDRAM_SIZE / 4; i++)
  {
    if (*pSRAM++ != (~i))
    {
      err++;
    }
  }

  if (err > 0)
  {
    return (4 * err);
  }

  /* Test byte access to verify FSMC_NBL0, FSMC_NBL1 lines */
  pBytes = (uint8_t *)EXT_SDRAM_ADDR;
  for (i = 0; i < sizeof(ByteBuf); i++)
  {
    *pBytes++ = ByteBuf[i];
  }

  /* Compare SDRAM data */
  err = 0;
  pBytes = (uint8_t *)EXT_SDRAM_ADDR;
  for (i = 0; i < sizeof(ByteBuf); i++)
  {
    if (*pBytes++ != ByteBuf[i])
    {
      err++;
    }
  }
  if (err > 0)
  {
    return err;
  }
  return 0;
}
