/************************************************************************************************************************/
/* COMPILER_SUPPORT HEADER                                                                                            	*/
/*                                                                                                                      */
/* AUTHORS : Yves GUERTE, 12 September 2004                                                                             */
/*                                                                                                                      */
/* CONTENT : Functions that set the access to the data compared between tests						*/
/*                                                                                                                      */
/* 															*/
/*															*/
/************************************************************************************************************************/
#ifndef __COMPILER_SUPPORT__
#define __COMPILER_SUPPORT__

#include "cmp_functions.h"

// kind of compiler
// allows to know how to define when cc options are for size or speed
typedef enum t_e_compiler {e_gcc=0, e_scc, e_ppc, e_mwccarm, e_armcc, e_gccarm, e_win32_x86, e_dsp56800e, e_mac_ppc, e_dsp56800} t_compiler;

// To allow enumeration output
char * t_compiler_image[]; // = {"gcc", "scc", "ppc", "mwccarm", "armcc", "gccarm", "win32_x86", "dsp56800e", "mac_ppc", "dsp56800"};

// comparison criterion (needed to select comparison field depending on the CC)
// size, speed or compilation speed
typedef enum t_e_cmp_purpose {e_size, e_speed, e_cc_speed}
			 t_cmp_purpose;

// To allow enumeration output
char * t_cmp_purpose_image[]; // = {"size", "speed", "cc_speed"};



// ----------------------------------------------------------------------------------------------------------
// The 2 following pointers to function are modified by the set_access_fct function
// depending on the compiler and the kind of comparison we want to do


	// function that gets the data that must be compared
	char * (*access_fct)(const t_exec_dataref exec_dataref);

	// function that returns if a set of cc options is for the specified optimization purpose
	int (*is_for_purpose)(const t_cc_options cc_opt);


// function that sets the access_fct and is_for_purpose values
void set_access_fct(const t_compiler CC, const t_cmp_purpose cmp_purpose);


#endif


