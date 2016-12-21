#ifndef BISON_SRC_XML_HIST_YACC_H
# define BISON_SRC_XML_HIST_YACC_H

#ifndef YYSTYPE
typedef union {
	char			*s;
	t_history		FLXT_history;
	t_report		FLXT_report;
	t_attribute_seq_opt	FLXT_attribute_seq_opt;
	t_run_id		FLXT_run_id;
	t_scenario_file   	FLXT_scenario_file;
	t_date            	FLXT_start_date;
	t_date            	FLXT_end_date;
	
	t_compiler_version	FLXT_compiler_version;
	t_host_type		FLXT_host_type;
	t_host_name		FLXT_host_name;
	t_tool                  FLXT_tool;
	t_tool_name             FLXT_tool_name;
	t_tool_version          FLXT_tool_version;

	t_scenario              FLXT_scenario;
	t_test_def		FLXT_test_def;
	t_param_files           FLXT_param_files;
	t_filename		FLXT_filename;
	t_rawdata		FLXT_rawdata;
	t_param_file            FLXT_param_file;
	t_test                  FLXT_test;
	t_opt_report_error      FLXT_opt_report_error;

	t_test_path             FLXT_test_path;
	t_options_set		FLXT_options_set;
	t_test_name             FLXT_test_name;
	t_test_mode             FLXT_test_mode;
	t_level                 FLXT_level;
	t_cc_options            FLXT_cc_options;
	t_cflags                FLXT_cflags;
	t_makefile              FLXT_makefile;
	t_make_options          FLXT_make_options;
	t_simulator             FLXT_simulator;
	t_sim_options           FLXT_sim_options;
	t_targets               FLXT_targets;
	t_compilation           FLXT_compilation;
	t_make_argv             FLXT_make_argv;
	t_exec                  FLXT_exec;
	t_target                FLXT_target;

	t_description           FLXT_description;
	t_status                FLXT_status;
	t_size                  FLXT_size;
	t_input                 FLXT_input;
	t_n_frames              FLXT_n_frames;
	t_sample_p_frame        FLXT_sample_p_frame;
	t_e_freq                FLXT_e_freq;
	t_argv                  FLXT_argv;
	t_cycles                FLXT_cycles;
	t_cycles_p_frame        FLXT_cycles_p_frame;
	t_mips                  FLXT_mips;
	t_attribute             FLXT_attribute;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	VERSION	257
# define	ATTDEF	258
# define	ENDDEF	259
# define	EQ	260
# define	SLASH	261
# define	CLOSE	262
# define	END	263
# define	START_HISTORY	264
# define	CLOSE_HISTORY	265
# define	START_REPORT	266
# define	CLOSE_REPORT	267
# define	START_RUN_ID	268
# define	CLOSE_RUN_ID	269
# define	START_SCENARIO_FILE	270
# define	CLOSE_SCENARIO_FILE	271
# define	START_START_DATE	272
# define	CLOSE_START_DATE	273
# define	START_END_DATE	274
# define	CLOSE_END_DATE	275
# define	START_COMPILER_VERSION	276
# define	CLOSE_COMPILER_VERSION	277
# define	START_TOOL	278
# define	CLOSE_TOOL	279
# define	START_TOOL_NAME	280
# define	CLOSE_TOOL_NAME	281
# define	START_TOOL_VERSION	282
# define	CLOSE_TOOL_VERSION	283
# define	START_SCENARIO	284
# define	CLOSE_SCENARIO	285
# define	START_PARAM_FILES	286
# define	CLOSE_PARAM_FILES	287
# define	START_PARAM_FILE	288
# define	CLOSE_PARAM_FILE	289
# define	START_FILENAME	290
# define	CLOSE_FILENAME	291
# define	START_TEST_DEF	292
# define	CLOSE_TEST_DEF	293
# define	START_TEST_PATH	294
# define	CLOSE_TEST_PATH	295
# define	START_OPTIONS_SET	296
# define	CLOSE_OPTIONS_SET	297
# define	START_TEST	298
# define	CLOSE_TEST	299
# define	START_TEST_NAME	300
# define	CLOSE_TEST_NAME	301
# define	START_HOST_TYPE	302
# define	CLOSE_HOST_TYPE	303
# define	START_HOST_NAME	304
# define	CLOSE_HOST_NAME	305
# define	START_TEST_MODE	306
# define	CLOSE_TEST_MODE	307
# define	START_LEVEL	308
# define	CLOSE_LEVEL	309
# define	START_CC_OPTIONS	310
# define	CLOSE_CC_OPTIONS	311
# define	START_CFLAGS	312
# define	CLOSE_CFLAGS	313
# define	START_MAKEFILE	314
# define	CLOSE_MAKEFILE	315
# define	START_MAKE_OPTIONS	316
# define	CLOSE_MAKE_OPTIONS	317
# define	START_SIMULATOR	318
# define	CLOSE_SIMULATOR	319
# define	START_SIM_OPTIONS	320
# define	CLOSE_SIM_OPTIONS	321
# define	START_TARGETS	322
# define	CLOSE_TARGETS	323
# define	START_TARGET	324
# define	CLOSE_TARGET	325
# define	START_COMPILATION	326
# define	CLOSE_COMPILATION	327
# define	START_MAKE_ARGV	328
# define	CLOSE_MAKE_ARGV	329
# define	START_EXEC	330
# define	CLOSE_EXEC	331
# define	START_DESCRIPTION	332
# define	CLOSE_DESCRIPTION	333
# define	START_STATUS	334
# define	CLOSE_STATUS	335
# define	START_SIZE	336
# define	CLOSE_SIZE	337
# define	START_INPUT	338
# define	CLOSE_INPUT	339
# define	START_N_FRAMES	340
# define	CLOSE_N_FRAMES	341
# define	START_SAMPLE_P_FRAME	342
# define	CLOSE_SAMPLE_P_FRAME	343
# define	START_E_FREQ	344
# define	CLOSE_E_FREQ	345
# define	START_ARGV	346
# define	CLOSE_ARGV	347
# define	START_CYCLES	348
# define	CLOSE_CYCLES	349
# define	START_CYCLES_P_FRAME	350
# define	CLOSE_CYCLES_P_FRAME	351
# define	START_MIPS	352
# define	CLOSE_MIPS	353
# define	START_OPT_REPORT_ERROR	354
# define	CLOSE_OPT_REPORT_ERROR	355
# define	ENCODING	356
# define	NAME	357
# define	VALUE	358
# define	DATA	359
# define	COMMENT	360
# define	START	361
# define	RAWDATA	362


extern YYSTYPE yy1lval;

#endif /* not BISON_SRC_XML_HIST_YACC_H */
