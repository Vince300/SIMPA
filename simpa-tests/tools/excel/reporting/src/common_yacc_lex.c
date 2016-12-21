/************************************************************************************************************************/
/* MAIN MODULE                                                                                        			*/
/*                                                                                                                      */
/* AUTHORS : Yves GUERTE, July 2004                                                                                */
/*                                                                                                                      */
/* CONTENT :                                                                                                            */
/*                                                                                                                      */
/* 															*/
/*															*/
/************************************************************************************************************************/

#include <ctype.h>
#include <string.h>
#include "common_yacc_lex.h"

// -----------------------------------------------------
// attribute and attributes sequence

void free_attribute(t_attribute a) {
        if (a != NULL) {
                free(a->name);
                free(a->value);
                free(a);
        }
}
void dump_attribute(t_attribute a) {
        if (a != NULL) {
                fprintf(stderr,"name==%s, value==%s; ",a->name, a->value);
        }
}

t_attribute_seq_opt empty_attribute_seq_opt() {
        return NULL;
}
void free_attribute_seq_opt(t_attribute_seq_opt a) {
        if (a != NULL) {
                free_attribute        (a->attribute);
                free_attribute_seq_opt(a->next);
                
                free(a);
        }
}
void dump_attribute_seq_opt(t_attribute_seq_opt a) {
        if (a != NULL) {
                fprintf(stderr,"Attributes: ");
                dump_attribute(a->attribute);
                dump_attribute_seq_opt(a->next);
        }
        else {
                fprintf(stderr,".\n");
        }
}
t_attribute_seq_opt add_attribute_to_attribute_seq_opt(const t_attribute a, t_attribute_seq_opt as) {
        t_attribute_seq_opt asr = malloc(sizeof(s_attribute_seq_opt));
        asr->attribute = a;
        asr->next = as;
        return asr;
}


// -----------------------------------------------------
// Errors
t_opt_report_errors empty_opt_report_errors() {
        return NULL;
}
void free_opt_report_errors(t_opt_report_errors e) {fprintf(stderr,"To be implemented.\n");}
void dump_opt_report_errors(t_opt_report_errors e) {fprintf(stderr,"To be implemented.\n");}

// -----------------------------------------------------
// tool (version)
t_tool empty_tool() {
        t_tool t = malloc(sizeof(s_tool));
        t->tool_name    = NULL;
        t->tool_version = NULL;
        return t;
}
void free_tool(t_tool t) {fprintf(stderr,"To be implemented.\n");}
void dump_tool(t_tool t) {fprintf(stderr,"To be implemented.\n");}
t_tool add_tool_name_to_tool(const t_tool_name n, t_tool t) {
        t->tool_name = n;
        return t;
}
t_tool add_tool_version_to_tool(const t_tool_version v, t_tool t) {
        t->tool_version = v;
        return t;
}

// tools
t_tools empty_tools() {
        return NULL;
}
void free_tools(t_tools t) {fprintf(stderr,"To be implemented.\n");}
void dump_tools(t_tools t) {fprintf(stderr,"To be implemented.\n");}
t_tools add_tool_to_tools(const t_tool t,                  t_tools ts) {
        t_tools l = malloc(sizeof(s_tools));
        l->tool = t;
        l->next = ts;
        return l;
}

// compiler_version of compiler tools
t_compiler_version empty_compiler_version() {
        t_compiler_version v;
        v = malloc(sizeof(s_compiler_version)) ;
        v->host_type = NULL;
        v->host_name = NULL;
        v->tools     = NULL;
        return v;
}
void free_compiler_version(t_compiler_version v) {fprintf(stderr,"To be implemented.\n");}
void dump_compiler_version(t_compiler_version v) {fprintf(stderr,"To be implemented.\n");}
t_compiler_version add_host_type_to_compiler_version(const t_host_type t, t_compiler_version v) {
        v->host_type = t;
        return v;
}
t_compiler_version add_host_name_to_compiler_version(const t_host_name n, t_compiler_version v) {
        v->host_name = n;
        return v;
}
t_compiler_version add_tool_to_compiler_version(const t_tool t, t_compiler_version v) {
        v->tools = add_tool_to_tools(t, v->tools);
        return v;
}
void free_compiler_versions(t_compiler_versions vs) {fprintf(stderr,"To be implemented.\n");}
void dump_compiler_versions(t_compiler_versions vs) {fprintf(stderr,"To be implemented.\n");}

// -----------------------------------------------------
// For scenario:
// test_def
t_test_def empty_test_def() {
        t_test_def t = malloc(sizeof(s_test_def)) ;
        t->test_path   = NULL;
        t->options_set = NULL;
        return t;
}
void free_test_def(t_test_def t) {fprintf(stderr,"To be implemented.\n");}
void dump_test_def(t_test_def t) {fprintf(stderr,"To be implemented.\n");}
t_test_def add_test_path_to_test_def(const t_test_path tp, t_test_def t) {
        t->test_path = tp;
        return t;
}
t_test_def add_options_set_to_test_def(const t_options_set os, t_test_def t) {
        t->options_set = os;
        return t;
}

// scenario
t_scenario empty_scenario() {
        t_scenario s = malloc(sizeof(s_scenario)) ;
        s->host_name = NULL;
        s->test_def  = NULL;
        return s;
}
void free_scenario(t_scenario s) {fprintf(stderr,"To be implemented.\n");}
void dump_scenario(t_scenario s) {fprintf(stderr,"To be implemented.\n");}
t_scenario add_host_name_to_scenario(const t_host_name h, t_scenario s) {
        s->host_name = h;
        return s;
}
t_scenario add_test_def_to_scenario(const t_test_def t, t_scenario s) {
        s->test_def = t;
        return s;
}

// -----------------------------------------------------
// For param_files:
// param_file
t_param_file empty_param_file() {
        t_param_file p = malloc(sizeof(s_param_file)) ;
        p->filename = NULL;
        p->rawdata  = NULL;
        return p;
}
void free_param_file(t_param_file p) {fprintf(stderr,"To be implemented.\n");}
void dump_param_file(t_param_file p) {fprintf(stderr,"To be implemented.\n");}
t_param_file add_filename_to_param_file(const t_filename f, t_param_file p) {
        p->filename = f;
        return p;
}
t_param_file add_rawdata_to_param_file(const t_rawdata r, t_param_file p) {
        p->rawdata = r;
        return p;
}

// param_files_seq
t_param_files_seq empty_param_files_seq() {
        return NULL;
}
void free_param_files_seq(t_param_files_seq p) {fprintf(stderr,"To be implemented.\n");}
void dump_param_files_seq(t_param_files_seq p) {fprintf(stderr,"To be implemented.\n");}

// param_files
t_param_files empty_param_files() {
        t_param_files p = malloc(sizeof(s_param_files)) ;
        p->host_name       = NULL;
        p->param_files_seq = NULL;
        return p;
}
void free_param_files(t_param_files p) {fprintf(stderr,"To be implemented.\n");}
void dump_param_files(t_param_files p) {fprintf(stderr,"To be implemented.\n");}
t_param_files add_host_name_to_param_files(const t_host_name h, t_param_files ps) {
        ps->host_name = h;
        return ps;
}
t_param_files add_param_file_to_param_files(const t_param_file p, t_param_files ps) {
        t_param_files_seq l = malloc(sizeof(s_param_files_seq)) ;
        l->param_file = p;
        l->next = ps->param_files_seq;
        ps->param_files_seq = l;
        return ps;
}

// -----------------------------------------------------
// compilation

 t_compilation empty_compilation() {
        t_compilation c = malloc(sizeof(s_compilation)) ;
        
        c->target =            NULL;
        c->cflags =            NULL;
        c->make_argv =         NULL;
        c->start_date =        NULL;
        c->end_date =          NULL;
        return c;
}
void free_compilation(t_compilation c) {fprintf(stderr,"To be implemented.\n");}
void dump_compilation(t_compilation c) {fprintf(stderr,"To be implemented.\n");}

t_compilation add_target_to_compilation(const t_target t,                     t_compilation c) {
        c ->target = t; return c;
}

t_compilation add_cflags_to_compilation(const t_cflags f,                     t_compilation c) {
        c ->cflags = f; return c;
}

t_compilation add_make_argv_to_compilation(const t_make_argv m,               t_compilation c) {
        c ->make_argv = m; return c;
}

t_compilation add_start_date_to_compilation(const t_date d,                   t_compilation c) {
        c ->start_date = d; return c;
}

t_compilation add_end_date_to_compilation(const t_date d,                     t_compilation c) {
        c ->end_date = d; return c;
}


// -----------------------------------------------------
// compilations

t_compilations empty_compilations() {
        return NULL;
}
void free_compilations(t_compilations c) {fprintf(stderr,"To be implemented.\n");}
void dump_compilations(t_compilations c) {fprintf(stderr,"To be implemented.\n");}
t_compilations add_compilation_to_compilations(const t_compilation c,  t_compilations cs) {
        t_compilations l = malloc(sizeof(s_compilations));
        l->compilation = c;
        l->next        = cs;
        return l;
}


// -----------------------------------------------------
// exec

t_exec empty_exec() {
        t_exec e = malloc(sizeof(s_exec)) ;
        
        e->target =            NULL;
        e->description =       NULL;
        e->status =            NULL;
        e->size =              NULL;
        e->input =             NULL;
        e->n_frames =          NULL;
        e->sample_p_frame =    NULL;
        e->e_freq =            NULL;
        e->argv =              NULL;
        e->cycles =            NULL;
        e->cycles_p_frame =    NULL;
        e->mips =              NULL;
        e->start_date =        NULL;
        e->end_date =          NULL;
              
        return e;
}
void free_exec(t_exec e) {fprintf(stderr,"To be implemented.\n");}
void dump_exec(t_exec e) {fprintf(stderr,"To be implemented.\n");}

t_exec add_target_to_exec(const t_target t,                     t_exec e) {
        e ->target = t; return e;
}
t_exec add_description_to_exec(const t_description d,           t_exec e) {
        e ->description = d; return e;
}
t_exec add_status_to_exec(const t_status s,                     t_exec e) {
        e ->status = s; return e;
}
t_exec add_size_to_exec(const t_size s,                         t_exec e) {
        e ->size = s; return e;
}
t_exec add_input_to_exec(const t_input i,                       t_exec e) {
        e ->input = i; return e;
}
t_exec add_n_frames_to_exec(const t_n_frames nf,                t_exec e) {
        e ->n_frames = nf; return e;
}
t_exec add_sample_p_frame_to_exec(const t_sample_p_frame sf,    t_exec e) {
        e ->sample_p_frame = sf; return e;
}
t_exec add_e_freq_to_exec(const t_e_freq ef,                    t_exec e) {
        e ->e_freq = ef; return e;
}
t_exec add_argv_to_exec(const t_argv a,                         t_exec e) {
        e ->argv = a; return e;
}
t_exec add_cycles_to_exec(const t_cycles c,                     t_exec e) {
        e ->cycles = c; return e;
}
t_exec add_cycles_p_frame_to_exec(const t_cycles_p_frame c,     t_exec e) {
        e ->cycles_p_frame = c; return e;
}
t_exec add_mips_to_exec(const t_mips m,                         t_exec e) {
        e ->mips = m; return e;
}
t_exec add_start_date_to_exec(const t_date d,                   t_exec e) {
        e ->start_date = d; return e;
}
t_exec add_end_date_to_exec(const t_date d,                     t_exec e) {
        e ->end_date = d; return e;
}

// -----------------------------------------------------
// execs
t_execs empty_execs() {
        return NULL;
}
void free_execs(t_execs e) {fprintf(stderr,"To be implemented.\n");}
void dump_execs(t_execs e) {fprintf(stderr,"To be implemented.\n");}
t_execs add_exec_to_execs(const t_exec e,                  t_execs es) {
        t_execs l = malloc(sizeof(s_execs));
        l->exec   = e;
        l->next   = es;
        return l;
}

// -----------------------------------------------------
// targets
t_targets empty_targets() {
        return NULL;
}
void free_targets(t_targets t) {fprintf(stderr,"To be implemented.\n");}
void dump_targets(t_targets t) {fprintf(stderr,"To be implemented.\n");}
t_targets add_target_to_targets(const t_target tg,                  t_targets t) {
        t_targets ts = malloc(sizeof(s_targets));
        ts->target = tg;
        ts->next   = t;
        return ts;
}

// -----------------------------------------------------
// test

t_test empty_test() {
        t_test t = malloc(sizeof(s_test)) ;

        t->test_path         =  NULL;
        t->start_date        =  NULL;
        t->end_date          =  NULL;
        t->test_name         =  NULL;
        t->host_name         =  NULL;
        t->test_mode         =  NULL;
        t->level             =  NULL;
        t->cc_options        =  NULL;
        t->cflags            =  NULL;
        t->makefile          =  NULL;
        t->make_options      =  NULL;
        t->simulator         =  NULL;
        t->sim_options       =  NULL;
        t->targets           =  NULL;
        t->compilations      =  NULL;
        t->execs             =  NULL;
        t->opt_report_errors =  NULL;
        return t;
}
void free_test(t_test t) {fprintf(stderr,"To be implemented.\n");}
void dump_test(t_test t) {fprintf(stderr,"To be implemented.\n");}

t_test add_test_path_to_test(const t_test_path tp,              t_test t) {
        t ->test_path = tp; return t;
}
t_test add_start_date_to_test(const t_date d,                   t_test t) {
        t ->start_date = d; return t;
}
t_test add_end_date_to_test(const t_date d,                     t_test t) {
        t ->end_date = d; return t;
}
t_test add_test_name_to_test(const t_test_name tn,              t_test t) {
        t ->test_name = tn; return t;
}
t_test add_host_name_to_test(const t_host_name hn,              t_test t) {
        t ->host_name = hn; return t;
}
t_test add_test_mode_to_test(const t_test_mode m,               t_test t) {
        t ->test_mode = m; return t;
}
t_test add_level_to_test(const t_level l,                       t_test t) {
        t ->level = l; return t;
}
t_test add_cc_options_to_test(const t_cc_options co,            t_test t) {
        t ->cc_options = co; return t;
}
t_test add_cflags_to_test(const t_cflags cf,                    t_test t) {
        t ->cflags = cf; return t;
}
t_test add_makefile_to_test(const t_makefile m,                 t_test t) {
        t ->makefile = m; return t;
}
t_test add_make_options_to_test(const t_make_options mo,        t_test t) {
        t ->make_options = mo; return t;
}
t_test add_simulator_to_test(const t_simulator s,               t_test t) {
        t ->simulator = s; return t;
}
t_test add_sim_options_to_test(const t_sim_options so,          t_test t) {
        t ->sim_options = so; return t;
}
t_test add_targets_to_test(const t_targets tg,                  t_test t) {
        t->targets = tg;
        return t;
}
t_test add_compilation_to_test(const t_compilation c,           t_test t){
        /*
        t_compilations cs = malloc(sizeof(s_compilations));
        cs->compilation = c;
        cs->next = t->compilations;
        t->compilations = cs;
        */
        t->compilations = add_compilation_to_compilations(c, t->compilations);
        
        return t;
}
t_test add_exec_to_test(const t_exec e,                       t_test t) {
        t_execs es = malloc(sizeof(s_execs));
        es->exec = e;
        es->next = t->execs;
        t->execs = es;
        return t;
}
t_test add_opt_report_error_to_test(const t_opt_report_error e, t_test t) {
        t_opt_report_errors es = malloc(sizeof(s_opt_report_errors));
        es->opt_report_error = e;
        es->next = t->opt_report_errors;
        t->opt_report_errors = es;
        return t;
}


// -----------------------------------------------------
// tests
void free_tests(t_tests t) {fprintf(stderr,"To be implemented.\n");}
void dump_tests(t_tests t) {fprintf(stderr,"To be implemented.\n");}

// -----------------------------------------------------
// report

t_report empty_report() {
        t_report r = malloc(sizeof(s_report)) ;
        
        r->run_id            = NULL;
        r->scenario_file     = NULL;
        r->start_date        = NULL;
        r->end_date          = NULL;
        r->compiler_versions = NULL;
        r->scenario          = NULL;
        r->param_files       = NULL;
        r->tests             = NULL;
        r->opt_report_errors = NULL;
        return r;
}
void free_report(t_report r) {
        if (r != NULL) {
                free                  (r->run_id           );
                free                  (r->scenario_file    );
                free                  (r->start_date       );
                free                  (r->end_date         );
                free_compiler_versions(r->compiler_versions);
                free_scenario         (r->scenario         );
                free_param_files      (r->param_files      );
                free_tests            (r->tests            );
                free                  (r->opt_report_errors);
                free(r);
        }
}
void dump_report(t_report r) {
        if (r != NULL) {
                fprintf(stderr, "run_id == %s\n",               r->run_id           );
                fprintf(stderr, "scenario_file == %s\n",        r->scenario_file    );
                fprintf(stderr, "start_date == %s\n",           r->start_date       );
                fprintf(stderr, "end_date == %s\n",             r->end_date         );
                dump_compiler_versions(                         r->compiler_versions);
                dump_scenario(                                  r->scenario         );
                dump_param_files(                               r->param_files      );
                dump_tests(                                     r->tests            );
                dump_opt_report_errors(                         r->opt_report_errors);
        }
}
t_report add_run_id_to_report(const t_run_id ri,                        t_report r) {
        r ->run_id = ri; return r;
}
t_report add_scenario_file_to_report(const t_scenario_file sf,          t_report r) {
        r ->scenario_file = sf; return r;
}
t_report add_start_date_to_report(const t_date d,                       t_report r) {
        r ->start_date = d; return r;
}
t_report add_end_date_to_report(const t_date d,                         t_report r) {
        r ->end_date = d; return r;
}
t_report add_compiler_version_to_report(const t_compiler_version v,     t_report r) {
        t_compiler_versions vs = malloc(sizeof(s_compiler_versions));
        vs->compiler_version = v;
        vs->next = r->compiler_versions;
        r->compiler_versions = vs;
        return r;
}
t_report add_scenario_to_report(const t_scenario s,                     t_report r) {
        r ->scenario = s; return r;
}
t_report add_param_files_to_report(const t_param_files p,               t_report r) {
        r ->param_files = p; return r;
}
t_report add_test_to_report(const t_test t,                             t_report r) {
        t_tests ts = malloc(sizeof(s_tests));
        ts->test = t;
        ts->next = r->tests;
        r->tests = ts;
        return r;
}
t_report add_opt_report_error_to_report(const t_opt_report_error e,     t_report r) {
        t_opt_report_errors es = malloc(sizeof(s_opt_report_errors));
        es->opt_report_error = e;
        es->next = r->opt_report_errors;
        r->opt_report_errors = es;
        return r;
}

// -----------------------------------------------------
// reports
void free_reports(t_reports r) {
        if (r != NULL) {
                free_reports(r->next);
                free_report(r->report);
                free(r);
        }
}
void dump_reports(t_reports r) {
        if (r != NULL) {
                dump_report(r->report);
                dump_reports(r->next);
        }
}

// -----------------------------------------------------
// history

t_history empty_history() {
        t_history h = malloc(sizeof(s_history));
        
        h->nb_reports  = 0;
        h->reports     = NULL;
        h->last_report = NULL;
        return h;
}
void free_history(t_history h) {
        if (h != NULL) {
                free_reports(h->reports);
                free(h);
        }
}
void dump_history(t_history h) {
        if (h != NULL) {
                fprintf(stderr,"nb_reports == %d\n", h->nb_reports);
                dump_reports(h->reports);
        }
        else {
                fprintf(stderr,"Empty history.\n");
        }
}
t_history add_report_to_history(const t_report r, t_history h) {
        if (r != NULL) {
                if (h->reports != NULL) {
                        h->last_report->next = malloc(sizeof(s_reports));
                        h->last_report = h->last_report->next;
                }
                else {
                        h->reports = malloc(sizeof(s_reports));
                        h->last_report = h->reports;
                }
                h->last_report->report = r;
                h->last_report->next = NULL;
                h->nb_reports++;
        }
        return h;
}

/**************************************************************************************************************************
* FUNCTION:     strcmpiu
*
* DESCRIPTION: insensitive string comparison with an uppercase string
*
* INPUTS: first arg:  string i
*         second arg: string in uppercase u
*
* OUTPUTS:
*
* RETURNS: strcmp(uppercase(i),u) 
***************************************************************************************************************************
* RESTRICTIONS:
*
* BUGS:
***************************************************************************************************************************
* AUTHOR:       YGT
*
* DATE:
***************************************************************************************************************************/
int strcmpiu(char *i, char *u) {
        while (toupper(*i) == *u++)
                if (*i++ == '\0') return(0);
        return(toupper(*i) - *--u) ;
}


/**************************************************************************************************************************
* FUNCTION:     strcmpil
*
* DESCRIPTION: insensitive string comparison with a lowercase string
*
* INPUTS: first arg:  string i
*         second arg: string in lowercase u
*
* OUTPUTS:
*
* RETURNS: strcmp(lowercase(i),u) 
***************************************************************************************************************************
* RESTRICTIONS:
*
* BUGS:
***************************************************************************************************************************
* AUTHOR:       YGT
*
* DATE:
***************************************************************************************************************************/
int strcmpil(char *i, char *u) {
        while (tolower(*i) == *u++)
                if (*i++ == '\0') return(0);
        return(tolower(*i) - *--u) ;
}












