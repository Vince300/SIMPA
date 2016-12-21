/* Version 3.3    Last modified: December 26, 1995 */

/* WARNING: Make sure that the proper flags are defined for your system */

/*
   Types definitions
*/

#ifndef TYPEDEF_H
#define TYPEDEF_H

#if defined(_USE_CW_PROTO_)
#include <prototype.h>
#else

#if defined(__BORLANDC__) || defined(__WATCOMC__) || defined(_MSC_VER) || defined(__ZTC__) || defined(__ARMCC_VERSION)
typedef short Word16;
typedef long Word32;
typedef int Flag;
#elif defined(__MWERKS__) && ( defined(__arm) || defined(__m56800E__) || defined(__m56800__) )
typedef short Word16;
typedef long Word32;
typedef int Flag;
#elif defined(__sun)
typedef short Word16;
typedef long Word32;
typedef int Flag;
#elif defined(__unix__) || defined(__unix)
typedef short Word16;
typedef int Word32;
typedef int Flag;
#elif defined(__GNUC__) ||  defined(_ENTERPRISE_C_) || defined(__POWERPC__)
typedef short Word16;
typedef long Word32;
typedef int Flag;
#else
#error  COMPILER NOT TESTED typedef.h needs to be updated, see readme
#endif

#endif /*USE_CW_PROTO*/
#endif /*TYPEDEF_H*/
