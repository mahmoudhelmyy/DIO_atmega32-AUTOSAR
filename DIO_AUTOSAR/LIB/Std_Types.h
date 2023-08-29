/*======================================================================================================
 * Module: Compiler Abstraction																			*															*
 * File Name: Std_Types.h																				*																*
 * Description: Standard Types                    													    *	
 * Author: Mahmoud-Helmy																				*
 *======================================================================================================*/


#ifndef STD_TYPES_H
#define STD_TYPES_H


# include "Platform_Types.h"
# include "Compiler.h"


/* Id for the company in the AUTOSAR
 * for example Mahmoud Helmy's ID = 1000 :) */
#define STD_TYPES_VENDOR_ID                                  (1000U)

/*
 * Module Version 1.0.0
 */
#define STD_TYPES_SW_MAJOR_VERSION                           (1U)
#define STD_TYPES_SW_MINOR_VERSION                           (0U)
#define STD_TYPES_SW_PATCH_VERSION                           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION                   (4U)
#define STD_TYPES_AR_RELEASE_MINOR_VERSION                   (0U)
#define STD_TYPES_AR_RELEASE_PATCH_VERSION                   (3U)

#define STD_HIGH        0x01U       /* Standard HIGH */
#define STD_LOW         0x00U       /* Standard LOW */

#define LOGIC_HIGH        0x01U       /* Standard HIGH */
#define LOGIC_LOW         0x00U       /* Standard LOW */

#define STD_ACTIVE      0x01U       /* Logical state active */
#define STD_IDLE        0x00U       /* Logical state idle */

#define STD_ON          0x01U       /* Standard ON */
#define STD_OFF         0x00U       /* Standard OFF */

typedef uint8         Std_ReturnType;
#define E_OK            ((Std_ReturnType)0x00U)      /* Function Return OK */
#define E_NOT_OK        ((Std_ReturnType)0x01U)      /* Function Return NOT OK */




/* The memory class is used for the declaration of local pointers */
#define AUTOMATIC

/* The memory class is used within type definitions, where no memory
   qualifier can be specified */
#define TYPEDEF

/* This is used to define the void pointer to zero definition */
#define NULL_PTR          ((void *)0)

/* This is used to define the abstraction of compiler keyword inline */
#define INLINE            inline

/* This is used to define the local inline function */
#define LOCAL_INLINE      static inline

/* This is used to define the abstraction of compiler keyword static */
#define STATIC            static


/*
 * Structure for the Version of the module.
 * This is requested by calling <Module name>_GetVersionInfo()
 */
typedef struct
{
  uint16  vendorID;
  uint16  moduleID;
  uint8 sw_major_version;
  uint8 sw_minor_version;
  uint8 sw_patch_version;
} Std_VersionInfoType;



#endif /* STD_TYPES_H */

