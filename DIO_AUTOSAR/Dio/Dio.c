/*===============================================================================
 * Module: DIO																	*															*
 * File Name: Dio.c																*																*
 * Description: Source file for AVR ATmega32 Microcontroller - DIO Driver		*
 * Author: Mahmoud-Helmy														*
 *==============================================================================*/
/* =============================================================================
 * 								 INCLUDES
 * =============================================================================*/
#include "Dio.h"
#include "MemMap.h"

/* =============================================================================
 * 								VERSION CHECK
 * =============================================================================*/
/* Software Version checking between MemMap.h and Dio.h files */
#if ((DIO_REGS_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION)\
 ||  (DIO_REGS_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION)\
 ||  (DIO_REGS_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION))
  #error "The SW version of Dio_Cfg.h does not match the expected version"
#endif

#if (DIO_DEV_ERROR_DETECT == STD_ON)

#include "../Det/Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif
#endif

/* ==============================================================================================================
 * 							 GLOBAL VARIABLES
 * ==============================================================================================================*/
/* @struct Dio_ConfigType: * This structure defines the configuration for the DIO module. 
 *						   * It contains an array of pointers to Dio_ConfigPin structures.
 * @member channels[DIO_CONFIGURED_CHANNLES]: * This array holds pointers to individual pin configurations. 
 *										  * The size of the array is DIO_CONFIGURED_CHANNLES, 
 *											which represents the number of configured channels.
 *
 * @struct Dio_ConfigPin: This structure represents the configuration of an individual pin within the DIO module.
 * @member Port_Id: This member stores the ID of the port to which the pin belongs. 
 * @member Pin_Id: This member stores the ID of the pin.
 * @member dir: This member indicates the direction of the pin, whether it's an input or an output.
 * @member level: This member indicates the initial level (high or low) of the pin.
 
 
 * This is a static pointer to a constant Dio_ConfigType structure. 
 * It will be used to store the configuration data for the DIO module.
 */
STATIC const Dio_ConfigType *Dio_PortChannels = NULL_PTR;

/* This is a static variable that keeps track of the initialization status of the DIO module. 
 * It's initialized to DIO_NOT_INITIALIZED
 */
STATIC uint8 Dio_Status = DIO_NOT_INITIALIZED;


/**
 * @brief Extracts the pin number from the given ChannelId.
 * @param ChannelId The ID of the pin.
 * @return The extracted pin number.
 *
 * This function extracts the pin number from the given ChannelId based on certain conditions.
 */
STATIC uint8 getChannelNum(Dio_ChannelType ChannelId) {
    if (ChannelId <= 7) {
        /*If ChannelId is 7 or less, return it as the pin number*/
        return ChannelId;

    } else if (ChannelId > 7) {
        /*If ChannelId is greater than 7, calculate the pin number using modulo*/
        return ChannelId % NUM_OF_PINS_IN_SINGLE_PORT;
    } else {
        /* Do Nothing */
    }
    /* Return the ChannelId in case no condition is met*/
    return ChannelId;
}

/* ==============================================================================================================
 * 												 APIs
 * ==============================================================================================================*/

/*==================================================================================
 * Service Name: Dio_Init
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant, meaning it's not designed to be safely called simultaneously from multiple execution contexts.
 * Parameters (in): ConfigPtr - Pointer to post-build configuration data.
 * Parameters (input): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Initialize the Dio module.
 *===================================================================================*/
void Dio_Init(const Dio_ConfigType *ConfigPtr) {
/*If it's defined as STD_ON, error detection is enabled.*/
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is a NULL_PTR 
	 * (NULL_PTR == ConfigPtr) >> Yoda conditions: In this case, if you accidentally use a single equal sign (=) instead of a double equal sign (==).
	 */
	if (NULL_PTR == ConfigPtr) {
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_INIT_SID, DIO_E_PARAM_CONFIG);
	} else
#endif
	{
		if (DIO_NOT_INITIALIZED == Dio_Status) {
			Dio_Status = DIO_INITIALIZED;
			Dio_PortChannels = ConfigPtr;
			uint8 ChannelNum;
			/* store the pointer to the relevant PORT register.
			 * by using the volatile keyword, you ensure that the compiler treats the Port_Ptr pointer as potentially changing its value at any time, 
			 * which is essential when dealing with memory-mapped hardware registers that can be modified by external factors. 
			 * This helps prevent unexpected behavior and ensures accurate interaction with hardware peripherals.*/
			volatile uint8 *Port_Ptr = NULL_PTR;

			/* Point to the correct PORT register according to the Port Id stored in the Port_Id member */
			for (uint8 i = 0; i < DIO_CONFIGURED_CHANNLES; ++i) {
				if (Dio_PortChannels->channels[i] == NULL_PTR) {
					/* Do Nothing */
					} else {
					/* Assigns the appropriate address of the PORT register to the Port_Ptr variable.*/
					switch (Dio_PortChannels->channels[i]->Port_Id) {
					case (PORTA_ID):
						Port_Ptr = &PORTA;
						break;
					case (PORTB_ID):
						Port_Ptr = &PORTB;
						break;
					case (PORTC_ID):
						Port_Ptr = &PORTC;
						break;
					case (PORTD_ID):
						Port_Ptr = &PORTD;
						break;
					}

					ChannelNum = getChannelNum(Dio_PortChannels->channels[i]->Pin_Id);
					/* Ensuring that a valid PORT register has been determined.*/
					if (Port_Ptr != NULL_PTR) {
						/*Set Pin Direction*/
						if (Dio_PortChannels->channels[i]->dir == INPUT) {
							SET_BIT(*Port_Ptr, ChannelNum);
						} else if (Dio_PortChannels->channels[i]->dir == OUTPUT) {
							CLEAR_BIT(*Port_Ptr, ChannelNum);
						} else {
							/* Do Nothing (there's no configuration for this pin, so no action is taken) */
						}

						/*Set Pin Value*/
						if (Dio_PortChannels->channels[i]->level == STD_HIGH) {
							SET_BIT(*Port_Ptr, ChannelNum);
						} else if (Dio_PortChannels->channels[i]->level == STD_LOW) {
							CLEAR_BIT(*Port_Ptr, ChannelNum);
						} else {
							/* Do Nothing */
						}
					} else {
						/* Do Nothing */
					}
				}
			}
		} else {
			/* Do Nothing */
		}
	}
}

/* =============================================================================
 * Service Name: Dio_SetupChannelDirection
 * Service ID[hex]: None
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Port_Id - ID of DIO port.
 * 				    Channel_Id - ID of DIO pin.
 *                  Direction - Value to be written.
 * Parameters (input): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the direction of a channel.
 * =============================================================================*/
void Dio_SetupChannelDirection(Dio_PortType Port_Id, Dio_ChannelType Channel_Id, Dio_Direction dir) {
	volatile uint8 *Port_Ptr = NULL_PTR;
	boolean error = FALSE;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status) {
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SETUP_CHANNEL_DIRECTION_SID, DIO_E_UNINIT);
		error = TRUE;
	} else {
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= Channel_Id) {
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SETUP_CHANNEL_DIRECTION_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	} else {
		/* No Action Required */
	}
#endif

	/* In-case there are no errors */
	if (FALSE == error) {
		uint8 ChannelNum = getChannelNum(Channel_Id);

		/* Point to the correct PORT register according to the Port Id stored in the Port_Id member */
		switch (Port_Id) {
		case (PORTA_ID):
			Port_Ptr = &DDRA;
			break;
		case (PORTB_ID):
			Port_Ptr = &DDRB;
			break;
		case (PORTC_ID):
			Port_Ptr = &DDRC;
			break;
		case (PORTD_ID):
			Port_Ptr = &DDRD;
			break;
		}

		if (Port_Ptr != NULL_PTR) {
			if (GET_BIT(*Port_Ptr, ChannelNum) == INPUT) {
				SET_BIT(*Port_Ptr, ChannelNum);
			} else if (GET_BIT(*Port_Ptr, ChannelNum) == OUTPUT) {
				CLEAR_BIT(*Port_Ptr, ChannelNum);
			} else {
				/* Do Nothing */
			}
		} else {
			/* Do Nothing */
		}
	}
}

/* =============================================================================
 * Service Name: Dio_SetupPortDirection
 * Service ID[hex]: None
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Port_Id - ID of DIO port.
 *                  Direction - Value to be written.
 * Parameters (input): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the direction of a port.
 * =============================================================================*/
void Dio_SetupPortDirection(Dio_PortType Port_Id, Dio_Direction dir) {
	volatile uint8 *Port_Ptr = NULL_PTR;
	boolean error = FALSE;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status) {
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_SID, DIO_E_UNINIT);
		error = TRUE;
	} else {
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_PORTS <= Port_Id) {

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SETUP_PORD_DIRECTION_SID, DIO_E_PARAM_INVALID_PORT_ID);
		error = TRUE;
	} else {
		/* No Action Required */
	}
#endif

	/* Point to the correct PORT register according to the Port Id stored in the Port_Id member */
	switch (Port_Id) {
	case (PORTA_ID):
		Port_Ptr = &DDRA;
		break;
	case (PORTB_ID):
		Port_Ptr = &DDRB;
		break;
	case (PORTC_ID):
		Port_Ptr = &DDRC;
		break;
	case (PORTD_ID):
		Port_Ptr = &DDRD;
		break;
	}
	if (Port_Ptr != NULL_PTR) {
		if (dir == INPUT) {
			*Port_Ptr = dir;
		} else if (dir == OUTPUT) {
			*Port_Ptr = dir;
		} else {
			/* Do Nothing */
		}
	} else {
		/* Do Nothing */
	}
}

/* =============================================================================
 * Service Name: Dio_WriteChannel
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Port_Id - ID of DIO port.
 * 				    Channel_Id - ID of DIO pin.
 *                  Level - Value to be written.
 * Parameters (input): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set a level of a channel.
 * =============================================================================*/
void Dio_WriteChannel(Dio_PortType Port_Id, Dio_ChannelType Channel_Id,Dio_PinLevelType level) {
	volatile uint8 *Port_Ptr = NULL_PTR;
	boolean error = FALSE;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status) {
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_SID, DIO_E_UNINIT);
		error = TRUE;
	} else {
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= Channel_Id) {

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	} else {
		/* No Action Required */
	}
#endif

	/* In-case there are no errors */
	if (FALSE == error) {
		uint8 ChannelNum = getChannelNum(Channel_Id);

		switch (Port_Id) {
		case (PORTA_ID):
			Port_Ptr = &PORTA;
			break;
		case (PORTB_ID):
			Port_Ptr = &PORTB;
			break;
		case (PORTC_ID):
			Port_Ptr = &PORTC;
			break;
		case (PORTD_ID):
			Port_Ptr = &PORTD;
			break;
		}
		if (Port_Ptr != NULL_PTR) {
			if (level == STD_HIGH) {
				SET_BIT(*Port_Ptr, ChannelNum);
			} else if (level == STD_LOW) {
				CLEAR_BIT(*Port_Ptr, ChannelNum);
			} else {
				/* Do Nothing */
			}
		} else {
			/* Do Nothing */
		}
	}
}


/* =============================================================================
 * Service Name: Dio_ReadChannel
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Port_Id - ID of DIO port.
 * 				    Channel_Id - ID of DIO pin.
 * Parameters (input): None
 * Parameters (out): None
 * Return value: LevelType
 * 				 STD_HIGH The physical level of the corresponding Pin is STD_HIGH
 * 				 STD_LOW The physical level of the corresponding Pin is STD_LOW
 * Description: Function to Return the value of the specified DIO channel.
 * =============================================================================*/
Dio_LevelType Dio_ReadChannel(Dio_PortType Port_Id, Dio_ChannelType Channel_Id) {
	volatile uint8 *Port_Ptr = NULL_PTR;
	Dio_LevelType output = STD_LOW;
	boolean error = FALSE;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status) {
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_SID, DIO_E_UNINIT);
		error = TRUE;
	} else {
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= Channel_Id) {

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	} else {
		/* No Action Required */
	}
#endif

	/* In-case there are no errors */
	if (FALSE == error) {
		/* Point to the correct PORT register according to the Port Id stored in the Port_Id member */

		uint8 pinNum = getChannelNum(Channel_Id);
		switch (Port_Id) {
			case (PORTA_ID):
			Port_Ptr = &PORTA;
			break;
			case (PORTB_ID):
			Port_Ptr = &PORTB;
			break;
			case (PORTC_ID):
			Port_Ptr = &PORTC;
			break;
			case  (PORTD_ID):
			Port_Ptr = &PORTD;
			break;
		}
		if (Port_Ptr != NULL_PTR) {
			if (GET_BIT(*Port_Ptr, pinNum) == STD_HIGH) {
				output = STD_HIGH;
			} else if (GET_BIT(*Port_Ptr, pinNum) == STD_LOW) {
				output = STD_LOW;
			} else {
				/* Do Nothing */
			}
		} else {
			/* Do Nothing */
		}
	}
	return output;
}

/* =============================================================================
 * Service name: Dio_WritePort
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * PortId ID of DIO Port Parameters (in): Level Value to be written
 * Parameters(inout):None
 * Parameters (out): None
 * Return value: None
 * Description: Service to set a value of the port
 * =============================================================================*/
void Dio_WritePort(Dio_PortType Port_Id, Dio_PinLevelType level) {
	volatile uint8 *Port_Ptr = NULL_PTR;
	boolean error = FALSE;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status) {
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_SID,DIO_E_UNINIT);
		error = TRUE;
	} else {
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_PORTS <= Port_Id) {

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_PORT_SID,
				DIO_E_PARAM_INVALID_PORT_ID);
		error = TRUE;
	} else {
		/* No Action Required */
	}
#endif

	/* In-case there are no errors */
	if (FALSE == error) {
		/* Point to the correct PORT register according to the Port Id stored in the Port_Id member */
		switch (Port_Id) {
		case 1:
			Port_Ptr = &PORTA;
			break;
		case 2:
			Port_Ptr = &PORTB;
			break;
		case 3:
			Port_Ptr = &PORTC;
			break;
		case 4:
			Port_Ptr = &PORTD;
			break;
		}
		if (Port_Ptr != NULL_PTR) {
			if (level == STD_HIGH) {
				*Port_Ptr |= level;
			} else if (level == STD_LOW) {
				*Port_Ptr |= level;
			} else {
				/* Do Nothing */
			}
		} else {
			/* Do Nothing */
		}
	}
}

/* =============================================================================
 * Service Name: Dio_ReadPort
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Port_Id - ID of DIO port.
 * Parameters (input): None
 * Parameters (out): None
 * Return value: Dio_PortLevelType Level of all channels of that port
 * Description: Function to Returns the level of all channels of that port.
 * =============================================================================*/
Dio_PortLevelType Dio_ReadPort(Dio_PortType Port_Id) {
	Dio_LevelType output = STD_LOW;
	boolean error = FALSE;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status) {
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_SID,
				DIO_E_UNINIT);
		error = TRUE;
	} else {
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= Port_Id) {

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_PORT_SID,
				DIO_E_PARAM_INVALID_PORT_ID);
		error = TRUE;
	} else {
		/* No Action Required */
	}
#endif

	/* In-case there are no errors */
	if (FALSE == error) {
		/* Point to the correct PORT register according to the Port Id stored in the Port_Id member */
		switch (Port_Id) {
		case (PORTA_ID):
			output = PINA;
			break;
		case (PORTB_ID):
			output = PINB;
			break;
		case (PORTC_ID):
			output = PINC;
			break;
		case (PORTD_ID):
			output = PIND;
			break;
		}
	}
	return output;
}

/* =============================================================================
 * Service Name:  Dio_FlipChannel
 * Service ID[hex]: 0x11
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Port_Id - ID of DIO port.
 * 				    Channel_Id - ID of DIO pin.
 * Parameters (input): None
 * Parameters (out): None
 * Return value: None
 * Description: Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel and return
 *              the level of the channel after flip.
 * =============================================================================*/
void  Dio_FlipChannel(Dio_PortType Port_Id, Dio_ChannelType Channel_Id) {
	volatile uint8 *Port_Ptr = NULL_PTR;
	boolean error = FALSE;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status) {
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_SID, DIO_E_UNINIT);
		error = TRUE;
	} else {
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= Channel_Id) {

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_TOGGLE_PIN_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	} else {
		/* No Action Required */
	}
#endif

	/* In-case there are no errors */
	if (FALSE == error) {
		uint8 ChannelNum = getChannelNum(Channel_Id);

		/* Point to the correct PORT register according to the Port Id stored in the Port_Id member */
		switch (Port_Id) {
		case (PORTA_ID):
			Port_Ptr = &PORTA;
			break;
		case (PORTB_ID):
			Port_Ptr = &PORTB;
			break;
		case (PORTC_ID):
			Port_Ptr = &PORTC;
			break;
		case PORTD_ID:
			Port_Ptr = &PORTD;
			break;
		}
		if (Port_Ptr != NULL_PTR) {
			if (GET_BIT(*Port_Ptr, ChannelNum) == STD_HIGH) {
				CLEAR_BIT(*Port_Ptr, ChannelNum);
			} else if (GET_BIT(*Port_Ptr, ChannelNum) == STD_LOW) {
				SET_BIT(*Port_Ptr, ChannelNum);
			} else {
				/* Do Nothing */
			}
		} else {
			/* Do Nothing */
		}
	}
}

/* =============================================================================
 * Service Name: Dio_GetVersionInfo
 * Service ID[hex]: 0x12
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (input): None
 * Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to get the version information of this module.
 * =============================================================================*/

#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo) {
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if (NULL_PTR == versioninfo) {
		/* Report to DET  */
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_GET_VERSION_INFO_SID, DIO_E_PARAM_POINTER);
	} else
#endif
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16) DIO_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16) DIO_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8) DIO_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8) DIO_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8) DIO_SW_PATCH_VERSION;
	}
}
#endif
