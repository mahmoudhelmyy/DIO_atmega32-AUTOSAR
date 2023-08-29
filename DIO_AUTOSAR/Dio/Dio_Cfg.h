 /*======================================================================================================
 * Module: DIO																							*															*
 * File Name: Dio_Cfg.h																					*																*
 * Description: Pre-Compile Configuration Header file for AVR ATmega32 Microcontroller- Dio Driver		*
 * Author: Mahmoud-Helmy																				*
 *======================================================================================================*/
/* =====================================================================================================
 * 											 FILE GUARD
 * =====================================================================================================*/
#ifndef DIO_CFG_H
#define DIO_CFG_H
/* =====================================================================================================
 * 										VERSION DEFINITION
 * =====================================================================================================*/
/*
 * Module Version 1.0.0
 */
#define DIO_CFG_SW_MAJOR_VERSION              (1U)
#define DIO_CFG_SW_MINOR_VERSION              (0U)
#define DIO_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define DIO_CFG_AR_RELEASE_PATCH_VERSION     (3U)
/* =====================================================================================================
 * 											INCLUDES
 * =====================================================================================================*/
/* Standard AUTOSAR types */
#include "../LIB/Std_Types.h"
/* =====================================================================================================
 * 								          VERSION CHECK
 * =====================================================================================================*/
/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != DIO_CFG_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != DIO_CFG_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != DIO_CFG_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif
/* =====================================================================================================
 * 								    Configuration Parameters
 * =====================================================================================================*/
/* Pre-compile option for Development Error Detect */
#define DIO_DEV_ERROR_DETECT                (STD_OFF)

/* Pre-compile option for Version Info API */
#define DIO_VERSION_INFO_API                (STD_ON)


#define INPUT                              (uint8)0x00
#define OUTPUT                             (uint8)0x01
#define PIN_INPUT                          (uint8)0x00
#define PIN_OUTPUT                         (uint8)0x01


/* Number of the configured Dio Channels */
#define DIO_CONFIGURED_PORTS       	        (4U)  /*A, B, C, D*/
#define DIO_TOTAL_CHANNLES        	        (32U)
#define DIO_CONFIGURED_CHANNLES             (32U) /* 4 PORTS * 8 PINS = 32 Channels*/
#define NUM_OF_PINS_IN_SINGLE_PORT			(8U)


#define PORTA_ID                          (uint8)0x01
#define PORTB_ID                          (uint8)0x02
#define PORTC_ID                          (uint8)0x03
#define PORTD_ID                          (uint8)0x04

/* Port Input Pins (generic) */
#define    PIN0         0
#define    PIN1         1
#define    PIN2         2
#define    PIN3         3
#define    PIN4         4
#define    PIN5         5
#define    PIN6         6
#define    PIN7         7

/* Port Input Pins (generic) */
#define    PIN0_ID         0
#define    PIN1_ID         1
#define    PIN2_ID         2
#define    PIN3_ID         3
#define    PIN4_ID         4
#define    PIN5_ID         5
#define    PIN6_ID         6
#define    PIN7_ID         7

/* Port Input Pins (generic) */
#define    PIN_A_0         0  // 0
#define    PIN_A_1         1  // 1
#define    PIN_A_2         2  // 2
#define    PIN_A_3         3  // 3
#define    PIN_A_4         4  // 4
#define    PIN_A_5         5  // 5
#define    PIN_A_6         6  // 6
#define    PIN_A_7         7  // 7
#define    PIN_B_0         8  // 0
#define    PIN_B_1         9  // 1
#define    PIN_B_2         10 // 2
#define    PIN_B_3         11 // 3
#define    PIN_B_4         12 // 4
#define    PIN_B_5         13 // 5
#define    PIN_B_6         14 // 6
#define    PIN_B_7         15 // 7
#define    PIN_C_0         16 // 0
#define    PIN_C_1         17 // 1
#define    PIN_C_2         18 // 2
#define    PIN_C_3         19 // 3
#define    PIN_C_4         20 // 4
#define    PIN_C_5         21 // 5
#define    PIN_C_6         22 // 6
#define    PIN_C_7         23 // 7
#define    PIN_D_0         24 // 0
#define    PIN_D_1         25 // 1
#define    PIN_D_2         26 // 2
#define    PIN_D_3         27 // 3
#define    PIN_D_4         28 // 4
#define    PIN_D_5         29 // 5
#define    PIN_D_6         30 // 6
#define    PIN_D_7         31 // 7

#endif /* DIO_CFG_H */
