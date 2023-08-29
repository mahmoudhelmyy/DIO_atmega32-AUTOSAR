/*
 * DIO_AUTOSAR.c
 *
 * Created: 8/21/2023 5:50:12 PM
 * Author: Mahmoud-Helmy
 */ 
#define LED_PORT  PORTC_ID
#define LED_PIN   PIN2_ID
#include <util/delay.h> /* For the delay functions */
#include "/Career/EME_SEITECH/AUTOSAR/DIO_AUTOSAR/DIO_AUTOSAR/Dio/Dio.h"
int main(void){
	Dio_SetupChannelDirection(PORTC_ID,PIN0_ID,PIN_OUTPUT);
	Dio_WriteChannel(PORTC_ID,PIN_C_0,STD_HIGH);
	}

