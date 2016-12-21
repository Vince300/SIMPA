/************************************************************************
MOTOROLA - METROWERKS
FILE : xml_hist.y
DATE OF LAST CHANGE :
VERSION :
AUTHOR : GUERTE YVES
CONTENT : GRAMMAR FOR XML HISTORY OF REPORTS
*************************************************************************/

/************** include section **************/
%{
#include "common_yacc_lex.h"
extern char yy1text[];

/* #define my_printf(x...) printf(x) */
#define my_printf(x...) {}

%}

/************** Tokens and Structures used **************/

%token VERSION ATTDEF ENDDEF EQ SLASH CLOSE END
%token START_HISTORY          CLOSE_HISTORY          
%token START_REPORT           CLOSE_REPORT           
%token START_RUN_ID           CLOSE_RUN_ID          
%token START_SCENARIO_FILE    CLOSE_SCENARIO_FILE    
%token START_START_DATE       CLOSE_START_DATE             
%token START_END_DATE         CLOSE_END_DATE             
%token START_COMPILER_VERSION CLOSE_COMPILER_VERSION 
%token START_TOOL             CLOSE_TOOL
%token START_TOOL_NAME        CLOSE_TOOL_NAME
%token START_TOOL_VERSION     CLOSE_TOOL_VERSION
%token START_SCENARIO         CLOSE_SCENARIO         
%token START_PARAM_FILES      CLOSE_PARAM_FILES      
%token START_PARAM_FILE       CLOSE_PARAM_FILE      
%token START_FILENAME         CLOSE_FILENAME      
%token START_TEST_DEF         CLOSE_TEST_DEF        
%token START_TEST_PATH        CLOSE_TEST_PATH        
%token START_OPTIONS_SET      CLOSE_OPTIONS_SET        
%token START_TEST             CLOSE_TEST        
%token START_TEST_NAME        CLOSE_TEST_NAME        
%token START_HOST_TYPE        CLOSE_HOST_TYPE        
%token START_HOST_NAME        CLOSE_HOST_NAME        
%token START_TEST_MODE        CLOSE_TEST_MODE        
%token START_LEVEL            CLOSE_LEVEL            
%token START_CC_OPTIONS       CLOSE_CC_OPTIONS       
%token START_CFLAGS           CLOSE_CFLAGS           
%token START_MAKEFILE         CLOSE_MAKEFILE         
%token START_MAKE_OPTIONS     CLOSE_MAKE_OPTIONS     
%token START_SIMULATOR        CLOSE_SIMULATOR        
%token START_SIM_OPTIONS      CLOSE_SIM_OPTIONS      
%token START_TARGETS          CLOSE_TARGETS          
%token START_TARGET           CLOSE_TARGET           
%token START_COMPILATION      CLOSE_COMPILATION             
%token START_MAKE_ARGV        CLOSE_MAKE_ARGV             
%token START_EXEC             CLOSE_EXEC             
%token START_DESCRIPTION      CLOSE_DESCRIPTION      
%token START_STATUS           CLOSE_STATUS           
%token START_SIZE             CLOSE_SIZE             
%token START_INPUT            CLOSE_INPUT            
%token START_N_FRAMES         CLOSE_N_FRAMES         
%token START_SAMPLE_P_FRAME   CLOSE_SAMPLE_P_FRAME   
%token START_E_FREQ           CLOSE_E_FREQ           
%token START_ARGV             CLOSE_ARGV             
%token START_CYCLES           CLOSE_CYCLES           
%token START_CYCLES_P_FRAME   CLOSE_CYCLES_P_FRAME   
%token START_MIPS             CLOSE_MIPS             
%token START_OPT_REPORT_ERROR CLOSE_OPT_REPORT_ERROR 
%token <s> ENCODING NAME VALUE DATA COMMENT START
%token <FLXT_rawdata> RAWDATA


%type <s>                       /* name_opt */			content_string
%type <FLXT_history>             element_history                 empty_or_content_history                content_history

/* Elements contained by history */
/* %type <FLXT_history>             element_history                 empty_or_content_history                content_history */
%type <FLXT_report>              element_report                  empty_or_content_report                 content_report
%type <FLXT_attribute_seq_opt>   attribute_seq_opt

/* Elements contained by report */
/* %type <FLXT_report>              element_report                  empty_or_content_report                 content_report */
%type <FLXT_run_id>              element_run_id                  empty_or_content_run_id                 
%type <FLXT_scenario_file>       element_scenario_file           empty_or_content_scenario_file          
%type <FLXT_start_date>          element_start_date              empty_or_content_start_date             
%type <FLXT_end_date>            element_end_date                empty_or_content_end_date               
%type <FLXT_compiler_version>    element_compiler_version        empty_or_content_compiler_version       content_compiler_version
%type <FLXT_scenario>            element_scenario                empty_or_content_scenario               content_scenario
%type <FLXT_param_files>         element_param_files             empty_or_content_param_files            content_param_files
%type <FLXT_test>                element_test                    empty_or_content_test                   content_test
%type <FLXT_opt_report_error>    element_opt_report_error        empty_or_content_opt_report_error

/* Elements contained by compiler_version */
/* %type <FLXT_compiler_version>    element_compiler_version        empty_or_content_compiler_version       content_compiler_version */
%type <FLXT_host_type>           element_host_type               empty_or_content_host_type                   
%type <FLXT_host_name>           element_host_name               empty_or_content_host_name                   
%type <FLXT_tool>                element_tool                    empty_or_content_tool                   content_tool     

/* Elements contained by tool */
/* %type <FLXT_tool>                element_tool                    empty_or_content_tool                   content_tool */     
%type <FLXT_tool_name>           element_tool_name               empty_or_content_tool_name                   
%type <FLXT_tool_version>        element_tool_version            empty_or_content_tool_version                

/* Elements contained by scenario */
/* %type <FLXT_scenario>            element_scenario                empty_or_content_scenario               content_scenario */
/* %type <FLXT_host_name>           element_host_name               empty_or_content_host_name               */     
%type <FLXT_test_def>            element_test_def                empty_or_content_test_def               content_test_def     

/* Elements contained by test_def */
%type <FLXT_test_path>           element_test_path               empty_or_content_test_path                   
%type <FLXT_options_set>         element_options_set             empty_or_content_options_set                 

/* Elements contained by param_files */
/* %type <FLXT_param_files>         element_param_files             empty_or_content_param_files            content_param_files */
/* %type <FLXT_host_name>           element_host_name               empty_or_content_host_name              content_host_name */     
%type <FLXT_param_file>         	element_param_file             	empty_or_content_param_file            	content_param_file

/* Elements contained by param_file */
/* %type <FLXT_param_file>         element_param_file             empty_or_content_param_file            content_param_file */
%type <FLXT_filename>         	element_filename             	empty_or_content_filename            


/* Elements contained by test */
/* %type <FLXT_test>             element_test                    empty_or_content_test                   content_test */
/* %type <FLXT_test_path>           element_test_path               empty_or_content_test_path               */     
%type <FLXT_test_name>           element_test_name               empty_or_content_test_name                   
/* %type <FLXT_host_name>           element_host_name               empty_or_content_host_name               */     
%type <FLXT_test_mode>           element_test_mode               empty_or_content_test_mode                   
%type <FLXT_level>               element_level                   empty_or_content_level                           
%type <FLXT_cc_options>          element_cc_options              empty_or_content_cc_options                 
%type <FLXT_cflags>              element_cflags                  empty_or_content_cflags                         
%type <FLXT_makefile>            element_makefile                empty_or_content_makefile                     
%type <FLXT_make_options>        element_make_options            empty_or_content_make_options             
%type <FLXT_simulator>           element_simulator               empty_or_content_simulator                   
%type <FLXT_sim_options>         element_sim_options             empty_or_content_sim_options               
%type <FLXT_targets>             element_targets                 empty_or_content_targets                content_targets        
%type <FLXT_compilation>         element_compilation             empty_or_content_compilation            content_compilation          
%type <FLXT_make_argv>           element_make_argv               empty_or_content_make_argv          
%type <FLXT_exec>                element_exec                    empty_or_content_exec                   content_exec          
/* %type <FLXT_opt_report_error>    element_opt_report_error        empty_or_content_opt_report_error */


/* Elements contained by compilation */
/* %type <FLXT_compilation>         element_compilation             empty_or_content_compilation            content_compilation          */
%type <FLXT_target>              element_target                  empty_or_content_target           	
/* %type <FLXT_cflags>              element_cflags                  empty_or_content_cflags                         */
%type <FLXT_make_argv>           element_make_argv               empty_or_content_make_argv           	
/* %type <FLXT_start_date>          element_start_date              empty_or_content_start_date             */
/* %type <FLXT_end_date>            element_end_date                empty_or_content_end_date               */


/* Elements contained by exec */
/* %type <FLXT_exec>             element_exec                    empty_or_content_exec             	content_exec */
/* %type <FLXT_target>              element_target                  empty_or_content_target           	*/
%type <FLXT_description>         element_description             empty_or_content_description      	
%type <FLXT_status>              element_status                  empty_or_content_status           	
%type <FLXT_size>                element_size                    empty_or_content_size             	
%type <FLXT_input>               element_input                   empty_or_content_input            	
%type <FLXT_n_frames>            element_n_frames                empty_or_content_n_frames 		
%type <FLXT_sample_p_frame>      element_sample_p_frame          empty_or_content_sample_p_frame   	
%type <FLXT_e_freq>              element_e_freq                  empty_or_content_e_freq           	
%type <FLXT_argv>                element_argv                    empty_or_content_argv             	
%type <FLXT_cycles>              element_cycles                  empty_or_content_cycles           	
%type <FLXT_cycles_p_frame>      element_cycles_p_frame          empty_or_content_cycles_p_frame   	
%type <FLXT_mips>                element_mips                    empty_or_content_mips             	
								      
%type <FLXT_target>              element_target                  empty_or_content_target                         

%type <FLXT_attribute>           attribute

%union {
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
}

%start document

/************** Non terminals type declaration **************/


%%
/************** Grammar begin ***************/
document
 : prolog
   element_history		{result_history = $2;}
   misc_seq_opt			
 ;
prolog
 : version_opt encoding_opt
   misc_seq_opt
 ;
version_opt
 : VERSION			{my_printf("<?xml version=\"1.0\" ?>\n");}
 | /*empty*/
 ;
encoding_opt
 : ENCODING			{my_printf("<?XML-ENCODING %s?>\n",$1); free($1);}
 | /*empty*/
 ;
misc_seq_opt
 : misc_seq_opt misc
 | /*empty*/
 ;
misc
 : COMMENT			{my_printf("%s", $1);}
 | attribute_decl
 ;
attribute_decl
 : ATTDEF NAME			{my_printf("\n<?XML-ATT %s", $2);}
   attribute_seq_opt ENDDEF	{my_printf("?>\n");}
 ;	
/************** Generic ***************/
//element
// : START                        {my_printf("\n<%s", $1); free($1);}
//   attribute_seq_opt
//   empty_or_content
// ;
//empty_or_content
// : SLASH CLOSE                  {my_printf("/>\n");}
// | CLOSE                        {my_printf(">");}
//   content END name_opt CLOSE   {my_printf("</%s>\n", $5); free($5);}
// ;
//content
// : content DATA                 {my_printf("%s", $2); free($2);}
// | content misc
// | content element
// | content RAWDATA              {my_printf("\n%s\n", $2); free($2);}
// | /*empty*/
// ;
//name_opt
// : NAME				{$$ = $1;}
// | /*empty*/			{$$ = strdup("");}
// ;
/************** History ***************/
element_history
 : START_HISTORY		{my_printf("<HISTORY");}
   attribute_seq_opt
   empty_or_content_history	{$$ = $4;}
 ;
empty_or_content_history
 : SLASH CLOSE			{
				 my_printf("/>\n");
				 $$ = empty_history();
				}
 | CLOSE			{my_printf(">");}
   content_history
   CLOSE_HISTORY		{ 
				 my_printf("</HISTORY>\n");
				 $$ = $3;
				}
 ;
content_history
 : content_history misc		{$$ = $1;}
 | content_history
   element_report		{$$ = add_report_to_history($2, $1);}
 | error 			{yyclearin; yyerrok;}
 | /*empty*/			{$$ = empty_history();}
 ;
/************** Report ***************/
element_report
 : START_REPORT			{my_printf("\n<%s", "REPORT");}
   attribute_seq_opt
   empty_or_content_report	{$$ = $4}
 ;
empty_or_content_report
 : SLASH CLOSE			{
				 $$ = empty_report();
				 my_printf("/>\n");
				}
 | CLOSE			{my_printf(">");}
   content_report
   CLOSE_REPORT			{ 
				 my_printf("</%s>\n", "REPORT");
				 $$ = $3;
				}
 ;
content_report
 : content_report misc                     {$$ = $1;}
 | content_report element_run_id           {$$ = add_run_id_to_report($2, $1);}
 | content_report element_scenario_file    {$$ = add_scenario_file_to_report($2, $1);}
 | content_report element_start_date       {$$ = add_start_date_to_report($2, $1);}
 | content_report element_end_date         {$$ = add_end_date_to_report($2, $1);}
 | content_report element_compiler_version {$$ = add_compiler_version_to_report($2, $1);}
 | content_report element_scenario         {$$ = add_scenario_to_report($2, $1);}
 | content_report element_param_files      {$$ = add_param_files_to_report($2, $1);}
 | content_report element_test             {$$ = add_test_to_report($2, $1);}
 | content_report element_opt_report_error {$$ = add_opt_report_error_to_report($2, $1);}
 | error 				   {yyclearin; yyerrok;}
 | /*empty*/                               {$$ = empty_report();}
 ;
/************** Scenario ***************/
element_scenario
 : START_SCENARIO		{my_printf("<SCENARIO");}
   attribute_seq_opt
   empty_or_content_scenario	{$$ = $4;}
 ;
empty_or_content_scenario
 : SLASH CLOSE			{
				 my_printf("/>\n");
				 $$ = empty_scenario();
				}
 | CLOSE			{my_printf(">");}
   content_scenario
   CLOSE_SCENARIO		{ 
				 my_printf("</SCENARIO>\n");
				 $$ = $3;
				}
 ;
content_scenario
 : content_scenario misc	{$$ = $1;}
 | content_scenario
   element_host_name		{$$ = add_host_name_to_scenario($2, $1);}
 | content_scenario
   element_test_def		{$$ = add_test_def_to_scenario($2, $1);}
 | error 			{yyclearin; yyerrok;}
 | /*empty*/			{$$ = empty_scenario();}
 ;
/************** Test_def ***************/
element_test_def
 : START_TEST_DEF		{my_printf("<TEST_DEF");}
   attribute_seq_opt
   empty_or_content_test_def	{$$ = $4;}
 ;
empty_or_content_test_def
 : SLASH CLOSE			{
				 my_printf("/>\n");
				 $$ = empty_test_def();
				}
 | CLOSE			{my_printf(">");}
   content_test_def
   CLOSE_TEST_DEF		{ 
				 my_printf("</TEST_DEF>\n");
				 $$ = $3;
				}
 ;
content_test_def
 : content_test_def misc	{$$ = $1;}
 | content_test_def
   element_test_path		{$$ = add_test_path_to_test_def($2, $1);}
 | content_test_def
   element_options_set		{$$ = add_options_set_to_test_def($2, $1);}
 | error 			{yyclearin; yyerrok;}
 | /*empty*/			{$$ = empty_test_def();}
 ;
/************** Test ***************/
element_test
 : START_TEST				{my_printf("\n<%s", "TEST");}
   attribute_seq_opt
   empty_or_content_test		{$$ = $4;}
 ;
empty_or_content_test
 : SLASH CLOSE				{
					 $$ = empty_test();
					 my_printf("/>\n");
					}
 | CLOSE				{my_printf(">");}
   content_test
   CLOSE_TEST				{
					 my_printf("</%s>\n", "TEST");
					 $$ = $3;
					}
 ;
content_test
 : content_test misc			{$$ = $1;}
 | content_test element_test_path       {$$ = add_test_path_to_test($2, $1);}
 | content_test element_start_date      {$$ = add_start_date_to_test($2, $1);}
 | content_test element_end_date        {$$ = add_end_date_to_test($2, $1);}
 | content_test element_test_name       {$$ = add_test_name_to_test($2, $1);}
 | content_test element_host_name       {$$ = add_host_name_to_test($2, $1);}
 | content_test element_test_mode       {$$ = add_test_mode_to_test($2, $1);}
 | content_test element_level           {$$ = add_level_to_test($2, $1);}
 | content_test element_cc_options      {$$ = add_cc_options_to_test($2, $1);}
 | content_test element_cflags          {$$ = add_cflags_to_test($2, $1);}
 | content_test element_makefile        {$$ = add_makefile_to_test($2, $1);}
 | content_test element_make_options    {$$ = add_make_options_to_test($2, $1);}
 | content_test element_simulator       {$$ = add_simulator_to_test($2, $1);}
 | content_test element_sim_options     {$$ = add_sim_options_to_test($2, $1);}
 | content_test element_targets         {$$ = add_targets_to_test($2, $1);}
 | content_test element_compilation     {$$ = add_compilation_to_test($2, $1);}
 | content_test element_exec            {$$ = add_exec_to_test($2, $1);}
 | content_test element_opt_report_error {$$ = add_opt_report_error_to_test($2, $1);}
 | error 				{yyclearin; yyerrok;}
 | /*empty*/                            {$$ = empty_test();}
 ;
/************** Targets ***************/
element_targets
 : START_TARGETS		{my_printf("<TARGETS");}
   attribute_seq_opt
   empty_or_content_targets	{$$ = $4;}
 ;
empty_or_content_targets
 : SLASH CLOSE			{
				 my_printf("/>\n");
				 $$ = empty_targets();
				}
 | CLOSE			{my_printf(">");}
   content_targets
   CLOSE_TARGETS		{ 
				 my_printf("</TARGETS>\n");
				 $$ = $3;
				}
 ;
content_targets
 : content_targets misc		{$$ = $1;}
 | content_targets
   element_target		{$$ = add_target_to_targets($2, $1);}
 | error 			{yyclearin; yyerrok;}
 | /*empty*/			{$$ = empty_targets();}
 ;

/************** Compilation ***************/
element_compilation
 : START_COMPILATION				{my_printf("\n<%s", "COMPILATION");}
   attribute_seq_opt
   empty_or_content_compilation		{$$ = $4;}
 ;
empty_or_content_compilation
 : SLASH CLOSE				{
					 $$ = empty_compilation();
					 my_printf("/>\n");
					}
 | CLOSE				{my_printf(">");}
   content_compilation
   CLOSE_COMPILATION				{
					 my_printf("</%s>\n", "COMPILATION");
					 $$ = $3;
					}
 ;
content_compilation
 : content_compilation misc			{$$ = $1;}
 | content_compilation element_target          {$$ = add_target_to_compilation($2, $1);}
 | content_compilation element_cflags          {$$ = add_cflags_to_compilation($2, $1);}
 | content_compilation element_make_argv       {$$ = add_make_argv_to_compilation($2, $1);}
 | content_compilation element_start_date      {$$ = add_start_date_to_compilation($2, $1);}
 | content_compilation element_end_date        {$$ = add_end_date_to_compilation($2, $1);}
 | error 				{yyclearin; yyerrok;}
 | /*empty*/                            {$$ = empty_compilation();}
 ;
/************** Exec ***************/
element_exec
 : START_EXEC				{my_printf("\n<%s", "EXEC");}
   attribute_seq_opt
   empty_or_content_exec		{$$ = $4;}
 ;
empty_or_content_exec
 : SLASH CLOSE				{
					 $$ = empty_exec();
					 nb_execs++;
					 my_printf(" exec_num=\"%d\"/>\n", nb_execs);
					}
 | CLOSE				{my_printf(">");}
   content_exec
   CLOSE_EXEC				{
					 nb_execs++;
					 my_printf("</%s exec_num=\"%d\">\n", "EXEC", nb_execs);
					 $$ = $3;
					}
 ;
content_exec
 : content_exec misc			{$$ = $1;}
 | content_exec element_target          {$$ = add_target_to_exec($2, $1);}
 | content_exec element_description     {$$ = add_description_to_exec($2, $1);}
 | content_exec element_status          {$$ = add_status_to_exec($2, $1);}
 | content_exec element_size            {$$ = add_size_to_exec($2, $1);}
 | content_exec element_input           {$$ = add_input_to_exec($2, $1);}
 | content_exec element_n_frames        {$$ = add_n_frames_to_exec($2, $1);}
 | content_exec element_sample_p_frame  {$$ = add_sample_p_frame_to_exec($2, $1);}
 | content_exec element_e_freq          {$$ = add_e_freq_to_exec($2, $1);}
 | content_exec element_argv            {$$ = add_argv_to_exec($2, $1);}
 | content_exec element_cycles          {$$ = add_cycles_to_exec($2, $1);}
 | content_exec element_cycles_p_frame  {$$ = add_cycles_p_frame_to_exec($2, $1);}
 | content_exec element_mips            {$$ = add_mips_to_exec($2, $1);}
 | content_exec element_start_date      {$$ = add_start_date_to_exec($2, $1);}
 | content_exec element_end_date        {$$ = add_end_date_to_exec($2, $1);}
 | error 				{yyclearin; yyerrok;}
 | /*empty*/                            {$$ = empty_exec();}
 ;
/************** Compiler_version ***************/
element_compiler_version
 : START_COMPILER_VERSION		{my_printf("<COMPILER_VERSION");}
   attribute_seq_opt
   empty_or_content_compiler_version	{$$ = $4;}
 ;
empty_or_content_compiler_version
 : SLASH CLOSE				{
					 my_printf("/>\n");
					 $$ = empty_compiler_version();
					}
 | CLOSE				{my_printf(">");}
   content_compiler_version
   CLOSE_COMPILER_VERSION		{ 
					 my_printf("</COMPILER_VERSION>\n");
					 $$ = $3;
					}
 ;
content_compiler_version
 : content_compiler_version misc	{$$ = $1;}
 | content_compiler_version
   element_host_type			{$$ = add_host_type_to_compiler_version($2, $1);}
 | content_compiler_version
   element_host_name			{$$ = add_host_name_to_compiler_version($2, $1);}
 | content_compiler_version
   element_tool				{$$ = add_tool_to_compiler_version($2, $1);}
 | error 				{yyclearin; yyerrok;}
 | /*empty*/				{$$ = empty_compiler_version();}
 ;
/************** Tool ***************/
element_tool
 : START_TOOL			{my_printf("<TOOL");}
   attribute_seq_opt
   empty_or_content_tool	{$$ = $4;}
 ;
empty_or_content_tool
 : SLASH CLOSE			{
				 my_printf("/>\n");
				 $$ = empty_tool();
				}
 | CLOSE			{my_printf(">");}
   content_tool
   CLOSE_TOOL			{ 
				 my_printf("</TOOL>\n");
				 $$ = $3;
				}
 ;
content_tool
 : content_tool misc		{$$ = $1;}
 | content_tool
   element_tool_name		{$$ = add_tool_name_to_tool($2, $1);}
 | content_tool
   element_tool_version		{$$ = add_tool_version_to_tool($2, $1);}
 | error 			{yyclearin; yyerrok;}
 | /*empty*/			{$$ = empty_tool();}
 ;
/************** Param_files ***************/
element_param_files
 : START_PARAM_FILES		{my_printf("<PARAM_FILES");}
   attribute_seq_opt
   empty_or_content_param_files	{$$ = $4;}
 ;
empty_or_content_param_files
 : SLASH CLOSE			{
				 my_printf("/>\n");
				 $$ = empty_param_files();
				}
 | CLOSE			{my_printf(">");}
   content_param_files
   CLOSE_PARAM_FILES		{ 
				 my_printf("</PARAM_FILES>\n");
				 $$ = $3;
				}
 ;
content_param_files
 : content_param_files misc	{$$ = $1;}
 | content_param_files
   element_host_name		{$$ = add_host_name_to_param_files($2, $1);}
 | content_param_files
   element_param_file		{$$ = add_param_file_to_param_files($2, $1);}
 | error 			{yyclearin; yyerrok;}
 | /*empty*/			{$$ = empty_param_files();}
 ;
/************** Param_file ***************/
element_param_file
 : START_PARAM_FILE		{my_printf("<PARAM_FILE");}
   attribute_seq_opt
   empty_or_content_param_file	{$$ = $4;}
 ;
empty_or_content_param_file
 : SLASH CLOSE			{
				 my_printf("/>\n");
				 $$ = empty_param_file();
				}
 | CLOSE			{my_printf(">");}
   content_param_file
   CLOSE_PARAM_FILE		{ 
				 my_printf("</PARAM_FILE>\n");
				 $$ = $3;
				}
 ;
content_param_file
 : content_param_file misc	{$$ = $1;}
 | content_param_file
   element_filename		{$$ = add_filename_to_param_file($2, $1);}
 | content_param_file
 RAWDATA			{
				my_printf("<RAWDATA>\n%s\n</RAWDATA>\n",$2); 
				$$ = add_rawdata_to_param_file($2, $1);
				}
 | error 			{yyclearin; yyerrok;}
 | /*empty*/			{$$ = empty_param_file();}
 ;
/************** Others ***************/
attribute_seq_opt
 : attribute_seq_opt attribute	{$$ = add_attribute_to_attribute_seq_opt($2, $1);}
 | /*empty*/			{$$ = NULL;}
 ;
attribute
 : NAME				{my_printf(" %s", $1); free($1);}
 | NAME EQ VALUE		{my_printf(" %s=%s", $1, $3); free($1); free($3);}
 ;
/************** run_id (atomic) ***************/
element_run_id
 : START_RUN_ID				{my_printf("<RUN_ID");}
   attribute_seq_opt
   empty_or_content_run_id		{$$ = $4;}
 ;
empty_or_content_run_id
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_RUN_ID				{my_printf("</RUN_ID>\n"); $$ = $3;}
 ;
/************** scenario_file (atomic) ***************/
element_scenario_file
 : START_SCENARIO_FILE			{my_printf("<SCENARIO_FILE");}
   attribute_seq_opt
   empty_or_content_scenario_file	{$$ = $4;}
 ;
empty_or_content_scenario_file
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_SCENARIO_FILE			{my_printf("</SCENARIO_FILE>\n"); $$ = $3;}
 ;
/************** start_date (atomic) ***************/
element_start_date
 : START_START_DATE			{my_printf("<START_DATE");}
   attribute_seq_opt
   empty_or_content_start_date		{$$ = $4;}
 ;
empty_or_content_start_date
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_START_DATE			{my_printf("</START_DATE>\n"); $$ = $3;}
 ;
/************** end_date (atomic) ***************/
element_end_date
 : START_END_DATE			{my_printf("<END_DATE");}
   attribute_seq_opt
   empty_or_content_end_date		{$$ = $4;}
 ;
empty_or_content_end_date
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_END_DATE			{my_printf("</END_DATE>\n"); $$ = $3;}
 ;
/************** opt_report_error (atomic) ***************/
element_opt_report_error
 : START_OPT_REPORT_ERROR		{my_printf("<OPT_REPORT_ERROR");}
   attribute_seq_opt
   empty_or_content_opt_report_error	{$$ = $4;}
 ;
empty_or_content_opt_report_error
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_OPT_REPORT_ERROR		{my_printf("</OPT_REPORT_ERROR>\n"); $$ = $3;}
 ;
/************** host_type (atomic) ***************/
element_host_type
 : START_HOST_TYPE			{my_printf("<HOST_TYPE");}
   attribute_seq_opt
   empty_or_content_host_type		{$$ = $4;}
 ;
empty_or_content_host_type
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_HOST_TYPE			{my_printf("</HOST_TYPE>\n"); $$ = $3;}
 ;
/************** host_name (atomic) ***************/
element_host_name
 : START_HOST_NAME			{my_printf("<HOST_NAME");}
   attribute_seq_opt
   empty_or_content_host_name		{$$ = $4;}
 ;
empty_or_content_host_name
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_HOST_NAME			{my_printf("</HOST_NAME>\n"); $$ = $3;}
 ;
/************** tool_name (atomic) ***************/
element_tool_name
 : START_TOOL_NAME			{my_printf("<TOOL_NAME");}
   attribute_seq_opt
   empty_or_content_tool_name		{$$ = $4;}
 ;
empty_or_content_tool_name
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_TOOL_NAME			{my_printf("</TOOL_NAME>\n"); $$ = $3;}
 ;
/************** tool_version (atomic) ***************/
element_tool_version
 : START_TOOL_VERSION			{my_printf("<TOOL_VERSION");}
   attribute_seq_opt
   empty_or_content_tool_version	{$$ = $4;}
 ;
empty_or_content_tool_version
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_TOOL_VERSION			{my_printf("</TOOL_VERSION>\n"); $$ = $3;}
 ;
/************** filename (atomic) ***************/
element_filename
 : START_FILENAME			{my_printf("<FILENAME");}
   attribute_seq_opt
   empty_or_content_filename		{$$ = $4;}
 ;
empty_or_content_filename
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_FILENAME			{my_printf("</FILENAME>\n"); $$ = $3;}
 ;
/************** test_path (atomic) ***************/
element_test_path
 : START_TEST_PATH			{my_printf("<TEST_PATH");}
   attribute_seq_opt
   empty_or_content_test_path		{$$ = $4;}
 ;
empty_or_content_test_path
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_TEST_PATH			{my_printf("</TEST_PATH>\n"); $$ = $3;}
 ;
/************** options_set (atomic) ***************/
element_options_set
 : START_OPTIONS_SET			{my_printf("<OPTIONS_SET");}
   attribute_seq_opt
   empty_or_content_options_set		{$$ = $4;}
 ;
empty_or_content_options_set
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_OPTIONS_SET			{my_printf("</OPTIONS_SET>\n"); $$ = $3;}
 ;
/************** test_name (atomic) ***************/
element_test_name
 : START_TEST_NAME			{my_printf("<TEST_NAME");}
   attribute_seq_opt
   empty_or_content_test_name		{$$ = $4;}
 ;
empty_or_content_test_name
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_TEST_NAME			{my_printf("</TEST_NAME>\n"); $$ = $3;}
 ;
/************** test_mode (atomic) ***************/
element_test_mode
 : START_TEST_MODE			{my_printf("<TEST_MODE");}
   attribute_seq_opt
   empty_or_content_test_mode		{$$ = $4;}
 ;
empty_or_content_test_mode
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_TEST_MODE			{my_printf("</TEST_MODE>\n"); $$ = $3;}
 ;
/************** level (atomic) ***************/
element_level
 : START_LEVEL				{my_printf("<LEVEL");}
   attribute_seq_opt
   empty_or_content_level		{$$ = $4;}
 ;
empty_or_content_level
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_LEVEL				{my_printf("</LEVEL>\n"); $$ = $3;}
 ;
/************** cc_options (atomic) ***************/
element_cc_options
 : START_CC_OPTIONS			{my_printf("<CC_OPTIONS");}
   attribute_seq_opt
   empty_or_content_cc_options		{$$ = $4;}
 ;
empty_or_content_cc_options
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_CC_OPTIONS			{my_printf("</CC_OPTIONS>\n"); $$ = $3;}
 ;
/************** cflags (atomic) ***************/
element_cflags
 : START_CFLAGS				{my_printf("<CFLAGS");}
   attribute_seq_opt
   empty_or_content_cflags		{$$ = $4;}
 ;
empty_or_content_cflags
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_CFLAGS				{my_printf("</CFLAGS>\n"); $$ = $3;}
 ;
/************** makefile (atomic) ***************/
element_makefile
 : START_MAKEFILE			{my_printf("<MAKEFILE");}
   attribute_seq_opt
   empty_or_content_makefile		{$$ = $4;}
 ;
empty_or_content_makefile
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_MAKEFILE			{my_printf("</MAKEFILE>\n"); $$ = $3;}
 ;
/************** make_options (atomic) ***************/
element_make_options
 : START_MAKE_OPTIONS			{my_printf("<MAKE_OPTIONS");}
   attribute_seq_opt
   empty_or_content_make_options	{$$ = $4;}
 ;
empty_or_content_make_options
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_MAKE_OPTIONS			{my_printf("</MAKE_OPTIONS>\n"); $$ = $3;}
 ;
/************** simulator (atomic) ***************/
element_simulator
 : START_SIMULATOR			{my_printf("<SIMULATOR");}
   attribute_seq_opt
   empty_or_content_simulator		{$$ = $4;}
 ;
empty_or_content_simulator
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_SIMULATOR			{my_printf("</SIMULATOR>\n"); $$ = $3;}
 ;
/************** sim_options (atomic) ***************/
element_sim_options
 : START_SIM_OPTIONS			{my_printf("<SIM_OPTIONS");}
   attribute_seq_opt
   empty_or_content_sim_options		{$$ = $4;}
 ;
empty_or_content_sim_options
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_SIM_OPTIONS			{my_printf("</SIM_OPTIONS>\n"); $$ = $3;}
 ;
/************** target (atomic) ***************/
element_target
 : START_TARGET				{my_printf("<TARGET");}
   attribute_seq_opt
   empty_or_content_target		{$$ = $4;}
 ;
empty_or_content_target
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_TARGET				{my_printf("</TARGET>\n"); $$ = $3;}
 ;
/************** make_argv (atomic) ***************/
element_make_argv
 : START_MAKE_ARGV				{my_printf("<MAKE_ARGV");}
   attribute_seq_opt
   empty_or_content_make_argv		{$$ = $4;}
 ;
empty_or_content_make_argv
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_MAKE_ARGV				{my_printf("</MAKE_ARGV>\n"); $$ = $3;}
 ;
/************** description (atomic) ***************/
element_description
 : START_DESCRIPTION			{my_printf("<DESCRIPTION");}
   attribute_seq_opt
   empty_or_content_description		{$$ = $4;}
 ;
empty_or_content_description
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_DESCRIPTION			{my_printf("</DESCRIPTION>\n"); $$ = $3;}
 ;
/************** status (atomic) ***************/
element_status
 : START_STATUS				{my_printf("<STATUS");}
   attribute_seq_opt
   empty_or_content_status		{$$ = $4;}
 ;
empty_or_content_status
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_STATUS				{my_printf("</STATUS>\n"); $$ = $3;}
 ;
/************** size (atomic) ***************/
element_size
 : START_SIZE				{my_printf("<SIZE");}
   attribute_seq_opt
   empty_or_content_size		{$$ = $4;}
 ;
empty_or_content_size
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_SIZE				{my_printf("</SIZE>\n"); $$ = $3;}
 ;
/************** input (atomic) ***************/
element_input
 : START_INPUT				{my_printf("<INPUT");}
   attribute_seq_opt
   empty_or_content_input		{$$ = $4;}
 ;
empty_or_content_input
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_INPUT				{my_printf("</INPUT>\n"); $$ = $3;}
 ;
/************** n_frames (atomic) ***************/
element_n_frames
 : START_N_FRAMES			{my_printf("<N_FRAMES");}
   attribute_seq_opt
   empty_or_content_n_frames		{$$ = $4;}
 ;
empty_or_content_n_frames
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_N_FRAMES			{my_printf("</N_FRAMES>\n"); $$ = $3;}
 ;
/************** sample_p_frame (atomic) ***************/
element_sample_p_frame
 : START_SAMPLE_P_FRAME			{my_printf("<SAMPLE_P_FRAME");}
   attribute_seq_opt
   empty_or_content_sample_p_frame	{$$ = $4;}
 ;
empty_or_content_sample_p_frame
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_SAMPLE_P_FRAME			{my_printf("</SAMPLE_P_FRAME>\n"); $$ = $3;}
 ;
/************** e_freq (atomic) ***************/
element_e_freq
 : START_E_FREQ				{my_printf("<E_FREQ");}
   attribute_seq_opt
   empty_or_content_e_freq		{$$ = $4;}
 ;
empty_or_content_e_freq
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_E_FREQ				{my_printf("</E_FREQ>\n"); $$ = $3;}
 ;
/************** argv (atomic) ***************/
element_argv
 : START_ARGV				{my_printf("<ARGV");}
   attribute_seq_opt
   empty_or_content_argv		{$$ = $4;}
 ;
empty_or_content_argv
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_ARGV				{my_printf("</ARGV>\n"); $$ = $3;}
 ;
/************** cycles (atomic) ***************/
element_cycles
 : START_CYCLES				{my_printf("<CYCLES");}
   attribute_seq_opt
   empty_or_content_cycles		{$$ = $4;}
 ;
empty_or_content_cycles
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_CYCLES				{my_printf("</CYCLES>\n"); $$ = $3;}
 ;
/************** cycles_p_frame (atomic) ***************/
element_cycles_p_frame
 : START_CYCLES_P_FRAME			{my_printf("<CYCLES_P_FRAME");}
   attribute_seq_opt
   empty_or_content_cycles_p_frame	{$$ = $4;}
 ;
empty_or_content_cycles_p_frame
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				{my_printf(">");}
   content_string
   CLOSE_CYCLES_P_FRAME			{my_printf("</CYCLES_P_FRAME>\n"); $$ = $3;}
 ;
/************** mips (atomic) ***************/
element_mips
 : START_MIPS				{my_printf("<MIPS");}
   attribute_seq_opt
   empty_or_content_mips		{$$ = $4;}
 ;
empty_or_content_mips
 : SLASH CLOSE				{$$ = NULL;}
 | CLOSE				    {my_printf(">");}
   content_string
   CLOSE_MIPS				{my_printf("</MIPS>\n"); $$ = $3;}
 ;
/************** string content of atomic elements ***************/
content_string
 : content_string DATA			{my_printf("DATA(%s)",$2); $$ = $2;}
 | content_string misc			{$$ = $1;}
 | error 				        {yyclearin; yyerrok;}
 | /*empty*/			    	{$$ = strdup("");}
 ;
/************** END OF GENERAL PARSER **************/

