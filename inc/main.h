/*
 ============================================================================
 Name        : main.h
 Author      : Mariusz Mikulski
 Date	     : 21 Feb 2023
 Version     : 1.0.0
 Copyright   : Your copyright notice (� 2021. All Rights Reserved.)
 Description : write description of file.
 ============================================================================
*/

#ifndef _MAIN_H_
#define _MAIN_H_

/*
+=============================================================================+
| includes
+=============================================================================+
*/

#include <stdint.h>

#define __STATIC_INLINE static inline

#include <cmsis_gcc.h>
#include <stm32f091xc.h>
#include <core_cm0.h>

#include "../startup/inc/SystemStartup.h"

/* modules */
#include "../module/module.h"

/* stm32 */
#include <STM32/gpio/inc/gpio.h>

/* utils */
#include <Utils/delay/inc/delay.h>


#include <string.h>

#include "../module/externalmemory/SD2/interface/FatFS/source/inc/ff.h"
#include "../module/externalmemory/SD2/interface/FatFS/source/inc/diskio.h"
#include "../module/externalmemory/SD2/inc/SDv2.h"

/*
+=============================================================================+
*/

#endif /* _MAIN_H_ */
