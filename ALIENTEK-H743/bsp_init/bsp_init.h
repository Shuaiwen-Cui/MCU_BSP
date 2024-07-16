/**
 * @file bsp_init.h
 * @author SHUAIWEN CUI (SHUAIWEN001 AT e DOT ntu DOT edu DOT sg)
 * @brief This file contains the headers of the BSP initialization functions.
 * @version 1.0
 * @date 2024-07-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef BSP_INIT_H
#define BSP_INIT_H

#define BSP_INIT_SUCCESS 0
#define BSP_INIT_FAIL 1

#define BSP_INIT_TEST 1 // test required for the BSP initialization

/**
 * @name Modules To Be Enabled
 * @brief This section is to determine the modules to be included in the project
 * ! This is where you configure the modules to be included in the project
 */

#define MODULE_ENABLE_LED    // Enable LED module
#define MODULE_ENABLE_KEY    // Enable Key module
#define MODULE_ENABLE_USART1 // Enable USART1 module
#define MODULE_ENABLE_SDRAM  // Enable SDRAM module
#define MODULE_ENABLE_MEMORY // Enable Memory module - for memory management on SDRAM

/**
 * @name Include Files
 * 
 */

#ifdef MODULE_ENABLE_LED

#include "iled.h"

#endif

#ifdef MODULE_ENABLE_KEY

#include "ikey.h"

#endif


#ifdef MODULE_ENABLE_USART1 //! Note - Do rember to check the MicroLib option in the project settings

#include <stdio.h>
#include "iusart.h"

#endif


#ifdef MODULE_ENABLE_SDRAM

#include "isdram.h"

#endif


#ifdef MODULE_ENABLE_MEMORY

#include "imemory.h"

#endif


/**
 * @name Function Prototypes
 * 
 */

// The BSP initialization function - including all the initialization functions
int BSP_Init();

#ifdef MODULE_ENABLE_USART1
// IO retargetting
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
#endif

#endif /* BSP_INIT_H */