/************************************************************************************************************************/
/* COMPILER_SUPPORT MODULE                                                                                              */
/*                                                                                                                      */
/* AUTHORS : Yves GUERTE, 12 September 2004                                                                             */
/*                                                                                                                      */
/* CONTENT : Functions that set the access to the data compared between tests						*/
/*                                                                                                                      */
/* 															*/
/*															*/
/************************************************************************************************************************/
#include <time.h>
#include "compiler_support.h"

// To allow enumeration output
char * t_compiler_image[] = {"gcc", "scc", "ppc", "mwccarm", "armcc", "gccarm", "win32_x86", "dsp56800e", "mac_ppc", "dsp56800"};

// To allow enumeration output
char * t_cmp_purpose_image[] = {"size", "speed", "cc_speed"};


/************************************************************************************************************************/
/* Access to fields in history:																							*/
/* Same for all compilers                                                                                               */
/************************************************************************************************************************/

// function that returns the size field from an execution
static char *access_size(t_exec_dataref exec_dataref) {
        return exec_dataref->exec->size;
}

// function that returns the speed field from an execution
static char *access_cycles(t_exec_dataref exec_dataref) {
        return exec_dataref->exec->cycles;
}

// function that returns the compilation duration value
static char *access_make_duration(t_exec_dataref exec_dataref) {
        
        // cf K&R page 157
        
        // result including possible sign
        char *r = NULL;
        
        // End of t1 and t2
        // char *et1, *et2;
        
        // Does not yet exist: exec_dataref->make->start_date
        // long t1 = strtol(exec_dataref->make->start_date, &et1, 10);
        // long t2 = strtol(exec_dataref->make->end_date,   &et2, 10);
        
        // // return difftime(info_exec->end_date, info_exec->start_date);
        // // DEBUG saprintf(&r, "%ld", t2 - t1);
        return r;
}

/************************************************************************************************************************/
/* for SCC                                                                                                              */  
/************************************************************************************************************************/
static int is_for_size_purpose_scc(const t_cc_options cc_opt) {
        
        //returned status
        int r = 0;
        
        int i, j;
        
        // Will contain pointers to (duplicated) substrings of cc_opt
        t_cc_options    cc_options_tab[MAX_NB_CC_OPTIONS];
        // Will contain the number of substrings of cc_opt
        int  nb_cc_options = 0;
        
        // We extract substrings => cc_options_tab
        split_cc_opt(cc_opt, cc_options_tab, &nb_cc_options);
        
        for (i=0; i < nb_cc_options; i++) {
                if (strcmp(cc_options_tab[i], "-Os") == 0) {
                        r = 1;
                        for (j=i ; j < nb_cc_options; j++) {
                            free(cc_options_tab[j]);
                        }
                        break;
                }
                free(cc_options_tab[i]);
        }
        return r;
}

static int is_for_speed_purpose_scc(const t_cc_options cc_opt) {
        if (is_for_size_purpose_scc(cc_opt) == 1) {
            return 0;
        }
        else {
            return 1;
        }
}



/************************************************************************************************************************/
/* function that sets the access_fct and is_for_purpose values                                                          */  
/************************************************************************************************************************/

void set_access_fct(const t_compiler cc, const t_cmp_purpose cmp_purpose) {
        
        switch (cmp_purpose) {
                case e_size:     access_fct = &access_size;          break;
                case e_speed:    access_fct = &access_cycles;        break;
                case e_cc_speed: access_fct = &access_make_duration; break;
                        default: errlog("ERROR: set_access_fct with cmp_purpose=='%s' unknown.", t_cmp_purpose_image[cmp_purpose]);
                                 break;
        }
        
        switch (cmp_purpose) {
                case e_size:
                        switch (cc) {
                                case e_scc:
                                        is_for_purpose = &is_for_size_purpose_scc;
                                        break;
                                default: errlog("Not yet implemented: size comparison for %s compiler.", t_compiler_image[cc]);
                        }
                        break;
                case e_speed:
                        switch (cc) {
                                case e_scc:
                                        is_for_purpose = &is_for_speed_purpose_scc;
                                        break;
                                default: errlog("Not yet implemented: speed comparison for %s compiler.", t_compiler_image[cc]);
                        }
                        break;
                case e_cc_speed:
                        default: errlog("Not yet implemented: cc_speed comparison.");
                        break;
        }
        return;
}
                
