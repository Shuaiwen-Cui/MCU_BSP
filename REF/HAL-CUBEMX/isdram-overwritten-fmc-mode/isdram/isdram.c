/**
 * @file isdram.c
 * @author SHUAIWEN CUI (SHUAIWEN001@e.ntu.edu.sg)
 * @brief sdram related functions
 * @version 1.0
 * @date 2024-06-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
  
//#include "isdram.h"
//#include "fmc.h"

//static FMC_SDRAM_CommandTypeDef Command;
//#define sdramHandle hsdram2

///**
//  * @brief  delay a while
//  * @param  how long for delay
//  * @retval None
//  */
//static void SDRAM_delay(__IO uint32_t nCount)
//{
//  __IO uint32_t index = 0; 
//  for(index = (100000 * nCount); index != 0; index--)
//  {
//  }
//}

///**
//  * @brief  initialize SDRAM 6 steps
//  * @param  None. 
//  * @retval None.
//  * ! This is the core for SDRAM initialization. CubeMX will do FMC initialization, then we need this function to do SDRAM initialization. After that, we can use SDRAM in the application layer.
//  */
//void SDRAM_InitSequence(void)
//{
//	uint32_t temp = 0;

//	/* Step 1 ----------------------------------------------------------------*/
//	/* CONFIGURE COMMAND: enable the clock for sdram */
//	Command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
//	Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
//	Command.AutoRefreshNumber = 1;
//	Command.ModeRegisterDefinition = 0;
//	/* send command */
//	HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

//	/* delay for a while at least 200us */
//	SDRAM_delay(2);

//	/* Step 3 ----------------------------------------------------------------*/
//	/* CONFIGURE COMMAND: precharge all bank */
//	Command.CommandMode = FMC_SDRAM_CMD_PALL;
//	Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
//	Command.AutoRefreshNumber = 1;
//	Command.ModeRegisterDefinition = 0;
//	/* send command */
//	HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);   

//	/* Step 4 ----------------------------------------------------------------*/
//	/* CONFIGURE COMMAND: auto refresh */   
//	Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
//	Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
//	Command.AutoRefreshNumber = 4;
//	Command.ModeRegisterDefinition = 0;
//	/* send command */
//	HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

//	/* Step 5 ----------------------------------------------------------------*/
//	/* CONFIGURE SDRAM LOAD MODE register */
//	temp = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
//				   SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
//				   SDRAM_MODEREG_CAS_LATENCY_3           |
//				   SDRAM_MODEREG_OPERATING_MODE_STANDARD |
//				   SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

//	/* CONFIGURE COMMAND: set SDRAM register */
//	Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
//	Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
//	Command.AutoRefreshNumber = 1;
//	Command.ModeRegisterDefinition = temp;
//	/* send command */
//	HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

//	/* Step 6 ----------------------------------------------------------------*/
//	/* CONFIGURE REFRESH COUNTER */
//  /*
//    (SDRAM refresh period / Number of rows）*SDRAM时钟速度 – 20
//    = 64000(64 ms) / 8192*120MHz - 20
//    = 917.2 取值918

//    note: 64 / 8192 = 7.81us
//  */
//	/* CONFIGURE REFRESH RATE */
//	HAL_SDRAM_ProgramRefreshRate(&sdramHandle, 918); 
//}

///**
//  * @brief  write data to SDRAM in "word" format
//  * @param  pBuffer:  pointer to data
//  * @param  uwWriteAddress: address to write in SDRAM
//  * @param  uwBufferSize: size of data to write
//  * @retval None.
//  */
//void SDRAM_WriteBuffer(uint32_t* pBuffer, uint32_t uwWriteAddress, uint32_t uwBufferSize)
//{
//  __IO uint32_t write_pointer = (uint32_t)uwWriteAddress;

//  /* Disable write protection */
//  HAL_SDRAM_WriteProtection_Disable(&sdramHandle);
//  /* Check the SDRAM state */
//  while(HAL_SDRAM_GetState(&sdramHandle) != RESET)
//  {
//  }

//  /* write data to SDRAM by loops*/
//  for (; uwBufferSize != 0; uwBufferSize--) 
//  {
//    /* write data to SDRAM */
//    *(uint32_t *) (SDRAM_BANK_ADDR + write_pointer) = *pBuffer++;

//    /* address increment */
//    write_pointer += 4;
//  }
//    
//}

///**
//  * @brief  read data from SDRAM
//  * @param  pBuffer: pointer to data
//  * @param  ReadAddress: address to read in SDRAM
//  * @param  uwBufferSize: size of data to read
//  * @retval None.
//  */
//void SDRAM_ReadBuffer(uint32_t* pBuffer, uint32_t uwReadAddress, uint32_t uwBufferSize)
//{
//  __IO uint32_t write_pointer = (uint32_t)uwReadAddress;
//  
//   
//  /* Check the SDRAM state */
//  while ( HAL_SDRAM_GetState(&sdramHandle) != RESET)
//  {
//  }
//  
//  /* read data from SDRAM */
//  for(; uwBufferSize != 0x00; uwBufferSize--)
//  {
//   *pBuffer++ = *(__IO uint32_t *)(SDRAM_BANK_ADDR + write_pointer );
//    
//   /* address increment */
//    write_pointer += 4;
//  } 
//}


///**
//  * @brief  Test SDRAM
//  * @param  None
//  * @retval normal as 1, abnormal as 0
//  */
//uint8_t SDRAM_Test(void)
//{
//  /*写入数据计数器*/ /* counter for write data */
//  uint32_t counter=0;
//  
//  /* 8 bit data */
//  uint8_t ubWritedata_8b = 0, ubReaddata_8b = 0;  
//  
//  /* 16 bit data */
//  uint16_t uhWritedata_16b = 0, uhReaddata_16b = 0; 

//  /* 32 bit data */
//  uint32_t uwWritedata_32b = 0, uwReaddata_32b = 0;
//  
//  SDRAM_INFO("TESTING SDRAM..., WRITE AND READ AS 8/16/32 BIT...");


//  /* 8 bit data read and write*/
//  
//  /* reset SDRAM data to 0, W9825G6KH_SIZE is in 8 bit */
//  for (counter = 0x00; counter < W9825G6KH_SIZE; counter++)
//  {
//    *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)0x0;
//  }
//  
//  /* write data to SDRAM */
//  for (counter = 0; counter < W9825G6KH_SIZE; counter++)
//  {
//    *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)(ubWritedata_8b + counter);
//  }
//  
//  /* read data from SDRAM and check */
//  for(counter = 0; counter<W9825G6KH_SIZE;counter++ )
//  {
//    ubReaddata_8b = *(__IO uint8_t*)(SDRAM_BANK_ADDR + counter);  // read data from SDRAM
//    
//    if(ubReaddata_8b != (uint8_t)(ubWritedata_8b + counter))      // check data, if not equal, return 0
//    {
//      SDRAM_ERROR("8 BIT DATA READ AND WRITE ERROR!");
//      return 0;
//    }
//  }
//	
//  
//  /* 16 bit data read and write*/
//  
//  /* reset SDRAM data to 0 */
//  for (counter = 0x00; counter < W9825G6KH_SIZE/2; counter++)
//  {
//    *(__IO uint16_t*) (SDRAM_BANK_ADDR + 2*counter) = (uint16_t)0x00;
//  }
//  
//  /* write data to SDRAM */
//  for (counter = 0; counter < W9825G6KH_SIZE/2; counter++)
//  {
//    *(__IO uint16_t*) (SDRAM_BANK_ADDR + 2*counter) = (uint16_t)(uhWritedata_16b + counter);
//  }
//  
//  /* read data from SDRAM and check */
//  for(counter = 0; counter<W9825G6KH_SIZE/2;counter++ )
//  {
//    uhReaddata_16b = *(__IO uint16_t*)(SDRAM_BANK_ADDR + 2*counter);  // read data from SDRAM
//    
//    if(uhReaddata_16b != (uint16_t)(uhWritedata_16b + counter))      // check data, if not equal, return 0
//    {
//      SDRAM_ERROR("16 BIT DATA READ AND WRITE ERROR!");

//      return 0;
//    }
//  }

//  /* 32 bit data read and write*/
//  /* reset SDRAM data to 0 */
//  for (counter = 0x00; counter < W9825G6KH_SIZE/4; counter++)
//  {
//    *(__IO uint32_t*) (SDRAM_BANK_ADDR + 4*counter) = (uint32_t)0x00;
//  }

//  /* write data to SDRAM */
//  for (counter = 0; counter < W9825G6KH_SIZE/4; counter++)
//  {
//    *(__IO uint32_t*) (SDRAM_BANK_ADDR + 4*counter) = (uint32_t)(uwWritedata_32b + counter);
//  }
//  
//  /* read data from SDRAM and check */
//  for(counter = 0; counter<W9825G6KH_SIZE/4;counter++ )
//  {
//    uwReaddata_32b = *(__IO uint32_t*)(SDRAM_BANK_ADDR + 4*counter);  // read data from SDRAM
//    
//    if(uwReaddata_32b != (uint32_t)(uwWritedata_32b + counter))      // check data, if not equal, return 0
//    {
//      SDRAM_ERROR("32 BIT DATA READ AND WRITE ERROR!");
//      return 0;
//    }
//  }
//  
//  SDRAM_INFO("SDRAM READ AND WRITE TEST OK!"); 
//  /* normal, return 1 */
//  return 1;
//  

//}


///*********************************************END OF FILE**********************/

#include "isdram.h"  
static FMC_SDRAM_CommandTypeDef Command;
extern SDRAM_HandleTypeDef hsdram2;
#define sdramHandle hsdram2


/**
  * @brief  initialize SDRAM 6 steps
  * @param  None. 
  * @retval None.
  * ! This is the core for SDRAM initialization. CubeMX will do FMC initialization, then we need this function to do SDRAM initialization. After that, we can use SDRAM in the application layer.
  */
void SDRAM_InitSequence(void)
{
	uint32_t temp = 0;

	/* Step 1 ----------------------------------------------------------------*/
	/* CONFIGURE COMMAND: enable the clock for sdram */
	Command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
	Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
	Command.AutoRefreshNumber = 1;
	Command.ModeRegisterDefinition = 0;
	/* send command */
	HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

	/* delay for a while at least 200us */
	HAL_Delay(1);

	/* Step 3 ----------------------------------------------------------------*/
	/* CONFIGURE COMMAND: precharge all bank */
	Command.CommandMode = FMC_SDRAM_CMD_PALL;
	Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
	Command.AutoRefreshNumber = 1;
	Command.ModeRegisterDefinition = 0;
	/* send command */
	HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);   

	/* Step 4 ----------------------------------------------------------------*/
	/* CONFIGURE COMMAND: auto refresh */   
	Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
	Command.AutoRefreshNumber = 4;
	Command.ModeRegisterDefinition = 0;
	/* send command */
	HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

	/* Step 5 ----------------------------------------------------------------*/
	/* CONFIGURE SDRAM LOAD MODE register */
	temp = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
				   SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
				   SDRAM_MODEREG_CAS_LATENCY_3           |
				   SDRAM_MODEREG_OPERATING_MODE_STANDARD |
				   SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

	/* CONFIGURE COMMAND: set SDRAM register */
	Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
	Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
	Command.AutoRefreshNumber = 1;
	Command.ModeRegisterDefinition = temp;
	/* send command */
	HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

	/* Step 6 ----------------------------------------------------------------*/
	/* CONFIGURE REFRESH COUNTER */
  /*
    (SDRAM refresh period / Number of rows）*SDRAM时钟速度 – 20
    = 64000(64 ms) / 8192*120MHz - 20
    = 917.2 取值918

    note: 64 / 8192 = 7.81us
  */
	/* CONFIGURE REFRESH RATE */
	HAL_SDRAM_ProgramRefreshRate(&sdramHandle, 918); 
}


/**
  * @brief  Initialize RAM. Note that HAL_SDRAM_Init is actually conducted in MX_FMC_Init() but somehow not working, so we do that again here, the parameters are consistent with the ones in MX_FMC_Init().
  * @param  None
  * @retval None
  */
void SDRAM_Init(void)
{

  FMC_SDRAM_TimingTypeDef SdramTiming;

  /*sdram init*/
  hsdram2.Instance = FMC_SDRAM_DEVICE;
  /* hsdram2 struct init*/
  hsdram2.Init.SDBank = FMC_SDRAM_BANK2;
  hsdram2.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9;       // SDRAM column number
  hsdram2.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;            // SDRAM row number
  hsdram2.Init.MemoryDataWidth = SDRAM_MEMORY_WIDTH;                 // bus data width
  hsdram2.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;    // 4 banks
  hsdram2.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;                 // CAS
  hsdram2.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE; // disable write protection
  hsdram2.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;             // SDRAM clock 120 MHz
  hsdram2.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;                  // enable burst read
  hsdram2.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1;              // read pipe delay

  /* SDRAM timing */
  SdramTiming.LoadToActiveDelay = 2;       
  SdramTiming.ExitSelfRefreshDelay = 9;    
  SdramTiming.SelfRefreshTime = 6;         
  SdramTiming.RowCycleDelay = 8;           
  SdramTiming.WriteRecoveryTime = 4;       
  SdramTiming.RPDelay = 2;                 
  SdramTiming.RCDDelay = 2;                

  HAL_SDRAM_Init(&hsdram2, &SdramTiming);  // necessary
  /* FMC SDRAM init command */
  SDRAM_InitSequence(); 
  
}



/**
  * @brief  write data to SDRAM in "word" format
  * @param  pBuffer:  pointer to data
  * @param  uwWriteAddress: address to write in SDRAM
  * @param  uwBufferSize: size of data to write
  * @retval None.
  */
void SDRAM_WriteBuffer(uint32_t* pBuffer, uint32_t uwWriteAddress, uint32_t uwBufferSize)
{
  __IO uint32_t write_pointer = (uint32_t)uwWriteAddress;

  /* Disable write protection */
  HAL_SDRAM_WriteProtection_Disable(&sdramHandle);
  /* Check the SDRAM state */
  while(HAL_SDRAM_GetState(&sdramHandle) != RESET)
  {
  }

  /* write data to SDRAM by loops*/
  for (; uwBufferSize != 0; uwBufferSize--) 
  {
    /* write data to SDRAM */
    *(uint32_t *) (SDRAM_BANK_ADDR + write_pointer) = *pBuffer++;

    /* address increment */
    write_pointer += 4;
  }
    
}

/**
  * @brief  read data from SDRAM
  * @param  pBuffer: pointer to data
  * @param  ReadAddress: address to read in SDRAM
  * @param  uwBufferSize: size of data to read
  * @retval None.
  */
void SDRAM_ReadBuffer(uint32_t* pBuffer, uint32_t uwReadAddress, uint32_t uwBufferSize)
{
  __IO uint32_t write_pointer = (uint32_t)uwReadAddress;
  
   
  /* Check the SDRAM state */
  while ( HAL_SDRAM_GetState(&sdramHandle) != RESET)
  {
  }
  
  /* read data from SDRAM */
  for(; uwBufferSize != 0x00; uwBufferSize--)
  {
   *pBuffer++ = *(__IO uint32_t *)(SDRAM_BANK_ADDR + write_pointer );
    
   /* address increment */
    write_pointer += 4;
  } 
}


/**
  * @brief  Test SDRAM
  * @param  None
  * @retval normal as 1, abnormal as 0
  */
uint8_t SDRAM_Test(void)
{
  /*写入数据计数器*/ /* counter for write data */
  uint32_t counter=0;
  
  /* 8 bit data */
  uint8_t ubWritedata_8b = 0, ubReaddata_8b = 0;  
  
  /* 16 bit data */
  uint16_t uhWritedata_16b = 0, uhReaddata_16b = 0; 

  /* 32 bit data */
  uint32_t uwWritedata_32b = 0, uwReaddata_32b = 0;
  
  SDRAM_INFO("TESTING SDRAM..., WRITE AND READ AS 8/16/32 BIT...");


  /* 8 bit data read and write*/
  
  /* reset SDRAM data to 0, W9825G6KH_SIZE is in 8 bit */
  for (counter = 0x00; counter < W9825G6KH_SIZE; counter++)
  {
    *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)0x0;
  }
  
  /* write data to SDRAM */
  for (counter = 0; counter < W9825G6KH_SIZE; counter++)
  {
    *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)(ubWritedata_8b + counter);
  }
  
  /* read data from SDRAM and check */
  for(counter = 0; counter<W9825G6KH_SIZE;counter++ )
  {
    ubReaddata_8b = *(__IO uint8_t*)(SDRAM_BANK_ADDR + counter);  // read data from SDRAM
    
    if(ubReaddata_8b != (uint8_t)(ubWritedata_8b + counter))      // check data, if not equal, return 0
    {
      SDRAM_ERROR("8 BIT DATA READ AND WRITE ERROR!");
      return 0;
    }
  }
	
  
  /* 16 bit data read and write*/
  
  /* reset SDRAM data to 0 */
  for (counter = 0x00; counter < W9825G6KH_SIZE/2; counter++)
  {
    *(__IO uint16_t*) (SDRAM_BANK_ADDR + 2*counter) = (uint16_t)0x00;
  }
  
  /* write data to SDRAM */
  for (counter = 0; counter < W9825G6KH_SIZE/2; counter++)
  {
    *(__IO uint16_t*) (SDRAM_BANK_ADDR + 2*counter) = (uint16_t)(uhWritedata_16b + counter);
  }
  
  /* read data from SDRAM and check */
  for(counter = 0; counter<W9825G6KH_SIZE/2;counter++ )
  {
    uhReaddata_16b = *(__IO uint16_t*)(SDRAM_BANK_ADDR + 2*counter);  // read data from SDRAM
    
    if(uhReaddata_16b != (uint16_t)(uhWritedata_16b + counter))      // check data, if not equal, return 0
    {
      SDRAM_ERROR("16 BIT DATA READ AND WRITE ERROR!");

      return 0;
    }
  }

  /* 32 bit data read and write*/
  /* reset SDRAM data to 0 */
  for (counter = 0x00; counter < W9825G6KH_SIZE/4; counter++)
  {
    *(__IO uint32_t*) (SDRAM_BANK_ADDR + 4*counter) = (uint32_t)0x00;
  }

  /* write data to SDRAM */
  for (counter = 0; counter < W9825G6KH_SIZE/4; counter++)
  {
    *(__IO uint32_t*) (SDRAM_BANK_ADDR + 4*counter) = (uint32_t)(uwWritedata_32b + counter);
  }
  
  /* read data from SDRAM and check */
  for(counter = 0; counter<W9825G6KH_SIZE/4;counter++ )
  {
    uwReaddata_32b = *(__IO uint32_t*)(SDRAM_BANK_ADDR + 4*counter);  // read data from SDRAM
    
    if(uwReaddata_32b != (uint32_t)(uwWritedata_32b + counter))      // check data, if not equal, return 0
    {
      SDRAM_ERROR("32 BIT DATA READ AND WRITE ERROR!");
      return 0;
    }
  }
  
  SDRAM_INFO("SDRAM READ AND WRITE TEST OK!"); 
  /* normal, return 1 */
  return 1;
  

}


/*********************************************END OF FILE**********************/
