/************************************************************************
FREESCALE - METROWERKS
READER FOR XML REPORTS HISTORY
FILE : xml_hist.lex
DATE OF LAST CHANGE :
VERSION :
AUTHOR : GUERTE YVES
CONTENT :
*************************************************************************/
%option 8bit nodefault yylineno

/**************
include section
**************/
%{
#include "common_yacc_lex.h"
/* The yacc generated file */
#include "xml_hist-yacc.h"

static int keep;                        /* To store start condition */

static char* word(char *s)
{
  char *buf;
  int i, k;
  for (k = 0; isspace(s[k]) || s[k] == '<'; k++) ;
  for (i = k; s[i] && ! isspace(s[i]); i++) ;
  buf = malloc((i - k + 1) * sizeof(char));
  strncpy(buf, &s[k], i - k);
  buf[i - k] = '\0';
  return buf;
}
%}


nl              (\r\n|\r|\n)
ws              [ \t]+
open            "<"
close           ">"
namestart       [A-Za-z\200-\377_]
namechar        [A-Za-z\200-\377_0-9.-]
esc             "&#"[0-9]+";"|"&#x"[0-9a-fA-F]+";"
name            {namestart}{namechar}*
data            ([^<\n\r&]|{esc})+
/*
begin_comment   {open}"!--"
end_comment     "--"{close}
*/
comment         {open}"!--"([^-]|"-"[^-])*"--"{close}
string          \"([^"&]|{esc})*\"|\'([^'&]|{esc})*\'
version         {open}"?XML VERSION=\"1.0\" ?"{close}
encoding        {open}"?XML-ENCODING"{ws}{name}{ws}?"?"{close}
attdef          {open}"?XML-ATT"
openraw         {open}"!\[CDATA["
closeraw        "\]\]"{close}

start_history           {open}{ws}?"history"{ws}?
start_report            {open}{ws}?"report"{ws}?
start_run_id            {open}{ws}?"run_id"{ws}?
start_scenario_file     {open}{ws}?"scenario_file"{ws}?
start_start_date        {open}{ws}?"start_date"{ws}?
start_end_date          {open}{ws}?"end_date"{ws}?
start_compiler_version  {open}{ws}?"compiler_version"{ws}?
start_tool              {open}{ws}?"tool"{ws}?
start_tool_name         {open}{ws}?"tool_name"{ws}?
start_tool_version      {open}{ws}?"tool_version"{ws}?
start_scenario          {open}{ws}?"scenario"{ws}?
start_param_files       {open}{ws}?"param_files"{ws}?
start_param_file       	{open}{ws}?"param_file"{ws}?
start_filename          {open}{ws}?"filename"{ws}?
start_test_def          {open}{ws}?"test_def"{ws}?
start_test_path         {open}{ws}?"test_path"{ws}?
start_options_set       {open}{ws}?"options_set"{ws}?
start_test              {open}{ws}?"test"{ws}?
start_test_name         {open}{ws}?"test_name"{ws}?
start_host_type         {open}{ws}?"host_type"{ws}?
start_host_name         {open}{ws}?"host_name"{ws}?
start_test_mode         {open}{ws}?"test_mode"{ws}?
start_level             {open}{ws}?"level"{ws}?
start_cc_options        {open}{ws}?"cc_options"{ws}?
start_cflags            {open}{ws}?"cflags"{ws}?
start_makefile          {open}{ws}?"makefile"{ws}?
start_make_options      {open}{ws}?"make_options"{ws}?
start_simulator         {open}{ws}?"simulator"{ws}?
start_sim_options       {open}{ws}?"sim_options"{ws}?
start_targets           {open}{ws}?"targets"{ws}?
start_target            {open}{ws}?"target"{ws}?
start_compilation       {open}{ws}?"compilation"{ws}?
start_make_argv         {open}{ws}?"make_argv"{ws}?
start_exec              {open}{ws}?"exec"{ws}?
start_description       {open}{ws}?"description"{ws}?
start_status            {open}{ws}?"status"{ws}?
start_size              {open}{ws}?"size"{ws}?
start_input             {open}{ws}?"input"{ws}?
start_n_frames          {open}{ws}?"n_frames"{ws}?
start_sample_p_frame    {open}{ws}?"sample_p_frame"{ws}?
start_e_freq            {open}{ws}?"e_freq"{ws}?
start_argv              {open}{ws}?"argv"{ws}?
start_cycles            {open}{ws}?"cycles"{ws}?
start_cycles_p_frame    {open}{ws}?"cycles_p_frame"{ws}?
start_mips              {open}{ws}?"mips"{ws}?
start_opt_report_error  {open}{ws}?"error"{ws}?

close_history           {open}{ws}?"/history"{ws}?{close}
close_report            {open}{ws}?"/report"{ws}?{close}
close_run_id            {open}{ws}?"/run_id"{ws}?{close}
close_scenario_file     {open}{ws}?"/scenario_file"{ws}?{close}
close_start_date        {open}{ws}?"/start_date"{ws}?{close}
close_end_date          {open}{ws}?"/end_date"{ws}?{close}
close_compiler_version  {open}{ws}?"/compiler_version"{ws}?{close}
close_tool    		{open}{ws}?"/tool"{ws}?{close}
close_tool_name    	{open}{ws}?"/tool_name"{ws}?{close}
close_tool_version    	{open}{ws}?"/tool_version"{ws}?{close}
close_scenario          {open}{ws}?"/scenario"{ws}?{close}
close_param_files       {open}{ws}?"/param_files"{ws}?{close}
close_param_file       	{open}{ws}?"/param_file"{ws}?{close}
close_filename       	{open}{ws}?"/filename"{ws}?{close}
close_test_def          {open}{ws}?"/test_def"{ws}?{close}
close_test_path         {open}{ws}?"/test_path"{ws}?{close}
close_options_set       {open}{ws}?"/options_set"{ws}?{close}
close_test              {open}{ws}?"/test"{ws}?{close}
close_test_name         {open}{ws}?"/test_name"{ws}?{close}
close_host_type         {open}{ws}?"/host_type"{ws}?{close}
close_host_name         {open}{ws}?"/host_name"{ws}?{close}
close_test_mode         {open}{ws}?"/test_mode"{ws}?{close}
close_level             {open}{ws}?"/level"{ws}?{close}
close_cc_options        {open}{ws}?"/cc_options"{ws}?{close}
close_cflags            {open}{ws}?"/cflags"{ws}?{close}
close_makefile          {open}{ws}?"/makefile"{ws}?{close}
close_make_options      {open}{ws}?"/make_options"{ws}?{close}
close_simulator         {open}{ws}?"/simulator"{ws}?{close}
close_sim_options       {open}{ws}?"/sim_options"{ws}?{close}
close_targets           {open}{ws}?"/targets"{ws}?{close}
close_target            {open}{ws}?"/target"{ws}?{close}
close_compilation       {open}{ws}?"/compilation"{ws}?{close}
close_make_argv         {open}{ws}?"/make_argv"{ws}?{close}
close_exec              {open}{ws}?"/exec"{ws}?{close}
close_description       {open}{ws}?"/description"{ws}?{close}
close_status            {open}{ws}?"/status"{ws}?{close}
close_size              {open}{ws}?"/size"{ws}?{close}
close_input             {open}{ws}?"/input"{ws}?{close}
close_n_frames          {open}{ws}?"/n_frames"{ws}?{close}
close_sample_p_frame    {open}{ws}?"/sample_p_frame"{ws}?{close}
close_e_freq            {open}{ws}?"/e_freq"{ws}?{close}
close_argv              {open}{ws}?"/argv"{ws}?{close}
close_cycles            {open}{ws}?"/cycles"{ws}?{close}
close_cycles_p_frame    {open}{ws}?"/cycles_p_frame"{ws}?{close}
close_mips              {open}{ws}?"/mips"{ws}?{close}
close_opt_report_error	{open}{ws}?"/error"{ws}?{close}

/*
 * The CONTENT mode is used for the content of elements, i.e.,
 * between the ">" and "<" of element tags.
 * The INITIAL mode is used outside the top level element
 * and inside markup.
 */

%x RAW
%s CONTENT
/*
%x STATE_COMMENT
*/
%%

{nl}                            {++line_num;}
{ws}                            {/* skip */}
<INITIAL>{nl}                   {++line_num;}
<INITIAL>{ws}                   {/* skip */}
<INITIAL>{version}              {return VERSION;}
<INITIAL>{encoding}             {yy1lval.s = word(yy1text + 14); return ENCODING;}
<INITIAL>"/"                    {return SLASH;}
<INITIAL>"="                    {return EQ;}
<INITIAL>{close}                {BEGIN(CONTENT); return CLOSE;}
<INITIAL>{name}                 {yy1lval.s = strdup(yy1text); return NAME;}
<INITIAL>{string}               {yy1lval.s = strdup(yy1text); return VALUE;}
<INITIAL>"?"{close}             {BEGIN(keep); return ENDDEF;}

{openraw}                       {BEGIN(RAW);}
<RAW>{nl}                       {++line_num; yymore();}
<RAW>[^\]\r\n]*                 {yymore();}
<RAW>[^\]\r\n]*{nl}             {++line_num; yymore();}
<RAW>"\]"+[^\]>\r\n]*           {yymore();}
<RAW>"\]"+[^\]>\r\n]*{nl}       {++line_num; yymore();}
<RAW>{closeraw}                 {BEGIN(INITIAL); yy1lval.FLXT_rawdata = malloc(yyleng - 2);
						 strncpy(yy1lval.FLXT_rawdata, yy1text, yyleng - 3);
						 yy1lval.FLXT_rawdata[yyleng - 3] = '\0';
						 return RAWDATA;}

{attdef}                        {keep = YY_START; BEGIN(INITIAL); return ATTDEF;}

{start_history}                 {BEGIN(INITIAL); return START_HISTORY;}
{start_report}                  {BEGIN(INITIAL); return START_REPORT;}
{start_run_id}                  {BEGIN(INITIAL); return START_RUN_ID;}
{start_scenario_file}           {BEGIN(INITIAL); return START_SCENARIO_FILE;}
{start_start_date}              {BEGIN(INITIAL); return START_START_DATE;}
{start_end_date}                {BEGIN(INITIAL); return START_END_DATE;}
{start_compiler_version}        {BEGIN(INITIAL); return START_COMPILER_VERSION;}
{start_tool}                    {BEGIN(INITIAL); return START_TOOL;}
{start_tool_name}               {BEGIN(INITIAL); return START_TOOL_NAME;}
{start_tool_version}            {BEGIN(INITIAL); return START_TOOL_VERSION;}
{start_scenario}                {BEGIN(INITIAL); return START_SCENARIO;}
{start_param_files}             {BEGIN(INITIAL); return START_PARAM_FILES;}
{start_param_file}              {BEGIN(INITIAL); return START_PARAM_FILE;}
{start_filename}                {BEGIN(INITIAL); return START_FILENAME;}
{start_test_def}                {BEGIN(INITIAL); return START_TEST_DEF;}
{start_test_path}               {BEGIN(INITIAL); return START_TEST_PATH;}
{start_options_set}             {BEGIN(INITIAL); return START_OPTIONS_SET;}
{start_test}                    {BEGIN(INITIAL); return START_TEST;}
{start_test_name}               {BEGIN(INITIAL); return START_TEST_NAME;}
{start_host_type}               {BEGIN(INITIAL); return START_HOST_TYPE;}
{start_host_name}               {BEGIN(INITIAL); return START_HOST_NAME;}
{start_test_mode}               {BEGIN(INITIAL); return START_TEST_MODE;}
{start_level}                   {BEGIN(INITIAL); return START_LEVEL;}
{start_cc_options}              {BEGIN(INITIAL); return START_CC_OPTIONS;}
{start_cflags}                  {BEGIN(INITIAL); return START_CFLAGS;}
{start_makefile}                {BEGIN(INITIAL); return START_MAKEFILE;}
{start_make_options}            {BEGIN(INITIAL); return START_MAKE_OPTIONS;}
{start_simulator}               {BEGIN(INITIAL); return START_SIMULATOR;}
{start_sim_options}             {BEGIN(INITIAL); return START_SIM_OPTIONS;}
{start_targets}                 {BEGIN(INITIAL); return START_TARGETS;}
{start_target}                  {BEGIN(INITIAL); return START_TARGET;}
{start_compilation}             {BEGIN(INITIAL); return START_COMPILATION;}
{start_make_argv}               {BEGIN(INITIAL); return START_MAKE_ARGV;}
{start_exec}                    {BEGIN(INITIAL); return START_EXEC;}
{start_description}             {BEGIN(INITIAL); return START_DESCRIPTION;}
{start_status}                  {BEGIN(INITIAL); return START_STATUS;}
{start_size}                    {BEGIN(INITIAL); return START_SIZE;}
{start_input}                   {BEGIN(INITIAL); return START_INPUT;}
{start_n_frames}                {BEGIN(INITIAL); return START_N_FRAMES;}
{start_sample_p_frame}          {BEGIN(INITIAL); return START_SAMPLE_P_FRAME;}
{start_e_freq}                  {BEGIN(INITIAL); return START_E_FREQ;}
{start_argv}                    {BEGIN(INITIAL); return START_ARGV;}
{start_cycles}                  {BEGIN(INITIAL); return START_CYCLES;}
{start_cycles_p_frame}          {BEGIN(INITIAL); return START_CYCLES_P_FRAME;}
{start_mips}                    {BEGIN(INITIAL); return START_MIPS;}
{start_opt_report_error}        {BEGIN(INITIAL); return START_OPT_REPORT_ERROR;}

			     
{close_history}                 {BEGIN(INITIAL); return CLOSE_HISTORY;}
{close_report}                  {BEGIN(INITIAL); return CLOSE_REPORT;}
{close_run_id}                  {BEGIN(INITIAL); return CLOSE_RUN_ID;}
{close_scenario_file}           {BEGIN(INITIAL); return CLOSE_SCENARIO_FILE;}
{close_start_date}              {BEGIN(INITIAL); return CLOSE_START_DATE;}
{close_end_date}                {BEGIN(INITIAL); return CLOSE_END_DATE;}
{close_compiler_version}        {BEGIN(INITIAL); return CLOSE_COMPILER_VERSION;}
{close_tool}                    {BEGIN(INITIAL); return CLOSE_TOOL;}
{close_tool_name}               {BEGIN(INITIAL); return CLOSE_TOOL_NAME;}
{close_tool_version}            {BEGIN(INITIAL); return CLOSE_TOOL_VERSION;}
{close_scenario}                {BEGIN(INITIAL); return CLOSE_SCENARIO;}
{close_param_files}             {BEGIN(INITIAL); return CLOSE_PARAM_FILES;}
{close_param_file}              {BEGIN(INITIAL); return CLOSE_PARAM_FILE;}
{close_filename}                {BEGIN(INITIAL); return CLOSE_FILENAME;}
{close_test_def}                {BEGIN(INITIAL); return CLOSE_TEST_DEF;}
{close_test_path}               {BEGIN(INITIAL); return CLOSE_TEST_PATH;}
{close_options_set}             {BEGIN(INITIAL); return CLOSE_OPTIONS_SET;}
{close_test}                    {BEGIN(INITIAL); return CLOSE_TEST;}
{close_test_name}               {BEGIN(INITIAL); return CLOSE_TEST_NAME;}
{close_host_type}               {BEGIN(INITIAL); return CLOSE_HOST_TYPE;}
{close_host_name}               {BEGIN(INITIAL); return CLOSE_HOST_NAME;}
{close_test_mode}               {BEGIN(INITIAL); return CLOSE_TEST_MODE;}
{close_level}                   {BEGIN(INITIAL); return CLOSE_LEVEL;}
{close_cc_options}              {BEGIN(INITIAL); return CLOSE_CC_OPTIONS;}
{close_cflags}                  {BEGIN(INITIAL); return CLOSE_CFLAGS;}
{close_makefile}                {BEGIN(INITIAL); return CLOSE_MAKEFILE;}
{close_make_options}            {BEGIN(INITIAL); return CLOSE_MAKE_OPTIONS;}
{close_simulator}               {BEGIN(INITIAL); return CLOSE_SIMULATOR;}
{close_sim_options}             {BEGIN(INITIAL); return CLOSE_SIM_OPTIONS;}
{close_targets}                 {BEGIN(INITIAL); return CLOSE_TARGETS;}
{close_target}                  {BEGIN(INITIAL); return CLOSE_TARGET;}
{close_compilation}             {BEGIN(INITIAL); return CLOSE_COMPILATION;}
{close_make_argv}               {BEGIN(INITIAL); return CLOSE_MAKE_ARGV;}
{close_exec}                    {BEGIN(INITIAL); return CLOSE_EXEC;}
{close_description}             {BEGIN(INITIAL); return CLOSE_DESCRIPTION;}
{close_status}                  {BEGIN(INITIAL); return CLOSE_STATUS;}
{close_size}                    {BEGIN(INITIAL); return CLOSE_SIZE;}
{close_input}                   {BEGIN(INITIAL); return CLOSE_INPUT;}
{close_n_frames}                {BEGIN(INITIAL); return CLOSE_N_FRAMES;}
{close_sample_p_frame}          {BEGIN(INITIAL); return CLOSE_SAMPLE_P_FRAME;}
{close_e_freq}                  {BEGIN(INITIAL); return CLOSE_E_FREQ;}
{close_argv}                    {BEGIN(INITIAL); return CLOSE_ARGV;}
{close_cycles}                  {BEGIN(INITIAL); return CLOSE_CYCLES;}
{close_cycles_p_frame}          {BEGIN(INITIAL); return CLOSE_CYCLES_P_FRAME;}
{close_mips}                    {BEGIN(INITIAL); return CLOSE_MIPS;}
{close_opt_report_error}        {BEGIN(INITIAL); return CLOSE_OPT_REPORT_ERROR;}

{open}{ws}?{name}               {BEGIN(INITIAL); yy1lval.s= word(yy1text); return START;}
{open}{ws}?"/"                  {BEGIN(INITIAL); return END;}
{comment}                       {yy1lval.s = strdup(yy1text); return COMMENT;}

<CONTENT>{data}                 {yy1lval.s = strdup(yy1text); return DATA;}

.                               {fprintf(stderr, "!ERROR(%c) line %d\n", *yy1text, yy1lineno);}
<<EOF>>                         {yyterminate();}

%%

/************************************************************

Functions body : Only for parsing purpose

	- parse_xml_hist(FILE *) : Call the parser

*************************************************************/

int parse_xml_hist(char *file_name) {
	int status;
	FILE *file;
	current_file_name = malloc(strlen(file_name)+20);
	sprintf(current_file_name,"%s",file_name);
	file=fopen(current_file_name,"r");
	line_num=1;
	yyin = file;
	if (file==NULL)  errlog("unable to process file %s\n",current_file_name);
	fprintf(stderr,"Begin Parsing %s .....\n",current_file_name);
	status=yy1parse();
	fclose(file);
	fprintf(stderr,"Finish Parsing %s ..... %d lines \n",current_file_name,line_num);
	return status;
}

/* in case of mistakes in the parser*/
int yy1error(char *s) {
	errlog("%s reading '%s' in file %s at line %d\n", s,yy1text,current_file_name,line_num);
	return 0;
}

int yy1wrap (){
	return 1;
}
