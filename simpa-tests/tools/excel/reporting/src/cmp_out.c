/************************************************************************************************************************/
/* CMP_OUT MODULE                                                                                                       */
/*                                                                                                                      */
/* AUTHORS : Yves GUERTE, 18 October 2004                                                                               */
/*                                                                                                                      */
/* CONTENT : Functions that output report comparison                                                                    */
/*                                                                                                                      */
/*                                                             */
/*                                                            */
/************************************************************************************************************************/
#include <stdio.h>
#include <assert.h>
#include "util.h"
#include "cmp_out.h"
#include "qa_xml.h"
#include "compiler_support.h"

#ifdef  DEBUG_cmp_out
#define DEBUG_cmp_out_printf(x...) fprintf(stderr, x)
#else
#define DEBUG_cmp_out_printf(x...) {}
#endif

// --------------------------------------------------
// Global variables



/**************************************************************************************************************************
* FUNCTION:     
*
* DESCRIPTION:  
*
* INPUTS:       
*
* OUTPUTS:      
*
* RETURNS:      
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         22 November 2004
***************************************************************************************************************************/

#define pxml_string_cell(stream, data, options...) \
    \
    pxml_begin_tag(stream, "Cell", options); \
    pxml_atomic_element(stream, "Data", data, "ss:Type", "String", NULL); \
    pxml_end_tag(stream, "Cell");


#define pxml_number_cell(stream, data, options...) \
    \
    pxml_begin_tag(stream, "Cell", options); \
    pxml_atomic_element(stream, "Data", data, "ss:Type", "Number", NULL); \
    pxml_end_tag(stream, "Cell");


#define pxml_formula_cell(stream, data, options...) \
    \
    pxml_atomic_element(stream, "Cell", "", "ss:Formula", data, options);

    

/**************************************************************************************************************************
* FUNCTION:     xml_header
*
* DESCRIPTION:  Writes the XML header for an Excel file
*
* INPUTS:       global "out_file" stream already opened
*
* OUTPUTS:      
*
* RETURNS:      none
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         10 November 2004
***************************************************************************************************************************/
void xml_header() {

    pxml_header(out_file);
    
    pxml_begin_tag(out_file, "Workbook",
                             "xmlns",     "urn:schemas-microsoft-com:office:spreadsheet",
                             "xmlns:o",   "urn:schemas-microsoft-com:office:office",
                             "xmlns:x",   "urn:schemas-microsoft-com:office:excel",
                              "xmlns:ss",  "urn:schemas-microsoft-com:office:spreadsheet",
                              "xmlns:html", "http://www.w3.org/TR/REC-html40", NULL);

    pxml_begin_tag(out_file, "DocumentProperties",
                             "xmlns", "urn:schemas-microsoft-com:office:office", NULL);

    pxml_atomic_element(out_file, "Author",     author,            NULL);
    pxml_atomic_element(out_file, "LastAuthor", author,            NULL);
    pxml_atomic_element(out_file, "Created",    current_date,    NULL);
    pxml_atomic_element(out_file, "LastSaved",  current_date,    NULL);
    pxml_atomic_element(out_file, "Company",    company,        NULL);
    pxml_atomic_element(out_file, "Version",    version,        NULL);
    
    pxml_end_tag(out_file, "DocumentProperties");
    
    // Styles --------------------------------------------------------------------------
    pxml_begin_tag(out_file, "Styles", NULL);
    
    pxml_begin_tag(out_file, "Style",
                             "ss:ID",   "Default",
                             "ss:Name", "Normal", NULL);
      pxml_empty_tag(out_file, "Alignment", "ss:Vertical", "Bottom", NULL);
      pxml_empty_tag(out_file, "Borders", NULL);
      pxml_empty_tag(out_file, "Font", NULL);
      pxml_empty_tag(out_file, "Interior", NULL);
      pxml_empty_tag(out_file, "NumberFormat", NULL);
      pxml_empty_tag(out_file, "Protection", NULL);
    pxml_end_tag(out_file, "Style");


    // Bold center (for column headers)
    pxml_begin_tag(out_file, "Style",
                             "ss:ID",   BOLDCENTER_STYL_ID,
                             "ss:Name", "boldcenter", NULL);
      pxml_empty_tag(out_file, "Alignment", "ss:Horizontal", "Center", "ss:Vertical", "Bottom", NULL);
      pxml_empty_tag(out_file, "Font", "ss:Bold", "1", NULL);
    pxml_end_tag(out_file, "Style");


    // A percentage neither good nor bad
    pxml_begin_tag(out_file, "Style",
                             "ss:ID",   PERCENT_STYL_ID,
                             "ss:Name", "percent", NULL);
      pxml_empty_tag(out_file, "Alignment", "ss:Horizontal", "Center", "ss:Vertical", "Bottom", NULL);
      pxml_empty_tag(out_file, "NumberFormat", "ss:Format", "0.000%", NULL);
    pxml_end_tag(out_file, "Style");
    
    

    // Good percentage
    pxml_begin_tag(out_file, "Style",
                             "ss:ID",   GOOD_PERCENT_STYL_ID,
                             "ss:Name", "good_percent", NULL);
      pxml_empty_tag(out_file, "Alignment", "ss:Horizontal", "Center", "ss:Vertical", "Bottom", NULL);
      pxml_empty_tag(out_file, "NumberFormat", "ss:Format", "0.000%", NULL);
      pxml_empty_tag(out_file, "Font", "ss:Color", "green", NULL);
    pxml_end_tag(out_file, "Style");
    
    
    // Bad percentage
    pxml_begin_tag(out_file, "Style",
                             "ss:ID",   BAD_PERCENT_STYL_ID,
                             "ss:Name", "bad_percent", NULL);
      pxml_empty_tag(out_file, "Alignment", "ss:Horizontal", "Center", "ss:Vertical", "Bottom", NULL);
      pxml_empty_tag(out_file, "NumberFormat", "ss:Format", "0.000%", NULL);
      pxml_empty_tag(out_file, "Font", "ss:Color", "red", NULL);
    pxml_end_tag(out_file, "Style");
    
    
    // FAIL
    pxml_begin_tag(out_file, "Style",
                             "ss:ID",   FAIL_STYL_ID,
                             "ss:Name", "fail", NULL);
      pxml_empty_tag(out_file, "Font", "ss:Color", "red", NULL);
    pxml_end_tag(out_file, "Style");
    
    
    
    pxml_end_tag(out_file, "Styles");
    
    fflush(out_file);
    return;
}


// -----------------------------------------------------------------------------------------------------------------------
// Opens a worksheet of given name
void xml_open_worksheet(const char *sheet_name) {
    
    pxml_begin_tag(out_file, "Worksheet",
                             "ss:Name",   sheet_name, NULL);
    return;
}

// -----------------------------------------------------------------------------------------------------------------------
// Close current worksheet
void xml_close_worksheet() {
    
    pxml_end_tag(out_file, "Worksheet");
    return;
}
    

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
void xml_versions(t_history h) {
    
        // Temporary variables for loops...
        t_reports       rs;
        
        // local pointer to cmp_fields, exec_dataref, info_exec
        t_cmp_fields    lp_cmp_fields   = NULL;

                t_compiler_versions       cc_versions;
        
    pxml_begin_tag(out_file, "Table", NULL);
    
    // Columns formatting
    /*
    pxml_empty_tag(out_file, "Column", "ss:AutoFitWidth", "0", "ss:Width", "45", NULL);
    pxml_empty_tag(out_file, "Column", "ss:AutoFitWidth", "0", "ss:Width", "90", NULL);
    pxml_empty_tag(out_file, "Column", "ss:AutoFitWidth", "0", "ss:Width", "110", "ss:Span", "1", NULL);
    */
    
    // First line
        pxml_begin_tag(out_file, "Row", NULL);
        pxml_string_cell(out_file, "Versions", "ss:Index", "5", "ss:StyleID", BOLDCENTER_STYL_ID, NULL);
        pxml_end_tag(out_file, "Row");

        // We go directly to the row 10
        pxml_empty_tag(out_file, "Row", "ss:Index", "10", NULL);
        
    
    // We ... TODO
    for (rs = h->reports; rs != NULL; rs = rs->next) {

                cc_versions = rs->report->compiler_versions;
        
    } // end of for (rs = h->reports; rs != NULL; rs = rs->next)
        

    pxml_end_tag(out_file, "Table");

}



/**************************************************************************************************************************
* FUNCTION:     xml_column_format_and_title
*
* DESCRIPTION:  Writes results comparison between test sessions in an XML Excel file
*
* INPUTS:       
*
* OUTPUTS:      
*
* RETURNS:      none
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         1 December 2004
***************************************************************************************************************************/
static void xml_column_format_and_title(const char *title, const int l_nb_run_ids) {
    
    char *s;
    
    // Columns formatting
    pxml_empty_tag(out_file, "Column", "ss:AutoFitWidth", "0", "ss:Width", "45", NULL);
    pxml_empty_tag(out_file, "Column", "ss:AutoFitWidth", "0", "ss:Width", "90", NULL);
    pxml_empty_tag(out_file, "Column", "ss:AutoFitWidth", "0", "ss:Width", "110", "ss:Span", "1", NULL);
    // l_nb_run_ids may fit in 2 digits
    sprintf((s = malloc(sizeof(char) * 3)), "%02d", l_nb_run_ids);
    pxml_empty_tag(out_file, "Column", "ss:AutoFitWidth", "0", "ss:Width", "65", "ss:Span", s, NULL);
    free(s);
    
    // Title on the first line
    pxml_begin_tag(out_file, "Row", NULL);
    pxml_string_cell(out_file, title, "ss:Index", "5", "ss:StyleID", BOLDCENTER_STYL_ID, NULL);
    pxml_end_tag(out_file, "Row");
    
    return;
}



/**************************************************************************************************************************
* FUNCTION:     xml_output_table
*
* DESCRIPTION:  Writes results comparison between test sessions in an XML Excel file
*
* INPUTS:       
*
* OUTPUTS:      
*
* RETURNS:      none
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         1 December 2004
***************************************************************************************************************************/
static void xml_output_table(
                char *** const table,           // content
				char *** const table_style,     // content styles
                char *** const line_two_table,  // line criterion cells
                char **  const col_table,        // column headers
				int      const l_nb_cmp_data,
				int      const l_nb_run_ids
				) {
    
    char *s;
    
    // index of set of comparison criterions
    int i_crit;
    
    // index of the exec
    int j_exec;
    
    // index for criterion
    int n;
            
    // ---------------------------------------------------------------------------------------------
    // Columns headers
    pxml_begin_tag(out_file, "Row", NULL);
    
    pxml_string_cell(out_file, col_table[0], "ss:Index", "5", "ss:StyleID", BOLDCENTER_STYL_ID, NULL);
    
    for (j_exec = 1 ; j_exec < l_nb_run_ids ; j_exec++) {
        
        pxml_string_cell(out_file, col_table[j_exec], "ss:StyleID", BOLDCENTER_STYL_ID, NULL);
    
    }
    pxml_end_tag(out_file, "Row");


    // for each criterion (line)
    for (i_crit = 0 ; i_crit < l_nb_cmp_data ; i_crit++) {
        
        // New line
        pxml_begin_tag(out_file, "Row", NULL);
        
        // Line criterions
        for (n = 0 ; n < NB_CRITERION ; n++) {
            pxml_string_cell(out_file, line_two_table[i_crit][n], NULL);
        }
        
        // Comparison data
        for (j_exec = 0 ; j_exec < l_nb_run_ids ; j_exec++) {
            
            s = table[i_crit][j_exec];
            
            if (s == NULL) {
                if (table_style[i_crit][j_exec] == NULL) {
                    pxml_string_cell(out_file, NO_RESULT_STRING, NULL);
                }
                else {
                    pxml_string_cell(out_file, NO_RESULT_STRING, "ss:StyleID", table_style[i_crit][j_exec], NULL);
                }
            }
            else if (s[0] == '=') {
                if (table_style[i_crit][j_exec] == NULL) {
                    pxml_formula_cell(out_file, s, NULL);
                }
                else {
                    pxml_formula_cell(out_file, s, "ss:StyleID", table_style[i_crit][j_exec], NULL);
                }
            }
            else if (isdigit(s[0]) || (s[0] == '+') || (s[0] == '-')) {
                if (table_style[i_crit][j_exec] == NULL) {
                    pxml_number_cell(out_file, s, NULL);
                }
                else {
                    pxml_number_cell(out_file, s, "ss:StyleID", table_style[i_crit][j_exec], NULL);
                }
            }
            else {
                if (table_style[i_crit][j_exec] == NULL) {
                    pxml_string_cell(out_file, s, NULL);
                }
                else {
                    pxml_string_cell(out_file, s, "ss:StyleID", table_style[i_crit][j_exec], NULL);
                }
            }
        }
        pxml_end_tag(out_file, "Row");
    } // end for (i_crit = 0 ; i_crit < l_nb_cmp_data ; i_crit++)    
}




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
void xml_output(const char *purpose, const t_comparison_data cmp_data, const int nb_cmp_data) {
        
    // tmp variables
    char	*s;
    int		m, n, o;
    // Data kept during each line generation: first value, previous value, current value
    __int64  r0,  r1,  r2;
    char    *s0, *s1, *s2;
    int      l0,  l1,  l2;
    int     ok_r0, ok_r1, ok_r2;


    // index of set on comparison criterions
    int i_crit, l_i_crit;
    
    // index of the exec
    int j_exec;
            
    // all exec data for the criterium fields
    t_exec_dataref        a_exec_dataref; 
    
    // CC options of each execution
    t_cc_options cc_opt;
    
    // run_ids for the current comparison purpose (size/speed/...)
    t_all_run_ids    l_all_run_ids = malloc(sizeof(t_run_id) * nb_run_ids);
    int              l_nb_run_ids = 0;
    
    // actual number of comparison criterion for the current comparison purpose (size/speed/...)
    int              l_nb_cmp_data = 0;
 
    // If cmp_data[i] is for the current comparison purpose
    int *ok_cmp_data = malloc(sizeof(int) * nb_cmp_data);
    
    // -----------------------------------------------------------------------------------------------
    
    // Tables of the cells containing comparison values (as strings)
    // comparing with previous
    // comparing with first
    
    char ***cwp_table; // max: [nb_cmp_data][nb_run_ids + 1];
    char ***cwf_table; // max: [nb_cmp_data][nb_run_ids + 1];
    // Styles
    char ***cwp_table_style; // max: [nb_cmp_data][nb_run_ids + 1];
    char ***cwf_table_style; // max: [nb_cmp_data][nb_run_ids + 1];
    
    
    // Columns headers
    char **col_cwp_table; // max: [nb_run_ids + 1];
    char **col_cwf_table; // max: [nb_run_ids + 1];
    
    
    // lines beginning (criterions) for the 2 tables
    // NB_CRITERION == #(host_type x test_name x [target + argv] x cc_options)
    char ***line_two_table; // max: [nb_cmp_data][4];
    
    
    // -----------------------------------------------------------------------------------------------
    // BEGINNING OF CODE
    // -----------------------------------------------------------------------------------------------
    
    // Dynamic allocations / verifications
    if (l_all_run_ids == NULL) {
        errlog("ERROR: memory allocation for l_all_run_ids in xml_output() in %s\n", __FILE__);
        return;
    }
    if (ok_cmp_data == NULL) {
        errlog("ERROR: memory allocation for ok_cmp_data in xml_output() in %s\n", __FILE__);
        return;
    }
    
    // -----------------------------------------------------------------------------------------------
    // We search all run_ids for this purpose
    // and fill ok_cmp_data
    // and compute l_nb_cmp_data actual number of lines
    
    
    // for each criterion (line)
    for (i_crit = 0 ; i_crit < nb_cmp_data ; i_crit++) {
            
        // compilation options
        cc_opt = cmp_data[i_crit].cmp_fields->cc_options;
        
        // if compil was for size/speed/...
        if ((*is_for_purpose)(cc_opt) == 1) {
            
            // line to take in account
            ok_cmp_data[i_crit] = 1;
            l_nb_cmp_data++;
            
            for (n = 0 ; n < cmp_data[i_crit].nb_run_ids ; n++) {
                
                DEBUG_cmp_out_printf("%s, ", cmp_data[i_crit].all_run_ids[n]);
                
                // if run_id is not known
                if (bsearch(&(cmp_data[i_crit].all_run_ids[n]), l_all_run_ids, l_nb_run_ids, sizeof(t_run_id), &strp_cmp) == NULL ) {
                        
                    // We add it
                    l_all_run_ids[l_nb_run_ids++] = strdup(cmp_data[i_crit].all_run_ids[n]);
                    qsort(l_all_run_ids, l_nb_run_ids, sizeof(t_run_id), &strp_cmp);
                }
            }
            DEBUG_cmp_out_printf("\n");
        }
        else {
            ok_cmp_data[i_crit] = 0;
        }
    } // end for (i_crit = 0 ; i_crit < nb_cmp_data ; i_crit++)
    
    if (l_nb_cmp_data == 0) {
        errlog("No data to compare for the current comparison purpose (size/speed/...)\n");
        free(l_all_run_ids);
        free(ok_cmp_data);
        return;
    }

    
    // -----------------------------------------------------------------------------------------------
    // We allocate and initialize the result tables
    
    // Table for comparisons with previous
    if ((cwp_table = malloc(sizeof(char**) * l_nb_cmp_data)) == NULL) {
        errlog("ERROR: memory allocation for cwp_table in xml_output() in %s\n", __FILE__);
        return;
    }                
    // Table for comparisons with first
    if ((cwf_table = malloc(sizeof(char**) * l_nb_cmp_data)) == NULL) {
        errlog("ERROR: memory allocation for cwf_table in xml_output() in %s\n", __FILE__);
        return;
    }
    // Table for styles for comparisons with previous
    if ((cwp_table_style = malloc(sizeof(char**) * l_nb_cmp_data)) == NULL) {
        errlog("ERROR: memory allocation for cwp_table_style in xml_output() in %s\n", __FILE__);
        return;
    }                
    // Table for styles for comparisons with first
    if ((cwf_table_style = malloc(sizeof(char**) * l_nb_cmp_data)) == NULL) {
        errlog("ERROR: memory allocation for cwf_table_style in xml_output() in %s\n", __FILE__);
        return;
    }
    
    // Initialization of comparisons tables and style formats
    for (i_crit = 0 ; i_crit < l_nb_cmp_data ; i_crit++) {
        
        if ((cwp_table[i_crit] = malloc(sizeof(char*) * l_nb_run_ids)) == NULL) {
            errlog("ERROR: memory allocation for cwp_table[%u] in xml_output() in %s\n", i_crit, __FILE__);
            return;
        }                
        if ((cwf_table[i_crit] = malloc(sizeof(char*) * l_nb_run_ids)) == NULL) {
            errlog("ERROR: memory allocation for cwf_table[%u] in xml_output() in %s\n", i_crit, __FILE__);
            return;
        }                
        if ((cwp_table_style[i_crit] = malloc(sizeof(char*) * l_nb_run_ids)) == NULL) {
            errlog("ERROR: memory allocation for cwp_table_style[%u] in xml_output() in %s\n", i_crit, __FILE__);
            return;
        }                
        if ((cwf_table_style[i_crit] = malloc(sizeof(char*) * l_nb_run_ids)) == NULL) {
            errlog("ERROR: memory allocation for cwf_table_style[%u] in xml_output() in %s\n", i_crit, __FILE__);
            return;
        }                
        for (j_exec = 0 ; j_exec < l_nb_run_ids ; j_exec++) {
            
            cwp_table[i_crit][j_exec] = NULL;
            cwf_table[i_crit][j_exec] = NULL;
            cwp_table_style[i_crit][j_exec] = NULL;
            cwf_table_style[i_crit][j_exec] = NULL;
        }
    }
    
     // Columns headers
    if ((col_cwp_table = malloc(sizeof(char*) * (l_nb_run_ids))) == NULL) {
        errlog("ERROR: memory allocation for col_cwp_table in xml_output() in %s\n", __FILE__);
        return;
    }
    if ((col_cwf_table = malloc(sizeof(char*) * (l_nb_run_ids))) == NULL) {
        errlog("ERROR: memory allocation for col_cwf_table in xml_output() in %s\n", __FILE__);
        return;
    }
    
    // lines beginning (criterions) for the 2 tables
    // NB_CRITERION == #(host_type x test_name x [target + argv] x cc_options)
    if ((line_two_table = malloc(sizeof(char**) * l_nb_cmp_data)) == NULL) {
        errlog("ERROR: memory allocation for line_two_table in xml_output() in %s\n", __FILE__);
        return;
    }
    for (i_crit = 0 ; i_crit < l_nb_cmp_data ; i_crit++) {
    
        if ((line_two_table[i_crit] = malloc(sizeof(char*) * NB_CRITERION)) == NULL) {
            errlog("ERROR: memory allocation for line_two_table[%u] in xml_output() in %s\n", i_crit, __FILE__);
            return;
        }                
    }

    
    // -----------------------------------------------------------------------------------------------
    // main data computation loop
    

    // Columns headers
    col_cwp_table[0] = strdup(l_all_run_ids[0]);
    col_cwf_table[0] = strdup(l_all_run_ids[0]);
    //
    m = (n = (o = strlen(l_all_run_ids[0])));
    for (j_exec = 1 ; j_exec < l_nb_run_ids ; j_exec++) {
         
         o = strlen(l_all_run_ids[j_exec]);
         
         col_cwp_table[j_exec] = malloc(sizeof(char*) * (n + o + 2));
         col_cwf_table[j_exec] = malloc(sizeof(char*) * (m + o + 2));
         
         strcpy(col_cwp_table[j_exec], l_all_run_ids[j_exec]);
         strcpy(col_cwf_table[j_exec], l_all_run_ids[j_exec]);
         
         strcpy(col_cwp_table[j_exec]+o, "/");
         strcpy(col_cwf_table[j_exec]+o, "/");
         
         strcpy(col_cwp_table[j_exec]+o+1, l_all_run_ids[j_exec - 1]);
         strcpy(col_cwf_table[j_exec]+o+1, l_all_run_ids[0]);
                      
         n = o;
    }


    // lines beginning (criterions) for the 2 tables
    // NB_CRITERION == #(host_type x test_name x [target + argv] x cc_options)
    for (i_crit = 0, l_i_crit = 0 ; i_crit < nb_cmp_data ; i_crit++) {
        
        if (ok_cmp_data[i_crit] == 1) {
            
            for (n = 0 ; n < NB_CRITERION ; n++) {
                line_two_table[l_i_crit][n] = access_crit(cmp_data[i_crit].cmp_fields, n);
            }
            l_i_crit++;
        }
    }


    // We fill comparison cells
    // for each criterion (line)
    for (i_crit = 0, l_i_crit = 0 ; i_crit < nb_cmp_data ; i_crit++) {
            
        assert(l_i_crit <= l_nb_cmp_data);	

        // if compil was for size/speed/...
        if (ok_cmp_data[i_crit] == 1) {
             
            // Set of results
            a_exec_dataref = cmp_data[i_crit].exec_dataref;
            
            // Initialization of tmp values
            r2 = (r1 = (r0 = (__int64)(0)));
            s2 = (s1 = (s0 = ""));
            l2 = (l1 = (l0 = 0));
            ok_r2 = (ok_r1 = (ok_r0 = 0));
            
            // For all results for these criterions
            for (j_exec = 0 ; j_exec < l_nb_run_ids ;) {
                
                // At least one result ?
                if (a_exec_dataref != NULL) {

                    o = strcmp(a_exec_dataref->run_id, l_all_run_ids[j_exec]);
                    
                    // We test if we have the value for this column
                    if ( o < 0 ) {
                        // if before there was multiple a_exec_dataref with the same run_id => error
                        
                        errlog("ERROR: run_id %s encountered as should be at least %s for criterion: sys=='%s', test=='%s', target=='%s', options=='%s'.\n",
                               a_exec_dataref->run_id,
                               l_all_run_ids[j_exec],
                               line_two_table[l_i_crit][0],
                               line_two_table[l_i_crit][1],
                               line_two_table[l_i_crit][2],
                               line_two_table[l_i_crit][3]
                               );
                               
                        cwp_table[l_i_crit][j_exec] = strdup(NO_RESULT_STRING);
                        cwf_table[l_i_crit][j_exec] = strdup(NO_RESULT_STRING);
                            
                        // Next result
                        a_exec_dataref = a_exec_dataref->next;
                        continue;
                    }
                    else if ( o > 0 ) { // if the a_exec_dataref is for a future column
                        
                        cwp_table[l_i_crit][j_exec] = strdup(NO_RESULT_STRING);
                        cwf_table[l_i_crit][j_exec] = strdup(NO_RESULT_STRING);
                        
                        // Value of this column cannot be used for next comparison
                        ok_r2 = 0;
                            
                    }
                    else { // 0: if the data exists for this run_id
                        
                        //if this is a FAIL
                        if (strncmp((s = a_exec_dataref->exec->status), FAIL_STRING, FAIL_STRLEN) == 0) {
                                cwp_table[l_i_crit][j_exec] = strdup(s);
                                cwf_table[l_i_crit][j_exec] = strdup(s);
                                cwp_table_style[l_i_crit][j_exec] = FAIL_STYL_ID;
                                cwf_table_style[l_i_crit][j_exec] = FAIL_STYL_ID;
                        }
                        else {
                            s2 = (*access_fct)(a_exec_dataref);
                            l2 = strlen(s2);
                            
                            // We convert string into value
                            ok_r2 = sscanf(s2, "%lld", &r2);
                                
                            
                            // If we are in the firts column
                            if (j_exec == 0) {
                                
                                // First value
                                s0    = s2;
                                l0    = l2;
                                r0    = r2;
                                ok_r0 = ok_r2;
                                
                                cwp_table[l_i_crit][0] = strdup(s0);
                                cwf_table[l_i_crit][0] = strdup(s0);
                            }
                            else { // Others columns than first one
                                
                                // If we can do the comparison with previous column
                                if ((ok_r1 == 1) && (ok_r2 == 1)) {
                                        if (r1 != (__int64)(0)) {
                                                
                                                if ( (((__int64)(1000) * (r2 - r1)) /r1) <= SMALLER_GOOD_PERTHOUSANDAGE) {
                                                        cwp_table_style[l_i_crit][j_exec] = GOOD_PERCENT_STYL_ID;
                                                }
                                                else if ( (((__int64)(1000) * (r2 - r1)) /r1) >= SMALLER_BAD_PERTHOUSANDAGE) {
                                                        cwp_table_style[l_i_crit][j_exec] = BAD_PERCENT_STYL_ID;
                                                }
                                                else {
                                                        cwp_table_style[l_i_crit][j_exec] = PERCENT_STYL_ID;
                                                }
                                        }
                                        else {
                                            cwp_table_style[l_i_crit][j_exec] = PERCENT_STYL_ID;
                                        }
                                        // We put the computation formula
                                        cwp_table[l_i_crit][j_exec] = malloc(sizeof(char) * (strlen("=(%s-%s)/%s")-6+l2+l1+l1+1));
                                        sprintf(cwp_table[l_i_crit][j_exec], "=(%s-%s)/%s", s2, s1, s1);
                                }
                                else {
                                    cwp_table[l_i_crit][j_exec] = strdup(MISSING_VALUES);
                                }
                                // If we can do the comparison with first column
                                if ((ok_r0 == 1) && (ok_r2 == 1)) {
                                        if (r0 != (__int64)(0)) {
                                                
                                                if ( (((__int64)(1000) * (r2 - r0)) /r0) <= SMALLER_GOOD_PERTHOUSANDAGE) {
                                                        cwf_table_style[l_i_crit][j_exec] = GOOD_PERCENT_STYL_ID;
                                                }
                                                else if ( (((__int64)(1000) * (r2 - r0)) /r0) >= SMALLER_BAD_PERTHOUSANDAGE) {
                                                        cwf_table_style[l_i_crit][j_exec] = BAD_PERCENT_STYL_ID;
                                                }
                                                else {
                                                        cwf_table_style[l_i_crit][j_exec] = PERCENT_STYL_ID;
                                                }
                                        }
                                        else {
                                            cwf_table_style[l_i_crit][j_exec] = PERCENT_STYL_ID;
                                        }
                                        // We put the computation formula
                                        cwf_table[l_i_crit][j_exec] = malloc(sizeof(char) * (strlen("=(%s-RC[-%02u])/RC[-%02u]")-10+l2+4+1));
                                        sprintf(cwf_table[l_i_crit][j_exec], "=(%s-RC[-%02u])/RC[-%02u]", s2, j_exec, j_exec);                            
                                
                                }
                                else {
                                    cwf_table[l_i_crit][j_exec] = strdup(MISSING_VALUES);
                                }
                            } // end if (j_exec == 0)
                        } // end if (strncmp(s2, FAIL_STRING, FAIL_STRLEN) == 0)
                        
                        // Next result
                        a_exec_dataref = a_exec_dataref->next;
                    }			        
                }
                else {
                        // else there is no more result
                        
                    cwp_table[l_i_crit][j_exec] = strdup(NO_RESULT_STRING);
                    cwf_table[l_i_crit][j_exec] = strdup(NO_RESULT_STRING);
                    ok_r2 = 0;
                    
                } // end if (a_exec_dataref != NULL)
                
                // Increment separated from "for" loop to be able to do a continue without increment
                j_exec++;
                
                s1    = s2;
                l1    = l2;
                r1    = r2;
                ok_r1 = ok_r2;
                
            } // end for (j_exec = 1 ; j_exec < l_nb_run_ids ; )
            
            l_i_crit++;
             
        } // end if ((*is_for_purpose)(cc_opt))
        
    } // end for (i_crit = 0 ; i_crit < l_nb_cmp_data ; i_crit++)
    
    
    // -----------------------------------------------------------------------------------------------
    // XML output loop
    
    // ------------------------------------------
    // New Worksheet for comparison with previous
    
    // Title
    s = malloc(sizeof(char) * (strlen(purpose) + strlen("_vs_previous") + 1));
    strcat(strcpy(s, purpose), "_vs_previous");
    
    xml_open_worksheet(s);
    pxml_begin_tag(out_file, "Table", NULL);
    
    // We set column width and put the title on the first line
    xml_column_format_and_title(s, l_nb_run_ids);
    free(s);
    
    // We go directly to the row 10
    pxml_empty_tag(out_file, "Row", "ss:Index", "10", NULL);

    // We output the comparison table
    xml_output_table(cwp_table, cwp_table_style, line_two_table, col_cwp_table, l_nb_cmp_data, l_nb_run_ids);
    
    // end of output of the worksheet
    pxml_end_tag(out_file, "Table");
    xml_close_worksheet();


    // ------------------------------------------
    // New Worksheet for comparison with first
    s = malloc(sizeof(char) * (strlen(purpose) + strlen("_vs_first") + 1));
    strcat(strcpy(s, purpose), "_vs_first");
    
    xml_open_worksheet(s);
    pxml_begin_tag(out_file, "Table", NULL);
    
    // We set column width and put the title on the first line
    xml_column_format_and_title(s, l_nb_run_ids);
    free(s);
    
    // We go directly to the row 10
    pxml_empty_tag(out_file, "Row", "ss:Index", "10", NULL);

    // We output the comparison table
    xml_output_table(cwf_table, cwf_table_style, line_two_table, col_cwf_table, l_nb_cmp_data, l_nb_run_ids);
    
    // end of output of the worksheet
    pxml_end_tag(out_file, "Table");
    xml_close_worksheet();


    // -----------------------------------------------------------------------------------------------
    // Cleaning
    for (i_crit = 0 ; i_crit < l_nb_cmp_data ; i_crit++) {
        
        for (j_exec = 0 ; j_exec < l_nb_run_ids ; j_exec++) {
                if ((s = cwp_table[i_crit][j_exec]) != NULL) free(s);
                if ((s = cwf_table[i_crit][j_exec]) != NULL) free(s);
        }
        free(cwp_table[i_crit]);
        free(cwf_table[i_crit]);
        free(cwp_table_style[i_crit]);
        free(cwf_table_style[i_crit]);
    }
    free(cwp_table);
    free(cwf_table);
    free(cwp_table_style);
    free(cwf_table_style);

    for (j_exec = 0 ; j_exec < l_nb_run_ids ; j_exec++) {
        free(col_cwp_table[j_exec]);
        free(col_cwf_table[j_exec]);
    }
    free(col_cwp_table);
    free(col_cwf_table);

    for (i_crit = 0 ; i_crit < l_nb_cmp_data ; i_crit++) {
        for (n = 0 ; n < NB_CRITERION ; n++) {
            free(line_two_table[i_crit][n]);
        }
    }
    free(line_two_table);

    free(ok_cmp_data);
    free(l_all_run_ids);
    
    return;
}


