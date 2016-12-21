/************************************************************************************************************************/
/* MAIN MODULE                                                                                        			*/
/*                                                                                                                      */
/* AUTHORS : Yves GUERTE, July 2004                                                                                     */
/*                                                                                                                      */
/* CONTENT :                                                                                                            */
/*                                                                                                                      */
/* 															*/
/*															*/
/************************************************************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include "common_yacc_lex.h"
#include "cmp_functions.h"
#include "compiler_support.h"
#include "qa_xml.h"
#include "cmp_out.h"

#ifdef  DEBUG_main
#define DEBUG_main_printf(x...) fprintf(stderr, x)
#else
#define DEBUG_main_printf(x...) {}
#endif


// ------------------------------------------------
// Next used in common_yacc_lex
FILE *log_file;
char *current_file_name;
int line_num;
int Always_Exit = 0;
int nb_common_yacc_lex_errors = 0;

// Result of the parsing
t_history result_history;
//
int nb_execs = 0;

// ------------------------------------------------
// Next used in cmp_out
FILE *out_file;

// author of the Excel comparison report
char author[]  = "qatools";
char company[] = "Freescale";

// Current date, for example "2004-11-13T23:44:40Z"
// will be initialized in main
char current_date[21];

char version[] = "1.0";
// ------------------------------------------------


// symbolic compiler name
// used to switch functions in cmp_fields
static t_compiler default_cc = e_scc ;

/**************************************************************************************************************************
* FUNCTION:     errlog
*
* DESCRIPTION:  Log errors in the file log_file, if Always_exit is set, quit
*		program on error
*
* INPUTS:
*
* OUTPUTS:
*
* RETURNS:
***************************************************************************************************************************
* RESTRICTIONS:
*
* BUGS:
***************************************************************************************************************************
* AUTHOR:       YGT
*
* DATE:
***************************************************************************************************************************/
const int nb_max_common_yacc_lex_errors = 50;

void errlog(char *s1, ...) {
        va_list	par_list	= {};
        va_start(par_list, s1);
        vfprintf(log_file, s1, par_list);
        vfprintf(stderr,   s1, par_list);
        va_end(par_list);
        if(nb_common_yacc_lex_errors++ > nb_max_common_yacc_lex_errors) {
            fprintf (stderr,"\nToo much errors, exiting.\n\n");
            exit(1);
        }
        if(Always_Exit) exit(1);
}



/**************************************************************************************************************************
* FUNCTION:     man
*
* DESCRIPTION:  gives the answer to the -help parameter
*
* INPUTS:
*
* OUTPUTS:      answer to the -help parameter on STDOUT
*
* RETURNS:
***************************************************************************************************************************
* RESTRICTIONS:
*
* BUGS:
***************************************************************************************************************************
* AUTHOR:       YGT
*
* DATE:
***************************************************************************************************************************/
static void man(char *progname) {
    
    fprintf(stdout, "%s options:\n", progname);
    fprintf(stdout, "\t-help          : this message.\n");
    fprintf(stdout, "\t-o  <filename> : the xml excel result.\n");
    fprintf(stdout, "\t-cc <compiler> : among gcc, scc, ppc, mwccarm, armcc, gccarm, win32_x86, dsp56800e, mac_ppc, dsp56800.\n");
    fprintf(stdout, "\t                 'scc' is default parameter.\n");
    fprintf(stdout, "\t-e             : to exit at the first parsing error.\n");
    fprintf(stdout, "\t<filename>     : the xml report history input file.\n");
    fprintf(stdout, "\n");
}

/***************************************************************************************************************************
* FUNCTION:     main
*
* DESCRIPTION:	Main program
*
* INPUTS:
*
* OUTPUTS:
*
* RETURNS:
****************************************************************************************************************************
* RESTRICTIONS:
*
* BUGS:
****************************************************************************************************************************
* AUTHOR:       Yves GUERTE
*
* DATE:
****************************************************************************************************************************/
int main(int argc, char *argv[]) {
        
        // status returned
        int status = 0;
        
        char *progname = basename(argv[0]);
        
		// Current_date (example: "2004-11-13T23:44:40Z")
		char current_date[21];
		time_t calentime = time(NULL);
		struct tm *ltime = localtime(&calentime);
		size_t len_current_date = strftime(current_date,20,"%Y-%m-%dT%H:%M%SZ",ltime);
        
        // -------- Parameters possible options
        // input filename
        char *in_fname = NULL;
        
        // output filename
        char *out_fname = NULL;
        
        // symbolic compiler name
        t_compiler cc = default_cc;
        // -------- end of Parameters possible options
        
        // parameters parsing status
        int params_error = 0;
        
        log_file = fopen("errlog.log","w");
        if (log_file == NULL) {
            fprintf(stderr, "ERROR: cannot open errlog.log\n\n");
        }
        
        // No parameter
        if (argc == 1) {
            man(progname);
            exit(1);
        }
        
        fprintf(stderr, "\nStart Parsing command line ...\n\n");
        
        while(--argc > 0) {
                ++argv;
                if (strcmpil((*argv), "-cc") == 0) {
                        if (--argc > 0) {
                               ++argv;
                               // gcc, scc, ppc, mwccarm, armcc, gccarm, win32_x86, dsp56800e, mac_ppc, dsp56800
                               if        (strcmpil((*argv), "gcc")       == 0) { cc=e_gcc       ; fprintf(stderr, "Parameter -cc %s OK\n", *argv);
                               } else if (strcmpil((*argv), "scc")       == 0) { cc=e_scc       ; fprintf(stderr, "Parameter -cc %s OK\n", *argv);
                               } else if (strcmpil((*argv), "ppc")       == 0) { cc=e_ppc       ; fprintf(stderr, "Parameter -cc %s OK\n", *argv);
                               } else if (strcmpil((*argv), "mwccarm")   == 0) { cc=e_mwccarm   ; fprintf(stderr, "Parameter -cc %s OK\n", *argv);
                               } else if (strcmpil((*argv), "armcc")     == 0) { cc=e_armcc     ; fprintf(stderr, "Parameter -cc %s OK\n", *argv);
                               } else if (strcmpil((*argv), "gccarm")    == 0) { cc=e_gccarm    ; fprintf(stderr, "Parameter -cc %s OK\n", *argv);
                               } else if (strcmpil((*argv), "win32_x86") == 0) { cc=e_win32_x86 ; fprintf(stderr, "Parameter -cc %s OK\n", *argv);
                               } else if (strcmpil((*argv), "dsp56800e") == 0) { cc=e_dsp56800e ; fprintf(stderr, "Parameter -cc %s OK\n", *argv);
                               } else if (strcmpil((*argv), "mac_ppc")   == 0) { cc=e_mac_ppc   ; fprintf(stderr, "Parameter -cc %s OK\n", *argv);
                               } else if (strcmpil((*argv), "dsp56800")  == 0) { cc=e_dsp56800  ; fprintf(stderr, "Parameter -cc %s OK\n", *argv);
                               } else {
                                       errlog("-cc parameter value unknown: %s.\n", *argv);
                                       params_error = 1;
                               }
                        }
                        else {
                               fprintf(stderr, "-cc parameter is missing.\n");
                               params_error = 1;
                        }
                } else if (strcmpil((*argv), "-o") == 0) {
                        if (--argc > 0) {
                        	++argv;
                        	out_fname = strdup(*argv);
                        }
                } else if (strcmpil((*argv), "-e") == 0) {
                               fprintf(stderr, "Always_Exit OK\n");
                               Always_Exit=1;
                } else if ((strcmpil((*argv), "-h") == 0)
                           || (strcmpil((*argv), "-help") == 0)
                           || (strcmpil((*argv), "--help") == 0)) {
                               man(progname);
                               exit(0);
                }
                else if (*argv[0] == '-') {
                        errlog("Unknown option %s\n", *argv);
                        params_error = 1;
                }
                else {
                        in_fname=*argv;
                }

        }
        fprintf(stderr, "\nFinish Persing command line ...\n\n");
        
        
        
// ------------------------------------------------
        // We verify the parameters and open output file
        if ((params_error == 1) && (Always_Exit = 1)) return 1;
        
        if (in_fname == NULL) {
        	errlog("I need an input filename.");
        }
        if (out_fname == NULL) {
        	out_file = stdout;
        }
        else {
        	out_file = fopen(out_fname,"w");
        	
        	if (out_file == NULL) {
                errlog("ERROR: cannot open %s\n", out_fname);
        	    fclose(log_file);
        	    return 1;
            }

        }
        
// ------------------------------------------------
        // Initialization of the internal structure that will contain the history
        result_history = empty_history();
#ifdef DBG
        yy1debug = 1;
#endif
        
        fprintf(stderr, "\nStart Parsing file %s ...\n\n", in_fname);
        status = parse_xml_hist(in_fname);
        fprintf(stderr, "\nFinish Parsing file %s with status %d.\n\n", in_fname, status);
        
#ifdef DEBUG_main
        DEBUG_main_printf("\nStart Dumping history ...\n\n");
        dump_history(result_history);
        DEBUG_main_printf("\nFinish Dumping history.\n\n");
#endif
// ------------------------------------------------
        fprintf(stderr, "\nStart searching common tests ...\n\n");
        // results will be in comparison_data[nb_comparison_data] global variables
        common_tests(result_history);
        fprintf(stderr, "\nFinish searching common tests.\n\n");
        
        
// ------------------------------------------------
        // We generate header
        xml_header();
        
        // We begin the comparison for speed
        fprintf(stderr, "\nStart comparison for speed...\n\n");
        //
        set_access_fct(cc, e_speed);
        xml_output("SPEED", comparison_data, nb_comparison_data);
        
        
        // We begin the comparison for size
        fprintf(stderr, "\nStart comparison for size...\n\n");
        //
        set_access_fct(cc, e_size);
        xml_output("SIZE", comparison_data, nb_comparison_data);
        
        // We generate versions sheet
        xml_open_worksheet("Versions");
        xml_versions(result_history);
        xml_close_worksheet();
        
        // We close all opened XML object
        pxml_until_tag_level(out_file,-1);
        fclose(out_file);
        fprintf(stderr, "\nFinish comparison.\n\n");

        // free_history(result_history);
        return(status);
}
