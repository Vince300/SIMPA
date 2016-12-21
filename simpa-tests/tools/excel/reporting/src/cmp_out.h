/************************************************************************************************************************/
/* CMP_OUT HEADER                                                                                                       */
/*                                                                                                                      */
/* AUTHORS : Yves GUERTE, 18 October 2004                                                                               */
/*                                                                                                                      */
/* CONTENT : Functions that output report comparison                                                                    */
/*                                                                                                                      */
/* 															*/
/*															*/
/************************************************************************************************************************/
#include <time.h>
#include <ctype.h>
#include "common_yacc_lex.h"
#include "cmp_functions.h"

/* ----------------------------------------------------*/
// __int64 is used for cycles number
#ifndef _MSC_VER

#ifndef __int64
#define __int64 long long
#endif

#ifndef __uint64
#define __uint64 unsigned long long
#endif

#else

#ifndef __uint64
#define __uint64 unsigned __int64
#endif

#endif

// --------------------------------------------------
// Global variables, defined in main.c
// output comparison file
extern FILE *out_file;

// author of the Excel comparison report
extern char author[];
extern char company[];

// Current date, for example "2004-11-13T23:44:40Z"
extern char current_date[21];

extern char version[];

// --------------------------------------------------
// Global variables, defined in cmp_out.c

// Cell value when no result from the report
#define NO_RESULT_STRING	"No result."
#define FAIL_STRING         "FAIL"
#define FAIL_STRLEN			4
#define MISSING_VALUES      ""

// Ids fore styles
#define PERCENT_STYL_ID      "s100"
#define GOOD_PERCENT_STYL_ID "s101"
#define BAD_PERCENT_STYL_ID	 "s102"
#define FAIL_STYL_ID         "s103"
#define BOLDCENTER_STYL_ID   "s104"

#define SMALLER_GOOD_PERTHOUSANDAGE (__int64)(-1)
#define SMALLER_BAD_PERTHOUSANDAGE  (__int64)(+1)


/**************************************************************************************************************************
* FUNCTION:     xml_versions
*
* DESCRIPTION:  Writes versions sheet in an XML Excel file
*
* INPUTS:       global "out_file" stream already opened,
*
*               h: history result of the parsing
*
* OUTPUTS:      versions sheet in global "out_file" stream.
*
* RETURNS:      none
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         26 November 2004
***************************************************************************************************************************/
void xml_versions(t_history h);


/**************************************************************************************************************************
* FUNCTION:     xml_header
*
* DESCRIPTION:  Writes the XML header for an Excel file
*
* INPUTS:       cmp_data[nb_cmp_data]: 
*               A list per {host_type x test_name x cc_options x target x argv} of {report_ptr x test_ptr x exec_ptr}
*               where list is sorted by report_ptr -> run_id
*
*               global "out_file" stream already opened
*
* OUTPUTS:      does the comparison loop using the pointer to function : access_fct
*               and writing to out_file
*
* RETURNS:      none
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         10 November 2004
***************************************************************************************************************************/
void xml_header();

// -----------------------------------------------------------------------------------------------------------------------
// Opens a worksheet of given name
void xml_open_worksheet(const char *sheet_name);

// -----------------------------------------------------------------------------------------------------------------------
// Close current worksheet
void xml_close_worksheet();


/**************************************************************************************************************************
* FUNCTION:     xml_output
*
* DESCRIPTION:  Writes results comparison between test sessions in an XML Excel file
*
* INPUTS:       purpose: string telling comparison purpose (speed / size / cc duration, ...)
*               cmp_data[nb_cmp_data]: 
*               A list per {host_type x test_name x cc_options x target x argv} of {report_ptr x test_ptr x exec_ptr}
*               where list is sorted by report_ptr -> run_id
*
*               global "out_file" stream already opened
*
* OUTPUTS:      does the comparison loop using the pointer to function : access_fct
*               and writing to out_file
*
* RETURNS:      none
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         10 November 2004
***************************************************************************************************************************/
void xml_output(const char *purpose, const t_comparison_data cmp_data, const int nb_cmp_data);


