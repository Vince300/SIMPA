#line 1 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\compiler_support.c"	/* stack depth 0 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\time.h"	/* stack depth 1 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ansi_parms.h"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\msl_c_version.h"	/* stack depth 3 */
#line 11 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ansi_parms.h"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\mslGlobals.h"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\ansi_prefix.Win32.h"	/* stack depth 4 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\os_enum.h"	/* stack depth 5 */
#line 11 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\ansi_prefix.Win32.h"	/* stack depth 4 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\Win32-x86 Support\\Headers\\Prefix Files\\x86_prefix.h"	/* stack depth 5 */
#line 14 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\ansi_prefix.Win32.h"	/* stack depth 4 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\callingconv.win32.h"	/* stack depth 5 */
#line 67 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\ansi_prefix.Win32.h"	/* stack depth 4 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\wchar_t.h"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ansi_parms.h"	/* stack depth 6 */
#line 11 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\wchar_t.h"	/* stack depth 5 */
#line 30
	typedef unsigned short wchar_t;
#line 53
typedef wchar_t wint_t;
typedef wchar_t wctype_t;
typedef int 	mbstate_t;
typedef wchar_t Wint_t;
#line 183 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\ansi_prefix.Win32.h"	/* stack depth 4 */
#line 32 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\mslGlobals.h"	/* stack depth 3 */
#line 13 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ansi_parms.h"	/* stack depth 2 */
#line 11 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\time.h"	/* stack depth 1 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ctime"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\null.h"	/* stack depth 3 */
#line 19 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ctime"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\size_t.h"	/* stack depth 3 */
#line 28
		typedef unsigned int size_t;
#line 20 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ctime"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\time.win32.h"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Common\\Include\\extras_time.h"	/* stack depth 4 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Win32\\Include\\extras_time_win32.h"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\startup.win32.h"	/* stack depth 6 */
#line 14
 extern int  _doserrno;


int	__cdecl __set_errno(unsigned long);




unsigned long __cdecl __dup_core(void *handle, void **dup_handle);



int * __cdecl __get_MSL_init_count(void);
#line 13 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Win32\\Include\\extras_time_win32.h"	/* stack depth 5 */




	char * __cdecl strtime(char *) __attribute__((nothrow)) ;
	char * __cdecl _strtime(char *) __attribute__((nothrow)) ;
	char * __cdecl _strdate(char *str) __attribute__((nothrow)) ;
#line 16 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Common\\Include\\extras_time.h"	/* stack depth 4 */






	char * __cdecl strdate(char *str) __attribute__((nothrow)) ;
#line 12 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\time.win32.h"	/* stack depth 3 */
#line 23
	extern int _daylight;
	extern long _timezone;
	extern char *_tzname[2];

	void __cdecl tzset(void);
#line 27 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ctime"	/* stack depth 2 */
#line 43
#pragma options align=native
#line 58
		typedef long clock_t;




		typedef long time_t;







	struct tm
	{
		int	tm_sec;
		int	tm_min;
		int	tm_hour;
		int	tm_mday;
		int	tm_mon;
		int	tm_year;
		int	tm_wday;
		int	tm_yday;
		int	tm_isdst;
	};


		clock_t __cdecl clock(void) __attribute__((nothrow)) ;
		time_t __cdecl time(time_t *) __attribute__((nothrow)) ;
		struct tm * __cdecl gmtime(const time_t *) __attribute__((nothrow)) ;



		double	__cdecl difftime(time_t, time_t) __attribute__((nothrow)) ;


	time_t __cdecl mktime(struct tm *) __attribute__((nothrow)) ;
	char * __cdecl asctime(const struct tm *) __attribute__((nothrow)) ;
	char * __cdecl ctime(const time_t *) __attribute__((nothrow)) ;
	struct tm * __cdecl localtime(const time_t *) __attribute__((nothrow)) ;
	size_t __cdecl strftime(char * restrict , size_t, const char * restrict , const struct tm * restrict ) __attribute__((nothrow)) ;





#pragma options align=reset
#line 17 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\time.h"	/* stack depth 1 */
#line 11 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\compiler_support.c"	/* stack depth 0 */
#line 1 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\compiler_support.h"	/* stack depth 1 */
#line 1 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\cmp_functions.h"	/* stack depth 2 */
#line 1 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\common_yacc_lex.h"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ctype.h"	/* stack depth 4 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cctype"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\clocale"	/* stack depth 6 */
#line 38
#pragma options align=native
#line 38
	struct lconv
	{
		char * 	decimal_point;
		char * 	thousands_sep;
		char * 	grouping;
		char * 	mon_decimal_point;
		char * 	mon_thousands_sep;
		char * 	mon_grouping;
		char * 	positive_sign;
		char * 	negative_sign;
		char * 	currency_symbol;
		char   	frac_digits;
		char   	p_cs_precedes;
		char   	n_cs_precedes;
		char   	p_sep_by_space;
		char   	n_sep_by_space;
		char   	p_sign_posn;
		char   	n_sign_posn;
		char * 	int_curr_symbol;
		char	int_frac_digits;

		char 	int_p_cs_precedes;
		char 	int_n_cs_precedes;
		char 	int_p_sep_by_space;
		char 	int_n_sep_by_space;
		char 	int_p_sign_posn;
		char 	int_n_sign_posn;

	};

#pragma options align=reset

	char			* __cdecl setlocale(int, const char *) __attribute__((nothrow)) ;
	struct lconv	* __cdecl localeconv(void) __attribute__((nothrow)) ;
#line 17 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cctype"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\eof.h"	/* stack depth 6 */
#line 18 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cctype"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ctype_api.h"	/* stack depth 6 */
#line 23
		extern const unsigned short __msl_ctype_map[256 ];
		extern const unsigned char __lower_map[256 ];
		extern const unsigned char __upper_map[256 ];


	extern const unsigned short __ctype_mapC[256 ];
	extern const unsigned char __lower_mapC[256 ];
	extern const unsigned char __upper_mapC[256 ];
#line 19 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cctype"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\locale_api.h"	/* stack depth 6 */
#line 28
#pragma options align=native


typedef int (* __decode_mbyte) (wchar_t *, const char *,  size_t );
typedef int (* __encode_mbyte) (char *, wchar_t);




struct _loc_mon_cmpt_vals
{
	char * mon_decimal_point;
	char * mon_thousands_sep;
	char * mon_grouping;
	char * positive_sign;
	char * negative_sign;
	char * currency_symbol;
	char   frac_digits;
	char   p_cs_precedes;
	char   n_cs_precedes;
	char   p_sep_by_space;
	char   n_sep_by_space;
	char   p_sign_posn;
	char   n_sign_posn;
	char * int_curr_symbol;
	char   int_frac_digits;
	char   int_p_cs_precedes;
	char   int_n_cs_precedes;
	char   int_p_sep_by_space;
	char   int_n_sep_by_space;
	char   int_p_sign_posn;
	char   int_n_sign_posn;
};

struct _loc_mon_cmpt
{
	char   CmptName[8 ];
	char * mon_decimal_point;
	char * mon_thousands_sep;
	char * mon_grouping;
	char * positive_sign;
	char * negative_sign;
	char * currency_symbol;
	char   frac_digits;
	char   p_cs_precedes;
	char   n_cs_precedes;
	char   p_sep_by_space;
	char   n_sep_by_space;
	char   p_sign_posn;
	char   n_sign_posn;
	char * int_curr_symbol;
	char   int_frac_digits;
	char   int_p_cs_precedes;
	char   int_n_cs_precedes;
	char   int_p_sep_by_space;
	char   int_n_sep_by_space;
	char   int_p_sign_posn;
	char   int_n_sign_posn;
};

struct _loc_coll_cmpt
{
	char   CmptName[8 ];
	int char_start_value;
	int char_coll_tab_size;
	short char_spec_accents;
	unsigned short * char_coll_table_ptr;
	unsigned short * wchar_coll_seq_ptr;
};
#line 110
struct _loc_ctype_cmpt
{


	char   CmptName[8 ];
	const unsigned short * ctype_map_ptr;
	const unsigned char * upper_map_ptr;
	const unsigned char * lower_map_ptr;


	const unsigned short * wctype_map_ptr;
	const wchar_t *       wupper_map_ptr;
	const wchar_t *       wlower_map_ptr;

	__decode_mbyte  decode_mb;
	__encode_mbyte  encode_wc;


	};
#line 143
struct _loc_num_cmpt_vals
{
	char * decimal_point;
	char * thousands_sep;
	char * grouping;
};

struct _loc_num_cmpt
{
	char   CmptName[8 ];
	char * decimal_point;
	char * thousands_sep;
	char * grouping;
};



struct _loc_time_cmpt
{

	char   CmptName[8 ];

	char * am_pm;
	char * DateTime_Format;
	char * Twelve_hr_format;
	char * Date_Format;
	char * Time_Format;
	char * Day_Names;

    char * MonthNames;
    char * TimeZone;
};
#line 187
struct __locale
{
	struct __locale *   		next_locale;
	char               			locale_name[48 ];
	struct _loc_coll_cmpt * 	coll_cmpt_ptr;
	struct _loc_ctype_cmpt *	ctype_cmpt_ptr;
	struct _loc_mon_cmpt *  	mon_cmpt_ptr;
	struct _loc_num_cmpt *  	num_cmpt_ptr;
	struct _loc_time_cmpt * 	time_cmpt_ptr;
};




 extern struct __locale _current_locale;






#pragma options align=reset
#line 20 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cctype"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\msl_thread_local_data.h"	/* stack depth 6 */
#line 21 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cctype"	/* stack depth 5 */







 int __cdecl isalnum(int) __attribute__((nothrow)) ;
 int __cdecl isalpha(int) __attribute__((nothrow)) ;

 int __cdecl isblank(int) __attribute__((nothrow)) ;

 int __cdecl iscntrl(int) __attribute__((nothrow)) ;
 int __cdecl isdigit(int) __attribute__((nothrow)) ;
 int __cdecl isgraph(int) __attribute__((nothrow)) ;
 int __cdecl islower(int) __attribute__((nothrow)) ;
 int __cdecl isprint(int) __attribute__((nothrow)) ;
 int __cdecl ispunct(int) __attribute__((nothrow)) ;
 int __cdecl isspace(int) __attribute__((nothrow)) ;
 int __cdecl isupper(int) __attribute__((nothrow)) ;
 int __cdecl isxdigit(int) __attribute__((nothrow)) ;
 int __cdecl tolower(int) __attribute__((nothrow)) ;
 int __cdecl toupper(int) __attribute__((nothrow)) ;
#line 17 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ctype.h"	/* stack depth 4 */
#line 4 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\common_yacc_lex.h"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdio.h"	/* stack depth 4 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\va_list.h"	/* stack depth 6 */
#line 20
	typedef char * va_list;
#line 24 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\file_struc.h"	/* stack depth 6 */
#line 24
#pragma options align=native



enum __file_kinds
{
	__closed_file,
	__disk_file,
	__console_file,
	__unavailable_file
};

enum __open_modes
{
	__must_exist,
	__create_if_necessary,
	__create_or_truncate
};


	enum __file_orientation
	{
		__unoriented,
		__char_oriented,
		__wide_oriented
	};


enum __io_modes
{
	__read				= 1,
	__write				= 2,
	__read_write		= 3,
	__append			= 4
};

typedef struct
{
	unsigned int	open_mode		: 2;
	unsigned int	io_mode			: 3;
	unsigned int	buffer_mode		: 2;
	unsigned int	file_kind		: 3;


		unsigned int	file_orientation: 2;


	unsigned int	binary_io		: 1;
} __file_modes;

enum __io_states
{
	__neutral,
	__writing,
	__reading,
	__rereading
};

typedef struct
{
	unsigned int	io_state	: 3;
	unsigned int	free_buffer	: 1;
	unsigned char	eof;
	unsigned char	error;
} __file_state;

typedef unsigned long	__file_handle;

typedef unsigned long	fpos_t;

typedef struct _FILE FILE;

enum __io_results
{
     __no_io_error,
     __io_error,
     __io_EOF
};

typedef void * __ref_con;
typedef void (* __idle_proc)  (void);
typedef int  (* __pos_proc)   (__file_handle file, fpos_t * position, int mode, __ref_con ref_con);
typedef int  (* __io_proc)    (__file_handle file, unsigned char * buff, size_t * count, __ref_con ref_con);
typedef int	 (* __close_proc) (__file_handle file);



struct _FILE
{
	__file_handle		handle;
	__file_modes		mode;
	__file_state		state;


		unsigned char       is_dynamically_allocated;


	unsigned char		char_buffer;
	unsigned char		char_buffer_overflow;
	unsigned char		ungetc_buffer[2 ];


		wchar_t				ungetwc_buffer[2 ];


	unsigned long		position;
	unsigned char *		buffer;
	unsigned long		buffer_size;
	unsigned char *		buffer_ptr;
	unsigned long		buffer_len;
	unsigned long		buffer_alignment;
	unsigned long		saved_buffer_len;
	unsigned long		buffer_pos;
	__pos_proc			position_proc;
	__io_proc			read_proc;
	__io_proc			write_proc;
	__close_proc		close_proc;
	__ref_con			ref_con;


		struct _FILE *      next_file_struct;

};
#line 190
extern FILE __files[];





#pragma options align=reset
#line 30 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdio_api.h"	/* stack depth 6 */
#line 25
#pragma options align=native



 size_t __cdecl __fread(void *, size_t, size_t, FILE *) __attribute__((nothrow)) ;
 size_t __cdecl __fwrite(const void *, size_t, size_t, FILE *) __attribute__((nothrow)) ;
 fpos_t __cdecl _ftell(FILE * restrict ) __attribute__((nothrow)) ;
 int __cdecl _fseek(FILE *, fpos_t, int) __attribute__((nothrow)) ;
 int __cdecl __get_char(FILE *  ) __attribute__((nothrow)) ;
 int __cdecl __put_char(int c,FILE *  ) __attribute__((nothrow)) ;

typedef struct
{
	char * CharStr;
	size_t MaxCharCount;
	size_t CharsWritten;
} __OutStrCtrl;

typedef struct
{
	char * NextChar;
	int    NullCharDetected;
} __InStrCtrl;

void * __cdecl __FileWrite(void *, const char *, size_t) __attribute__((nothrow)) ;
void * __cdecl __StringWrite(void *, const char *, size_t) __attribute__((nothrow)) ;
int    __cdecl __FileRead(void *, int, int) __attribute__((nothrow)) ;
int    __cdecl __StringRead(void *, int, int) __attribute__((nothrow)) ;

enum __ReadProcActions
{
	__GetAChar,
	__UngetAChar,
	__TestForError
};



typedef struct
{
	wchar_t * wCharStr;
	size_t MaxCharCount;
	size_t CharsWritten;
} __wOutStrCtrl;

typedef struct
{
	wchar_t * wNextChar;
	int    wNullCharDetected;
} __wInStrCtrl;

void * __cdecl __wFileWrite(void *, const wchar_t *, size_t) __attribute__((nothrow)) ;
void * __cdecl __wStringWrite(void *, const wchar_t *, size_t) __attribute__((nothrow)) ;

wint_t __wFileRead(void *, wint_t, int) __attribute__((nothrow)) ;
wint_t __wStringRead(void *, wint_t, int) __attribute__((nothrow)) ;


enum __WReadProcActions
{
	__GetAwChar,
	__UngetAwChar,
	__TestForwcsError
};


 FILE * __cdecl __handle_open(__file_handle handle, const char * mode) __attribute__((nothrow)) ;

FILE * __cdecl __handle_reopen(__file_handle handle, const char * mode, FILE *) __attribute__((nothrow)) ;
void   __cdecl __set_ref_con(FILE *, __ref_con ref_con) __attribute__((nothrow)) ;
void   __cdecl __set_idle_proc(FILE *, __idle_proc idle_proc) __attribute__((nothrow)) ;


	FILE * __cdecl __whandle_open(__file_handle handle, const wchar_t * mode) __attribute__((nothrow)) ;
	FILE * __cdecl __whandle_reopen(__file_handle handle, const wchar_t * mode, FILE *) __attribute__((nothrow)) ;






#pragma options align=reset
#line 31 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdio.posix.h"	/* stack depth 6 */
#line 23
	int __cdecl fileno(FILE *) __attribute__((nothrow)) ;


		FILE *	__cdecl fdopen(int , const char *) __attribute__((nothrow)) ;



		int __cdecl _fileno(FILE *) __attribute__((nothrow)) ;
		FILE * __cdecl _fdopen(int, const char *) __attribute__((nothrow)) ;
#line 34 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Win32\\Include\\extras_stdio_win32.h"	/* stack depth 6 */
#line 38 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 5 */






#pragma options align=native



 void __cdecl setbuf(FILE * restrict , char * restrict ) __attribute__((nothrow)) ;
 int __cdecl setvbuf(FILE * restrict , char * restrict , int, size_t) __attribute__((nothrow)) ;
 int __cdecl fclose(FILE *) __attribute__((nothrow)) ;
 int __cdecl fflush(FILE *) __attribute__((nothrow)) ;
 int __cdecl fprintf(FILE * restrict , const char * restrict , ...) __attribute__((nothrow)) ;
 int __cdecl fscanf(FILE * restrict , const char * restrict , ...) __attribute__((nothrow)) ;
 int __cdecl scanf(const char * restrict , ...) __attribute__((nothrow)) ;
 int __cdecl sprintf(char * restrict , const char * restrict , ...) __attribute__((nothrow)) ;
 int __cdecl snprintf(char * restrict , size_t, const char * restrict , ...) __attribute__((nothrow)) ;
 int __cdecl sscanf(const char * restrict , const char * restrict , ...) __attribute__((nothrow)) ;
 int __cdecl vfscanf(FILE * restrict , const char * restrict , va_list) __attribute__((nothrow)) ;
 int __cdecl vsscanf(const char * restrict , const char * restrict , va_list) __attribute__((nothrow)) ;
 int __cdecl vscanf(const char * restrict , va_list) __attribute__((nothrow)) ;
 int __cdecl vfprintf(FILE * restrict , const char * restrict , va_list) __attribute__((nothrow)) ;
 int __cdecl vprintf(const char * restrict , va_list) __attribute__((nothrow)) ;
 int __cdecl vsprintf(char * restrict , const char * restrict , va_list) __attribute__((nothrow)) ;
 int __cdecl vsnprintf(char * restrict , size_t, const char * restrict , va_list) __attribute__((nothrow)) ;
 int __cdecl fgetc(FILE *) __attribute__((nothrow)) ;
 char * __cdecl fgets(char * restrict , int, FILE * restrict ) __attribute__((nothrow)) ;
 int __cdecl fputc(int, FILE *) __attribute__((nothrow)) ;
 int __cdecl fputs(const char * restrict , FILE * restrict ) __attribute__((nothrow)) ;
 char * __cdecl gets(char *) __attribute__((nothrow)) ;
 int __cdecl puts(const char *) __attribute__((nothrow)) ;
 int __cdecl ungetc(int, FILE *) __attribute__((nothrow)) ;
 size_t __cdecl fread(void * restrict , size_t, size_t, FILE * restrict ) __attribute__((nothrow)) ;
 size_t __cdecl fwrite(const void * restrict , size_t, size_t, FILE * restrict ) __attribute__((nothrow)) ;
 int __cdecl fgetpos(FILE * restrict , fpos_t * restrict ) __attribute__((nothrow)) ;
 long __cdecl ftell(FILE *) __attribute__((nothrow)) ;
 int __cdecl fsetpos(FILE *, const fpos_t *) __attribute__((nothrow)) ;
 int __cdecl fseek(FILE *, long, int) __attribute__((nothrow)) ;
 void	__cdecl rewind(FILE *) __attribute__((nothrow)) ;
 void	__cdecl clearerr(FILE *) __attribute__((nothrow)) ;
 void	__cdecl perror(const char *) __attribute__((nothrow)) ;


	int __cdecl fwide(FILE *, int) __attribute__((nothrow)) ;



	int __cdecl remove(const char *) __attribute__((nothrow)) ;
	int __cdecl rename(const char *, const char *) __attribute__((nothrow)) ;
	char * __cdecl tmpnam(char *) __attribute__((nothrow)) ;
	FILE * __cdecl tmpfile(void) __attribute__((nothrow)) ;
	FILE * __cdecl fopen(const char * restrict , const char * restrict ) __attribute__((nothrow)) ;
	FILE * __cdecl freopen(const char * restrict , const char * restrict , FILE * restrict ) __attribute__((nothrow)) ;

	int __cdecl _wremove(const wchar_t *) __attribute__((nothrow)) ;
	int __cdecl _wrename(const wchar_t *, const wchar_t *) __attribute__((nothrow)) ;
	wchar_t * __cdecl _wtmpnam(wchar_t *) __attribute__((nothrow)) ;
	FILE * __cdecl _wfopen(const wchar_t * restrict , const wchar_t * restrict ) __attribute__((nothrow)) ;
	FILE * __cdecl _wfreopen(const wchar_t * restrict , const wchar_t * restrict , FILE * restrict ) __attribute__((nothrow)) ;






	int __cdecl printf(const char * restrict , ...) __attribute__((nothrow)) ;
#line 151
	int __cdecl getc(FILE *  );
	int __cdecl putc(int c, FILE *  );
#line 169
	int __cdecl getchar(void);
	int __cdecl putchar(int c);




	int __cdecl feof  (FILE *  );
	int __cdecl ferror(FILE *  );
#line 186
#pragma options align=reset
#line 17 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdio.h"	/* stack depth 4 */
#line 5 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\common_yacc_lex.h"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\string.h"	/* stack depth 4 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstring"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Common\\Include\\extras_string.h"	/* stack depth 6 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Win32\\Include\\extras_string_win32.h"	/* stack depth 7 */
#line 16
	int __cdecl _stricmp(const char *, const char *) __attribute__((nothrow)) ;
	int __cdecl _strnicmp(const char *, const char *, size_t ) __attribute__((nothrow)) ;
	int __cdecl _strcmpi(const char *, const char *) __attribute__((nothrow)) ;
	int __cdecl _strncmpi(const char *, const char *, size_t ) __attribute__((nothrow)) ;
	int	__cdecl _strcasecmp (const char *, const char *) __attribute__((nothrow)) ;
	int	__cdecl _strncasecmp(const char *, const char *,  size_t ) __attribute__((nothrow)) ;
	char * __cdecl _strrev(char *) __attribute__((nothrow)) ;
	char * __cdecl _strupr(char *) __attribute__((nothrow)) ;
	char * __cdecl _strset(char *, int ) __attribute__((nothrow)) ;
	char * __cdecl _strnset(char *, int , size_t ) __attribute__((nothrow)) ;
	char * __cdecl _strspnp(char *, const char *) __attribute__((nothrow)) ;
	char * __cdecl _strdup(const char *str) __attribute__((nothrow)) ;
	char * __cdecl _strlwr (char *) __attribute__((nothrow)) ;
	int __cdecl _stricoll(const char *, const char *) __attribute__((nothrow)) ;
	int __cdecl _strncoll(const char *, const char *, size_t ) __attribute__((nothrow)) ;
	int __cdecl _strnicoll(const char *, const char *, size_t ) __attribute__((nothrow)) ;
#line 15 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Common\\Include\\extras_string.h"	/* stack depth 6 */






	int __cdecl stricmp(const char *, const char *) __attribute__((nothrow)) ;
	int __cdecl strnicmp(const char *, const char *, size_t ) __attribute__((nothrow)) ;
	int __cdecl strcmpi(const char *, const char *) __attribute__((nothrow)) ;
	int __cdecl strncmpi(const char *, const char *, size_t ) __attribute__((nothrow)) ;
	int	__cdecl strcasecmp (const char *, const char *) __attribute__((nothrow)) ;
	int	__cdecl strncasecmp(const char *, const char *, size_t ) __attribute__((nothrow)) ;
	char * __cdecl strset(char *, int ) __attribute__((nothrow)) ;
	char * __cdecl strnset(char *, int , size_t ) __attribute__((nothrow)) ;
	char * __cdecl strrev(char *) __attribute__((nothrow)) ;
	char * __cdecl strupr(char *) __attribute__((nothrow)) ;
	char * __cdecl strspnp(char *, const char *) __attribute__((nothrow)) ;
	char * __cdecl strlwr (char *) __attribute__((nothrow)) ;
	char * __cdecl strdup(const char *str) __attribute__((nothrow)) ;
	int __cdecl stricoll(const char *, const char *) __attribute__((nothrow)) ;
	int __cdecl strncoll(const char *, const char *, size_t ) __attribute__((nothrow)) ;
	int __cdecl strnicoll(const char *, const char *, size_t ) __attribute__((nothrow)) ;
#line 27 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstring"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\string_api.h"	/* stack depth 6 */
#line 20
	char * __cdecl __strerror(int , char *) __attribute__((nothrow)) ;
	void * __cdecl __memrchr(const void *, int, size_t) __attribute__((nothrow)) ;
#line 32 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstring"	/* stack depth 5 */





 void * __cdecl memset(void *, int, size_t) __attribute__((nothrow)) ;
 int	  __cdecl memcmp(const void *, const void *, size_t) __attribute__((nothrow)) ;
 void * __cdecl memcpy(void * restrict , const void * restrict , size_t) __attribute__((nothrow)) ;
 void * __cdecl memmove(void *, const void *, size_t) __attribute__((nothrow)) ;
 size_t __cdecl strlen(const char *) __attribute__((nothrow)) ;
 char * __cdecl strcpy(char * restrict , const char * restrict ) __attribute__((nothrow)) ;
 char * __cdecl strncpy(char * restrict , const char * restrict , size_t) __attribute__((nothrow)) ;
 char * __cdecl strcat(char * restrict , const char * restrict ) __attribute__((nothrow)) ;
 char * __cdecl strncat(char * restrict , const char * restrict , size_t) __attribute__((nothrow)) ;
 int    __cdecl strcmp(const char *, const char *) __attribute__((nothrow)) ;
 int    __cdecl strncmp(const char *, const char *, size_t) __attribute__((nothrow)) ;
 int    __cdecl strcoll(const char *, const char *) __attribute__((nothrow)) ;
 size_t __cdecl strxfrm(char * restrict , const char * restrict , size_t) __attribute__((nothrow)) ;

 void * __cdecl memchr(const void *, int, size_t) __attribute__((nothrow)) ;
 char * __cdecl strchr(const char *, int) __attribute__((nothrow)) ;
 char * __cdecl strpbrk(const char *, const char *) __attribute__((nothrow)) ;
 char * __cdecl strrchr(const char *, int) __attribute__((nothrow)) ;
 char * __cdecl strstr(const char * , const char *) __attribute__((nothrow)) ;







 size_t __cdecl strspn(const char *, const char *) __attribute__((nothrow)) ;
 size_t __cdecl strcspn(const char *, const char *) __attribute__((nothrow)) ;
 char * __cdecl strtok(char * restrict , const char * restrict ) __attribute__((nothrow)) ;
 char * __cdecl strerror(int) __attribute__((nothrow)) ;
#line 17 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\string.h"	/* stack depth 4 */
#line 6 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\common_yacc_lex.h"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdlib.h"	/* stack depth 4 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdlib"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\div_t.h"	/* stack depth 6 */
#line 14
#pragma options align=native



	typedef struct {
		int	quot;
		int	rem;
	} div_t;

	typedef struct {
		long	quot;
		long	rem;
	} ldiv_t;



		typedef struct
		{
			long long	quot;
			long long	rem;
		} lldiv_t;






#pragma options align=reset
#line 23 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdlib"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Common\\Include\\extras_stdlib.h"	/* stack depth 6 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Win32\\Include\\extras_stdlib_win32.h"	/* stack depth 7 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\file_io.h"	/* stack depth 8 */
#line 16
	extern __file_modes __temp_file_mode;

	int  __cdecl __open_file(const char * name, __file_modes mode, __file_handle * handle) __attribute__((nothrow)) ;
	int  __cdecl __open_temp_file(__file_handle * handle) __attribute__((nothrow)) ;

	int  __read_file(__file_handle handle, unsigned char * buffer, size_t * count, __ref_con ref_con) __attribute__((nothrow)) ;
	int  __write_file(__file_handle handle, unsigned char * buffer, size_t * count, __ref_con ref_con) __attribute__((nothrow)) ;
	int  __position_file(__file_handle handle, fpos_t * position, int mode, __ref_con ref_con) __attribute__((nothrow)) ;
	int  __close_file(__file_handle handle) __attribute__((nothrow)) ;

	void __cdecl __temp_file_name(char * name_str, void *) __attribute__((nothrow)) ;
	int  __cdecl __delete_file(const char * name) __attribute__((nothrow)) ;
	int  __cdecl __rename_file(const char * old_name, const char * new_name) __attribute__((nothrow)) ;

	FILE * __cdecl __reopen(FILE * file) __attribute__((nothrow)) ;
	int __cdecl __get_file_modes(const char * mode, __file_modes * modes) __attribute__((nothrow)) ;


	int	 __cdecl __wopen_file(const wchar_t * name, __file_modes mode, __file_handle * handle) __attribute__((nothrow)) ;
	void __cdecl __wtemp_file_name(wchar_t * name_str, void *) __attribute__((nothrow)) ;
	int	 __cdecl __wdelete_file(const wchar_t * name) __attribute__((nothrow)) ;
	int	 __cdecl __wrename_file(const wchar_t * old_name, const wchar_t * new_name) __attribute__((nothrow)) ;
	int __cdecl __wget_file_modes (const wchar_t * mode, __file_modes * modes) __attribute__((nothrow)) ;


	char * __cdecl __msl_itoa(int, char *, int) __attribute__((nothrow)) ;
	char * __cdecl __msl_strrev(char *) __attribute__((nothrow)) ;
	int    __cdecl __msl_strnicmp(const char *, const char *, int ) __attribute__((nothrow)) ;
	char * __cdecl __msl_getcwd(char *, int) __attribute__((nothrow)) ;
	char * __cdecl __msl_strdup(const char *) __attribute__((nothrow)) ;
#line 13 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Win32\\Include\\extras_stdlib_win32.h"	/* stack depth 7 */
#line 24
 	void __cdecl makepath(char*, const char*, const char*, const char*, const char *) __attribute__((nothrow)) ;
	void __cdecl splitpath (const char *, char *, char *, char *, char *) __attribute__((nothrow)) ;
	int  __cdecl putenv(const char *) __attribute__((nothrow)) ;

	void   __cdecl _makepath(char*, const char*, const char*, const char*, const char *) __attribute__((nothrow)) ;
	void   __cdecl _splitpath (const char *, char *, char *, char *, char *) __attribute__((nothrow)) ;
	int    __cdecl _putenv(const char *) __attribute__((nothrow)) ;
	char * __cdecl _fullpath(char *, const char *, size_t ) __attribute__((nothrow)) ;
	void   __cdecl _searchenv(const char *, const char *, char*) __attribute__((nothrow)) ;
	char * __cdecl _itoa(int, char *, int) __attribute__((nothrow)) ;
	char * __cdecl _ultoa(unsigned long, char *, int) __attribute__((nothrow)) ;
	char *  __cdecl _gcvt(double, int, char *) __attribute__((nothrow)) ;

	__inline char* __cdecl _ltoa(int x, char *y, int z) __attribute__((nothrow)) { return (_itoa(x, y, z)); }
#line 16 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Common\\Include\\extras_stdlib.h"	/* stack depth 6 */





	char * __cdecl itoa(int, char *, int) __attribute__((nothrow)) ;
	char * __cdecl ultoa(unsigned long, char *, int) __attribute__((nothrow)) ;

	__inline char* __cdecl ltoa(int x, char *y, int z) __attribute__((nothrow)) { return (itoa(x, y, z)); }


		char * __cdecl gcvt(double, int, char *) __attribute__((nothrow)) ;
#line 32 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdlib"	/* stack depth 5 */
#line 53
	double __cdecl atof(const char *) __attribute__((nothrow)) ;
	double __cdecl strtod (const char * restrict , char ** restrict ) __attribute__((nothrow)) ;

	long double __cdecl strtold(const char * restrict , char ** restrict ) __attribute__((nothrow)) ;
	float __cdecl strtof(const char * restrict , char ** restrict ) __attribute__((nothrow)) ;



 int __cdecl atoi(const char *) __attribute__((nothrow)) ;
 long	__cdecl atol(const char *) __attribute__((nothrow)) ;



 long	long __cdecl atoll(const char *) __attribute__((nothrow)) ;



 long	__cdecl strtol(const char * restrict , char ** restrict , int) __attribute__((nothrow)) ;
 unsigned long __cdecl strtoul(const char * restrict , char ** restrict , int) __attribute__((nothrow)) ;



	long long __cdecl strtoll(const char * restrict , char ** restrict , int) __attribute__((nothrow)) ;
	unsigned long long __cdecl strtoull(const char * restrict , char ** restrict , int) __attribute__((nothrow)) ;



 int    __cdecl rand (void) __attribute__((nothrow)) ;
 void	  __cdecl srand(unsigned int) __attribute__((nothrow)) ;
 void * __cdecl calloc(size_t , size_t) __attribute__((nothrow)) ;
 void	  __cdecl free(void *) __attribute__((nothrow)) ;
 void * __cdecl malloc(size_t) __attribute__((nothrow)) ;
 void * __cdecl realloc(void *, size_t) __attribute__((nothrow)) ;
 size_t __cdecl __msize(void *) __attribute__((nothrow)) ;
#line 106
 size_t __cdecl __allocate_size (void*) __attribute__((nothrow)) ;
 void* __cdecl __allocate (size_t, size_t*) __attribute__((nothrow)) ;
 int __cdecl __allocate_resize (void*, size_t, size_t*) __attribute__((nothrow)) ;
 int __cdecl __allocate_expand (void*, size_t, size_t, size_t*) __attribute__((nothrow)) ;
#line 129
	void __cdecl abort(void) __attribute__((nothrow)) ;
	int __cdecl atexit(void (__cdecl *func)(void)) __attribute__((nothrow)) ;
	void __cdecl exit(int);

	void __cdecl _Exit(int) __attribute__((nothrow)) ;
#line 144
 char * __cdecl getenv(const char *) __attribute__((nothrow)) ;
 int __cdecl system(const char *) __attribute__((nothrow)) ;

typedef  int 	(*_compare_function)(const void*, const void*);

 void* __cdecl bsearch(const void*, const void*, size_t, size_t, _compare_function);

 void __cdecl qsort(void*, size_t, size_t, _compare_function);

 int __cdecl abs (int) __attribute__((nothrow)) ;

 long	__cdecl labs(long) __attribute__((nothrow)) ;



	long long __cdecl llabs(long long) __attribute__((nothrow)) ;
#line 174
 div_t __cdecl div (int,int) __attribute__((nothrow)) ;
 ldiv_t __cdecl ldiv(long,long) __attribute__((nothrow)) ;



	lldiv_t __cdecl lldiv(long long,long long) __attribute__((nothrow)) ;
#line 205
 int __cdecl mblen(const char *, size_t) __attribute__((nothrow)) ;


	int __cdecl mbtowc(wchar_t * restrict , const char * restrict , size_t) __attribute__((nothrow)) ;
	int __cdecl wctomb(char *, wchar_t) __attribute__((nothrow)) ;
	size_t __cdecl mbstowcs(wchar_t * restrict , const char * restrict , size_t) __attribute__((nothrow)) ;
	size_t __cdecl wcstombs(char * restrict , const wchar_t * restrict , size_t) __attribute__((nothrow)) ;
#line 17 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdlib.h"	/* stack depth 4 */
#line 7 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\common_yacc_lex.h"	/* stack depth 3 */







int yy1lex();
int yy1wrap();
int yy1error(char *s);
int yy1parse();



int parse_xml_hist(char *file_name);



extern FILE *log_file;
void errlog(char *s1, ...);
extern char *current_file_name;
extern int line_num;
extern int Always_Exit;







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


typedef char *t_opt_report_error;




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



typedef struct s_opt_report_errors {
	t_opt_report_error		opt_report_error;
	struct s_opt_report_errors 	*next;
} s_opt_report_errors, *t_opt_report_errors;
t_opt_report_errors empty_opt_report_errors();
void free_opt_report_errors(t_opt_report_errors e);
void dump_opt_report_errors(t_opt_report_errors e);



typedef struct s_tool {
	t_tool_name				tool_name;
	t_tool_version				tool_version;
} s_tool, *t_tool;
t_tool empty_tool();
void free_tool(t_tool t);
void dump_tool(t_tool t);
t_tool add_tool_name_to_tool(const t_tool_name n, t_tool t);
t_tool add_tool_version_to_tool(const t_tool_version v, t_tool t);


typedef struct s_tools {
	t_tool				tool;
	struct s_tools 		*next;
} s_tools, *t_tools;
t_tools empty_tools();
void free_tools(t_tools t);
void dump_tools(t_tools t);
t_tools add_tool_to_tools(const t_tool tg,                  t_tools t);


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


typedef struct s_compiler_versions {
	t_compiler_version		compiler_version;
	struct s_compiler_versions	*next;
} s_compiler_versions, *t_compiler_versions;
void free_compiler_versions(t_compiler_versions vs);
void dump_compiler_versions(t_compiler_versions vs);





typedef struct s_test_def {
	t_test_path			test_path;
	t_options_set			options_set;
} s_test_def, *t_test_def;
t_test_def empty_test_def();
void free_test_def(t_test_def t);
void dump_test_def(t_test_def t);
t_test_def add_test_path_to_test_def(const t_test_path tp, t_test_def t);
t_test_def add_options_set_to_test_def(const t_options_set os, t_test_def t);


typedef struct s_scenario {
	t_host_name			host_name;
	t_test_def			test_def;
} s_scenario, *t_scenario;
t_scenario empty_scenario();
void free_scenario(t_scenario s);
void dump_scenario(t_scenario s);
t_scenario add_host_name_to_scenario(const t_host_name h, t_scenario s);
t_scenario add_test_def_to_scenario(const t_test_def t, t_scenario s);




typedef struct s_param_file {
	t_filename			filename;
	t_rawdata			rawdata;
} s_param_file, *t_param_file;
t_param_file empty_param_file();
void free_param_file(t_param_file p);
void dump_param_file(t_param_file p);
t_param_file add_filename_to_param_file(const t_filename f, t_param_file p);
t_param_file add_rawdata_to_param_file(const t_rawdata r, t_param_file p);


typedef struct s_param_files_seq {
	t_param_file			param_file;
	struct s_param_files_seq	*next;
} s_param_files_seq, *t_param_files_seq;
t_param_files_seq empty_param_files_seq();
void free_param_files_seq(t_param_files_seq p);
void dump_param_files_seq(t_param_files_seq p);


typedef struct s_param_files {
	t_host_name			host_name;
	t_param_files_seq		param_files_seq;
} s_param_files, *t_param_files;
t_param_files empty_param_files();
void free_param_files(t_param_files p);
void dump_param_files(t_param_files p);
t_param_files add_host_name_to_param_files(const t_host_name h, t_param_files ps);
t_param_files add_param_file_to_param_files(const t_param_file p, t_param_files ps);



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



typedef struct s_compilations {
	t_compilation		compilation;
	struct s_compilations	*next;
} s_compilations, *t_compilations;
t_compilations empty_compilations();
void free_compilations(t_compilations c);
void dump_compilations(t_compilations c);
t_compilations add_compilation_to_compilations(const t_compilation c,                  t_compilations cs);



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



typedef struct s_execs {
	t_exec		exec;
	struct s_execs	*next;
} s_execs, *t_execs;
t_execs empty_execs();
void free_execs(t_execs e);
void dump_execs(t_execs e);
t_execs add_exec_to_execs(const t_exec e,                  t_execs es);



typedef struct s_targets {
	t_target		target;
	struct s_targets	*next;
} s_targets, *t_targets;
t_targets empty_targets();
void free_targets(t_targets t);
void dump_targets(t_targets t);
t_targets add_target_to_targets(const t_target tg,                  t_targets t);



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



typedef struct s_tests {
	t_test		test;
	struct s_tests	*next;
} s_tests, *t_tests;
void free_tests(t_tests t);
void dump_tests(t_tests t);



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


typedef struct s_reports {
	t_report		report;
	struct s_reports	*next;
} s_reports, *t_reports;
void free_reports(t_reports r);
void dump_reports(t_reports r);



typedef struct s_history {
	int			nb_reports;
	t_reports		reports;
	t_reports		last_report;
} s_history, *t_history;
void free_history(t_history h);
void dump_history(t_history h);
t_history empty_history();
t_history add_report_to_history(const t_report r, t_history h) ;







int strcmpiu(char *i, char *u);


int strcmpil(char *i, char *u);


extern t_history result_history;

extern int		 nb_execs;
#line 14 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\cmp_functions.h"	/* stack depth 2 */
#line 1 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\util.h"	/* stack depth 3 */
#line 39
int strp_cmp(const void *s1, const void *s2);
#line 15 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\cmp_functions.h"	/* stack depth 2 */
#line 45
void split_cc_opt(const char * cc_opt, char *cc_options_tab[50 ], int *p_nb_cc_options);
#line 69
t_cc_options norm_cc_opt(t_cc_options cc_opt) ;
#line 117
typedef struct s_cmp_fields {
	t_host_type		host_type;
	t_test_name		test_name;
	t_cc_options		cc_options;
	t_target		target;
	t_argv			argv;
} s_cmp_fields, *t_cmp_fields;

typedef struct s_exec_dataref {
	t_report		report;
	t_test			test;
	t_exec			exec;
	struct s_exec_dataref	*next;
} s_exec_dataref, *t_exec_dataref;

typedef t_run_id	*t_all_run_ids;



extern t_all_run_ids	all_run_ids;
extern int				nb_run_ids;

typedef struct s_info_exec {
	t_cmp_fields		cmp_fields;
	t_exec_dataref		exec_dataref;
	t_all_run_ids		all_run_ids;
	int					nb_run_ids;
} s_info_exec, *t_info_exec;

typedef s_info_exec *t_comparison_data;



extern t_comparison_data comparison_data;
extern int		  nb_comparison_data;


void common_tests(t_history h);
#line 178
t_host_type search_host_type(const t_compiler_versions vs, const t_host_name h);
#line 203
char * access_crit(const t_cmp_fields cmp_fields, const int i_field);
#line 14 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\compiler_support.h"	/* stack depth 1 */




typedef enum t_e_compiler {e_gcc=0, e_scc, e_ppc, e_mwccarm, e_armcc, e_gccarm, e_win32_x86, e_dsp56800e, e_mac_ppc, e_dsp56800} t_compiler;


char * t_compiler_image[];



typedef enum t_e_cmp_purpose {e_size, e_speed, e_cc_speed}
			 t_cmp_purpose;


char * t_cmp_purpose_image[];
#line 39
	char * (*access_fct)(const t_exec_dataref exec_dataref);


	int (*is_for_purpose)(const t_cc_options cc_opt);



void set_access_fct(const t_compiler CC, const t_cmp_purpose cmp_purpose);
#line 12 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\compiler_support.c"	/* stack depth 0 */



char * t_compiler_image[] = {"gcc", "scc", "ppc", "mwccarm", "armcc", "gccarm", "win32_x86", "dsp56800e", "mac_ppc", "dsp56800"};


char * t_cmp_purpose_image[] = {"size", "speed", "cc_speed"};
#line 27
static char *access_size(t_exec_dataref exec_dataref) {
        return exec_dataref->exec->size;
}


static char *access_cycles(t_exec_dataref exec_dataref) {
        return exec_dataref->exec->cycles;
}


static char *access_make_duration(t_exec_dataref exec_dataref) {




        char *r = 0L ;
#line 53
        return r;
}




static int is_for_size_purpose_scc(const t_cc_options cc_opt) {


        int r = 0;

        int i;


        t_cc_options    cc_options_tab[50 ];

        int  nb_cc_options = 0;


        split_cc_opt(cc_opt, cc_options_tab, &nb_cc_options);

        for (i=0; i < nb_cc_options; i++) {
                if (strcmp(cc_options_tab[i], "-Os") == 0) {
                        r = 1;
                }
                free(cc_options_tab[i]);
        }
        return r;
}

static int is_for_speed_purpose_scc(const t_cc_options cc_opt) {
        return !(is_for_size_purpose_scc(cc_opt));
}







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
