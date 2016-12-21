#ifndef __COMMON_LEX_YACC__
#define __COMMON_LEX_YACC__

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef __GNUC__
#include <file_io.h>
#endif


/* ----------------------------------------------------*/
int yy1lex();
int yy1wrap();
int yy1error(char *s);
int yy1parse();
#ifdef DBG
extern int yy1debug;
#endif
int parse_xml_hist(char *file_name);

/* ----------------------------------------------------*/
// Next 5 defined in the main.c
extern FILE *log_file;
void errlog(char *s1, ...);
extern char *current_file_name;
extern int line_num;
extern int Always_Exit;
// 2 others at the end of this file

/* ----------------------------------------------------*/
/* Type definitions for the report objects types       */
/* Extern constants are in common_yacc_lex.c           */
/* ----------------------------------------------------*/

typedef char *t_run_id;         
typedef char *t_scenario_file;        
typedef char *t_date;            
typedef char *t_test_path;
typedef char *t_options_set;
typedef char *t_test_name;
typedef char *t_host_type;
typedef char *t_host_name;
typedef char *t_tool_name;
typedef char *t_tool_version;
typedef char *t_filename;
typedef char *t_rawdata;
typedef char *t_test_mode;
typedef char *t_level;
typedef char *t_cc_options;
typedef char *t_cflags;
typedef char *t_makefile;
typedef char *t_make_options;
typedef char *t_simulator;
typedef char *t_sim_options;
typedef char *t_target;
typedef char *t_make_argv;
typedef char *t_description;
typedef char *t_status;
typedef char *t_size;
typedef char *t_input;
typedef char *t_n_frames;
typedef char *t_sample_p_frame;
typedef char *t_e_freq;
typedef char *t_argv;
typedef char *t_cycles;
typedef char *t_cycles_p_frame;
typedef char *t_mips;
// -----------------------------------------------------
// optional report error (user break, ...
typedef char *t_opt_report_error;


// -----------------------------------------------------
// attribute and attribute sequence
typedef struct s_attribute {
	char		*name;
	char 		*value;
} s_attribute, *t_attribute;
void free_attribute(t_attribute a);
void dump_attribute(t_attribute a);

typedef struct s_attribute_seq_opt {
	t_attribute			attribute;
	struct s_attribute_seq_opt	*next;
} s_attribute_seq_opt, *t_attribute_seq_opt;
void free_attribute_seq_opt(t_attribute_seq_opt a);
void dump_attribute_seq_opt(t_attribute_seq_opt a);
t_attribute_seq_opt add_attribute_to_attribute_seq_opt(const t_attribute a, t_attribute_seq_opt as);

// -----------------------------------------------------
// Errors
typedef struct s_opt_report_errors {
	t_opt_report_error		opt_report_error;
	struct s_opt_report_errors 	*next;
} s_opt_report_errors, *t_opt_report_errors;
t_opt_report_errors empty_opt_report_errors();
void free_opt_report_errors(t_opt_report_errors e);
void dump_opt_report_errors(t_opt_report_errors e);

// -----------------------------------------------------
// tool (version)
typedef struct s_tool {
	t_tool_name				tool_name;
	t_tool_version				tool_version;
} s_tool, *t_tool;
t_tool empty_tool();
void free_tool(t_tool t);
void dump_tool(t_tool t);
t_tool add_tool_name_to_tool(const t_tool_name n, t_tool t);
t_tool add_tool_version_to_tool(const t_tool_version v, t_tool t);

// tools
typedef struct s_tools {
	t_tool				tool;
	struct s_tools 		*next;
} s_tools, *t_tools;
t_tools empty_tools();
void free_tools(t_tools t);
void dump_tools(t_tools t);
t_tools add_tool_to_tools(const t_tool tg,                  t_tools t);

// compiler_version of compiler tools
typedef struct s_compiler_version {
	t_host_type                     host_type;
	t_host_name                     host_name;
	t_tools                         tools;
} s_compiler_version, *t_compiler_version;
t_compiler_version empty_compiler_version();
void free_compiler_version(t_compiler_version v);
void dump_compiler_version(t_compiler_version v);
t_compiler_version add_host_type_to_compiler_version(const t_host_type t, t_compiler_version v);
t_compiler_version add_host_name_to_compiler_version(const t_host_name n, t_compiler_version v);
t_compiler_version add_tool_to_compiler_version(const t_tool t, t_compiler_version v);

// compiler_versions
typedef struct s_compiler_versions {
	t_compiler_version		compiler_version;
	struct s_compiler_versions	*next;
} s_compiler_versions, *t_compiler_versions;
void free_compiler_versions(t_compiler_versions vs);
void dump_compiler_versions(t_compiler_versions vs);


// -----------------------------------------------------
// For scenario:
// test_def
typedef struct s_test_def {
	t_test_path			test_path;
	t_options_set			options_set;
} s_test_def, *t_test_def;
t_test_def empty_test_def();
void free_test_def(t_test_def t);
void dump_test_def(t_test_def t);
t_test_def add_test_path_to_test_def(const t_test_path tp, t_test_def t);
t_test_def add_options_set_to_test_def(const t_options_set os, t_test_def t);

// scenario
typedef struct s_scenario {
	t_host_name			host_name;
	t_test_def			test_def;
} s_scenario, *t_scenario;
t_scenario empty_scenario();
void free_scenario(t_scenario s);
void dump_scenario(t_scenario s);
t_scenario add_host_name_to_scenario(const t_host_name h, t_scenario s);
t_scenario add_test_def_to_scenario(const t_test_def t, t_scenario s);

// -----------------------------------------------------
// For param_files:
// param_file
typedef struct s_param_file {
	t_filename			filename;
	t_rawdata			rawdata;
} s_param_file, *t_param_file;
t_param_file empty_param_file();
void free_param_file(t_param_file p);
void dump_param_file(t_param_file p);
t_param_file add_filename_to_param_file(const t_filename f, t_param_file p);
t_param_file add_rawdata_to_param_file(const t_rawdata r, t_param_file p);

// param_files_seq
typedef struct s_param_files_seq {
	t_param_file			param_file;
	struct s_param_files_seq	*next;
} s_param_files_seq, *t_param_files_seq;
t_param_files_seq empty_param_files_seq();
void free_param_files_seq(t_param_files_seq p);
void dump_param_files_seq(t_param_files_seq p);

// param_files
typedef struct s_param_files {
	t_host_name			host_name;
	t_param_files_seq		param_files_seq;
} s_param_files, *t_param_files;
t_param_files empty_param_files();
void free_param_files(t_param_files p);
void dump_param_files(t_param_files p);
t_param_files add_host_name_to_param_files(const t_host_name h, t_param_files ps);
t_param_files add_param_file_to_param_files(const t_param_file p, t_param_files ps);

// -----------------------------------------------------
// compilation
typedef struct s_compilation {
      t_target                          target;
      t_cflags                          cflags;
      t_make_argv                       make_argv;
      t_date                            start_date;
      t_date                            end_date;         
} s_compilation, *t_compilation;
t_compilation empty_compilation();
void free_compilation(t_compilation c);
void dump_compilation(t_compilation c);


t_compilation add_target_to_compilation(const t_target t,                     t_compilation c);
t_compilation add_cflags_to_compilation(const t_cflags f,                     t_compilation c);
t_compilation add_make_argv_to_compilation(const t_make_argv m,               t_compilation c);
t_compilation add_start_date_to_compilation(const t_date d,                   t_compilation c);
t_compilation add_end_date_to_compilation(const t_date d,                     t_compilation c);

// -----------------------------------------------------
// compilations
typedef struct s_compilations {
	t_compilation		compilation;
	struct s_compilations	*next;
} s_compilations, *t_compilations;
t_compilations empty_compilations();
void free_compilations(t_compilations c);
void dump_compilations(t_compilations c);
t_compilations add_compilation_to_compilations(const t_compilation c,                  t_compilations cs);

// -----------------------------------------------------
// exec
typedef struct s_exec {
      t_target                          target;
      t_description                     description;
      t_status                          status;
      t_size                            size;
      t_input                           input;
      t_n_frames                        n_frames;
      t_sample_p_frame                  sample_p_frame;
      t_e_freq                          e_freq;
      t_argv                            argv;
      t_cycles                          cycles;
      t_cycles_p_frame                  cycles_p_frame;
      t_mips                            mips;
      t_date                            start_date;
      t_date                            end_date;         
} s_exec, *t_exec;
t_exec empty_exec();
void free_exec(t_exec e);
void dump_exec(t_exec e);
t_exec add_target_to_exec(const t_target t,                     t_exec e);
t_exec add_description_to_exec(const t_description d,           t_exec e);
t_exec add_status_to_exec(const t_status s,                     t_exec e);
t_exec add_size_to_exec(const t_size s,                         t_exec e);
t_exec add_input_to_exec(const t_input i,                       t_exec e);
t_exec add_n_frames_to_exec(const t_n_frames nf,                t_exec e);
t_exec add_sample_p_frame_to_exec(const t_sample_p_frame sf,    t_exec e);
t_exec add_e_freq_to_exec(const t_e_freq ef,                    t_exec e);
t_exec add_argv_to_exec(const t_argv a,                         t_exec e);
t_exec add_cycles_to_exec(const t_cycles c,                     t_exec e);
t_exec add_cycles_p_frame_to_exec(const t_cycles_p_frame c,     t_exec e);
t_exec add_mips_to_exec(const t_mips m,                         t_exec e);
t_exec add_start_date_to_exec(const t_date d,                   t_exec e);
t_exec add_end_date_to_exec(const t_date d,                     t_exec e);

// -----------------------------------------------------
// execs
typedef struct s_execs {
	t_exec		exec;
	struct s_execs	*next;
} s_execs, *t_execs;
t_execs empty_execs();
void free_execs(t_execs e);
void dump_execs(t_execs e);
t_execs add_exec_to_execs(const t_exec e,                  t_execs es);

// -----------------------------------------------------
// targets
typedef struct s_targets {
	t_target		target;
	struct s_targets	*next;
} s_targets, *t_targets;
t_targets empty_targets();
void free_targets(t_targets t);
void dump_targets(t_targets t);
t_targets add_target_to_targets(const t_target tg,                  t_targets t);

// -----------------------------------------------------
// test
typedef struct s_test {
      t_test_path                       test_path;
      t_date                            start_date;
      t_date                            end_date;
      t_test_name                       test_name;
      t_host_name                       host_name;
      t_test_mode                       test_mode;
      t_level                           level;
      t_cc_options                      cc_options;
      t_cflags                          cflags;
      t_makefile                        makefile;
      t_make_options                    make_options;
      t_simulator                       simulator;
      t_sim_options                     sim_options;
      t_targets                         targets;
      t_compilations                    compilations;
      t_execs                           execs;
      t_opt_report_errors               opt_report_errors;
} s_test, *t_test;
t_test empty_test();
void free_test(t_test t);
void dump_test(t_test t);
t_test add_test_path_to_test(const t_test_path tp,              t_test t);
t_test add_start_date_to_test(const t_date d,                   t_test t);
t_test add_end_date_to_test(const t_date d,                     t_test t);
t_test add_test_name_to_test(const t_test_name tn,              t_test t);
t_test add_host_name_to_test(const t_host_name hn,              t_test t);
t_test add_test_mode_to_test(const t_test_mode m,               t_test t);
t_test add_level_to_test(const t_level l,                       t_test t);
t_test add_cc_options_to_test(const t_cc_options co,            t_test t);
t_test add_cflags_to_test(const t_cflags cf,                    t_test t);
t_test add_makefile_to_test(const t_makefile m,                 t_test t);
t_test add_make_options_to_test(const t_make_options mo,        t_test t);
t_test add_simulator_to_test(const t_simulator s,               t_test t);
t_test add_sim_options_to_test(const t_sim_options so,          t_test t);
t_test add_targets_to_test(const t_targets tg,                  t_test t);
t_test add_compilation_to_test(const t_compilation c,           t_test t);
t_test add_exec_to_test(const t_exec e,                         t_test t);
t_test add_opt_report_error_to_test(const t_opt_report_error e, t_test t);

// -----------------------------------------------------
// tests
typedef struct s_tests {
	t_test		test;
	struct s_tests	*next;
} s_tests, *t_tests;
void free_tests(t_tests t);
void dump_tests(t_tests t);

// -----------------------------------------------------
// report
typedef struct s_report {
      t_run_id                  run_id          ;
      t_scenario_file           scenario_file   ;
      t_date                    start_date      ;
      t_date                    end_date        ;
      t_compiler_versions       compiler_versions;
      t_scenario                scenario        ;
      t_param_files             param_files     ;
      t_tests                   tests           ;
      t_opt_report_errors	opt_report_errors;
} s_report, *t_report;
t_report empty_report();
void free_report(t_report r);
void dump_report(t_report r);
t_report add_run_id_to_report(const t_run_id ri,                        t_report r);
t_report add_scenario_file_to_report(const t_scenario_file sf,          t_report r);
t_report add_start_date_to_report(const t_date d,                       t_report r);
t_report add_end_date_to_report(const t_date d,                         t_report r);
t_report add_compiler_version_to_report(const t_compiler_version v,     t_report r);
t_report add_scenario_to_report(const t_scenario s,                     t_report r);
t_report add_param_files_to_report(const t_param_files p,               t_report r);
t_report add_test_to_report(const t_test t,                             t_report r);
t_report add_opt_report_error_to_report(const t_opt_report_error e,     t_report r);

// reports
typedef struct s_reports {
	t_report		report;
	struct s_reports	*next;
} s_reports, *t_reports;
void free_reports(t_reports r);
void dump_reports(t_reports r);

// -----------------------------------------------------
// history
typedef struct s_history {
	int			nb_reports;
	t_reports		reports;
	t_reports		last_report;
} s_history, *t_history;
void free_history(t_history h);
void dump_history(t_history h);
t_history empty_history(); 
t_history add_report_to_history(const t_report r, t_history h) ;

/* ----------------------------------------------------------------*/
/* Here are the functions definitions for the report objects types */
/* are in common_yacc_lex.c                                        */
/* ----------------------------------------------------------------*/

// DESCRIPTION: insensitive string comparison with an uppercase string
int strcmpiu(char *i, char *u);

// DESCRIPTION: insensitive string comparison with a lowercase string
int strcmpil(char *i, char *u);

// Result of the parsing
extern t_history result_history;
//
extern int		 nb_execs;

#endif








