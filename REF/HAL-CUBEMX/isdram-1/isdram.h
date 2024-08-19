#ifndef __ISDRAM_H
#define	__ISDRAM_H

#include "stm32h7xx.h"
#include <stdio.h>

#define W9825G6KH_SIZE (32*1024*1024)  //32M Bytes W9825G6

/*SDRAM choose bank*/
#define FMC_BANK_SDRAM            FMC_Bank1_SDRAM  
#define FMC_COMMAND_TARGET_BANK   FMC_SDRAM_CMD_TARGET_BANK1

/**
  * @brief  FMC SDRAM data base address
  */   
#define SDRAM_BANK_ADDR     ((uint32_t)0xC0000000)

/**
 * @brief time out limit
 * 
 */
#define SDRAM_TIMEOUT                    ((uint32_t)0xFFFF)

/**
  * @brief  FMC SDRAM MODE CONFIG REGISTER RELATED DEFINES
  */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000) 
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)     

/*INFO OUTPUT*/
#define SDRAM_DEBUG_ON         1

#define SDRAM_INFO(fmt,arg...)           printf("<<-SDRAM-INFO->> "fmt"\n",##arg)
#define SDRAM_ERROR(fmt,arg...)          printf("<<-SDRAM-ERROR->> "fmt"\n",##arg)
#define SDRAM_DEBUG(fmt,arg...)          do{\
                                          if(SDRAM_DEBUG_ON)\
                                          printf("<<-SDRAM-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)


/** @defgroup STM32 SDRAM FUNCTION 
  * @{
  */ 
void SDRAM_InitSequence(void);
void  SDRAM_WriteBuffer(uint32_t* pBuffer, uint32_t uwWriteAddress, uint32_t uwBufferSize);
void  SDRAM_ReadBuffer(uint32_t* pBuffer, uint32_t uwReadAddress, uint32_t uwBufferSize);
uint8_t SDRAM_Test(void);



#endif /* __ISDRAM_H */
