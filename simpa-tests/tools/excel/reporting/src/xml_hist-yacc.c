/* A Bison parser, made from src/xml_hist.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse yy1parse
#define yylex yy1lex
#define yyerror yy1error
#define yylval yy1lval
#define yychar yy1char
#define yydebug yy1debug
#define yynerrs yy1nerrs
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

#line 11 "src/xml_hist.y"

#include "common_yacc_lex.h"
extern char yy1text[];

/* #define my_printf(x...) printf(x) */
#define my_printf(x...) {}


#line 171 "src/xml_hist.y"
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
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		571
#define	YYFLAG		-32768
#define	YYNTBASE	109

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 362 ? yytranslate[x] : 317)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     6,    10,    12,    13,    15,    16,    19,
      20,    22,    24,    25,    31,    32,    37,    40,    41,    46,
      49,    52,    54,    55,    56,    61,    64,    65,    70,    73,
      76,    79,    82,    85,    88,    91,    94,    97,   100,   102,
     103,   104,   109,   112,   113,   118,   121,   124,   127,   129,
     130,   131,   136,   139,   140,   145,   148,   151,   154,   156,
     157,   158,   163,   166,   167,   172,   175,   178,   181,   184,
     187,   190,   193,   196,   199,   202,   205,   208,   211,   214,
     217,   220,   223,   226,   228,   229,   230,   235,   238,   239,
     244,   247,   250,   252,   253,   254,   259,   262,   263,   268,
     271,   274,   277,   280,   283,   286,   288,   289,   290,   295,
     298,   299,   304,   307,   310,   313,   316,   319,   322,   325,
     328,   331,   334,   337,   340,   343,   346,   349,   351,   352,
     353,   358,   361,   362,   367,   370,   373,   376,   379,   381,
     382,   383,   388,   391,   392,   397,   400,   403,   406,   408,
     409,   410,   415,   418,   419,   424,   427,   430,   433,   435,
     436,   437,   442,   445,   446,   451,   454,   457,   460,   462,
     463,   466,   467,   469,   473,   474,   479,   482,   483,   488,
     489,   494,   497,   498,   503,   504,   509,   512,   513,   518,
     519,   524,   527,   528,   533,   534,   539,   542,   543,   548,
     549,   554,   557,   558,   563,   564,   569,   572,   573,   578,
     579,   584,   587,   588,   593,   594,   599,   602,   603,   608,
     609,   614,   617,   618,   623,   624,   629,   632,   633,   638,
     639,   644,   647,   648,   653,   654,   659,   662,   663,   668,
     669,   674,   677,   678,   683,   684,   689,   692,   693,   698,
     699,   704,   707,   708,   713,   714,   719,   722,   723,   728,
     729,   734,   737,   738,   743,   744,   749,   752,   753,   758,
     759,   764,   767,   768,   773,   774,   779,   782,   783,   788,
     789,   794,   797,   798,   803,   804,   809,   812,   813,   818,
     819,   824,   827,   828,   833,   834,   839,   842,   843,   848,
     849,   854,   857,   858,   863,   864,   869,   872,   873,   878,
     879,   884,   887,   888,   893,   894,   899,   902,   903,   908,
     909,   914,   917,   918,   923,   924,   929,   932,   933,   938,
     939,   944,   947,   948,   953,   954,   959,   962,   963,   968,
     969,   974,   977,   978,   983,   986,   989,   991
};
static const short yyrhs[] =
{
      -1,   111,   118,   110,   114,     0,   112,   113,   114,     0,
       3,     0,     0,   102,     0,     0,   114,   115,     0,     0,
     106,     0,   116,     0,     0,     4,   103,   117,   178,     5,
       0,     0,    10,   119,   178,   120,     0,     7,     8,     0,
       0,     8,   121,   122,    11,     0,   122,   115,     0,   122,
     123,     0,     1,     0,     0,     0,    12,   124,   178,   125,
       0,     7,     8,     0,     0,     8,   126,   127,    13,     0,
     127,   115,     0,   127,   180,     0,   127,   184,     0,   127,
     188,     0,   127,   192,     0,   127,   158,     0,   127,   128,
       0,   127,   168,     0,   127,   138,     0,   127,   196,     0,
       1,     0,     0,     0,    30,   129,   178,   130,     0,     7,
       8,     0,     0,     8,   131,   132,    31,     0,   132,   115,
       0,   132,   204,     0,   132,   133,     0,     1,     0,     0,
       0,    38,   134,   178,   135,     0,     7,     8,     0,     0,
       8,   136,   137,    39,     0,   137,   115,     0,   137,   220,
       0,   137,   224,     0,     1,     0,     0,     0,    44,   139,
     178,   140,     0,     7,     8,     0,     0,     8,   141,   142,
      45,     0,   142,   115,     0,   142,   220,     0,   142,   188,
       0,   142,   192,     0,   142,   228,     0,   142,   204,     0,
     142,   232,     0,   142,   236,     0,   142,   240,     0,   142,
     244,     0,   142,   248,     0,   142,   252,     0,   142,   256,
       0,   142,   260,     0,   142,   143,     0,   142,   148,     0,
     142,   153,     0,   142,   196,     0,     1,     0,     0,     0,
      68,   144,   178,   145,     0,     7,     8,     0,     0,     8,
     146,   147,    69,     0,   147,   115,     0,   147,   264,     0,
       1,     0,     0,     0,    72,   149,   178,   150,     0,     7,
       8,     0,     0,     8,   151,   152,    73,     0,   152,   115,
       0,   152,   264,     0,   152,   244,     0,   152,   268,     0,
     152,   188,     0,   152,   192,     0,     1,     0,     0,     0,
      76,   154,   178,   155,     0,     7,     8,     0,     0,     8,
     156,   157,    77,     0,   157,   115,     0,   157,   264,     0,
     157,   272,     0,   157,   276,     0,   157,   280,     0,   157,
     284,     0,   157,   288,     0,   157,   292,     0,   157,   296,
       0,   157,   300,     0,   157,   304,     0,   157,   308,     0,
     157,   312,     0,   157,   188,     0,   157,   192,     0,     1,
       0,     0,     0,    22,   159,   178,   160,     0,     7,     8,
       0,     0,     8,   161,   162,    23,     0,   162,   115,     0,
     162,   200,     0,   162,   204,     0,   162,   163,     0,     1,
       0,     0,     0,    24,   164,   178,   165,     0,     7,     8,
       0,     0,     8,   166,   167,    25,     0,   167,   115,     0,
     167,   208,     0,   167,   212,     0,     1,     0,     0,     0,
      32,   169,   178,   170,     0,     7,     8,     0,     0,     8,
     171,   172,    33,     0,   172,   115,     0,   172,   204,     0,
     172,   173,     0,     1,     0,     0,     0,    34,   174,   178,
     175,     0,     7,     8,     0,     0,     8,   176,   177,    35,
       0,   177,   115,     0,   177,   216,     0,   177,   108,     0,
       1,     0,     0,   178,   179,     0,     0,   103,     0,   103,
       6,   104,     0,     0,    14,   181,   178,   182,     0,     7,
       8,     0,     0,     8,   183,   316,    15,     0,     0,    16,
     185,   178,   186,     0,     7,     8,     0,     0,     8,   187,
     316,    17,     0,     0,    18,   189,   178,   190,     0,     7,
       8,     0,     0,     8,   191,   316,    19,     0,     0,    20,
     193,   178,   194,     0,     7,     8,     0,     0,     8,   195,
     316,    21,     0,     0,   100,   197,   178,   198,     0,     7,
       8,     0,     0,     8,   199,   316,   101,     0,     0,    48,
     201,   178,   202,     0,     7,     8,     0,     0,     8,   203,
     316,    49,     0,     0,    50,   205,   178,   206,     0,     7,
       8,     0,     0,     8,   207,   316,    51,     0,     0,    26,
     209,   178,   210,     0,     7,     8,     0,     0,     8,   211,
     316,    27,     0,     0,    28,   213,   178,   214,     0,     7,
       8,     0,     0,     8,   215,   316,    29,     0,     0,    36,
     217,   178,   218,     0,     7,     8,     0,     0,     8,   219,
     316,    37,     0,     0,    40,   221,   178,   222,     0,     7,
       8,     0,     0,     8,   223,   316,    41,     0,     0,    42,
     225,   178,   226,     0,     7,     8,     0,     0,     8,   227,
     316,    43,     0,     0,    46,   229,   178,   230,     0,     7,
       8,     0,     0,     8,   231,   316,    47,     0,     0,    52,
     233,   178,   234,     0,     7,     8,     0,     0,     8,   235,
     316,    53,     0,     0,    54,   237,   178,   238,     0,     7,
       8,     0,     0,     8,   239,   316,    55,     0,     0,    56,
     241,   178,   242,     0,     7,     8,     0,     0,     8,   243,
     316,    57,     0,     0,    58,   245,   178,   246,     0,     7,
       8,     0,     0,     8,   247,   316,    59,     0,     0,    60,
     249,   178,   250,     0,     7,     8,     0,     0,     8,   251,
     316,    61,     0,     0,    62,   253,   178,   254,     0,     7,
       8,     0,     0,     8,   255,   316,    63,     0,     0,    64,
     257,   178,   258,     0,     7,     8,     0,     0,     8,   259,
     316,    65,     0,     0,    66,   261,   178,   262,     0,     7,
       8,     0,     0,     8,   263,   316,    67,     0,     0,    70,
     265,   178,   266,     0,     7,     8,     0,     0,     8,   267,
     316,    71,     0,     0,    74,   269,   178,   270,     0,     7,
       8,     0,     0,     8,   271,   316,    75,     0,     0,    78,
     273,   178,   274,     0,     7,     8,     0,     0,     8,   275,
     316,    79,     0,     0,    80,   277,   178,   278,     0,     7,
       8,     0,     0,     8,   279,   316,    81,     0,     0,    82,
     281,   178,   282,     0,     7,     8,     0,     0,     8,   283,
     316,    83,     0,     0,    84,   285,   178,   286,     0,     7,
       8,     0,     0,     8,   287,   316,    85,     0,     0,    86,
     289,   178,   290,     0,     7,     8,     0,     0,     8,   291,
     316,    87,     0,     0,    88,   293,   178,   294,     0,     7,
       8,     0,     0,     8,   295,   316,    89,     0,     0,    90,
     297,   178,   298,     0,     7,     8,     0,     0,     8,   299,
     316,    91,     0,     0,    92,   301,   178,   302,     0,     7,
       8,     0,     0,     8,   303,   316,    93,     0,     0,    94,
     305,   178,   306,     0,     7,     8,     0,     0,     8,   307,
     316,    95,     0,     0,    96,   309,   178,   310,     0,     7,
       8,     0,     0,     8,   311,   316,    97,     0,     0,    98,
     313,   178,   314,     0,     7,     8,     0,     0,     8,   315,
     316,    99,     0,   316,   105,     0,   316,   115,     0,     1,
       0,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   236,   236,   241,   245,   246,   249,   250,   253,   254,
     257,   258,   261,   261,   288,   288,   293,   297,   297,   305,
     306,   308,   309,   313,   313,   318,   322,   322,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     345,   345,   350,   354,   354,   362,   363,   365,   367,   368,
     372,   372,   377,   381,   381,   389,   390,   392,   394,   395,
     399,   399,   404,   408,   408,   416,   417,   418,   419,   420,
     421,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   434,   435,   439,   439,   444,   448,   448,
     456,   457,   459,   460,   465,   465,   470,   474,   474,   482,
     483,   484,   485,   486,   487,   488,   489,   493,   493,   498,
     503,   503,   512,   513,   514,   515,   516,   517,   518,   519,
     520,   521,   522,   523,   524,   525,   526,   527,   528,   532,
     532,   537,   541,   541,   549,   550,   552,   554,   556,   557,
     561,   561,   566,   570,   570,   578,   579,   581,   583,   584,
     588,   588,   593,   597,   597,   605,   606,   608,   610,   611,
     615,   615,   620,   624,   624,   632,   633,   635,   640,   641,
     645,   646,   649,   650,   654,   654,   659,   660,   660,   666,
     666,   671,   672,   672,   678,   678,   683,   684,   684,   690,
     690,   695,   696,   696,   702,   702,   707,   708,   708,   714,
     714,   719,   720,   720,   726,   726,   731,   732,   732,   738,
     738,   743,   744,   744,   750,   750,   755,   756,   756,   762,
     762,   767,   768,   768,   774,   774,   779,   780,   780,   786,
     786,   791,   792,   792,   798,   798,   803,   804,   804,   810,
     810,   815,   816,   816,   822,   822,   827,   828,   828,   834,
     834,   839,   840,   840,   846,   846,   851,   852,   852,   858,
     858,   863,   864,   864,   870,   870,   875,   876,   876,   882,
     882,   887,   888,   888,   894,   894,   899,   900,   900,   906,
     906,   911,   912,   912,   918,   918,   923,   924,   924,   930,
     930,   935,   936,   936,   942,   942,   947,   948,   948,   954,
     954,   959,   960,   960,   966,   966,   971,   972,   972,   978,
     978,   983,   984,   984,   990,   990,   995,   996,   996,  1002,
    1002,  1007,  1008,  1008,  1014,  1014,  1019,  1020,  1020,  1026,
    1026,  1031,  1032,  1032,  1038,  1038,  1043,  1044,  1044,  1050,
    1050,  1055,  1056,  1056,  1062,  1063,  1064,  1065
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "VERSION", "ATTDEF", "ENDDEF", "EQ", "SLASH", 
  "CLOSE", "END", "START_HISTORY", "CLOSE_HISTORY", "START_REPORT", 
  "CLOSE_REPORT", "START_RUN_ID", "CLOSE_RUN_ID", "START_SCENARIO_FILE", 
  "CLOSE_SCENARIO_FILE", "START_START_DATE", "CLOSE_START_DATE", 
  "START_END_DATE", "CLOSE_END_DATE", "START_COMPILER_VERSION", 
  "CLOSE_COMPILER_VERSION", "START_TOOL", "CLOSE_TOOL", "START_TOOL_NAME", 
  "CLOSE_TOOL_NAME", "START_TOOL_VERSION", "CLOSE_TOOL_VERSION", 
  "START_SCENARIO", "CLOSE_SCENARIO", "START_PARAM_FILES", 
  "CLOSE_PARAM_FILES", "START_PARAM_FILE", "CLOSE_PARAM_FILE", 
  "START_FILENAME", "CLOSE_FILENAME", "START_TEST_DEF", "CLOSE_TEST_DEF", 
  "START_TEST_PATH", "CLOSE_TEST_PATH", "START_OPTIONS_SET", 
  "CLOSE_OPTIONS_SET", "START_TEST", "CLOSE_TEST", "START_TEST_NAME", 
  "CLOSE_TEST_NAME", "START_HOST_TYPE", "CLOSE_HOST_TYPE", 
  "START_HOST_NAME", "CLOSE_HOST_NAME", "START_TEST_MODE", 
  "CLOSE_TEST_MODE", "START_LEVEL", "CLOSE_LEVEL", "START_CC_OPTIONS", 
  "CLOSE_CC_OPTIONS", "START_CFLAGS", "CLOSE_CFLAGS", "START_MAKEFILE", 
  "CLOSE_MAKEFILE", "START_MAKE_OPTIONS", "CLOSE_MAKE_OPTIONS", 
  "START_SIMULATOR", "CLOSE_SIMULATOR", "START_SIM_OPTIONS", 
  "CLOSE_SIM_OPTIONS", "START_TARGETS", "CLOSE_TARGETS", "START_TARGET", 
  "CLOSE_TARGET", "START_COMPILATION", "CLOSE_COMPILATION", 
  "START_MAKE_ARGV", "CLOSE_MAKE_ARGV", "START_EXEC", "CLOSE_EXEC", 
  "START_DESCRIPTION", "CLOSE_DESCRIPTION", "START_STATUS", 
  "CLOSE_STATUS", "START_SIZE", "CLOSE_SIZE", "START_INPUT", 
  "CLOSE_INPUT", "START_N_FRAMES", "CLOSE_N_FRAMES", 
  "START_SAMPLE_P_FRAME", "CLOSE_SAMPLE_P_FRAME", "START_E_FREQ", 
  "CLOSE_E_FREQ", "START_ARGV", "CLOSE_ARGV", "START_CYCLES", 
  "CLOSE_CYCLES", "START_CYCLES_P_FRAME", "CLOSE_CYCLES_P_FRAME", 
  "START_MIPS", "CLOSE_MIPS", "START_OPT_REPORT_ERROR", 
  "CLOSE_OPT_REPORT_ERROR", "ENCODING", "NAME", "VALUE", "DATA", 
  "COMMENT", "START", "RAWDATA", "document", "@1", "prolog", 
  "version_opt", "encoding_opt", "misc_seq_opt", "misc", "attribute_decl", 
  "@2", "element_history", "@3", "empty_or_content_history", "@4", 
  "content_history", "element_report", "@5", "empty_or_content_report", 
  "@6", "content_report", "element_scenario", "@7", 
  "empty_or_content_scenario", "@8", "content_scenario", 
  "element_test_def", "@9", "empty_or_content_test_def", "@10", 
  "content_test_def", "element_test", "@11", "empty_or_content_test", 
  "@12", "content_test", "element_targets", "@13", 
  "empty_or_content_targets", "@14", "content_targets", 
  "element_compilation", "@15", "empty_or_content_compilation", "@16", 
  "content_compilation", "element_exec", "@17", "empty_or_content_exec", 
  "@18", "content_exec", "element_compiler_version", "@19", 
  "empty_or_content_compiler_version", "@20", "content_compiler_version", 
  "element_tool", "@21", "empty_or_content_tool", "@22", "content_tool", 
  "element_param_files", "@23", "empty_or_content_param_files", "@24", 
  "content_param_files", "element_param_file", "@25", 
  "empty_or_content_param_file", "@26", "content_param_file", 
  "attribute_seq_opt", "attribute", "element_run_id", "@27", 
  "empty_or_content_run_id", "@28", "element_scenario_file", "@29", 
  "empty_or_content_scenario_file", "@30", "element_start_date", "@31", 
  "empty_or_content_start_date", "@32", "element_end_date", "@33", 
  "empty_or_content_end_date", "@34", "element_opt_report_error", "@35", 
  "empty_or_content_opt_report_error", "@36", "element_host_type", "@37", 
  "empty_or_content_host_type", "@38", "element_host_name", "@39", 
  "empty_or_content_host_name", "@40", "element_tool_name", "@41", 
  "empty_or_content_tool_name", "@42", "element_tool_version", "@43", 
  "empty_or_content_tool_version", "@44", "element_filename", "@45", 
  "empty_or_content_filename", "@46", "element_test_path", "@47", 
  "empty_or_content_test_path", "@48", "element_options_set", "@49", 
  "empty_or_content_options_set", "@50", "element_test_name", "@51", 
  "empty_or_content_test_name", "@52", "element_test_mode", "@53", 
  "empty_or_content_test_mode", "@54", "element_level", "@55", 
  "empty_or_content_level", "@56", "element_cc_options", "@57", 
  "empty_or_content_cc_options", "@58", "element_cflags", "@59", 
  "empty_or_content_cflags", "@60", "element_makefile", "@61", 
  "empty_or_content_makefile", "@62", "element_make_options", "@63", 
  "empty_or_content_make_options", "@64", "element_simulator", "@65", 
  "empty_or_content_simulator", "@66", "element_sim_options", "@67", 
  "empty_or_content_sim_options", "@68", "element_target", "@69", 
  "empty_or_content_target", "@70", "element_make_argv", "@71", 
  "empty_or_content_make_argv", "@72", "element_description", "@73", 
  "empty_or_content_description", "@74", "element_status", "@75", 
  "empty_or_content_status", "@76", "element_size", "@77", 
  "empty_or_content_size", "@78", "element_input", "@79", 
  "empty_or_content_input", "@80", "element_n_frames", "@81", 
  "empty_or_content_n_frames", "@82", "element_sample_p_frame", "@83", 
  "empty_or_content_sample_p_frame", "@84", "element_e_freq", "@85", 
  "empty_or_content_e_freq", "@86", "element_argv", "@87", 
  "empty_or_content_argv", "@88", "element_cycles", "@89", 
  "empty_or_content_cycles", "@90", "element_cycles_p_frame", "@91", 
  "empty_or_content_cycles_p_frame", "@92", "element_mips", "@93", 
  "empty_or_content_mips", "@94", "content_string", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,   110,   109,   111,   112,   112,   113,   113,   114,   114,
     115,   115,   117,   116,   119,   118,   120,   121,   120,   122,
     122,   122,   122,   124,   123,   125,   126,   125,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     129,   128,   130,   131,   130,   132,   132,   132,   132,   132,
     134,   133,   135,   136,   135,   137,   137,   137,   137,   137,
     139,   138,   140,   141,   140,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   144,   143,   145,   146,   145,
     147,   147,   147,   147,   149,   148,   150,   151,   150,   152,
     152,   152,   152,   152,   152,   152,   152,   154,   153,   155,
     156,   155,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   159,
     158,   160,   161,   160,   162,   162,   162,   162,   162,   162,
     164,   163,   165,   166,   165,   167,   167,   167,   167,   167,
     169,   168,   170,   171,   170,   172,   172,   172,   172,   172,
     174,   173,   175,   176,   175,   177,   177,   177,   177,   177,
     178,   178,   179,   179,   181,   180,   182,   183,   182,   185,
     184,   186,   187,   186,   189,   188,   190,   191,   190,   193,
     192,   194,   195,   194,   197,   196,   198,   199,   198,   201,
     200,   202,   203,   202,   205,   204,   206,   207,   206,   209,
     208,   210,   211,   210,   213,   212,   214,   215,   214,   217,
     216,   218,   219,   218,   221,   220,   222,   223,   222,   225,
     224,   226,   227,   226,   229,   228,   230,   231,   230,   233,
     232,   234,   235,   234,   237,   236,   238,   239,   238,   241,
     240,   242,   243,   242,   245,   244,   246,   247,   246,   249,
     248,   250,   251,   250,   253,   252,   254,   255,   254,   257,
     256,   258,   259,   258,   261,   260,   262,   263,   262,   265,
     264,   266,   267,   266,   269,   268,   270,   271,   270,   273,
     272,   274,   275,   274,   277,   276,   278,   279,   278,   281,
     280,   282,   283,   282,   285,   284,   286,   287,   286,   289,
     288,   290,   291,   290,   293,   292,   294,   295,   294,   297,
     296,   298,   299,   298,   301,   300,   302,   303,   302,   305,
     304,   306,   307,   306,   309,   308,   310,   311,   310,   313,
     312,   314,   315,   314,   316,   316,   316,   316
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     4,     3,     1,     0,     1,     0,     2,     0,
       1,     1,     0,     5,     0,     4,     2,     0,     4,     2,
       2,     1,     0,     0,     4,     2,     0,     4,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     0,
       0,     4,     2,     0,     4,     2,     2,     2,     1,     0,
       0,     4,     2,     0,     4,     2,     2,     2,     1,     0,
       0,     4,     2,     0,     4,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     0,     0,     4,     2,     0,     4,
       2,     2,     1,     0,     0,     4,     2,     0,     4,     2,
       2,     2,     2,     2,     2,     1,     0,     0,     4,     2,
       0,     4,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     0,     0,
       4,     2,     0,     4,     2,     2,     2,     2,     1,     0,
       0,     4,     2,     0,     4,     2,     2,     2,     1,     0,
       0,     4,     2,     0,     4,     2,     2,     2,     1,     0,
       0,     4,     2,     0,     4,     2,     2,     2,     1,     0,
       2,     0,     1,     3,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     0,     4,     2,     0,     4,     0,
       4,     2,     0,     4,     2,     2,     1,     0
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       5,     4,     0,     7,    14,     1,     6,     9,   171,     9,
       3,     0,     2,     0,    10,     8,    11,     0,    17,   172,
      15,   170,    12,    16,     0,     0,   171,    21,     0,   173,
       0,    18,    23,    19,    20,    13,   171,     0,     0,    26,
      24,    25,     0,    38,     0,    27,   174,   179,   184,   189,
     129,    40,   150,    60,   194,    28,    34,    36,    33,    35,
      29,    30,    31,    32,    37,   171,   171,   171,   171,   171,
     171,   171,   171,   171,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   177,   175,     0,   182,   180,     0,
     187,   185,     0,   192,   190,     0,   132,   130,     0,    43,
      41,     0,   153,   151,     0,    63,    61,     0,   197,   195,
     176,     0,   181,     0,   186,     0,   191,     0,   131,     0,
      42,     0,   152,     0,    62,     0,   196,     0,   346,     0,
       0,     0,     0,   138,     0,    48,     0,   158,     0,    83,
       0,     0,   178,   344,   345,   183,   188,   193,   133,   140,
     199,   204,   134,   137,   135,   136,    44,    50,    45,    47,
      46,   154,   160,   155,   157,   156,   224,    64,   234,   239,
     244,   249,   254,   259,   264,   269,   274,    85,    94,   107,
      65,    79,    80,    81,    67,    68,    82,    70,    66,    69,
      71,    72,    73,    74,    75,    76,    77,    78,   198,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   143,   141,     0,   202,
     200,     0,   207,   205,     0,    53,    51,     0,   163,   161,
       0,   227,   225,     0,   237,   235,     0,   242,   240,     0,
     247,   245,     0,   252,   250,     0,   257,   255,     0,   262,
     260,     0,   267,   265,     0,   272,   270,     0,   277,   275,
       0,    88,    86,     0,    97,    95,     0,   110,   108,   142,
       0,   201,     0,   206,     0,    52,     0,   162,     0,   226,
       0,   236,     0,   241,     0,   246,     0,   251,     0,   256,
       0,   261,     0,   266,     0,   271,     0,   276,     0,    87,
       0,    96,     0,   109,     0,   148,     0,     0,     0,    58,
       0,   168,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    92,     0,   105,     0,   127,     0,   144,
     209,   214,   145,   146,   147,   203,   208,    54,   229,    55,
      56,    57,   164,   219,   167,   165,   166,   228,   238,   243,
     248,   253,   258,   263,   268,   273,   278,    89,   279,    90,
      91,    98,   284,    99,   103,   104,   101,   100,   102,   111,
     289,   294,   299,   304,   309,   314,   319,   324,   329,   334,
     339,   112,   125,   126,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   212,   210,     0,   217,   215,     0,   232,   230,     0,
     222,   220,     0,   282,   280,     0,   287,   285,     0,   292,
     290,     0,   297,   295,     0,   302,   300,     0,   307,   305,
       0,   312,   310,     0,   317,   315,     0,   322,   320,     0,
     327,   325,     0,   332,   330,     0,   337,   335,     0,   342,
     340,   211,     0,   216,     0,   231,     0,   221,     0,   281,
       0,   286,     0,   291,     0,   296,     0,   301,     0,   306,
       0,   311,     0,   316,     0,   321,     0,   326,     0,   331,
       0,   336,     0,   341,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   213,   218,   233,   223,   283,   288,   293,   298,
     303,   308,   313,   318,   323,   328,   333,   338,   343,     0,
       0,     0
};

static const short yydefgoto[] =
{
     569,     9,     2,     3,     7,    10,   144,    16,    26,     5,
       8,    20,    24,    28,    34,    36,    40,    42,    44,    56,
      70,   100,   121,   136,   159,   202,   246,   296,   330,    57,
      72,   106,   125,   140,   181,   214,   282,   320,   344,   182,
     215,   285,   322,   346,   183,   216,   288,   324,   348,    58,
      69,    97,   119,   134,   153,   199,   237,   290,   326,    59,
      71,   103,   123,   138,   164,   203,   249,   298,   332,    11,
      21,    60,    65,    85,   111,    61,    66,    88,   113,    62,
      67,    91,   115,    63,    68,    94,   117,    64,    73,   109,
     127,   154,   200,   240,   292,   155,   201,   243,   294,   353,
     416,   452,   502,   354,   417,   455,   504,   366,   419,   461,
     508,   188,   204,   252,   300,   361,   418,   458,   506,   189,
     205,   255,   302,   190,   206,   258,   304,   191,   207,   261,
     306,   192,   208,   264,   308,   193,   209,   267,   310,   194,
     210,   270,   312,   195,   211,   273,   314,   196,   212,   276,
     316,   197,   213,   279,   318,   380,   420,   464,   510,   388,
     421,   467,   512,   405,   422,   470,   514,   406,   423,   473,
     516,   407,   424,   476,   518,   408,   425,   479,   520,   409,
     426,   482,   522,   410,   427,   485,   524,   411,   428,   488,
     526,   412,   429,   491,   528,   413,   430,   494,   530,   414,
     431,   497,   532,   415,   432,   500,   534,   129
};

static const short yypact[] =
{
      19,-32768,    -3,   -91,-32768,-32768,-32768,-32768,-32768,-32768,
       8,    50,     8,   -88,-32768,-32768,-32768,    18,-32768,    30,
  -32768,-32768,-32768,-32768,    59,   -66,-32768,-32768,    12,-32768,
      32,-32768,-32768,-32768,-32768,-32768,-32768,   223,    33,-32768,
  -32768,-32768,   142,-32768,   288,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,   225,   307,   378,   701,   709,   729,
     735,   737,   740,    36,-32768,-32768,    38,-32768,-32768,    44,
  -32768,-32768,    48,-32768,-32768,    54,-32768,-32768,    61,-32768,
  -32768,    74,-32768,-32768,    76,-32768,-32768,    77,-32768,-32768,
  -32768,    16,-32768,   165,-32768,   235,-32768,   167,-32768,     5,
  -32768,   224,-32768,   150,-32768,    41,-32768,   174,-32768,   146,
     500,   584,   577,-32768,   488,-32768,   465,-32768,   509,-32768,
     562,   531,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,   742,   760,   771,
     776,   784,   793,   798,   803,   806,   808,   810,   812,   814,
     816,   818,   820,   822,   826,    86,-32768,-32768,    88,-32768,
  -32768,    90,-32768,-32768,    92,-32768,-32768,    94,-32768,-32768,
      96,-32768,-32768,    98,-32768,-32768,   100,-32768,-32768,   125,
  -32768,-32768,   129,-32768,-32768,   131,-32768,-32768,   137,-32768,
  -32768,   149,-32768,-32768,   151,-32768,-32768,   155,-32768,-32768,
     159,-32768,-32768,   168,-32768,-32768,   196,-32768,-32768,-32768,
      64,-32768,   237,-32768,   239,-32768,     9,-32768,     4,-32768,
     243,-32768,   256,-32768,   260,-32768,   264,-32768,   277,-32768,
     349,-32768,   351,-32768,   262,-32768,   353,-32768,   355,-32768,
     294,-32768,   176,-32768,    46,-32768,   480,   535,   194,-32768,
     254,-32768,    84,   605,   586,   597,   593,   609,   613,   615,
     625,   619,   600,-32768,    79,-32768,   607,-32768,   565,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,   828,   834,   839,   841,   843,   845,   847,
     849,   851,   853,   857,   859,   861,   863,   865,   868,   870,
     227,-32768,-32768,   229,-32768,-32768,   245,-32768,-32768,   251,
  -32768,-32768,   259,-32768,-32768,   261,-32768,-32768,   268,-32768,
  -32768,   269,-32768,-32768,   275,-32768,-32768,   279,-32768,-32768,
     280,-32768,-32768,   281,-32768,-32768,   283,-32768,-32768,   289,
  -32768,-32768,   297,-32768,-32768,   299,-32768,-32768,   301,-32768,
  -32768,-32768,   371,-32768,   373,-32768,   377,-32768,   443,-32768,
     439,-32768,   441,-32768,   383,-32768,   445,-32768,   447,-32768,
     449,-32768,   469,-32768,   471,-32768,   467,-32768,   486,-32768,
     462,-32768,   490,-32768,   494,   617,   627,   635,   648,   656,
     654,   660,   665,   669,   650,   671,   675,   682,   689,   691,
     693,   703,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    67,
     173,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,-32768,    45,    -9,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,     7,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,  -122,
  -32768,-32768,-32768,  -119,-32768,-32768,-32768,    62,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,  -106,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,   -45,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,   -35,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,  -321,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,  -113
};


#define	YYLAST		973


static const short yytable[] =
{
     130,    15,   131,    15,   132,   331,   133,     4,  -169,  -139,
     329,     6,    13,   -59,   141,    22,    13,   128,   184,    33,
    -347,   185,     1,    31,    32,   387,    23,   404,  -139,  -139,
     160,  -347,   165,    30,   187,    55,    25,    35,    29,  -169,
    -169,    41,   139,    37,   110,   -84,   112,   347,   -59,   -59,
    -128,   -59,   114,  -139,    12,  -139,   116,    17,    18,   -84,
      27,   -84,   118,   -22,  -128,   325,  -128,   570,  -149,   120,
     -22,   -22,    74,    75,    76,    77,    78,    79,    80,    81,
      82,   -84,   122,    13,   124,   126,   -84,   -84,    13,  -149,
    -149,   -84,  -149,   -84,   289,   -84,   291,   -84,   293,   -84,
     295,   -84,   297,   -84,   299,   -84,   301,   -84,   303,   -84,
    -169,  -139,  -169,   -84,    14,   -59,  -128,   -84,    14,   362,
     363,  -347,  -347,  -128,  -128,   152,  -128,   158,  -128,   163,
    -128,   180,  -128,   305,  -128,    19,  -128,   307,  -128,   309,
    -128,   -84,  -128,    43,  -128,   311,   -39,   -84,   377,   378,
      13,   137,  -128,    19,  -159,   -39,   -39,   313,   -39,   315,
     -39,   142,   -39,   317,   -39,   -22,   128,   319,   128,  -347,
    -149,  -347,   -39,   571,   -39,   128,   321,   345,  -347,   327,
    -106,   328,  -347,  -159,  -159,    14,   -39,   333,  -347,   334,
      14,   335,   364,   336,  -106,   337,  -106,   338,    13,   339,
    -159,   340,   186,   341,   323,   342,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   384,   135,   402,   385,   -49,   403,
      38,    39,    83,    84,  -106,   501,   128,   503,   128,  -347,
     128,  -347,   -39,  -347,   128,   356,  -106,  -347,   -39,  -106,
    -106,   143,    14,   505,  -347,   -49,  -159,   128,    13,   507,
    -347,   128,   -49,   128,  -347,   128,  -347,   509,  -347,   511,
    -347,  -347,  -347,  -347,   -49,  -347,   513,   515,   128,  -347,
    -347,  -347,  -106,   517,  -347,   360,  -347,   519,   521,   523,
    -347,   525,    13,   357,   166,   343,   358,   527,   -93,   143,
      14,    45,    46,  -347,    47,   529,    48,   531,    49,   533,
      50,   386,     0,  -347,    86,    87,     0,   352,    51,  -347,
      52,   359,     0,   365,     0,  -347,    19,     0,    19,     0,
     -49,     0,    53,     0,  -347,   379,     0,   383,     0,   401,
    -347,  -347,  -347,  -347,  -347,  -347,     0,     0,  -347,  -347,
     128,     0,   128,  -347,   128,  -347,   128,  -347,     0,  -347,
      14,  -347,  -347,   -93,   -93,  -347,  -347,  -347,  -347,  -347,
    -347,     0,   128,     0,   128,  -347,     0,  -347,   128,     0,
       0,  -347,  -347,  -347,   128,    89,    90,  -347,    54,   535,
       0,   536,     0,   537,    14,   538,     0,   539,  -347,   540,
     -93,   541,  -347,   542,     0,   543,     0,   544,  -347,   545,
      19,   546,  -347,   547,     0,   548,     0,   549,  -347,   550,
    -347,   551,  -347,   433,   434,   435,   436,   437,   438,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     128,     0,   128,  -347,   128,  -347,   128,  -347,   128,  -347,
     128,  -347,     0,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,   128,     0,     0,  -347,     0,   128,    13,
     128,  -347,   128,  -347,     0,  -347,  -347,  -347,  -347,  -347,
    -347,    19,  -347,  -347,    13,     0,     0,   128,  -347,  -347,
    -347,   128,    13,     0,  -347,   128,   156,     0,  -347,     0,
       0,     0,     0,   157,    13,   349,   350,     0,   351,     0,
    -347,   148,   149,    13,     0,   151,  -347,   145,     0,     0,
       0,     0,     0,     0,     0,     0,  -347,     0,     0,     0,
    -347,     0,     0,     0,  -347,    13,   150,     0,   151,    13,
       0,     0,   161,   162,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,   151,
    -347,     0,     0,     0,     0,     0,    13,  -347,  -347,    13,
       0,    14,  -347,  -347,  -347,  -347,  -347,  -347,     0,  -347,
      48,    13,    49,    48,   355,    49,    14,  -347,    13,     0,
      13,  -347,  -347,  -347,    14,  -347,  -347,    13,   147,  -347,
    -347,    13,   166,   146,    13,   143,    14,   167,   168,    13,
       0,    13,   151,    13,   169,    14,   170,    13,   171,    13,
     172,    13,   173,    13,   174,    48,   175,    49,   176,    13,
     177,    13,   198,   368,   178,   378,   143,    14,   179,    13,
     143,    14,   389,   390,   552,   391,   367,   392,   370,   393,
     369,   394,    13,   395,    13,   396,   553,   397,    13,   398,
      13,   399,    54,   400,    13,   172,   371,   376,    14,    13,
       0,    14,   372,    13,     0,    13,   373,   378,   554,    13,
     381,   382,   143,    14,   375,   555,    13,     0,   374,   143,
      14,   143,    14,    13,     0,    13,     0,    13,   143,    14,
       0,     0,   143,    14,     0,   143,    14,    13,    92,    93,
     143,    14,     0,    14,   143,    14,    95,    96,   143,    14,
     143,    14,   143,    14,   143,    14,     0,   556,     0,   557,
     143,    14,   143,    14,     0,   561,    98,    99,     0,   558,
     143,    14,   101,   102,   104,   105,   559,   107,   108,   235,
     236,     0,   560,   143,    14,   143,    14,     0,   562,   143,
      14,   143,    14,     0,   563,   143,    14,   238,   239,     0,
     143,    14,     0,   564,   143,    14,   143,    14,   241,   242,
     143,    14,   565,   244,   245,     0,   566,   143,    14,     0,
     567,   247,   248,     0,   143,    14,   143,    14,   143,    14,
     250,   251,   568,     0,    19,   253,   254,     0,   143,    14,
     256,   257,    19,   259,   260,   262,   263,   265,   266,   268,
     269,   271,   272,   274,   275,   277,   278,   280,   281,   283,
     284,     0,    19,   286,   287,   450,   451,     0,    19,     0,
      19,   453,   454,    19,     0,    19,   456,   457,   459,   460,
     462,   463,   465,   466,   468,   469,   471,   472,   474,   475,
     477,   478,     0,    19,   480,   481,   483,   484,   486,   487,
     489,   490,   492,   493,    19,   495,   496,   498,   499,    19,
       0,     0,     0,     0,     0,     0,     0,    19,     0,     0,
       0,     0,     0,     0,     0,     0,    19,     0,     0,     0,
       0,    19,     0,     0,     0,     0,    19,     0,     0,    19,
       0,    19,     0,    19,     0,    19,     0,    19,     0,    19,
       0,    19,     0,    19,     0,    19,     0,     0,     0,    19,
       0,    19,     0,     0,     0,     0,     0,    19,     0,     0,
       0,     0,    19,     0,    19,     0,    19,     0,    19,     0,
      19,     0,    19,     0,    19,     0,    19,     0,     0,     0,
      19,     0,    19,     0,    19,     0,    19,     0,    19,     0,
       0,    19,     0,    19
};

static const short yycheck[] =
{
     113,    10,   115,    12,   117,     1,     1,    10,     4,     4,
       1,   102,     4,     4,   127,   103,     4,     1,   140,    28,
       4,   140,     3,    11,    12,   346,     8,   348,    23,    24,
     136,    15,   138,    26,   140,    44,     6,     5,   104,    35,
      36,     8,     1,    36,     8,     4,     8,     1,    39,    40,
       4,    42,     8,    48,     9,    50,     8,     7,     8,    18,
       1,    20,     8,     4,    18,     1,    20,     0,     4,     8,
      11,    12,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    40,     8,     4,     8,     8,    45,    46,     4,    25,
      26,    50,    28,    52,     8,    54,     8,    56,     8,    58,
       8,    60,     8,    62,     8,    64,     8,    66,     8,    68,
     106,   106,   108,    72,   106,   106,    70,    76,   106,    35,
      36,   105,   106,    77,    78,   134,    80,   136,    82,   138,
      84,   140,    86,     8,    88,   103,    90,     8,    92,     8,
      94,   100,    96,     1,    98,     8,     4,   106,    69,    70,
       4,     1,   106,   103,     4,    13,    14,     8,    16,     8,
      18,    15,    20,     8,    22,   106,     1,     8,     1,     4,
     106,     4,    30,     0,    32,     1,     8,     1,     4,   292,
       4,   294,    17,    33,    34,   106,    44,   300,    21,   302,
     106,   304,   108,   306,    18,   308,    20,   310,     4,   312,
      50,   314,   140,   316,     8,   318,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   346,     1,   348,   346,     4,   348,
       7,     8,     7,     8,    58,     8,     1,     8,     1,     4,
       1,     4,   100,     4,     1,    51,    70,     4,   106,    73,
      74,   105,   106,     8,    19,    31,   106,     1,     4,     8,
       4,     1,    38,     1,     4,     1,     4,     8,     4,     8,
     105,   106,   105,   106,    50,   101,     8,     8,     1,   105,
     106,     4,   106,     8,    41,   330,    49,     8,     8,     8,
      51,     8,     4,    39,    40,     1,    42,     8,     4,   105,
     106,    13,    14,    47,    16,     8,    18,     8,    20,     8,
      22,   346,    -1,    53,     7,     8,    -1,   326,    30,    55,
      32,   330,    -1,   332,    -1,    63,   103,    -1,   103,    -1,
     106,    -1,    44,    -1,    57,   344,    -1,   346,    -1,   348,
     105,   106,   105,   106,   105,   106,    -1,    -1,   105,   106,
       1,    -1,     1,     4,     1,     4,     1,     4,    -1,     4,
     106,   105,   106,    69,    70,   105,   106,   105,   106,   105,
     106,    -1,     1,    -1,     1,     4,    -1,     4,     1,    -1,
      -1,     4,   105,   106,     1,     7,     8,     4,   100,   502,
      -1,   504,    -1,   506,   106,   508,    -1,   510,    27,   512,
     106,   514,    29,   516,    -1,   518,    -1,   520,    59,   522,
     103,   524,    61,   526,    -1,   528,    -1,   530,    65,   532,
      43,   534,    67,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
       1,    -1,     1,     4,     1,     4,     1,     4,     1,     4,
       1,     4,    -1,     4,   105,   106,   105,   106,   105,   106,
     105,   106,    79,     1,    -1,    -1,     4,    -1,     1,     4,
       1,     4,     1,     4,    -1,     4,   105,   106,   105,   106,
      37,   103,   105,   106,     4,    -1,    -1,     1,   105,   106,
       4,     1,     4,    -1,     4,     1,    31,    -1,     4,    -1,
      -1,    -1,    -1,    38,     4,    25,    26,    -1,    28,    -1,
      71,    23,    24,     4,    -1,    50,    75,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      83,    -1,    -1,    -1,    85,     4,    48,    -1,    50,     4,
      -1,    -1,    33,    34,   105,   106,   105,   106,   105,   106,
     105,   106,   105,   106,   105,   106,    87,    95,    91,    50,
      89,    -1,    -1,    -1,    -1,    -1,     4,   105,   106,     4,
      -1,   106,   105,   106,   105,   106,   105,   106,    -1,    93,
      18,     4,    20,    18,    49,    20,   106,    97,     4,    -1,
       4,   105,   106,    99,   106,   105,   106,     4,    21,   105,
     106,     4,    40,    19,     4,   105,   106,    45,    46,     4,
      -1,     4,    50,     4,    52,   106,    54,     4,    56,     4,
      58,     4,    60,     4,    62,    18,    64,    20,    66,     4,
      68,     4,   101,    47,    72,    70,   105,   106,    76,     4,
     105,   106,    77,    78,    27,    80,    41,    82,    55,    84,
      53,    86,     4,    88,     4,    90,    29,    92,     4,    94,
       4,    96,   100,    98,     4,    58,    57,    67,   106,     4,
      -1,   106,    59,     4,    -1,     4,    61,    70,    43,     4,
      73,    74,   105,   106,    65,    37,     4,    -1,    63,   105,
     106,   105,   106,     4,    -1,     4,    -1,     4,   105,   106,
      -1,    -1,   105,   106,    -1,   105,   106,     4,     7,     8,
     105,   106,    -1,   106,   105,   106,     7,     8,   105,   106,
     105,   106,   105,   106,   105,   106,    -1,    71,    -1,    75,
     105,   106,   105,   106,    -1,    85,     7,     8,    -1,    79,
     105,   106,     7,     8,     7,     8,    81,     7,     8,     7,
       8,    -1,    83,   105,   106,   105,   106,    -1,    87,   105,
     106,   105,   106,    -1,    89,   105,   106,     7,     8,    -1,
     105,   106,    -1,    91,   105,   106,   105,   106,     7,     8,
     105,   106,    93,     7,     8,    -1,    95,   105,   106,    -1,
      97,     7,     8,    -1,   105,   106,   105,   106,   105,   106,
       7,     8,    99,    -1,   103,     7,     8,    -1,   105,   106,
       7,     8,   103,     7,     8,     7,     8,     7,     8,     7,
       8,     7,     8,     7,     8,     7,     8,     7,     8,     7,
       8,    -1,   103,     7,     8,     7,     8,    -1,   103,    -1,
     103,     7,     8,   103,    -1,   103,     7,     8,     7,     8,
       7,     8,     7,     8,     7,     8,     7,     8,     7,     8,
       7,     8,    -1,   103,     7,     8,     7,     8,     7,     8,
       7,     8,     7,     8,   103,     7,     8,     7,     8,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,    -1,    -1,    -1,
      -1,   103,    -1,    -1,    -1,    -1,   103,    -1,    -1,   103,
      -1,   103,    -1,   103,    -1,   103,    -1,   103,    -1,   103,
      -1,   103,    -1,   103,    -1,   103,    -1,    -1,    -1,   103,
      -1,   103,    -1,    -1,    -1,    -1,    -1,   103,    -1,    -1,
      -1,    -1,   103,    -1,   103,    -1,   103,    -1,   103,    -1,
     103,    -1,   103,    -1,   103,    -1,   103,    -1,    -1,    -1,
     103,    -1,   103,    -1,   103,    -1,   103,    -1,   103,    -1,
      -1,   103,    -1,   103
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 237 "src/xml_hist.y"
{result_history = yyvsp[0].FLXT_history;;
    break;}
case 4:
#line 245 "src/xml_hist.y"
{my_printf("<?xml version=\"1.0\" ?>\n");;
    break;}
case 6:
#line 249 "src/xml_hist.y"
{my_printf("<?XML-ENCODING %s?>\n",yyvsp[0].s); free(yyvsp[0].s);;
    break;}
case 10:
#line 257 "src/xml_hist.y"
{my_printf("%s", yyvsp[0].s);;
    break;}
case 12:
#line 261 "src/xml_hist.y"
{my_printf("\n<?XML-ATT %s", yyvsp[0].s);;
    break;}
case 13:
#line 262 "src/xml_hist.y"
{my_printf("?>\n");;
    break;}
case 14:
#line 288 "src/xml_hist.y"
{my_printf("<HISTORY");;
    break;}
case 15:
#line 290 "src/xml_hist.y"
{yyval.FLXT_history = yyvsp[0].FLXT_history;;
    break;}
case 16:
#line 293 "src/xml_hist.y"
{
				 my_printf("/>\n");
				 yyval.FLXT_history = empty_history();
				;
    break;}
case 17:
#line 297 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 18:
#line 299 "src/xml_hist.y"
{ 
				 my_printf("</HISTORY>\n");
				 yyval.FLXT_history = yyvsp[-1].FLXT_history;
				;
    break;}
case 19:
#line 305 "src/xml_hist.y"
{yyval.FLXT_history = yyvsp[-1].FLXT_history;;
    break;}
case 20:
#line 307 "src/xml_hist.y"
{yyval.FLXT_history = add_report_to_history(yyvsp[0].FLXT_report, yyvsp[-1].FLXT_history);;
    break;}
case 21:
#line 308 "src/xml_hist.y"
{yyclearin; yyerrok;;
    break;}
case 22:
#line 309 "src/xml_hist.y"
{yyval.FLXT_history = empty_history();;
    break;}
case 23:
#line 313 "src/xml_hist.y"
{my_printf("\n<%s", "REPORT");;
    break;}
case 24:
#line 315 "src/xml_hist.y"
{yyval.FLXT_report = yyvsp[0].FLXT_report;
    break;}
case 25:
#line 318 "src/xml_hist.y"
{
				 yyval.FLXT_report = empty_report();
				 my_printf("/>\n");
				;
    break;}
case 26:
#line 322 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 27:
#line 324 "src/xml_hist.y"
{ 
				 my_printf("</%s>\n", "REPORT");
				 yyval.FLXT_report = yyvsp[-1].FLXT_report;
				;
    break;}
case 28:
#line 330 "src/xml_hist.y"
{yyval.FLXT_report = yyvsp[-1].FLXT_report;;
    break;}
case 29:
#line 331 "src/xml_hist.y"
{yyval.FLXT_report = add_run_id_to_report(yyvsp[0].FLXT_run_id, yyvsp[-1].FLXT_report);;
    break;}
case 30:
#line 332 "src/xml_hist.y"
{yyval.FLXT_report = add_scenario_file_to_report(yyvsp[0].FLXT_scenario_file, yyvsp[-1].FLXT_report);;
    break;}
case 31:
#line 333 "src/xml_hist.y"
{yyval.FLXT_report = add_start_date_to_report(yyvsp[0].FLXT_start_date, yyvsp[-1].FLXT_report);;
    break;}
case 32:
#line 334 "src/xml_hist.y"
{yyval.FLXT_report = add_end_date_to_report(yyvsp[0].FLXT_end_date, yyvsp[-1].FLXT_report);;
    break;}
case 33:
#line 335 "src/xml_hist.y"
{yyval.FLXT_report = add_compiler_version_to_report(yyvsp[0].FLXT_compiler_version, yyvsp[-1].FLXT_report);;
    break;}
case 34:
#line 336 "src/xml_hist.y"
{yyval.FLXT_report = add_scenario_to_report(yyvsp[0].FLXT_scenario, yyvsp[-1].FLXT_report);;
    break;}
case 35:
#line 337 "src/xml_hist.y"
{yyval.FLXT_report = add_param_files_to_report(yyvsp[0].FLXT_param_files, yyvsp[-1].FLXT_report);;
    break;}
case 36:
#line 338 "src/xml_hist.y"
{yyval.FLXT_report = add_test_to_report(yyvsp[0].FLXT_test, yyvsp[-1].FLXT_report);;
    break;}
case 37:
#line 339 "src/xml_hist.y"
{yyval.FLXT_report = add_opt_report_error_to_report(yyvsp[0].FLXT_opt_report_error, yyvsp[-1].FLXT_report);;
    break;}
case 38:
#line 340 "src/xml_hist.y"
{yyclearin; yyerrok;;
    break;}
case 39:
#line 341 "src/xml_hist.y"
{yyval.FLXT_report = empty_report();;
    break;}
case 40:
#line 345 "src/xml_hist.y"
{my_printf("<SCENARIO");;
    break;}
case 41:
#line 347 "src/xml_hist.y"
{yyval.FLXT_scenario = yyvsp[0].FLXT_scenario;;
    break;}
case 42:
#line 350 "src/xml_hist.y"
{
				 my_printf("/>\n");
				 yyval.FLXT_scenario = empty_scenario();
				;
    break;}
case 43:
#line 354 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 44:
#line 356 "src/xml_hist.y"
{ 
				 my_printf("</SCENARIO>\n");
				 yyval.FLXT_scenario = yyvsp[-1].FLXT_scenario;
				;
    break;}
case 45:
#line 362 "src/xml_hist.y"
{yyval.FLXT_scenario = yyvsp[-1].FLXT_scenario;;
    break;}
case 46:
#line 364 "src/xml_hist.y"
{yyval.FLXT_scenario = add_host_name_to_scenario(yyvsp[0].FLXT_host_name, yyvsp[-1].FLXT_scenario);;
    break;}
case 47:
#line 366 "src/xml_hist.y"
{yyval.FLXT_scenario = add_test_def_to_scenario(yyvsp[0].FLXT_test_def, yyvsp[-1].FLXT_scenario);;
    break;}
case 48:
#line 367 "src/xml_hist.y"
{yyclearin; yyerrok;;
    break;}
case 49:
#line 368 "src/xml_hist.y"
{yyval.FLXT_scenario = empty_scenario();;
    break;}
case 50:
#line 372 "src/xml_hist.y"
{my_printf("<TEST_DEF");;
    break;}
case 51:
#line 374 "src/xml_hist.y"
{yyval.FLXT_test_def = yyvsp[0].FLXT_test_def;;
    break;}
case 52:
#line 377 "src/xml_hist.y"
{
				 my_printf("/>\n");
				 yyval.FLXT_test_def = empty_test_def();
				;
    break;}
case 53:
#line 381 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 54:
#line 383 "src/xml_hist.y"
{ 
				 my_printf("</TEST_DEF>\n");
				 yyval.FLXT_test_def = yyvsp[-1].FLXT_test_def;
				;
    break;}
case 55:
#line 389 "src/xml_hist.y"
{yyval.FLXT_test_def = yyvsp[-1].FLXT_test_def;;
    break;}
case 56:
#line 391 "src/xml_hist.y"
{yyval.FLXT_test_def = add_test_path_to_test_def(yyvsp[0].FLXT_test_path, yyvsp[-1].FLXT_test_def);;
    break;}
case 57:
#line 393 "src/xml_hist.y"
{yyval.FLXT_test_def = add_options_set_to_test_def(yyvsp[0].FLXT_options_set, yyvsp[-1].FLXT_test_def);;
    break;}
case 58:
#line 394 "src/xml_hist.y"
{yyclearin; yyerrok;;
    break;}
case 59:
#line 395 "src/xml_hist.y"
{yyval.FLXT_test_def = empty_test_def();;
    break;}
case 60:
#line 399 "src/xml_hist.y"
{my_printf("\n<%s", "TEST");;
    break;}
case 61:
#line 401 "src/xml_hist.y"
{yyval.FLXT_test = yyvsp[0].FLXT_test;;
    break;}
case 62:
#line 404 "src/xml_hist.y"
{
					 yyval.FLXT_test = empty_test();
					 my_printf("/>\n");
					;
    break;}
case 63:
#line 408 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 64:
#line 410 "src/xml_hist.y"
{
					 my_printf("</%s>\n", "TEST");
					 yyval.FLXT_test = yyvsp[-1].FLXT_test;
					;
    break;}
case 65:
#line 416 "src/xml_hist.y"
{yyval.FLXT_test = yyvsp[-1].FLXT_test;;
    break;}
case 66:
#line 417 "src/xml_hist.y"
{yyval.FLXT_test = add_test_path_to_test(yyvsp[0].FLXT_test_path, yyvsp[-1].FLXT_test);;
    break;}
case 67:
#line 418 "src/xml_hist.y"
{yyval.FLXT_test = add_start_date_to_test(yyvsp[0].FLXT_start_date, yyvsp[-1].FLXT_test);;
    break;}
case 68:
#line 419 "src/xml_hist.y"
{yyval.FLXT_test = add_end_date_to_test(yyvsp[0].FLXT_end_date, yyvsp[-1].FLXT_test);;
    break;}
case 69:
#line 420 "src/xml_hist.y"
{yyval.FLXT_test = add_test_name_to_test(yyvsp[0].FLXT_test_name, yyvsp[-1].FLXT_test);;
    break;}
case 70:
#line 421 "src/xml_hist.y"
{yyval.FLXT_test = add_host_name_to_test(yyvsp[0].FLXT_host_name, yyvsp[-1].FLXT_test);;
    break;}
case 71:
#line 422 "src/xml_hist.y"
{yyval.FLXT_test = add_test_mode_to_test(yyvsp[0].FLXT_test_mode, yyvsp[-1].FLXT_test);;
    break;}
case 72:
#line 423 "src/xml_hist.y"
{yyval.FLXT_test = add_level_to_test(yyvsp[0].FLXT_level, yyvsp[-1].FLXT_test);;
    break;}
case 73:
#line 424 "src/xml_hist.y"
{yyval.FLXT_test = add_cc_options_to_test(yyvsp[0].FLXT_cc_options, yyvsp[-1].FLXT_test);;
    break;}
case 74:
#line 425 "src/xml_hist.y"
{yyval.FLXT_test = add_cflags_to_test(yyvsp[0].FLXT_cflags, yyvsp[-1].FLXT_test);;
    break;}
case 75:
#line 426 "src/xml_hist.y"
{yyval.FLXT_test = add_makefile_to_test(yyvsp[0].FLXT_makefile, yyvsp[-1].FLXT_test);;
    break;}
case 76:
#line 427 "src/xml_hist.y"
{yyval.FLXT_test = add_make_options_to_test(yyvsp[0].FLXT_make_options, yyvsp[-1].FLXT_test);;
    break;}
case 77:
#line 428 "src/xml_hist.y"
{yyval.FLXT_test = add_simulator_to_test(yyvsp[0].FLXT_simulator, yyvsp[-1].FLXT_test);;
    break;}
case 78:
#line 429 "src/xml_hist.y"
{yyval.FLXT_test = add_sim_options_to_test(yyvsp[0].FLXT_sim_options, yyvsp[-1].FLXT_test);;
    break;}
case 79:
#line 430 "src/xml_hist.y"
{yyval.FLXT_test = add_targets_to_test(yyvsp[0].FLXT_targets, yyvsp[-1].FLXT_test);;
    break;}
case 80:
#line 431 "src/xml_hist.y"
{yyval.FLXT_test = add_compilation_to_test(yyvsp[0].FLXT_compilation, yyvsp[-1].FLXT_test);;
    break;}
case 81:
#line 432 "src/xml_hist.y"
{yyval.FLXT_test = add_exec_to_test(yyvsp[0].FLXT_exec, yyvsp[-1].FLXT_test);;
    break;}
case 82:
#line 433 "src/xml_hist.y"
{yyval.FLXT_test = add_opt_report_error_to_test(yyvsp[0].FLXT_opt_report_error, yyvsp[-1].FLXT_test);;
    break;}
case 83:
#line 434 "src/xml_hist.y"
{yyclearin; yyerrok;;
    break;}
case 84:
#line 435 "src/xml_hist.y"
{yyval.FLXT_test = empty_test();;
    break;}
case 85:
#line 439 "src/xml_hist.y"
{my_printf("<TARGETS");;
    break;}
case 86:
#line 441 "src/xml_hist.y"
{yyval.FLXT_targets = yyvsp[0].FLXT_targets;;
    break;}
case 87:
#line 444 "src/xml_hist.y"
{
				 my_printf("/>\n");
				 yyval.FLXT_targets = empty_targets();
				;
    break;}
case 88:
#line 448 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 89:
#line 450 "src/xml_hist.y"
{ 
				 my_printf("</TARGETS>\n");
				 yyval.FLXT_targets = yyvsp[-1].FLXT_targets;
				;
    break;}
case 90:
#line 456 "src/xml_hist.y"
{yyval.FLXT_targets = yyvsp[-1].FLXT_targets;;
    break;}
case 91:
#line 458 "src/xml_hist.y"
{yyval.FLXT_targets = add_target_to_targets(yyvsp[0].FLXT_target, yyvsp[-1].FLXT_targets);;
    break;}
case 92:
#line 459 "src/xml_hist.y"
{yyclearin; yyerrok;;
    break;}
case 93:
#line 460 "src/xml_hist.y"
{yyval.FLXT_targets = empty_targets();;
    break;}
case 94:
#line 465 "src/xml_hist.y"
{my_printf("\n<%s", "COMPILATION");;
    break;}
case 95:
#line 467 "src/xml_hist.y"
{yyval.FLXT_compilation = yyvsp[0].FLXT_compilation;;
    break;}
case 96:
#line 470 "src/xml_hist.y"
{
					 yyval.FLXT_compilation = empty_compilation();
					 my_printf("/>\n");
					;
    break;}
case 97:
#line 474 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 98:
#line 476 "src/xml_hist.y"
{
					 my_printf("</%s>\n", "COMPILATION");
					 yyval.FLXT_compilation = yyvsp[-1].FLXT_compilation;
					;
    break;}
case 99:
#line 482 "src/xml_hist.y"
{yyval.FLXT_compilation = yyvsp[-1].FLXT_compilation;;
    break;}
case 100:
#line 483 "src/xml_hist.y"
{yyval.FLXT_compilation = add_target_to_compilation(yyvsp[0].FLXT_target, yyvsp[-1].FLXT_compilation);;
    break;}
case 101:
#line 484 "src/xml_hist.y"
{yyval.FLXT_compilation = add_cflags_to_compilation(yyvsp[0].FLXT_cflags, yyvsp[-1].FLXT_compilation);;
    break;}
case 102:
#line 485 "src/xml_hist.y"
{yyval.FLXT_compilation = add_make_argv_to_compilation(yyvsp[0].FLXT_make_argv, yyvsp[-1].FLXT_compilation);;
    break;}
case 103:
#line 486 "src/xml_hist.y"
{yyval.FLXT_compilation = add_start_date_to_compilation(yyvsp[0].FLXT_start_date, yyvsp[-1].FLXT_compilation);;
    break;}
case 104:
#line 487 "src/xml_hist.y"
{yyval.FLXT_compilation = add_end_date_to_compilation(yyvsp[0].FLXT_end_date, yyvsp[-1].FLXT_compilation);;
    break;}
case 105:
#line 488 "src/xml_hist.y"
{yyclearin; yyerrok;;
    break;}
case 106:
#line 489 "src/xml_hist.y"
{yyval.FLXT_compilation = empty_compilation();;
    break;}
case 107:
#line 493 "src/xml_hist.y"
{my_printf("\n<%s", "EXEC");;
    break;}
case 108:
#line 495 "src/xml_hist.y"
{yyval.FLXT_exec = yyvsp[0].FLXT_exec;;
    break;}
case 109:
#line 498 "src/xml_hist.y"
{
					 yyval.FLXT_exec = empty_exec();
					 nb_execs++;
					 my_printf(" exec_num=\"%d\"/>\n", nb_execs);
					;
    break;}
case 110:
#line 503 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 111:
#line 505 "src/xml_hist.y"
{
					 nb_execs++;
					 my_printf("</%s exec_num=\"%d\">\n", "EXEC", nb_execs);
					 yyval.FLXT_exec = yyvsp[-1].FLXT_exec;
					;
    break;}
case 112:
#line 512 "src/xml_hist.y"
{yyval.FLXT_exec = yyvsp[-1].FLXT_exec;;
    break;}
case 113:
#line 513 "src/xml_hist.y"
{yyval.FLXT_exec = add_target_to_exec(yyvsp[0].FLXT_target, yyvsp[-1].FLXT_exec);;
    break;}
case 114:
#line 514 "src/xml_hist.y"
{yyval.FLXT_exec = add_description_to_exec(yyvsp[0].FLXT_description, yyvsp[-1].FLXT_exec);;
    break;}
case 115:
#line 515 "src/xml_hist.y"
{yyval.FLXT_exec = add_status_to_exec(yyvsp[0].FLXT_status, yyvsp[-1].FLXT_exec);;
    break;}
case 116:
#line 516 "src/xml_hist.y"
{yyval.FLXT_exec = add_size_to_exec(yyvsp[0].FLXT_size, yyvsp[-1].FLXT_exec);;
    break;}
case 117:
#line 517 "src/xml_hist.y"
{yyval.FLXT_exec = add_input_to_exec(yyvsp[0].FLXT_input, yyvsp[-1].FLXT_exec);;
    break;}
case 118:
#line 518 "src/xml_hist.y"
{yyval.FLXT_exec = add_n_frames_to_exec(yyvsp[0].FLXT_n_frames, yyvsp[-1].FLXT_exec);;
    break;}
case 119:
#line 519 "src/xml_hist.y"
{yyval.FLXT_exec = add_sample_p_frame_to_exec(yyvsp[0].FLXT_sample_p_frame, yyvsp[-1].FLXT_exec);;
    break;}
case 120:
#line 520 "src/xml_hist.y"
{yyval.FLXT_exec = add_e_freq_to_exec(yyvsp[0].FLXT_e_freq, yyvsp[-1].FLXT_exec);;
    break;}
case 121:
#line 521 "src/xml_hist.y"
{yyval.FLXT_exec = add_argv_to_exec(yyvsp[0].FLXT_argv, yyvsp[-1].FLXT_exec);;
    break;}
case 122:
#line 522 "src/xml_hist.y"
{yyval.FLXT_exec = add_cycles_to_exec(yyvsp[0].FLXT_cycles, yyvsp[-1].FLXT_exec);;
    break;}
case 123:
#line 523 "src/xml_hist.y"
{yyval.FLXT_exec = add_cycles_p_frame_to_exec(yyvsp[0].FLXT_cycles_p_frame, yyvsp[-1].FLXT_exec);;
    break;}
case 124:
#line 524 "src/xml_hist.y"
{yyval.FLXT_exec = add_mips_to_exec(yyvsp[0].FLXT_mips, yyvsp[-1].FLXT_exec);;
    break;}
case 125:
#line 525 "src/xml_hist.y"
{yyval.FLXT_exec = add_start_date_to_exec(yyvsp[0].FLXT_start_date, yyvsp[-1].FLXT_exec);;
    break;}
case 126:
#line 526 "src/xml_hist.y"
{yyval.FLXT_exec = add_end_date_to_exec(yyvsp[0].FLXT_end_date, yyvsp[-1].FLXT_exec);;
    break;}
case 127:
#line 527 "src/xml_hist.y"
{yyclearin; yyerrok;;
    break;}
case 128:
#line 528 "src/xml_hist.y"
{yyval.FLXT_exec = empty_exec();;
    break;}
case 129:
#line 532 "src/xml_hist.y"
{my_printf("<COMPILER_VERSION");;
    break;}
case 130:
#line 534 "src/xml_hist.y"
{yyval.FLXT_compiler_version = yyvsp[0].FLXT_compiler_version;;
    break;}
case 131:
#line 537 "src/xml_hist.y"
{
					 my_printf("/>\n");
					 yyval.FLXT_compiler_version = empty_compiler_version();
					;
    break;}
case 132:
#line 541 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 133:
#line 543 "src/xml_hist.y"
{ 
					 my_printf("</COMPILER_VERSION>\n");
					 yyval.FLXT_compiler_version = yyvsp[-1].FLXT_compiler_version;
					;
    break;}
case 134:
#line 549 "src/xml_hist.y"
{yyval.FLXT_compiler_version = yyvsp[-1].FLXT_compiler_version;;
    break;}
case 135:
#line 551 "src/xml_hist.y"
{yyval.FLXT_compiler_version = add_host_type_to_compiler_version(yyvsp[0].FLXT_host_type, yyvsp[-1].FLXT_compiler_version);;
    break;}
case 136:
#line 553 "src/xml_hist.y"
{yyval.FLXT_compiler_version = add_host_name_to_compiler_version(yyvsp[0].FLXT_host_name, yyvsp[-1].FLXT_compiler_version);;
    break;}
case 137:
#line 555 "src/xml_hist.y"
{yyval.FLXT_compiler_version = add_tool_to_compiler_version(yyvsp[0].FLXT_tool, yyvsp[-1].FLXT_compiler_version);;
    break;}
case 138:
#line 556 "src/xml_hist.y"
{yyclearin; yyerrok;;
    break;}
case 139:
#line 557 "src/xml_hist.y"
{yyval.FLXT_compiler_version = empty_compiler_version();;
    break;}
case 140:
#line 561 "src/xml_hist.y"
{my_printf("<TOOL");;
    break;}
case 141:
#line 563 "src/xml_hist.y"
{yyval.FLXT_tool = yyvsp[0].FLXT_tool;;
    break;}
case 142:
#line 566 "src/xml_hist.y"
{
				 my_printf("/>\n");
				 yyval.FLXT_tool = empty_tool();
				;
    break;}
case 143:
#line 570 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 144:
#line 572 "src/xml_hist.y"
{ 
				 my_printf("</TOOL>\n");
				 yyval.FLXT_tool = yyvsp[-1].FLXT_tool;
				;
    break;}
case 145:
#line 578 "src/xml_hist.y"
{yyval.FLXT_tool = yyvsp[-1].FLXT_tool;;
    break;}
case 146:
#line 580 "src/xml_hist.y"
{yyval.FLXT_tool = add_tool_name_to_tool(yyvsp[0].FLXT_tool_name, yyvsp[-1].FLXT_tool);;
    break;}
case 147:
#line 582 "src/xml_hist.y"
{yyval.FLXT_tool = add_tool_version_to_tool(yyvsp[0].FLXT_tool_version, yyvsp[-1].FLXT_tool);;
    break;}
case 148:
#line 583 "src/xml_hist.y"
{yyclearin; yyerrok;;
    break;}
case 149:
#line 584 "src/xml_hist.y"
{yyval.FLXT_tool = empty_tool();;
    break;}
case 150:
#line 588 "src/xml_hist.y"
{my_printf("<PARAM_FILES");;
    break;}
case 151:
#line 590 "src/xml_hist.y"
{yyval.FLXT_param_files = yyvsp[0].FLXT_param_files;;
    break;}
case 152:
#line 593 "src/xml_hist.y"
{
				 my_printf("/>\n");
				 yyval.FLXT_param_files = empty_param_files();
				;
    break;}
case 153:
#line 597 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 154:
#line 599 "src/xml_hist.y"
{ 
				 my_printf("</PARAM_FILES>\n");
				 yyval.FLXT_param_files = yyvsp[-1].FLXT_param_files;
				;
    break;}
case 155:
#line 605 "src/xml_hist.y"
{yyval.FLXT_param_files = yyvsp[-1].FLXT_param_files;;
    break;}
case 156:
#line 607 "src/xml_hist.y"
{yyval.FLXT_param_files = add_host_name_to_param_files(yyvsp[0].FLXT_host_name, yyvsp[-1].FLXT_param_files);;
    break;}
case 157:
#line 609 "src/xml_hist.y"
{yyval.FLXT_param_files = add_param_file_to_param_files(yyvsp[0].FLXT_param_file, yyvsp[-1].FLXT_param_files);;
    break;}
case 158:
#line 610 "src/xml_hist.y"
{yyclearin; yyerrok;;
    break;}
case 159:
#line 611 "src/xml_hist.y"
{yyval.FLXT_param_files = empty_param_files();;
    break;}
case 160:
#line 615 "src/xml_hist.y"
{my_printf("<PARAM_FILE");;
    break;}
case 161:
#line 617 "src/xml_hist.y"
{yyval.FLXT_param_file = yyvsp[0].FLXT_param_file;;
    break;}
case 162:
#line 620 "src/xml_hist.y"
{
				 my_printf("/>\n");
				 yyval.FLXT_param_file = empty_param_file();
				;
    break;}
case 163:
#line 624 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 164:
#line 626 "src/xml_hist.y"
{ 
				 my_printf("</PARAM_FILE>\n");
				 yyval.FLXT_param_file = yyvsp[-1].FLXT_param_file;
				;
    break;}
case 165:
#line 632 "src/xml_hist.y"
{yyval.FLXT_param_file = yyvsp[-1].FLXT_param_file;;
    break;}
case 166:
#line 634 "src/xml_hist.y"
{yyval.FLXT_param_file = add_filename_to_param_file(yyvsp[0].FLXT_filename, yyvsp[-1].FLXT_param_file);;
    break;}
case 167:
#line 636 "src/xml_hist.y"
{
				my_printf("<RAWDATA>\n%s\n</RAWDATA>\n",yyvsp[0].FLXT_rawdata); 
				yyval.FLXT_param_file = add_rawdata_to_param_file(yyvsp[0].FLXT_rawdata, yyvsp[-1].FLXT_param_file);
				;
    break;}
case 168:
#line 640 "src/xml_hist.y"
{yyclearin; yyerrok;;
    break;}
case 169:
#line 641 "src/xml_hist.y"
{yyval.FLXT_param_file = empty_param_file();;
    break;}
case 170:
#line 645 "src/xml_hist.y"
{yyval.FLXT_attribute_seq_opt = add_attribute_to_attribute_seq_opt(yyvsp[0].FLXT_attribute, yyvsp[-1].FLXT_attribute_seq_opt);;
    break;}
case 171:
#line 646 "src/xml_hist.y"
{yyval.FLXT_attribute_seq_opt = NULL;;
    break;}
case 172:
#line 649 "src/xml_hist.y"
{my_printf(" %s", yyvsp[0].s); free(yyvsp[0].s);;
    break;}
case 173:
#line 650 "src/xml_hist.y"
{my_printf(" %s=%s", yyvsp[-2].s, yyvsp[0].s); free(yyvsp[-2].s); free(yyvsp[0].s);;
    break;}
case 174:
#line 654 "src/xml_hist.y"
{my_printf("<RUN_ID");;
    break;}
case 175:
#line 656 "src/xml_hist.y"
{yyval.FLXT_run_id = yyvsp[0].FLXT_run_id;;
    break;}
case 176:
#line 659 "src/xml_hist.y"
{yyval.FLXT_run_id = NULL;;
    break;}
case 177:
#line 660 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 178:
#line 662 "src/xml_hist.y"
{my_printf("</RUN_ID>\n"); yyval.FLXT_run_id = yyvsp[-1].s;;
    break;}
case 179:
#line 666 "src/xml_hist.y"
{my_printf("<SCENARIO_FILE");;
    break;}
case 180:
#line 668 "src/xml_hist.y"
{yyval.FLXT_scenario_file = yyvsp[0].FLXT_scenario_file;;
    break;}
case 181:
#line 671 "src/xml_hist.y"
{yyval.FLXT_scenario_file = NULL;;
    break;}
case 182:
#line 672 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 183:
#line 674 "src/xml_hist.y"
{my_printf("</SCENARIO_FILE>\n"); yyval.FLXT_scenario_file = yyvsp[-1].s;;
    break;}
case 184:
#line 678 "src/xml_hist.y"
{my_printf("<START_DATE");;
    break;}
case 185:
#line 680 "src/xml_hist.y"
{yyval.FLXT_start_date = yyvsp[0].FLXT_start_date;;
    break;}
case 186:
#line 683 "src/xml_hist.y"
{yyval.FLXT_start_date = NULL;;
    break;}
case 187:
#line 684 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 188:
#line 686 "src/xml_hist.y"
{my_printf("</START_DATE>\n"); yyval.FLXT_start_date = yyvsp[-1].s;;
    break;}
case 189:
#line 690 "src/xml_hist.y"
{my_printf("<END_DATE");;
    break;}
case 190:
#line 692 "src/xml_hist.y"
{yyval.FLXT_end_date = yyvsp[0].FLXT_end_date;;
    break;}
case 191:
#line 695 "src/xml_hist.y"
{yyval.FLXT_end_date = NULL;;
    break;}
case 192:
#line 696 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 193:
#line 698 "src/xml_hist.y"
{my_printf("</END_DATE>\n"); yyval.FLXT_end_date = yyvsp[-1].s;;
    break;}
case 194:
#line 702 "src/xml_hist.y"
{my_printf("<OPT_REPORT_ERROR");;
    break;}
case 195:
#line 704 "src/xml_hist.y"
{yyval.FLXT_opt_report_error = yyvsp[0].FLXT_opt_report_error;;
    break;}
case 196:
#line 707 "src/xml_hist.y"
{yyval.FLXT_opt_report_error = NULL;;
    break;}
case 197:
#line 708 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 198:
#line 710 "src/xml_hist.y"
{my_printf("</OPT_REPORT_ERROR>\n"); yyval.FLXT_opt_report_error = yyvsp[-1].s;;
    break;}
case 199:
#line 714 "src/xml_hist.y"
{my_printf("<HOST_TYPE");;
    break;}
case 200:
#line 716 "src/xml_hist.y"
{yyval.FLXT_host_type = yyvsp[0].FLXT_host_type;;
    break;}
case 201:
#line 719 "src/xml_hist.y"
{yyval.FLXT_host_type = NULL;;
    break;}
case 202:
#line 720 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 203:
#line 722 "src/xml_hist.y"
{my_printf("</HOST_TYPE>\n"); yyval.FLXT_host_type = yyvsp[-1].s;;
    break;}
case 204:
#line 726 "src/xml_hist.y"
{my_printf("<HOST_NAME");;
    break;}
case 205:
#line 728 "src/xml_hist.y"
{yyval.FLXT_host_name = yyvsp[0].FLXT_host_name;;
    break;}
case 206:
#line 731 "src/xml_hist.y"
{yyval.FLXT_host_name = NULL;;
    break;}
case 207:
#line 732 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 208:
#line 734 "src/xml_hist.y"
{my_printf("</HOST_NAME>\n"); yyval.FLXT_host_name = yyvsp[-1].s;;
    break;}
case 209:
#line 738 "src/xml_hist.y"
{my_printf("<TOOL_NAME");;
    break;}
case 210:
#line 740 "src/xml_hist.y"
{yyval.FLXT_tool_name = yyvsp[0].FLXT_tool_name;;
    break;}
case 211:
#line 743 "src/xml_hist.y"
{yyval.FLXT_tool_name = NULL;;
    break;}
case 212:
#line 744 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 213:
#line 746 "src/xml_hist.y"
{my_printf("</TOOL_NAME>\n"); yyval.FLXT_tool_name = yyvsp[-1].s;;
    break;}
case 214:
#line 750 "src/xml_hist.y"
{my_printf("<TOOL_VERSION");;
    break;}
case 215:
#line 752 "src/xml_hist.y"
{yyval.FLXT_tool_version = yyvsp[0].FLXT_tool_version;;
    break;}
case 216:
#line 755 "src/xml_hist.y"
{yyval.FLXT_tool_version = NULL;;
    break;}
case 217:
#line 756 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 218:
#line 758 "src/xml_hist.y"
{my_printf("</TOOL_VERSION>\n"); yyval.FLXT_tool_version = yyvsp[-1].s;;
    break;}
case 219:
#line 762 "src/xml_hist.y"
{my_printf("<FILENAME");;
    break;}
case 220:
#line 764 "src/xml_hist.y"
{yyval.FLXT_filename = yyvsp[0].FLXT_filename;;
    break;}
case 221:
#line 767 "src/xml_hist.y"
{yyval.FLXT_filename = NULL;;
    break;}
case 222:
#line 768 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 223:
#line 770 "src/xml_hist.y"
{my_printf("</FILENAME>\n"); yyval.FLXT_filename = yyvsp[-1].s;;
    break;}
case 224:
#line 774 "src/xml_hist.y"
{my_printf("<TEST_PATH");;
    break;}
case 225:
#line 776 "src/xml_hist.y"
{yyval.FLXT_test_path = yyvsp[0].FLXT_test_path;;
    break;}
case 226:
#line 779 "src/xml_hist.y"
{yyval.FLXT_test_path = NULL;;
    break;}
case 227:
#line 780 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 228:
#line 782 "src/xml_hist.y"
{my_printf("</TEST_PATH>\n"); yyval.FLXT_test_path = yyvsp[-1].s;;
    break;}
case 229:
#line 786 "src/xml_hist.y"
{my_printf("<OPTIONS_SET");;
    break;}
case 230:
#line 788 "src/xml_hist.y"
{yyval.FLXT_options_set = yyvsp[0].FLXT_options_set;;
    break;}
case 231:
#line 791 "src/xml_hist.y"
{yyval.FLXT_options_set = NULL;;
    break;}
case 232:
#line 792 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 233:
#line 794 "src/xml_hist.y"
{my_printf("</OPTIONS_SET>\n"); yyval.FLXT_options_set = yyvsp[-1].s;;
    break;}
case 234:
#line 798 "src/xml_hist.y"
{my_printf("<TEST_NAME");;
    break;}
case 235:
#line 800 "src/xml_hist.y"
{yyval.FLXT_test_name = yyvsp[0].FLXT_test_name;;
    break;}
case 236:
#line 803 "src/xml_hist.y"
{yyval.FLXT_test_name = NULL;;
    break;}
case 237:
#line 804 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 238:
#line 806 "src/xml_hist.y"
{my_printf("</TEST_NAME>\n"); yyval.FLXT_test_name = yyvsp[-1].s;;
    break;}
case 239:
#line 810 "src/xml_hist.y"
{my_printf("<TEST_MODE");;
    break;}
case 240:
#line 812 "src/xml_hist.y"
{yyval.FLXT_test_mode = yyvsp[0].FLXT_test_mode;;
    break;}
case 241:
#line 815 "src/xml_hist.y"
{yyval.FLXT_test_mode = NULL;;
    break;}
case 242:
#line 816 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 243:
#line 818 "src/xml_hist.y"
{my_printf("</TEST_MODE>\n"); yyval.FLXT_test_mode = yyvsp[-1].s;;
    break;}
case 244:
#line 822 "src/xml_hist.y"
{my_printf("<LEVEL");;
    break;}
case 245:
#line 824 "src/xml_hist.y"
{yyval.FLXT_level = yyvsp[0].FLXT_level;;
    break;}
case 246:
#line 827 "src/xml_hist.y"
{yyval.FLXT_level = NULL;;
    break;}
case 247:
#line 828 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 248:
#line 830 "src/xml_hist.y"
{my_printf("</LEVEL>\n"); yyval.FLXT_level = yyvsp[-1].s;;
    break;}
case 249:
#line 834 "src/xml_hist.y"
{my_printf("<CC_OPTIONS");;
    break;}
case 250:
#line 836 "src/xml_hist.y"
{yyval.FLXT_cc_options = yyvsp[0].FLXT_cc_options;;
    break;}
case 251:
#line 839 "src/xml_hist.y"
{yyval.FLXT_cc_options = NULL;;
    break;}
case 252:
#line 840 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 253:
#line 842 "src/xml_hist.y"
{my_printf("</CC_OPTIONS>\n"); yyval.FLXT_cc_options = yyvsp[-1].s;;
    break;}
case 254:
#line 846 "src/xml_hist.y"
{my_printf("<CFLAGS");;
    break;}
case 255:
#line 848 "src/xml_hist.y"
{yyval.FLXT_cflags = yyvsp[0].FLXT_cflags;;
    break;}
case 256:
#line 851 "src/xml_hist.y"
{yyval.FLXT_cflags = NULL;;
    break;}
case 257:
#line 852 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 258:
#line 854 "src/xml_hist.y"
{my_printf("</CFLAGS>\n"); yyval.FLXT_cflags = yyvsp[-1].s;;
    break;}
case 259:
#line 858 "src/xml_hist.y"
{my_printf("<MAKEFILE");;
    break;}
case 260:
#line 860 "src/xml_hist.y"
{yyval.FLXT_makefile = yyvsp[0].FLXT_makefile;;
    break;}
case 261:
#line 863 "src/xml_hist.y"
{yyval.FLXT_makefile = NULL;;
    break;}
case 262:
#line 864 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 263:
#line 866 "src/xml_hist.y"
{my_printf("</MAKEFILE>\n"); yyval.FLXT_makefile = yyvsp[-1].s;;
    break;}
case 264:
#line 870 "src/xml_hist.y"
{my_printf("<MAKE_OPTIONS");;
    break;}
case 265:
#line 872 "src/xml_hist.y"
{yyval.FLXT_make_options = yyvsp[0].FLXT_make_options;;
    break;}
case 266:
#line 875 "src/xml_hist.y"
{yyval.FLXT_make_options = NULL;;
    break;}
case 267:
#line 876 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 268:
#line 878 "src/xml_hist.y"
{my_printf("</MAKE_OPTIONS>\n"); yyval.FLXT_make_options = yyvsp[-1].s;;
    break;}
case 269:
#line 882 "src/xml_hist.y"
{my_printf("<SIMULATOR");;
    break;}
case 270:
#line 884 "src/xml_hist.y"
{yyval.FLXT_simulator = yyvsp[0].FLXT_simulator;;
    break;}
case 271:
#line 887 "src/xml_hist.y"
{yyval.FLXT_simulator = NULL;;
    break;}
case 272:
#line 888 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 273:
#line 890 "src/xml_hist.y"
{my_printf("</SIMULATOR>\n"); yyval.FLXT_simulator = yyvsp[-1].s;;
    break;}
case 274:
#line 894 "src/xml_hist.y"
{my_printf("<SIM_OPTIONS");;
    break;}
case 275:
#line 896 "src/xml_hist.y"
{yyval.FLXT_sim_options = yyvsp[0].FLXT_sim_options;;
    break;}
case 276:
#line 899 "src/xml_hist.y"
{yyval.FLXT_sim_options = NULL;;
    break;}
case 277:
#line 900 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 278:
#line 902 "src/xml_hist.y"
{my_printf("</SIM_OPTIONS>\n"); yyval.FLXT_sim_options = yyvsp[-1].s;;
    break;}
case 279:
#line 906 "src/xml_hist.y"
{my_printf("<TARGET");;
    break;}
case 280:
#line 908 "src/xml_hist.y"
{yyval.FLXT_target = yyvsp[0].FLXT_target;;
    break;}
case 281:
#line 911 "src/xml_hist.y"
{yyval.FLXT_target = NULL;;
    break;}
case 282:
#line 912 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 283:
#line 914 "src/xml_hist.y"
{my_printf("</TARGET>\n"); yyval.FLXT_target = yyvsp[-1].s;;
    break;}
case 284:
#line 918 "src/xml_hist.y"
{my_printf("<MAKE_ARGV");;
    break;}
case 285:
#line 920 "src/xml_hist.y"
{yyval.FLXT_make_argv = yyvsp[0].FLXT_make_argv;;
    break;}
case 286:
#line 923 "src/xml_hist.y"
{yyval.FLXT_make_argv = NULL;;
    break;}
case 287:
#line 924 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 288:
#line 926 "src/xml_hist.y"
{my_printf("</MAKE_ARGV>\n"); yyval.FLXT_make_argv = yyvsp[-1].s;;
    break;}
case 289:
#line 930 "src/xml_hist.y"
{my_printf("<DESCRIPTION");;
    break;}
case 290:
#line 932 "src/xml_hist.y"
{yyval.FLXT_description = yyvsp[0].FLXT_description;;
    break;}
case 291:
#line 935 "src/xml_hist.y"
{yyval.FLXT_description = NULL;;
    break;}
case 292:
#line 936 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 293:
#line 938 "src/xml_hist.y"
{my_printf("</DESCRIPTION>\n"); yyval.FLXT_description = yyvsp[-1].s;;
    break;}
case 294:
#line 942 "src/xml_hist.y"
{my_printf("<STATUS");;
    break;}
case 295:
#line 944 "src/xml_hist.y"
{yyval.FLXT_status = yyvsp[0].FLXT_status;;
    break;}
case 296:
#line 947 "src/xml_hist.y"
{yyval.FLXT_status = NULL;;
    break;}
case 297:
#line 948 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 298:
#line 950 "src/xml_hist.y"
{my_printf("</STATUS>\n"); yyval.FLXT_status = yyvsp[-1].s;;
    break;}
case 299:
#line 954 "src/xml_hist.y"
{my_printf("<SIZE");;
    break;}
case 300:
#line 956 "src/xml_hist.y"
{yyval.FLXT_size = yyvsp[0].FLXT_size;;
    break;}
case 301:
#line 959 "src/xml_hist.y"
{yyval.FLXT_size = NULL;;
    break;}
case 302:
#line 960 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 303:
#line 962 "src/xml_hist.y"
{my_printf("</SIZE>\n"); yyval.FLXT_size = yyvsp[-1].s;;
    break;}
case 304:
#line 966 "src/xml_hist.y"
{my_printf("<INPUT");;
    break;}
case 305:
#line 968 "src/xml_hist.y"
{yyval.FLXT_input = yyvsp[0].FLXT_input;;
    break;}
case 306:
#line 971 "src/xml_hist.y"
{yyval.FLXT_input = NULL;;
    break;}
case 307:
#line 972 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 308:
#line 974 "src/xml_hist.y"
{my_printf("</INPUT>\n"); yyval.FLXT_input = yyvsp[-1].s;;
    break;}
case 309:
#line 978 "src/xml_hist.y"
{my_printf("<N_FRAMES");;
    break;}
case 310:
#line 980 "src/xml_hist.y"
{yyval.FLXT_n_frames = yyvsp[0].FLXT_n_frames;;
    break;}
case 311:
#line 983 "src/xml_hist.y"
{yyval.FLXT_n_frames = NULL;;
    break;}
case 312:
#line 984 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 313:
#line 986 "src/xml_hist.y"
{my_printf("</N_FRAMES>\n"); yyval.FLXT_n_frames = yyvsp[-1].s;;
    break;}
case 314:
#line 990 "src/xml_hist.y"
{my_printf("<SAMPLE_P_FRAME");;
    break;}
case 315:
#line 992 "src/xml_hist.y"
{yyval.FLXT_sample_p_frame = yyvsp[0].FLXT_sample_p_frame;;
    break;}
case 316:
#line 995 "src/xml_hist.y"
{yyval.FLXT_sample_p_frame = NULL;;
    break;}
case 317:
#line 996 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 318:
#line 998 "src/xml_hist.y"
{my_printf("</SAMPLE_P_FRAME>\n"); yyval.FLXT_sample_p_frame = yyvsp[-1].s;;
    break;}
case 319:
#line 1002 "src/xml_hist.y"
{my_printf("<E_FREQ");;
    break;}
case 320:
#line 1004 "src/xml_hist.y"
{yyval.FLXT_e_freq = yyvsp[0].FLXT_e_freq;;
    break;}
case 321:
#line 1007 "src/xml_hist.y"
{yyval.FLXT_e_freq = NULL;;
    break;}
case 322:
#line 1008 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 323:
#line 1010 "src/xml_hist.y"
{my_printf("</E_FREQ>\n"); yyval.FLXT_e_freq = yyvsp[-1].s;;
    break;}
case 324:
#line 1014 "src/xml_hist.y"
{my_printf("<ARGV");;
    break;}
case 325:
#line 1016 "src/xml_hist.y"
{yyval.FLXT_argv = yyvsp[0].FLXT_argv;;
    break;}
case 326:
#line 1019 "src/xml_hist.y"
{yyval.FLXT_argv = NULL;;
    break;}
case 327:
#line 1020 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 328:
#line 1022 "src/xml_hist.y"
{my_printf("</ARGV>\n"); yyval.FLXT_argv = yyvsp[-1].s;;
    break;}
case 329:
#line 1026 "src/xml_hist.y"
{my_printf("<CYCLES");;
    break;}
case 330:
#line 1028 "src/xml_hist.y"
{yyval.FLXT_cycles = yyvsp[0].FLXT_cycles;;
    break;}
case 331:
#line 1031 "src/xml_hist.y"
{yyval.FLXT_cycles = NULL;;
    break;}
case 332:
#line 1032 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 333:
#line 1034 "src/xml_hist.y"
{my_printf("</CYCLES>\n"); yyval.FLXT_cycles = yyvsp[-1].s;;
    break;}
case 334:
#line 1038 "src/xml_hist.y"
{my_printf("<CYCLES_P_FRAME");;
    break;}
case 335:
#line 1040 "src/xml_hist.y"
{yyval.FLXT_cycles_p_frame = yyvsp[0].FLXT_cycles_p_frame;;
    break;}
case 336:
#line 1043 "src/xml_hist.y"
{yyval.FLXT_cycles_p_frame = NULL;;
    break;}
case 337:
#line 1044 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 338:
#line 1046 "src/xml_hist.y"
{my_printf("</CYCLES_P_FRAME>\n"); yyval.FLXT_cycles_p_frame = yyvsp[-1].s;;
    break;}
case 339:
#line 1050 "src/xml_hist.y"
{my_printf("<MIPS");;
    break;}
case 340:
#line 1052 "src/xml_hist.y"
{yyval.FLXT_mips = yyvsp[0].FLXT_mips;;
    break;}
case 341:
#line 1055 "src/xml_hist.y"
{yyval.FLXT_mips = NULL;;
    break;}
case 342:
#line 1056 "src/xml_hist.y"
{my_printf(">");;
    break;}
case 343:
#line 1058 "src/xml_hist.y"
{my_printf("</MIPS>\n"); yyval.FLXT_mips = yyvsp[-1].s;;
    break;}
case 344:
#line 1062 "src/xml_hist.y"
{my_printf("DATA(%s)",yyvsp[0].s); yyval.s = yyvsp[0].s;;
    break;}
case 345:
#line 1063 "src/xml_hist.y"
{yyval.s = yyvsp[-1].s;;
    break;}
case 346:
#line 1064 "src/xml_hist.y"
{yyclearin; yyerrok;;
    break;}
case 347:
#line 1065 "src/xml_hist.y"
{yyval.s = strdup("");;
    break;}
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 1069 "src/xml_hist.y"
