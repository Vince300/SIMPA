/************************************************************************************************************************/
/* CMP_FUNCTIONS HEADER                                                                                                 */
/*                                                                                                                      */
/* AUTHORS : Yves GUERTE, 30 August 2004                                                                                */
/*                                                                                                                      */
/* CONTENT : Functions that handle history of reports									*/
/*                                                                                                                      */
/* 															*/
/*															*/
/************************************************************************************************************************/
#ifndef __CMP_FUNCTIONS__
#define __CMP_FUNCTIONS__

#include "common_yacc_lex.h"
#include "util.h"

/* ----------------------------------------------------*/
// CONFIGURATION VARIABLES


/**************************************************************************************************************************
* FUNCTION:     split_cc_opt
*
* DESCRIPTION:  split a string containing CC options into an array of its sbustrings
*               
*
* INPUTS:       cc_opt is a string containing the CC options
*               cc_options_tab is an empty array of strings
*
* OUTPUTS:      cc_options_tab is an array of strings, will contain substrings recognized in cc_opt
*               p_nb_cc_options is the pointer to the number of substrings in cc_options_tab
*
* RETURNS:      
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         30 August 2004
***************************************************************************************************************************/
// Maximum number of substrings of cc_opt
#define MAX_NB_CC_OPTIONS 50

void split_cc_opt(const char * cc_opt, char *cc_options_tab[MAX_NB_CC_OPTIONS], int *p_nb_cc_options);


/**************************************************************************************************************************
* FUNCTION:     norm_cc_opt
*
* DESCRIPTION:  Normalize a list of CC options:
*		split the input string accordingly to the space char, handling substrings surrounded by '"' or "'"
*
* INPUTS:       The string containing the CC options
*
* OUTPUTS:      
*
* RETURNS:      Input string where all substrings are sorted alphabetically
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         30 August 2004
***************************************************************************************************************************/
// Separator char inserted between each subchar recognized
#define SEP_CHAR ','

t_cc_options norm_cc_opt(t_cc_options cc_opt) ;


/**************************************************************************************************************************
* FUNCTION:     common_tests
*
* DESCRIPTION:  search all tests with common properties that can be compared.
*		 
*
* INPUTS:       A test sessions history
*
* OUTPUTS:      
*
* RETURNS:      In comparison_data[nb_comparison_data] global variables: 
*               A list per {host_type x test_name x cc_options x target x argv} of {report_ptr x test_ptr x exec_ptr}
*               
*               where list is sorted by report_ptr -> run_id
*               // prop suppressed: where  (report_ptr -> run_id)  exists for all {host_type x test_name x cc_options x target x argv}
*
*               In all_run_ids[nb_run_ids] the sorted list of all run_ids
*		-----------------------------------------------------------------------------------------------------------
*               report_ptr -> run_id							(EXCEL <= run_id)
*		report_ptr -> test_list incl test_ptr
*		
*		test_ptr   -> test_name, cc_options					(EXCEL <= test_name, cc_options)
*		test_ptr   -> host_name
*		
*		report_ptr -> compiler_version_list incl {host_type x host_name}	(EXCEL <= host_type)
*		test_ptr -> exec_list incl exec_ptr
*		
*		exec_ptr -> target, description, input, argv, size, cycles		(EXCEL <= description, input, size|cycles)
*		-----------------------------------------------------------------------------------------------------------
*
*		Algorithm:
*			build the list per {host_type x test_name x cc_options x target x argv} of {report_ptr x test_ptr x exec_ptr}
*			prop suppressed: then removes {host_type x test_name x cc_options x target x argv} elements for report_ptr -> run_id
*			that are not everywhere.
*
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         30 August 2004
***************************************************************************************************************************/
// Maximum number of lines in a comparison table (max of #{host_type x test_name x cc_options x target x argv})
#define MAX_NB_RUN_ID		25

typedef struct s_cmp_fields {
	t_host_type		host_type;
	t_test_name		test_name;
	t_test_path     test_path; // To prevent pb when 2 different tests have the same name
	t_cc_options	cc_options;
	t_cc_options	norm_cc_options;
	t_target		target;
	t_argv			argv;
} s_cmp_fields, *t_cmp_fields;

typedef struct s_exec_dataref {
	t_run_id		run_id;
	t_exec			exec;
	struct s_exec_dataref	*next;
} s_exec_dataref, *t_exec_dataref;

typedef t_run_id	*t_all_run_ids;

// Result of the common_tests subroutine (global variables)
// Will contain the sorted -unique list of all run_id's of all the reports
extern t_all_run_ids	all_run_ids;
extern int				nb_run_ids;

typedef struct s_info_exec {
	t_cmp_fields		cmp_fields;    // criterium fields
	t_exec_dataref		exec_dataref;  // all exec data for the criterium fields
	t_all_run_ids		all_run_ids;   // all run_id's for the criterium fields
	int					nb_run_ids;    // number of # run_id's
} s_info_exec, *t_info_exec;

typedef s_info_exec *t_comparison_data;

// Result of the common_tests subroutine (global variables)
// Will contain exec results to compare, with comparison criterions as entries
extern t_comparison_data comparison_data;
extern int		  nb_comparison_data;

// described subroutine
void common_tests(t_history h);


/**************************************************************************************************************************
* FUNCTION:     search_host_type
*
* DESCRIPTION:  search the host_type corresponding to a host_name, looking in the compiler versions data.
*		 
*
* INPUTS:       t_compiler_versions vs : compiler tools versions, with hostname and associated hosttype
*		t_host_name h : the hostname
*
* OUTPUTS:      
*
* RETURNS:      the hosttype associated to the hostname if found in the compiler tools versions, else NULL.
*               
*
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         30 August 2004
***************************************************************************************************************************/
t_host_type search_host_type(const t_compiler_versions vs, const t_host_name h);



/**************************************************************************************************************************
* FUNCTION:     access_crit
*
* DESCRIPTION:  Returns each field value of the record of the comparison criterions
*
* INPUTS:       The index if the comparison criterion
*
* OUTPUTS:      
*
* RETURNS:      The string value of the comparison criterion[
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         17 November 2004
***************************************************************************************************************************/
// NB_CRITERION == #(host_type x test_name x [target + argv] x cc_options)
#define NB_CRITERION 4

// Returns the strings that are the 
char * access_crit(const t_cmp_fields cmp_fields, const int i_field);



#endif
// endif __CMP_FUNCTIONS__
