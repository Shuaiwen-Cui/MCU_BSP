/**
 * @file bsp_init.c
 * @author SHUAIWEN CUI (SHUAIWEN001 AT e DOT ntu DOT edu DOT sg)
 * @brief
 * @version 1.0
 * @date 2024-07-12
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "bsp_init.h"

/**
 * @name BSP_Init
 * @brief board support package initialization
 * @param None
 * @retval 0
 * 
 */
int BSP_Init(void)
{
    // Variables
    int i;
#ifdef MODULE_ENABLE_LED
    // BSP Initialization - LED - flash once to indicate OK
    LED(1);
    HAL_Delay(200);
    LED(0);
    HAL_Delay(200);
    LED(1);
#endif

#ifdef MODULE_ENABLE_KEY
    // BSP Initialization - Key
    // nothing required
#endif

#ifdef MODULE_ENABLE_USART1
    // Initialization - Count Down
    for (i = 0; i < 5; i++)
    {
        printf("[INITIALIZATION] Count Down: %d \n\r", 5 - i);
        HAL_Delay(1000);
    }

    // BSP Initialization - Serial Communication
    MCU_serial_init();
    MCU_printf("[INITIALIZATION] Serial Communication - SUCCESS\n\r");
    HAL_Delay(1000);
#endif

#ifdef MODULE_ENABLE_SDRAM
    // BSP Initialization - SDRAM
    printf("[INITIALIZATION] SDRAM Initialization - START\n\r");
    // SDRAM_InitSequence();
    // SDRAM_Init();
    // SDRAM_Test();
    W8925_Init();
    HAL_Delay(1000);
    printf("[INITIALIZATION] SDRAM Initialization - FINISHED\n\r");
    HAL_Delay(1000);
#endif

#ifdef MODULE_ENABLE_MEMORY
    // BSP Initialization - Memory Management
    printf("[INITIALIZATION] Memory Management Initialization - START\n\r");
    memory_init();
    printf("[INITIALIZATION] Memory Management Initialization - FINISHED\n\r");
    HAL_Delay(1000);
    printf("[INITIALIZATION] Memory Management Test - START\n\r");
    memory_management_test();
    printf("[INITIALIZATION] Memory Management Test - FINISHED\n\r");
    HAL_Delay(1000);
#endif

    return BSP_INIT_SUCCESS;
}

#ifdef MODULE_ENABLE_USART1
// MicroLib needed for retargetting
// retarget fputc for printf
int fputc(int ch, FILE *f)
{
    uint8_t temp = (uint8_t)ch;
    HAL_UART_Transmit(&huart1, &temp, 1, HAL_MAX_DELAY);
    return ch;
}

// retarget fgetc for scanf
int fgetc(FILE *f)
{
    while (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) == RESET)
        ;                                      // Wait until the data is received
    return (int)(huart1.Instance->RDR & 0xFF); // Read the received data
}
#endif