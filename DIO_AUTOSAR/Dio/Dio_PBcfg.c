 /*======================================================================================================
 * Module: DIO																							*															*
 * File Name: Dio_PBcfg.c																				*																*
 * Description: Post Build Configuration Source file for AVR ATmega32 Microcontroller - DIO Driver		*
 * Author: Mahmoud-Helmy																				*
 *======================================================================================================*/
/* =====================================================================================================
 * 											   INCLUDES
 * =====================================================================================================*/
#include "Dio.h"
#include "MemMap.h"
#include "../LIB/Std_Types.h"
/* =====================================================================================================
 * 										VERSION DEFINITION
 * =====================================================================================================*/
/*
 * Module Version 1.0.0
 */
#define DIO_PBCFG_SW_MAJOR_VERSION              (1U)
#define DIO_PBCFG_SW_MINOR_VERSION              (0U)
#define DIO_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define DIO_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)
/* =====================================================================================================
 * 										VERSION CHECK
 * =====================================================================================================*/
/* AUTOSAR Version checking between Dio_PBcfg.c and Dio.h files */
#if ((DIO_PBCFG_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((DIO_PBCFG_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION)\
 ||  (DIO_PBCFG_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION)\
 ||  (DIO_PBCFG_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif





/* PB structure used with Dio_Init API */
const Dio_ConfigChannel Dio_Configuration[] = {
	  /* Port_Num,  pin_Num,  Direction,      Level*/
        {PORTA_ID, 	PIN_A_0, 	 OUTPUT,	 STD_HIGH}, /*PORTA*/   // 0    // 0
        {PORTA_ID, 	PIN_A_1, 	 OUTPUT,	 STD_HIGH},             // 1    // 1
        {PORTA_ID, 	PIN_A_2, 	 OUTPUT,	 STD_HIGH},             // 2    // 2
        {PORTA_ID, 	PIN_A_3, 	 OUTPUT,	 STD_HIGH},             // 3    // 3
        {PORTA_ID, 	PIN_A_4, 	 OUTPUT,	 STD_HIGH},             // 4    // 4
        {PORTA_ID, 	PIN_A_5, 	 OUTPUT,	 STD_HIGH},             // 5    // 5
        {PORTA_ID, 	PIN_A_6, 	 OUTPUT,	 STD_HIGH},             // 6    // 6
        {PORTA_ID, 	PIN_A_7, 	 OUTPUT,	 STD_HIGH},             // 7    // 7

        {PORTB_ID, 	PIN_B_0, 	 OUTPUT,	 STD_HIGH}, /*PORTB*/   // 8    // 0
        {PORTB_ID, 	PIN_B_1, 	 OUTPUT,	 STD_HIGH},             // 9    // 1
        {PORTB_ID, 	PIN_B_2, 	 OUTPUT,	 STD_HIGH},             // 10   // 2
        {PORTB_ID, 	PIN_B_3, 	 OUTPUT,	 STD_HIGH},             // 11   // 3
        {PORTB_ID, 	PIN_B_4, 	 OUTPUT,	 STD_HIGH},             // 12   // 4
        {PORTB_ID, 	PIN_B_5, 	 OUTPUT,	 STD_HIGH},             // 13   // 5
        {PORTB_ID, 	PIN_B_6, 	 OUTPUT,	 STD_HIGH},             // 14   // 6
        {PORTB_ID, 	PIN_B_7, 	 OUTPUT,	 STD_HIGH},             // 15   // 7

        {PORTC_ID, 	PIN_C_0, 	 OUTPUT,	 STD_HIGH}, /*PORTC*/   // 16   // 0
        {PORTC_ID, 	PIN_C_1, 	 OUTPUT,	 STD_HIGH},             // 17   // 1
        {PORTC_ID, 	PIN_C_2, 	 OUTPUT,	 STD_HIGH},             // 18   // 2
        {PORTC_ID, 	PIN_C_3, 	 OUTPUT,	 STD_HIGH},             // 19   // 3
        {PORTC_ID, 	PIN_C_4, 	 OUTPUT,	 STD_HIGH},             // 20   // 4
        {PORTC_ID, 	PIN_C_5, 	 OUTPUT,	 STD_HIGH},             // 21   // 5
        {PORTC_ID, 	PIN_C_6, 	 OUTPUT,	 STD_HIGH},             // 22   // 6
        {PORTC_ID, 	PIN_C_7, 	 OUTPUT,	 STD_HIGH},             // 23   // 7

        {PORTD_ID, 	PIN_D_0, 	 OUTPUT,	 STD_HIGH}, /*PORTD*/   // 24   // 0
        {PORTD_ID, 	PIN_D_1, 	 OUTPUT,	 STD_HIGH},             // 25   // 1
        {PORTD_ID, 	PIN_D_2, 	 OUTPUT,	 STD_HIGH},				// 26   // 2
        {PORTD_ID, 	PIN_D_3, 	 OUTPUT,	 STD_HIGH},             // 27   // 3
        {PORTD_ID, 	PIN_D_4, 	 OUTPUT,	 STD_HIGH},             // 28   // 4
        {PORTD_ID, 	PIN_D_5, 	 OUTPUT,	 STD_HIGH},             // 29   // 5
        {PORTD_ID, 	PIN_D_6, 	 OUTPUT,	 STD_HIGH},             // 30   // 6
        {PORTD_ID, 	PIN_D_7, 	 OUTPUT,	 STD_HIGH}              // 31   // 7
	 };

const Dio_ConfigType Dio_ConfigurationSet = {{
NULL_PTR,       		         /* PORTA  PIN_A_0 */	/* &Dio_Configuration[PIN_A_0] */
NULL_PTR,       		         /* PORTA  PIN_A_1 */	/* &Dio_Configuration[PIN_A_1] */
NULL_PTR,       		         /* PORTA  PIN_A_2 */	/* &Dio_Configuration[PIN_A_2] */
NULL_PTR,       		         /* PORTA  PIN_A_3 */	/* &Dio_Configuration[PIN_A_3] */
NULL_PTR,    /* PORTA  PIN_A_4 */	/* &Dio_Configuration[PIN_A_4] */
NULL_PTR,       		         /* PORTA  PIN_A_5 */	/* &Dio_Configuration[PIN_A_5] */
NULL_PTR,       		         /* PORTA  PIN_A_6 */	/* &Dio_Configuration[PIN_A_6] */
NULL_PTR,       		         /* PORTA  PIN_A_7 */	/* &Dio_Configuration[PIN_A_7] */
NULL_PTR,       		         /* PORTB  PIN_B_0 */	/* &Dio_Configuration[PIN_B_0] */
NULL_PTR,       		         /* PORTB  PIN_B_1 */	/* &Dio_Configuration[PIN_B_1] */
NULL_PTR,       		         /* PORTB  PIN_B_2 */	/* &Dio_Configuration[PIN_B_2] */
NULL_PTR,       		         /* PORTB  PIN_B_3 */	/* &Dio_Configuration[PIN_B_3] */
NULL_PTR,       		         /* PORTB  PIN_B_4 */	/* &Dio_Configuration[PIN_B_4] */
NULL_PTR,       		         /* PORTB  PIN_B_5 */	/* &Dio_Configuration[PIN_B_5] */
NULL_PTR,       		         /* PORTB  PIN_B_6 */	/* &Dio_Configuration[PIN_B_6] */
NULL_PTR,       		         /* PORTB  PIN_B_7 */	/* &Dio_Configuration[PIN_B_7] */
&Dio_Configuration[PIN_C_0],     /* PORTC  PIN_C_0 */	/* &Dio_Configuration[PIN_C_0] */
&Dio_Configuration[PIN_C_1],         		         /* PORTC  PIN_C_1 */	/* &Dio_Configuration[PIN_C_1] */
&Dio_Configuration[PIN_C_2],     		         /* PORTC  PIN_C_2 */	/* &Dio_Configuration[PIN_C_2] */
NULL_PTR,       		         /* PORTC  PIN_C_3 */	/* &Dio_Configuration[PIN_C_3] */
NULL_PTR,       		         /* PORTC  PIN_C_4 */	/* &Dio_Configuration[PIN_C_4] */
NULL_PTR,       		         /* PORTC  PIN_C_5 */	/* &Dio_Configuration[PIN_C_5] */
NULL_PTR,       		         /* PORTC  PIN_C_6 */	/* &Dio_Configuration[PIN_C_6] */
NULL_PTR,       		         /* PORTC  PIN_C_7 */	/* &Dio_Configuration[PIN_C_7] */
NULL_PTR,       		         /* PORTD  PIN_D_0 */	/* &Dio_Configuration[PIN_D_0] */
NULL_PTR,       		         /* PORTD  PIN_D_1 */	/* &Dio_Configuration[PIN_D_1] */
NULL_PTR,      		         /* PORTD  PIN_D_2 */	/* &Dio_Configuration[PIN_D_2] */
NULL_PTR,       		         /* PORTD  PIN_D_3 */	/* &Dio_Configuration[PIN_D_3] */
NULL_PTR,       		         /* PORTD  PIN_D_4 */	/* &Dio_Configuration[PIN_D_4] */
NULL_PTR,       		         /* PORTD  PIN_D_5 */	/* &Dio_Configuration[PIN_D_5] */
NULL_PTR,       		         /* PORTD  PIN_D_6 */	/* &Dio_Configuration[PIN_D_6] */
NULL_PTR}       		         /* PORTD  PIN_D_7 */	/* &Dio_Configuration[PIN_D_7] */
};
