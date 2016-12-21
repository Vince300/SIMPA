/*-----------------------------------------------------------------------------				
*
* File:  typedefs.h
*
* Description:  
* This file contains typedefs for the fundamental data types.
*
* History:
* 12 Jan 01    Initial version.
* 16 Feb 01    Changed from NetComm conventions to StarCore conventions
*-----------------------------------------------------------------------------*/
#ifndef _TYPEDEFS_H 
#define _TYPEDEFS_H

/*------------------------*/
/* Fundamental Data Types */
/*------------------------*/
typedef	char		    Byte;
typedef unsigned char 	UByte;	
typedef unsigned char 	Bool;	

typedef	volatile char           VByte;
typedef volatile unsigned char 	VUByte;	
typedef	volatile short	        VWord16;   /* VHWORD*/
typedef	volatile unsigned short	VUWord16;  /* VUHWORD*/
typedef	volatile long	        VWord32;   /* VWORD*/
typedef volatile unsigned long 	VUWord32;  /* VUWORD*/
typedef volatile unsigned char 	VBool;	

#endif
