/*
 * BasicTypes.h
 *
 *  Created on: 2 ago. 2021
 *      Author: uid87544
 */

#ifndef BASICTYPES_H_
#define BASICTYPES_H_

typedef unsigned char boolean;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;


typedef signed char  sint8;
typedef signed short sint16;
typedef signed long  sint32;


#define TRUE  ((boolean)1)
#define FALSE ((boolean)0)

#define ASIL_A_VAR_NOINIT     //__attribute__ ((section (".asila_var_noinit")))

#define MPU_ERROR_VAR_NOINIT  //__attribute__ ((section (".mpu_error_info")))

#endif /* BASICTYPES_H_ */
