# HOW TO USE THE DRIVERS

## NOTES
This repo assumes that you use **CUBEMX** to generate the project. So, the initialization parts are generally not included in the drivers, which are assumed to be done by CUBEMX. If you do not use CUBEMX, you need to initialize the peripherals yourself.
In short, **the drivers are written to be used with CUBEMX generated projects.** 

## GENERAL
- **copy the respective driver folder to your project**, better put the drivers in a folder called `drivers` or something else in your project root. In the example provided, the drivers are put in a folder called `BSP` in the project root, standing for board support package.
- **add the driver folder to your project structure.** For Keil, you need to do this in 'Manage Project Items' -> 'Project' -> 'Project Items'; for STM32CubeIDE, you do not need to do this, just copy the driver folder to your project root as mentioned above.
- **include the folder containing the drivers in your project include path.** For Keil, you need to do this in 'Options for Target' -> 'C/C++' -> 'Include Paths'; for STM32CubeIDE, similarly, you need to do this in 'Properties' -> 'C/C++ General' -> 'Paths and Symbols'.
- **include the driver header file in your source file.** For example, if you want to use the GPIO driver, include the header file `gpio.h` in your source file.
- **modify the details according to your project requirements.** For example, if you want to use the GPIO driver, modify the GPIO pin number, GPIO mode, etc. according to your project requirements.


## LED - `iled`
- add the `iled` folder to your project.
- add the `led.h` and `led.c` files to your project.
- include the folder path in your project include path.
- ensure the GPIO port and pin macros are included in `main.h` or you can put the in `led.h`.
- in the drivers, there are LED_X(), LED_X_Toggle(). `X` can be modified to LED number or label according to your project requirements. You can set the label for the GPIO pin in CUUBEMX, and CUUBEMX will generate the macros for you in `main.h`.

## KEY - `ikey`
- add the `ikey` folder to your project.
- add the `key.h` and `key.c` files to your project.
- include the folder path in your project include path.
- ensure the GPIO port and pin macros are included in `main.h` or you can put the in `key.h`.

## USART - `iusart`
- add the `iusart` folder to your project.
- add the `usart.h` and `usart.c` files to your project.
- include the folder path in your project include path.
- retarget of printf() and scanf() to USART, which can be placed in 'main.c'.
- （1）initialize the USART in main.c before, for example, `MCU_serial_init();`.
- （2）use `MCU_printf()` for formatted output, for example, `MCU_printf("There are %d days in a week",7);`.

## SDRAM - `isdram`
- add the `isdram` folder to your project.
- add the `sdram.h` and `sdram.c` files to your project.
- include the folder path in your project include path.
- (1) conduct initialization in `main.c`, for example, place `SDRAM_InitSequence();` at proper place.
- (2) use the SDRAM functions in your project, for example, put `SDRAM_Test();` at proper place for SDRAM test.

## MEMORY MANAGEMENT - `imemeory`
- add the `imemeory` folder to your project.
- add the `memory.h` and `memory.c` files to your project.
- include the folder path in your project include path.
- (1) conduct initialization in `main.c`, for example, place `memory_init();` at proper place.
- (2) use the `memory_alloc()` and `memory_free()` functions in your project.

## SDCARD - `isdcard`
- add the `isdcard` folder to your project.
- add the `sdcard.h` and `sdcard.c` files to your project.
- include the folder path in your project include path.
- (1) conduct initialization in `main.c`, for example, place `SD_Init();` at proper place.
- (2) use the SDCARD functions in your project, for example, put `SD_Test();` at proper place for SDCARD test.

Note:: Do not use isdcard together with ifile, as ifile is based on FATFS, which has it own implementation for SD card communication.

## FILE - `ifile`
- add the `ifile` folder to your project.
- add the `file.h` and `file.c` files to your project.
- include the folder path in your project include path.
- call functions from `file.c` in your project at proper places.