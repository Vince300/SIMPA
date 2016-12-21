/*
    ITU-T G.723 Speech Coder   ANSII-C Source Code     Version 3.00
    copyright (c) 1995, AudioCodes, DSP Group, France Telecom,
    Universite de Sherbrooke.  All rights reserved.
*/


/*
   Types definitions
*/
#ifndef _TYPEDEF_H
#define _TYPEDEF_H

#ifdef __DSP__
typedef short Word16;
typedef long Word32;
typedef unsigned long   UWord32;
typedef int Flag;

#elif defined __unix__ || defined(__unix)
typedef short Word16;
typedef int   Word32;
typedef unsigned int   UWord32;
typedef int   Flag;

#elif defined(__BORLANDC__) || defined (__WATCOMC__) || defined(_MSC_VER) || defined(__ZTC__) || defined(__ARMCC_VERSION)
typedef  long  int   Word32   ;
typedef unsigned int   UWord32;
typedef  short int   Word16   ;
typedef  short int   Flag  ;

#elif defined(__MWERKS__) && ( defined(__arm) || defined(__m56800E__) || defined(__m56800__) )
typedef  long  int   Word32   ;
typedef unsigned int   UWord32;
typedef  short int   Word16   ;
typedef  short int   Flag  ;

#elif defined __sun
typedef short  Word16;
typedef long  Word32;
typedef unsigned int   UWord32;
typedef int   Flag;
#endif

#endif



