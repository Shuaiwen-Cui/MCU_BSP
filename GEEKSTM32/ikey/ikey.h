/**
 * @file ikey.h
 * @author SHUAIWEN CUI (shuaiwencui at gmail dot com)
 * @brief 
 * @version 1.0
 * @date 2024-07-14
 * ! Note: in this version, the key status reading is in blocking mode, which means the responsiveness is not good. Better to use interrupt mode.
 */
#ifndef IKEY_H_
#define IKEY_H_

#include "stm32h7xx_hal.h" // HAL library file declaration, replace it with the corresponding file according to the actual situation
#include "main.h" // IO definition and initialization function are in the main.c file, must be referenced

#define KEY_MODE 1 // 0: polling mode, 1: interrupt mode

#if KEY_MODE == 0
/**
 * @name KEY0
 * @brief Read the level of the key interface
 * @param None
 * @retval 1: key pressed, 0: key not pressed
 */
uint8_t KEY0(void);

/**
 * @name KEY1
 * @brief Read the level of the key interface
 * @param None
 * @retval 1: key pressed, 0: key not pressed
 */
uint8_t KEY1(void);

#else

//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin); // actually no need to state

#endif

#endif /* IKEY_H_ */