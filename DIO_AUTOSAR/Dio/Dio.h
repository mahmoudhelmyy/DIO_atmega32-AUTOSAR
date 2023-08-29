/*===============================================================================
 * Module: DIO																	*															*
 * File Name: Dio.h																*																*
 * Description: Header file for AVR ATmega32 Microcontroller - DIO Driver		*
 * Author: Mahmoud-Helmy														*
 *==============================================================================*/
/* =============================================================================
 * 							   FILE GUARD
 * =============================================================================*/
#ifndef DIO_H
#define DIO_H
/* =============================================================================
 * 								INCLUDES
 * =============================================================================*/
/* DIO Pre-Compile (Switches) Configuration Header file */
#include "Dio_Cfg.h"

/* Standard AUTOSAR types */
#include "../LIB/Std_Types.h"

/* Non AUTOSAR files */
#include "../LIB/Common_Macros.h"

/* =============================================================================
 * 								VERSION DEFINITION
 * =============================================================================*/
/* Id for the company in the AUTOSAR
 * for example Mahmoud Helmy's ID = 1000*/
#define DIO_VENDOR_ID    (1000U)

/* Dio Module Id */
#define DIO_MODULE_ID    (120U)

/* Dio Instance Id */
#define DIO_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define DIO_SW_MAJOR_VERSION           (1U)
#define DIO_SW_MINOR_VERSION           (0U)
#define DIO_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_AR_RELEASE_MAJOR_VERSION   (4U)
#define DIO_AR_RELEASE_MINOR_VERSION   (0U)
#define DIO_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Dio Status
 */
#define DIO_INITIALIZED                (1U)
#define DIO_NOT_INITIALIZED            (0U)


/* =============================================================================
 * 								VERSION CHECK
 * =============================================================================*/
/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif



/* AUTOSAR Version checking between Dio_Cfg.h and Dio.h files */
#if ((DIO_CFG_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_CFG_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_CFG_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Dio_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_Cfg.h and Dio.h files */
#if ((DIO_CFG_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION)\
 ||  (DIO_CFG_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION)\
 ||  (DIO_CFG_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION))
  #error "The SW version of Dio_Cfg.h does not match the expected version"
#endif

/* =============================================================================
 * 								DET ERROR CODES  
 * =============================================================================*/

/* DET code to report Invalid Channel */
#define DIO_E_PARAM_INVALID_CHANNEL_ID (uint8)0x0A

/* Dio_Init API service called with NULL pointer parameter */
#define DIO_E_PARAM_CONFIG             (uint8)0x10

/* DET code to report Invalid Port */
#define DIO_E_PARAM_INVALID_PORT_ID    (uint8)0x14

/* DET code to report Invalid Channel Group */
#define DIO_E_PARAM_INVALID_GROUP      (uint8)0x1F

/*
 * The API service shall return immediately without any further action,
 * beside reporting this development error.
 */
#define DIO_E_PARAM_POINTER             (uint8)0x20

/*
 * API service used without module initialization is reported using following
 * error code (Not exist in AUTOSAR 4.0.3 DIO SWS Document).
 */
#define DIO_E_UNINIT                   (uint8)0xF0
/* =============================================================================
 * 							 API SERVICE IDs    
 * =============================================================================*/

/* Service ID for DIO read Channel */
#define DIO_READ_CHANNEL_SID           (uint8)0x00

/* Service ID for DIO write Channel */
#define DIO_WRITE_CHANNEL_SID          (uint8)0x01

/* Service ID for DIO read Port */
#define DIO_READ_PORT_SID              (uint8)0x02

/* Service ID for DIO write Port */
#define DIO_WRITE_PORT_SID             (uint8)0x03

/* Service ID for DIO read Channel Group */
#define DIO_SETUP_CHANNEL_DIRECTION_SID    (uint8)0x04

/* Service ID for DIO write Channel Group */
#define DIO_SETUP_PORD_DIRECTION_SID   (uint8)0x05

/* Service ID for DIO write Channel Group */
#define DIO_TOGGLE_PIN_SID  		   (uint8)0x06

/* Service ID for DIO GetVersionInfo */
#define DIO_GET_VERSION_INFO_SID       (uint8)0x12

/* Service ID for DIO Init Channel */
#define DIO_INIT_SID                   (uint8)0x10


/* =============================================================================
 * 							 MODULES DATA TYPES   
 * =============================================================================*/

/* Type definition for Dio_Direction used by the DIO APIs */
typedef uint8 Dio_Direction;

/* Type definition for Dio_Pin used by the DIO APIs */
typedef uint8 Dio_ChannelType;

/* Type definition for Dio_PortType used by the DIO APIs */
typedef uint8 Dio_PortType;

/* Type definition for Dio_PinLevelType used by the DIO APIs */
typedef uint8 Dio_PinLevelType;

/* Type definition for Dio_PinLevelType used by the DIO APIs */
typedef uint8 Dio_PinGroupeType;

/* Type definition for Dio_LevelType used by the DIO APIs */
typedef uint8 Dio_LevelType;

/* Type definition for Dio_PortLevelType used by the DIO APIs */
typedef uint8 Dio_PortLevelType;

typedef struct Dio_ConfigChannel {
	/* Member contains the ID of the Port that this pin belongs to */
	Dio_PortType Port_Id;
	/* Member contains the ID of the pin*/
	Dio_ChannelType Pin_Id;
	/* Member contains the direction of the pin*/
	Dio_Direction dir;
	/* Member contains the level of the pint*/
	Dio_PinLevelType level;
} Dio_ConfigChannel;

/* Data Structure required for initializing the Dio Driver
@brief This structure contains all post-build configurable parameters of the DIO driver. 
A pointer to this structure is passed to the DIO driver initialization function for
configuration
 */
typedef struct Dio_ConfigType {
	const Dio_ConfigChannel *channels[DIO_CONFIGURED_CHANNLES];
} Dio_ConfigType;


/* =============================================================================
 * 							 FUNCTION PROTOTYPES   
 * =============================================================================*/
/* =============================================================================
 * Service Name: Dio_Init
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): ConfigPtr - Pointer to post-build configuration data.
 * Parameters (input): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Initialize the Dio module.
 * =============================================================================*/
/* Function for DIO Initialization API */
void Dio_Init(const Dio_ConfigType *ConfigPtr);

/* =============================================================================
 * Service Name: Dio_SetupPinrtDirection
 * Service ID[hex]: None
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Port_Id - ID of DIO port.
 * 				    Pin_Id - ID of DIO pin.
 *                  Direction - Value to be written.
 * Parameters (input): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the direction of a channel.
 * =============================================================================*/
/* Function for DIO Setup Pin Direction API */
void Dio_SetupChannelDirection(Dio_PortType Port_Id, Dio_ChannelType Channel_Id, Dio_Direction dir);

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
/* Function for DIO Setup Port Direction API */
void Dio_SetupPortDirection(Dio_PortType Port_Id, Dio_Direction dir);

/* =============================================================================
 * Service Name: Dio_ReadChannel
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Port_Id - ID of DIO port.
 * 				   Pin_Id - ID of DIO pin.
 * Parameters (input): None
 * Parameters (out): None
 * Return value: LevelType
 * 				 STD_HIGH The physical level of the corresponding Pin is STD_HIGH
 * 				 STD_LOW The physical level of the corresponding Pin is STD_LOW
 * Description: Function to Return the value of the specified DIO channel.
 * =============================================================================*/
/* Function for DIO read pin API */
Dio_LevelType Dio_ReadChannel(Dio_PortType Port_Id, Dio_ChannelType Pin_Id);
/* =============================================================================
 * Service Name: Dio_WriteChannel
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Port_Id - ID of DIO port.
 * 				   Pin_Id - ID of DIO pin.
 *                  Level - Value to be written.
 * Parameters (input): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set a level of a channel.
 * =============================================================================*/
/* Function for DIO write pin API */
void Dio_WriteChannel(Dio_PortType Port_Id, Dio_ChannelType Pin_Id,
		Dio_PinLevelType level);


/* =============================================================================
 * Service name: Dio_WritePort
 * Service ID[hex]: 0x03
 *Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * PortId ID of DIO Port Parameters (in): Level Value to be written
 * Parameters(inout):None
 * Parameters (out): None
 * Return value: None
 * Description: Service to set a value of the port
 * =============================================================================*/
/* Function for DIO write Port API */
void Dio_WritePort(Dio_PortType Port_Id, Dio_PinLevelType level);

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
/* Function for DIO read Port API */
Dio_PortLevelType Dio_ReadPort(Dio_PortType Port_Id);

/* =============================================================================
 * Service Name:  Dio_FlipChannel
 * Service ID[hex]: 0x11
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Port_Id - ID of DIO port.
 * 				    Pin_Id - ID of DIO pin.
 * Parameters (input): None
 * Parameters (out): None
 * Return value: None
 * Description: Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel and return
 *              the level of the channel after flip.
 * =============================================================================*/
/* Function for DIO flip channel API */
void  Dio_FlipChannel(Dio_PortType Port_Id, Dio_ChannelType Channel_Id);

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
/* Function for DIO Get Version Info API */
#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

/* =============================================================================
 *                         EXTERNAL VARIABLES                                   
 * =============================================================================*/

/* Extern PB structures to be used by Dio and other modules */
extern const Dio_ConfigType Dio_ConfigurationSet;

#endif /* DIO_H */
