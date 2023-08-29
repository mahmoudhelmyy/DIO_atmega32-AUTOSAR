/*======================================================================================================
 * Module: Compiler Abstraction																			*															*
 * File Name: Platform_Types.h																			*																*
 * Description: Contains types that dependent on platform.                     		                    *
 * Author: Mahmoud-Helmy																				*
 *======================================================================================================*/
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H


/* Id for the company in the AUTOSAR
 * for example Mahmoud Helmy's ID = 1000 :) */
#define PLATFORM_VENDOR_ID                          (1000U)

/*
 * Module Version 1.0.0
 */
#define PLATFORM_SW_MAJOR_VERSION                   (1U)
#define PLATFORM_SW_MINOR_VERSION                   (0U)
#define PLATFORM_SW_PATCH_VERSION                   (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PLATFORM_AR_RELEASE_MAJOR_VERSION           (4U)
#define PLATFORM_AR_RELEASE_MINOR_VERSION           (0U)
#define PLATFORM_AR_RELEASE_PATCH_VERSION           (3U)

/*
 * CPU register type width
 */
#define CPU_TYPE_8                                  (8U)
#define CPU_TYPE_16                                 (16U)
#define CPU_TYPE_32                                 (32U)

/*
 * Platform type and endianess definitions, specific for ARM Cortex-M4F
 */
#define CPU_TYPE            CPU_TYPE_32

#define CPU_BIT_ORDER    LSB_FIRST        /*little endian bit ordering*/
#define CPU_BYTE_ORDER   LOW_BYTE_FIRST   /*little endian byte ordering*/

#define WORD_LENGTH_BITS      32u
#define WORD_LENGTH_BYTES     4u
#define MSB_FIRST             0u    /* big endian bit ordering */
#define LSB_FIRST			  1u    /* little endian bit ordering */

#define HIGH_BYTE_FIRST  0u    /* big endian byte ordering */
#define LOW_BYTE_FIRST   1u    /* little endian byte ordering */

#ifndef TRUE
#define TRUE   1u
#endif

#ifndef FALSE
#define FALSE  0u
#endif

#define ENABLE    1u
#define DISABLE   0u

typedef unsigned char         boolean;       /*        TRUE .. FALSE           */
typedef signed char           sint8;         /*        -128 .. +127            */
typedef unsigned char         uint8;         /*           0 .. 255             */
typedef signed short          sint16;        /*      -32768 .. +32767          */
typedef unsigned short        uint16;        /*           0 .. 65535           */
typedef signed long           sint32;        /* -2147483648 .. +2147483647     */
typedef unsigned long         uint32;        /*           0 .. 4294967295      */
typedef float                 float32;
typedef double                float64;
typedef signed char           sint8_t;         /*        -128 .. +127            */
typedef unsigned char         uint8_t;         /*           0 .. 255             */
typedef signed short          sint16_t;        /*      -32768 .. +32767          */
typedef signed long           sint32_t;        /* -2147483648 .. +2147483647     */
typedef unsigned long         uint32_t;        /*           0 .. 4294967295      */
typedef float                 float32_t;
typedef double                float64_t;

//typedef signed char        int8_t;
//typedef short              int16_t;
//typedef int                int32_t;
//typedef long long          int64_t;
//typedef unsigned char      uint8_t;
//typedef unsigned short     uint16_t;
//typedef unsigned int       uint32_t;
//typedef unsigned long long uint64_t;
//typedef signed char        int_least8_t;
//typedef short              int_least16_t;
//typedef int                int_least32_t;
//typedef long long          int_least64_t;
//typedef unsigned char      uint_least8_t;
//typedef unsigned short     uint_least16_t;
//typedef unsigned int       uint_least32_t;
//typedef unsigned long long uint_least64_t;
//typedef signed char        int_fast8_t;
//typedef int                int_fast16_t;
//typedef int                int_fast32_t;
//typedef long long          int_fast64_t;
//typedef unsigned char      uint_fast8_t;
//typedef unsigned int       uint_fast16_t;
//typedef unsigned int       uint_fast32_t;
//typedef unsigned long long uint_fast64_t;

#ifdef PLATFORM_SUPPORT_SINT64_UINT64 /*Valid only for gnu and C99 */
typedef signed    long long  sint64;   /* -9223372036854775808 .. 9223372036854775807      */
typedef unsigned  long long  uint64;   /*                    0 .. 18446744073709551615     */

typedef signed    long long  sint64_t;   /* -9223372036854775808 .. 9223372036854775807      */
typedef unsigned  long long  uint64_t;   /*                    0 .. 18446744073709551615     */
#endif

#endif  /* PLATFORM_TYPES_H */
