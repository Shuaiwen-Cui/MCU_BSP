/*
 * iled.h
 *
 *  Created on: June 07, 2024
 *      Author: SHUAIWEN CUI
 */

#ifndef ILED_H_
#define ILED_H_

#include "stm32h7xx_hal.h" // HAL library file declaration, replace it with the corresponding file according to the actual situation
#include "main.h" // IO definition and initialization function are in the main.c file, must be referenced

void LED_R(uint8_t state);// LED_R independent control function (0 is off, other values are on)
void LED_R_Toggle(void);// LED_R Toggle
void LED_G(uint8_t state);// LED_G independent control function (0 is off, other values are on)
void LED_G_Toggle(void);// LED_G Toggle
#endif /* ILED_H_ */
