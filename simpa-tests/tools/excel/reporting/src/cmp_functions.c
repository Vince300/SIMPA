/************************************************************************************************************************/
/* CMP_FUNCTIONS MODULE                                                                                                 */
/*                                                                                                                      */
/* AUTHORS : Yves GUERTE, 30 August 2004                                                                                */
/*                                                                                                                      */
/* CONTENT : Functions that handle history of reports                                                                   */
/*                                                                                                                      */
/* 															*/
/*															*/
/************************************************************************************************************************/
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include "util.h"
#include "cmp_functions.h"

#ifdef  DEBUG_norm_cc_opt
#define DEBUG_norm_cc_opt_printf(x...) fprintf(stderr, x)
#else
#define DEBUG_norm_cc_opt_printf(x...) {}
#endif

#ifdef  DEBUG_common_tests
#define DEBUG_common_tests_printf(x...) fprintf(stderr, x)
#else
#define DEBUG_common_tests_printf(x...) {}
#endif



// #define malloc(s) my_malloc(s, __LINE__)

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
void split_cc_opt(const char * cc_opt, char *cc_options_tab[MAX_NB_CC_OPTIONS], int *p_nb_cc_options) {
        char *found, *buffer;
        char onechar[1] = " ";
        const char *i_opt = cc_opt;
        
        *p_nb_cc_options = 0;
        while (*i_opt) {
                // We skip space and tab chars
                while (*i_opt) {
                        // We stop if current char is not in {' ','\t'}
                        if (strchr(" \t", i_opt[0]) == NULL) break;
                        i_opt++;
                }
                if (i_opt[0] == '\0') break;
                
                // if it begins with a quote or double quote
                if (strchr("'\"", i_opt[0]) != NULL) {
                        onechar[0] = i_opt[0];
                        found = strpbrk(&i_opt[1], onechar);
                        if (found != NULL) {
                                buffer = malloc(sizeof(char) * (found - i_opt));
                                strncpy(buffer, &i_opt[1], found - i_opt - 1);
                                buffer[found - i_opt - 1] = '\0';

                                DEBUG_norm_cc_opt_printf("%s\n", buffer);

                                cc_options_tab[(*p_nb_cc_options)++] = buffer;
                                i_opt = found + 1;
                        }
                        else {

                                DEBUG_norm_cc_opt_printf("%s\n", i_opt);

                                cc_options_tab[(*p_nb_cc_options)++] = strdup(i_opt);
                                i_opt = i_opt + strlen(i_opt);
                        }
                }
                else {
                        found = strpbrk(i_opt, " \t");
                        if (found != NULL) {
                                buffer = malloc(sizeof(char) * (found - i_opt + 1));
                                strncpy(buffer, i_opt, found - i_opt);
                                buffer[found - i_opt] = '\0';

                                DEBUG_norm_cc_opt_printf("%s\n", buffer);

                                cc_options_tab[(*p_nb_cc_options)++] = buffer;
                                i_opt = found + 1;
                        }
                        else {

                                DEBUG_norm_cc_opt_printf("%s\n", i_opt);

                                cc_options_tab[(*p_nb_cc_options)++] = strdup(i_opt);
                                i_opt = i_opt + strlen(i_opt);
                        }
                }
        } // end while (*i_opt)
} // end split_cc_opt




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
t_cc_options norm_cc_opt(t_cc_options cc_opt) {
        
        // Will contain the returned string
        t_cc_options   result ;
        
        // Will contain pointers to (duplicated) substrings of cc_opt
        t_cc_options    cc_options_tab[MAX_NB_CC_OPTIONS];
        // Will contain the number of substrings of cc_opt
        int  nb_cc_options = 0;
        
        // tmp vars
        int   i;
        char *s, *sc;
        
        // --------------------------------------------------------------------        
        // Real beginning of norm_cc_opt
        
        // We extract substrings => cc_options_tab
        split_cc_opt(cc_opt, cc_options_tab, &nb_cc_options);
        
        // We sort cc_options_tab alphabetically
        qsort(cc_options_tab, nb_cc_options, sizeof(t_cc_options), &strp_cmp);
        
        // We allocate the size of the returned string (size exceed by the number of repeated space char)
        result = malloc(sizeof(char) * (strlen(cc_opt) + nb_cc_options + 1));
        
        // We build the returned string by concatenation of the sorted substrings
        s = result;
        for (i=0; i < nb_cc_options; i++) {
                sc = cc_options_tab[i];
                while (*sc) {
                        *s = *sc;
                        s++; sc++;
                }
                *(s++) = SEP_CHAR;

                DEBUG_norm_cc_opt_printf("%s\n", cc_options_tab[i]);

                free(cc_options_tab[i]);
        }
        if (nb_cc_options != 0) s--;
        *s = '\0';
        return result;
} // end norm_cc_opt



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
*       report_ptr -> run_id							(EXCEL <= run_id)
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
*			and then removes {host_type x test_name x cc_options x target x argv} elements for report_ptr -> run_id
*			that are not everywhere.
*
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         30 August 2004
***************************************************************************************************************************/

// Result of the common_tests subroutine (global variables)
// Will contain the sorted -unique list of all run_id's of all the reports
t_all_run_ids	all_run_ids = NULL;
int				nb_run_ids = 0;

// Result of the common_tests subroutine (global variables)
// Will contain exec results to compare, with comparison criterions as entries
t_comparison_data comparison_data;
int		  nb_comparison_data = 0;



// comparison of two cmp_fields, needed to launch qsort on the comparison_data array
static int cmp_fields_cmp(const void *s1, const void *s2) {
        t_cmp_fields cmp_fields1 = ((s_info_exec*)s1)->cmp_fields;
        t_cmp_fields cmp_fields2 = ((s_info_exec*)s2)->cmp_fields;
        
        t_cc_options cc1 = NULL;
        t_cc_options cc2 = NULL;
        int r;
        
#define allstrcmp(a,b) ( (a == NULL) ? ( (b == NULL) ? 0 : -1) : ( (b == NULL) ? 1 : strcmp(a,b)))
 
        if ((r = allstrcmp(cmp_fields1->host_type, cmp_fields2->host_type)) == 0 )
                if ((r = allstrcmp(cmp_fields1->test_name, cmp_fields2->test_name)) == 0 )
                        if ((r = allstrcmp(cmp_fields1->target, cmp_fields2->target)) == 0 )
                                if ((r = allstrcmp(cmp_fields1->argv, cmp_fields2->argv)) == 0 )
                                        r = allstrcmp(cmp_fields1->cc_options, cmp_fields2->cc_options);
        return r;
} // end cmp_fields_cmp




// search an element of the comparison_data array whose cmp_fields field match with the one in parameter
// and return a pointer to it (a pointer to s_info_exec, that is t_info_exec)
static t_info_exec srch_cmp_data(s_info_exec infos_exec) {
        return (t_info_exec)bsearch(&infos_exec, comparison_data, nb_comparison_data, sizeof(s_info_exec), &cmp_fields_cmp);
} // end srch_cmp_data




void common_tests(t_history h) {
        
        // Temporary variables for loops...
        t_reports       rs;
        t_tests         ts;
        t_execs         es;
        
        int             i, j, ok;
        
        // local pointer to cmp_fields, exec_dataref, info_exec
        t_cmp_fields    lp_cmp_fields   = NULL;
        t_exec_dataref  lp_exec_dataref = NULL;
        t_info_exec     lp_info_exec    = NULL;
        
        // handler to exec_dataref
        t_exec_dataref  *lpp_exec_dataref = NULL;
        
        // Will contain the sorted -unique list of all run_id's of all the reports
        all_run_ids = malloc(sizeof(t_run_id) * h->nb_reports);
        
        // We allocate the maximum number of comparison lines
        comparison_data = malloc(sizeof(s_info_exec) * nb_execs);
        
        // We build an array of all the execs
        // and keep list of all run_ids
        for (rs = h->reports; rs != NULL; rs = rs->next) {

                DEBUG_common_tests_printf("run_id==%s\n", rs->report->run_id); //debug

                // if run_id is not known
                if (bsearch(&rs->report->run_id, all_run_ids, nb_run_ids, sizeof(t_run_id), &strp_cmp) == NULL ) {
                        
                        // We add it
                        all_run_ids[nb_run_ids++] = rs->report->run_id;
                        qsort(all_run_ids, nb_run_ids, sizeof(t_run_id), &strp_cmp);
                }
                
                else {
                
                /* We allow multiple reports with same run_id for distributed tests
                        errlog("ERROR: a report with run_id '%s' appears 2 times. Second one skipped.\n", rs->report->run_id);
                        continue;
                */
                        
                }
                                        
                for (ts = rs->report->tests; ts != NULL; ts = ts->next) {

                        DEBUG_common_tests_printf("test_name==%s\n", ts->test->test_name); //debug

                        for (es = ts->test->execs; es != NULL; es = es->next) {

                                DEBUG_common_tests_printf("descr==%s\n", es->exec->description); //debug

                                lp_cmp_fields = malloc(sizeof(s_cmp_fields));
                                *lp_cmp_fields =
                                     ((struct s_cmp_fields) {
                                         .host_type       = search_host_type(rs->report->compiler_versions, ts->test->host_name),
                                         .test_name       = ts->test->test_name,
                                         .test_path       = ts->test->test_path,
                                         .cc_options      = ts->test->cc_options,
                                         .norm_cc_options = norm_cc_opt(ts->test->cc_options),
                                         .target          = es->exec->target,
                                         .argv            = es->exec->argv
                                      });

                                // We search exec_dataref with same comparison fields values in the comparison_data array
                                lp_info_exec = srch_cmp_data(((s_info_exec){.cmp_fields = lp_cmp_fields,
                                                                             .exec_dataref = NULL,
                                                                             .all_run_ids = NULL,
                                                                             .nb_run_ids = 0}));
                                
                                // If no exec has been found with same comparison fields
                                // we create the comparison fields
                                if (lp_info_exec == NULL) {
                                        // For update (that follows) of this added item
                                        // lp_info_exec contains either the found item or the created one
                                        lp_info_exec = &comparison_data[nb_comparison_data];
                                        nb_comparison_data++;
                                        
                                        *lp_info_exec =
                                                ((struct s_info_exec) {
                                                        .cmp_fields     = lp_cmp_fields,
                                                        .exec_dataref   = NULL,                          // filled after "if" block end
                                                        .all_run_ids    = malloc(sizeof(t_run_id) * h->nb_reports),
                                                        .nb_run_ids     = 1                              // all_run_ids 1st el. filled just after
                                                });
                                        lp_info_exec->all_run_ids[0] = rs->report->run_id;
                                }
                                else {
                                        free(lp_cmp_fields);
                                        lp_cmp_fields = NULL;
                                }
                                
                                lp_exec_dataref  = malloc(sizeof(s_exec_dataref));
                                *lp_exec_dataref =
                                     ((struct s_exec_dataref) {
                                             .run_id = rs->report->run_id,
                                             .exec   = es->exec,
                                             .next   = lp_info_exec->exec_dataref
                                      });

                                // We search where to insert the lp_info_exec
                                lpp_exec_dataref = &(lp_info_exec->exec_dataref);
                                
                                i = 1;
                                while (*lpp_exec_dataref != NULL) {
                                        if ((i = strcmp(rs->report->run_id, (*lpp_exec_dataref)->run_id)) <= 0) {
                                                break;
                                        }
                                        else {
                                                lpp_exec_dataref = &((*lpp_exec_dataref)->next);
                                        }
                                }
                                // If same run_id, same result means duplication
                                if (i == 0) {
                                    if ((strcmp(es->exec->status, (*lpp_exec_dataref)->exec->status) == 0)
                                        &&
                                         ((strcmp(es->exec->size, (*lpp_exec_dataref)->exec->size) == 0)
                                          &&
                                          (strcmp(es->exec->cycles, (*lpp_exec_dataref)->exec->cycles) == 0))) {
                                        
                                        errlog ("WARNING: same results with run_id==%s appear again for same criterions:\n", rs->report->run_id);
                                        errlog("test_name==%s, descr==%s\n", ts->test->test_name, es->exec->description);
                                        // DEBUG errlog("norm_cc_options==%s\n\n",lp_info_exec->cmp_fields->norm_cc_options);
                                        errlog("cc_options==%s\n\n",ts->test->cc_options);
                                    }
                                    else {
                                        // if same version of the test
                                        if (same_dirname(lp_info_exec->cmp_fields->test_path, ts->test->test_path) == 1) {
                                            errlog ("ERROR: different results with run_id==%s for same criterions\n", rs->report->run_id);
                                            errlog("test_name==%s, descr==%s\n", ts->test->test_name, es->exec->description);
                                            // DEBUG errlog("norm_cc_options==%s\n\n",lp_info_exec->cmp_fields->norm_cc_options);
                                            errlog("cc_options==%s\n\n",ts->test->cc_options);
                                        }
                                        else {
                                            errlog ("ERROR: run_id==%s: same '%s' test name but different test versions.\n\n", rs->report->run_id, ts->test->test_name);
                                        }
                                    }
                                }
                                else {
                                    
                                    // We add the compared data
                                    lp_exec_dataref->next = *lpp_exec_dataref;
                                    *lpp_exec_dataref = lp_exec_dataref;
                                                                    
                                    // if run_id of this exec is not known for this comparison set
                                    if (bsearch(&rs->report->run_id, lp_info_exec->all_run_ids, lp_info_exec->nb_run_ids, sizeof(t_run_id), &strp_cmp) == NULL ) {
                                            
                                            // We add it
                                            lp_info_exec->all_run_ids[lp_info_exec->nb_run_ids++] = rs->report->run_id;
                                            qsort(lp_info_exec->all_run_ids, lp_info_exec->nb_run_ids, sizeof(t_run_id), &strp_cmp);
                                    }
                                    
                                    // We sort the comparison_data array if new element has been added to comparison_data
                                    if (lp_cmp_fields != NULL) {
                                            qsort(comparison_data, nb_comparison_data, sizeof(s_info_exec), &cmp_fields_cmp);
                                    }
                                }
                        }
                }
        }
        
#ifdef DEBUG_common_tests
                                DEBUG_common_tests_printf("\nAll run_id's : ");
                                for (j=0; j < nb_run_ids; j++) {
                                        DEBUG_common_tests_printf("%s ", all_run_ids[j]);
                                }
                                DEBUG_common_tests_printf("\n");
#endif

        // We remove comparison_data[i] when one item does not have all run_id's of the run_ids array
        for (i = nb_comparison_data - 1; i >= 0; i--) {
                
                qsort(comparison_data[i].all_run_ids, comparison_data[i].nb_run_ids, sizeof(t_run_id), &strp_cmp);
        
                DEBUG_common_tests_printf("comparison_data[%d].cmp_fields->host_type  == %s\n", i, comparison_data[i].cmp_fields->host_type  );
                DEBUG_common_tests_printf("comparison_data[%d].cmp_fields->test_name  == %s\n", i, comparison_data[i].cmp_fields->test_name  );
                DEBUG_common_tests_printf("comparison_data[%d].cmp_fields->cc_options == %s\n", i, comparison_data[i].cmp_fields->cc_options );
                DEBUG_common_tests_printf("comparison_data[%d].cmp_fields->target     == %s\n", i, comparison_data[i].cmp_fields->target     );
                DEBUG_common_tests_printf("comparison_data[%d].cmp_fields->argv       == %s\n", i, comparison_data[i].cmp_fields->argv       );

                for (lp_exec_dataref = comparison_data[i].exec_dataref; 
                     lp_exec_dataref != NULL ;
                     lp_exec_dataref = lp_exec_dataref->next) {

                        DEBUG_common_tests_printf("<run_id>%s</run_id>\n", lp_exec_dataref->run_id);
                        DEBUG_common_tests_printf("<cycles>%s</cycles>\n", lp_exec_dataref->exec->cycles);

                        // We compare the list of run_ids
                        ok = (nb_run_ids == comparison_data[i].nb_run_ids);
                        j = 0;
                        while (ok && (j < nb_run_ids)) {
                                ok = (strcmp(all_run_ids[j], comparison_data[i].all_run_ids[j]) == 0);
                                j++;
                        }
                        if (! ok) {
#ifdef DEBUG_common_tests
                                DEBUG_common_tests_printf("comparison_data[%d] is not suppressed, but appears only in the reports with these run_id's : ", i);
                                for (j=0; j < comparison_data[i].nb_run_ids; j++) {
                                        DEBUG_common_tests_printf("%s ", comparison_data[i].all_run_ids[j]);
                                }
                                DEBUG_common_tests_printf("\n");
#endif
                                // We could here remove comparison_data[i] in such way:
                                /*
                                free(comparison_data[i].cmp_fields);
                                free(comparison_data[i].exec_dataref);
                                free(comparison_data[i].all_run_ids);
                                for (j = i; j < nb_comparison_data; j++) {
                                        comparison_data[j] = comparison_data[j+1];
                                }
                                nb_comparison_data--;
                                */
                        }
                }
        }
        return;
} // end common_tests



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
t_host_type search_host_type(const t_compiler_versions vs, const t_host_name h) {
        t_host_type             res = NULL;
        t_compiler_versions     vsl= vs;
        
        while (vsl != NULL) {
                if (strcmp(vsl->compiler_version->host_name, h) == 0) {
                        res = vsl->compiler_version->host_type;
                        vsl = NULL;
                }
                else {
                        vsl = vsl->next;
                }
        }
        return res;
} // end search_host_type



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
// NB_CRITERION == 4 == #(host_type x test_name x [target + argv] x cc_options)

static char * access_crit_0(const t_cmp_fields cmp_fields) {
        if (cmp_fields->host_type == NULL) {
            return strdup("");
        }
        else {
            return strdup(cmp_fields->host_type);
        }
}
static char * access_crit_1(const t_cmp_fields cmp_fields) {
        if (cmp_fields->test_name == NULL) {
            return strdup("");
        }
        else {
            return strdup(cmp_fields->test_name);
        }
}
static char * access_crit_2(const t_cmp_fields cmp_fields) {
        int  l1;
        char *s1, *s2, *s;
        
        s1 = (cmp_fields->target == NULL) ? "" : cmp_fields->target;
        s2 = (cmp_fields->argv   == NULL) ? "" : cmp_fields->argv;
        
        l1 = strlen(s1);
        s = malloc(sizeof(char) * (l1 + strlen(s2) + 2));
        
        strcpy(s,          s1);
        s[l1] = ' ';
        strcpy(s + l1 + 1, s2);
            
        return(s);
}
static char * access_crit_3(const t_cmp_fields cmp_fields) {
        if (cmp_fields->cc_options == NULL) {
            return strdup("");
        }
        else {
            return strdup(cmp_fields->cc_options);
        }
}

static char * ((*p_access_crit[NB_CRITERION])(const t_cmp_fields cmp_fields)) 
        = {
        &access_crit_0, &access_crit_1, &access_crit_2, &access_crit_3
        };


// Returns the strings that are the 
char* access_crit(const t_cmp_fields cmp_fields, const int i_field) {

        assert(( 0 <= i_field) && (i_field < NB_CRITERION));	
        
        return p_access_crit[i_field](cmp_fields);
}

























