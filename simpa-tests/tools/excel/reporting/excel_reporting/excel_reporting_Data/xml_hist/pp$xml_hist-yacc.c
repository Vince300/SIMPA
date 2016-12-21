#line 1 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\xml_hist-yacc.c"	/* stack depth 0 */
#line 11 "src/xml_hist.y"	/* stack depth 0 */
#line 1 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\common_yacc_lex.h"	/* stack depth 1 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ctype.h"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ansi_parms.h"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\msl_c_version.h"	/* stack depth 4 */
#line 11 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ansi_parms.h"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\mslGlobals.h"	/* stack depth 4 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\ansi_prefix.Win32.h"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\os_enum.h"	/* stack depth 6 */
#line 11 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\ansi_prefix.Win32.h"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\Win32-x86 Support\\Headers\\Prefix Files\\x86_prefix.h"	/* stack depth 6 */
#line 14 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\ansi_prefix.Win32.h"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\callingconv.win32.h"	/* stack depth 6 */
#line 67 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\ansi_prefix.Win32.h"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\wchar_t.h"	/* stack depth 6 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ansi_parms.h"	/* stack depth 7 */
#line 11 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\wchar_t.h"	/* stack depth 6 */
#line 30
	typedef unsigned short wchar_t;
#line 53
typedef wchar_t wint_t;
typedef wchar_t wctype_t;
typedef int 	mbstate_t;
typedef wchar_t Wint_t;
#line 183 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\ansi_prefix.Win32.h"	/* stack depth 5 */
#line 32 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\mslGlobals.h"	/* stack depth 4 */
#line 13 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ansi_parms.h"	/* stack depth 3 */
#line 11 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ctype.h"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cctype"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\clocale"	/* stack depth 4 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\null.h"	/* stack depth 5 */
#line 21 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\clocale"	/* stack depth 4 */
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
#line 17 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cctype"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\eof.h"	/* stack depth 4 */
#line 18 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cctype"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ctype_api.h"	/* stack depth 4 */
#line 23
		extern const unsigned short __msl_ctype_map[256 ];
		extern const unsigned char __lower_map[256 ];
		extern const unsigned char __upper_map[256 ];


	extern const unsigned short __ctype_mapC[256 ];
	extern const unsigned char __lower_mapC[256 ];
	extern const unsigned char __upper_mapC[256 ];
#line 19 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cctype"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\locale_api.h"	/* stack depth 4 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\size_t.h"	/* stack depth 5 */
#line 28
		typedef unsigned int size_t;
#line 13 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\locale_api.h"	/* stack depth 4 */
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
#line 20 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cctype"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\msl_thread_local_data.h"	/* stack depth 4 */
#line 21 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cctype"	/* stack depth 3 */







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
#line 17 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\ctype.h"	/* stack depth 2 */
#line 4 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\common_yacc_lex.h"	/* stack depth 1 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdio.h"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\va_list.h"	/* stack depth 4 */
#line 20
	typedef char * va_list;
#line 24 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\file_struc.h"	/* stack depth 4 */
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
#line 30 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdio_api.h"	/* stack depth 4 */
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
#line 31 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdio.posix.h"	/* stack depth 4 */
#line 23
	int __cdecl fileno(FILE *) __attribute__((nothrow)) ;


		FILE *	__cdecl fdopen(int , const char *) __attribute__((nothrow)) ;



		int __cdecl _fileno(FILE *) __attribute__((nothrow)) ;
		FILE * __cdecl _fdopen(int, const char *) __attribute__((nothrow)) ;
#line 34 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Win32\\Include\\extras_stdio_win32.h"	/* stack depth 4 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\startup.win32.h"	/* stack depth 5 */
#line 14
 extern int  _doserrno;


int	__cdecl __set_errno(unsigned long);




unsigned long __cdecl __dup_core(void *handle, void **dup_handle);



int * __cdecl __get_MSL_init_count(void);
#line 12 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Win32\\Include\\extras_stdio_win32.h"	/* stack depth 4 */
#line 38 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 3 */






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
#line 17 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdio.h"	/* stack depth 2 */
#line 5 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\common_yacc_lex.h"	/* stack depth 1 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\string.h"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstring"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Common\\Include\\extras_string.h"	/* stack depth 4 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Win32\\Include\\extras_string_win32.h"	/* stack depth 5 */
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
#line 15 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Common\\Include\\extras_string.h"	/* stack depth 4 */






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
#line 27 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstring"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\string_api.h"	/* stack depth 4 */
#line 20
	char * __cdecl __strerror(int , char *) __attribute__((nothrow)) ;
	void * __cdecl __memrchr(const void *, int, size_t) __attribute__((nothrow)) ;
#line 32 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstring"	/* stack depth 3 */





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
#line 17 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\string.h"	/* stack depth 2 */
#line 6 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\common_yacc_lex.h"	/* stack depth 1 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdlib.h"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdlib"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\div_t.h"	/* stack depth 4 */
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
#line 23 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdlib"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Common\\Include\\extras_stdlib.h"	/* stack depth 4 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Win32\\Include\\extras_stdlib_win32.h"	/* stack depth 5 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\file_io.h"	/* stack depth 6 */
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
#line 13 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Win32\\Include\\extras_stdlib_win32.h"	/* stack depth 5 */
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
#line 16 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Common\\Include\\extras_stdlib.h"	/* stack depth 4 */





	char * __cdecl itoa(int, char *, int) __attribute__((nothrow)) ;
	char * __cdecl ultoa(unsigned long, char *, int) __attribute__((nothrow)) ;

	__inline char* __cdecl ltoa(int x, char *y, int z) __attribute__((nothrow)) { return (itoa(x, y, z)); }


		char * __cdecl gcvt(double, int, char *) __attribute__((nothrow)) ;
#line 32 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdlib"	/* stack depth 3 */
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
#line 17 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdlib.h"	/* stack depth 2 */
#line 7 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\common_yacc_lex.h"	/* stack depth 1 */







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
#line 12 "src/xml_hist.y"	/* stack depth 0 */

extern char yy1text[];
#line 167

typedef union {
char *s;
t_history FLXT_history;
t_report FLXT_report;
t_attribute_seq_opt FLXT_attribute_seq_opt;
t_run_id FLXT_run_id;
t_scenario_file FLXT_scenario_file;
t_date FLXT_start_date;
t_date FLXT_end_date;

t_compiler_version FLXT_compiler_version;
t_host_type FLXT_host_type;
t_host_name FLXT_host_name;
t_tool FLXT_tool;
t_tool_name FLXT_tool_name;
t_tool_version FLXT_tool_version;

t_scenario FLXT_scenario;
t_test_def FLXT_test_def;
t_param_files FLXT_param_files;
t_filename FLXT_filename;
t_rawdata FLXT_rawdata;
t_param_file FLXT_param_file;
t_test FLXT_test;
t_opt_report_error FLXT_opt_report_error;

t_test_path FLXT_test_path;
t_options_set FLXT_options_set;
t_test_name FLXT_test_name;
t_test_mode FLXT_test_mode;
t_level FLXT_level;
t_cc_options FLXT_cc_options;
t_cflags FLXT_cflags;
t_makefile FLXT_makefile;
t_make_options FLXT_make_options;
t_simulator FLXT_simulator;
t_sim_options FLXT_sim_options;
t_targets FLXT_targets;
t_compilation FLXT_compilation;
t_make_argv FLXT_make_argv;
t_exec FLXT_exec;
t_target FLXT_target;

t_description FLXT_description;
t_status FLXT_status;
t_size FLXT_size;
t_input FLXT_input;
t_n_frames FLXT_n_frames;
t_sample_p_frame FLXT_sample_p_frame;
t_e_freq FLXT_e_freq;
t_argv FLXT_argv;
t_cycles FLXT_cycles;
t_cycles_p_frame FLXT_cycles_p_frame;
t_mips FLXT_mips;
t_attribute FLXT_attribute;
} yystype;
#line 241
static const char yytranslate[] =
{
0, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 1, 3, 4, 5,
6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
56, 57, 58, 59, 60, 61, 62, 63, 64, 65,
66, 67, 68, 69, 70, 71, 72, 73, 74, 75,
76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
96, 97, 98, 99, 100, 101, 102, 103, 104, 105,
106, 107, 108
};
#line 561
static const short yyr1[] =
{
0, 110, 109, 111, 112, 112, 113, 113, 114, 114,
115, 115, 117, 116, 119, 118, 120, 121, 120, 122,
122, 122, 122, 124, 123, 125, 126, 125, 127, 127,
127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
129, 128, 130, 131, 130, 132, 132, 132, 132, 132,
134, 133, 135, 136, 135, 137, 137, 137, 137, 137,
139, 138, 140, 141, 140, 142, 142, 142, 142, 142,
142, 142, 142, 142, 142, 142, 142, 142, 142, 142,
142, 142, 142, 142, 142, 144, 143, 145, 146, 145,
147, 147, 147, 147, 149, 148, 150, 151, 150, 152,
152, 152, 152, 152, 152, 152, 152, 154, 153, 155,
156, 155, 157, 157, 157, 157, 157, 157, 157, 157,
157, 157, 157, 157, 157, 157, 157, 157, 157, 159,
158, 160, 161, 160, 162, 162, 162, 162, 162, 162,
164, 163, 165, 166, 165, 167, 167, 167, 167, 167,
169, 168, 170, 171, 170, 172, 172, 172, 172, 172,
174, 173, 175, 176, 175, 177, 177, 177, 177, 177,
178, 178, 179, 179, 181, 180, 182, 183, 182, 185,
184, 186, 187, 186, 189, 188, 190, 191, 190, 193,
192, 194, 195, 194, 197, 196, 198, 199, 198, 201,
200, 202, 203, 202, 205, 204, 206, 207, 206, 209,
208, 210, 211, 210, 213, 212, 214, 215, 214, 217,
216, 218, 219, 218, 221, 220, 222, 223, 222, 225,
224, 226, 227, 226, 229, 228, 230, 231, 230, 233,
232, 234, 235, 234, 237, 236, 238, 239, 238, 241,
240, 242, 243, 242, 245, 244, 246, 247, 246, 249,
248, 250, 251, 250, 253, 252, 254, 255, 254, 257,
256, 258, 259, 258, 261, 260, 262, 263, 262, 265,
264, 266, 267, 266, 269, 268, 270, 271, 270, 273,
272, 274, 275, 274, 277, 276, 278, 279, 278, 281,
280, 282, 283, 282, 285, 284, 286, 287, 286, 289,
288, 290, 291, 290, 293, 292, 294, 295, 294, 297,
296, 298, 299, 298, 301, 300, 302, 303, 302, 305,
304, 306, 307, 306, 309, 308, 310, 311, 310, 313,
312, 314, 315, 314, 316, 316, 316, 316
};


static const short yyr2[] =
{
0, 0, 4, 3, 1, 0, 1, 0, 2, 0,
1, 1, 0, 5, 0, 4, 2, 0, 4, 2,
2, 1, 0, 0, 4, 2, 0, 4, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 1, 0,
0, 4, 2, 0, 4, 2, 2, 2, 1, 0,
0, 4, 2, 0, 4, 2, 2, 2, 1, 0,
0, 4, 2, 0, 4, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 1, 0, 0, 4, 2, 0, 4,
2, 2, 1, 0, 0, 4, 2, 0, 4, 2,
2, 2, 2, 2, 2, 1, 0, 0, 4, 2,
0, 4, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 1, 0, 0,
4, 2, 0, 4, 2, 2, 2, 2, 1, 0,
0, 4, 2, 0, 4, 2, 2, 2, 1, 0,
0, 4, 2, 0, 4, 2, 2, 2, 1, 0,
0, 4, 2, 0, 4, 2, 2, 2, 1, 0,
2, 0, 1, 3, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 0, 4, 2, 0, 4, 0,
4, 2, 0, 4, 2, 2, 1, 0
};




static const short yydefact[] =
{
5, 4, 0, 7, 14, 1, 6, 9, 171, 9,
3, 0, 2, 0, 10, 8, 11, 0, 17, 172,
15, 170, 12, 16, 0, 0, 171, 21, 0, 173,
0, 18, 23, 19, 20, 13, 171, 0, 0, 26,
24, 25, 0, 38, 0, 27, 174, 179, 184, 189,
129, 40, 150, 60, 194, 28, 34, 36, 33, 35,
29, 30, 31, 32, 37, 171, 171, 171, 171, 171,
171, 171, 171, 171, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 177, 175, 0, 182, 180, 0,
187, 185, 0, 192, 190, 0, 132, 130, 0, 43,
41, 0, 153, 151, 0, 63, 61, 0, 197, 195,
176, 0, 181, 0, 186, 0, 191, 0, 131, 0,
42, 0, 152, 0, 62, 0, 196, 0, 346, 0,
0, 0, 0, 138, 0, 48, 0, 158, 0, 83,
0, 0, 178, 344, 345, 183, 188, 193, 133, 140,
199, 204, 134, 137, 135, 136, 44, 50, 45, 47,
46, 154, 160, 155, 157, 156, 224, 64, 234, 239,
244, 249, 254, 259, 264, 269, 274, 85, 94, 107,
65, 79, 80, 81, 67, 68, 82, 70, 66, 69,
71, 72, 73, 74, 75, 76, 77, 78, 198, 171,
171, 171, 171, 171, 171, 171, 171, 171, 171, 171,
171, 171, 171, 171, 171, 171, 171, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 143, 141, 0, 202,
200, 0, 207, 205, 0, 53, 51, 0, 163, 161,
0, 227, 225, 0, 237, 235, 0, 242, 240, 0,
247, 245, 0, 252, 250, 0, 257, 255, 0, 262,
260, 0, 267, 265, 0, 272, 270, 0, 277, 275,
0, 88, 86, 0, 97, 95, 0, 110, 108, 142,
0, 201, 0, 206, 0, 52, 0, 162, 0, 226,
0, 236, 0, 241, 0, 246, 0, 251, 0, 256,
0, 261, 0, 266, 0, 271, 0, 276, 0, 87,
0, 96, 0, 109, 0, 148, 0, 0, 0, 58,
0, 168, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 92, 0, 105, 0, 127, 0, 144,
209, 214, 145, 146, 147, 203, 208, 54, 229, 55,
56, 57, 164, 219, 167, 165, 166, 228, 238, 243,
248, 253, 258, 263, 268, 273, 278, 89, 279, 90,
91, 98, 284, 99, 103, 104, 101, 100, 102, 111,
289, 294, 299, 304, 309, 314, 319, 324, 329, 334,
339, 112, 125, 126, 113, 114, 115, 116, 117, 118,
119, 120, 121, 122, 123, 124, 171, 171, 171, 171,
171, 171, 171, 171, 171, 171, 171, 171, 171, 171,
171, 171, 171, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 212, 210, 0, 217, 215, 0, 232, 230, 0,
222, 220, 0, 282, 280, 0, 287, 285, 0, 292,
290, 0, 297, 295, 0, 302, 300, 0, 307, 305,
0, 312, 310, 0, 317, 315, 0, 322, 320, 0,
327, 325, 0, 332, 330, 0, 337, 335, 0, 342,
340, 211, 0, 216, 0, 231, 0, 221, 0, 281,
0, 286, 0, 291, 0, 296, 0, 301, 0, 306,
0, 311, 0, 316, 0, 321, 0, 326, 0, 331,
0, 336, 0, 341, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 213, 218, 233, 223, 283, 288, 293, 298,
303, 308, 313, 318, 323, 328, 333, 338, 343, 0,
0, 0
};

static const short yydefgoto[] =
{
569, 9, 2, 3, 7, 10, 144, 16, 26, 5,
8, 20, 24, 28, 34, 36, 40, 42, 44, 56,
70, 100, 121, 136, 159, 202, 246, 296, 330, 57,
72, 106, 125, 140, 181, 214, 282, 320, 344, 182,
215, 285, 322, 346, 183, 216, 288, 324, 348, 58,
69, 97, 119, 134, 153, 199, 237, 290, 326, 59,
71, 103, 123, 138, 164, 203, 249, 298, 332, 11,
21, 60, 65, 85, 111, 61, 66, 88, 113, 62,
67, 91, 115, 63, 68, 94, 117, 64, 73, 109,
127, 154, 200, 240, 292, 155, 201, 243, 294, 353,
416, 452, 502, 354, 417, 455, 504, 366, 419, 461,
508, 188, 204, 252, 300, 361, 418, 458, 506, 189,
205, 255, 302, 190, 206, 258, 304, 191, 207, 261,
306, 192, 208, 264, 308, 193, 209, 267, 310, 194,
210, 270, 312, 195, 211, 273, 314, 196, 212, 276,
316, 197, 213, 279, 318, 380, 420, 464, 510, 388,
421, 467, 512, 405, 422, 470, 514, 406, 423, 473,
516, 407, 424, 476, 518, 408, 425, 479, 520, 409,
426, 482, 522, 410, 427, 485, 524, 411, 428, 488,
526, 412, 429, 491, 528, 413, 430, 494, 530, 414,
431, 497, 532, 415, 432, 500, 534, 129
};

static const short yypact[] =
{
19,-32768, -3, -91,-32768,-32768,-32768,-32768,-32768,-32768,
8, 50, 8, -88,-32768,-32768,-32768, 18,-32768, 30,
-32768,-32768,-32768,-32768, 59, -66,-32768,-32768, 12,-32768,
32,-32768,-32768,-32768,-32768,-32768,-32768, 223, 33,-32768,
-32768,-32768, 142,-32768, 288,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768, 225, 307, 378, 701, 709, 729,
735, 737, 740, 36,-32768,-32768, 38,-32768,-32768, 44,
-32768,-32768, 48,-32768,-32768, 54,-32768,-32768, 61,-32768,
-32768, 74,-32768,-32768, 76,-32768,-32768, 77,-32768,-32768,
-32768, 16,-32768, 165,-32768, 235,-32768, 167,-32768, 5,
-32768, 224,-32768, 150,-32768, 41,-32768, 174,-32768, 146,
500, 584, 577,-32768, 488,-32768, 465,-32768, 509,-32768,
562, 531,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768, 742, 760, 771,
776, 784, 793, 798, 803, 806, 808, 810, 812, 814,
816, 818, 820, 822, 826, 86,-32768,-32768, 88,-32768,
-32768, 90,-32768,-32768, 92,-32768,-32768, 94,-32768,-32768,
96,-32768,-32768, 98,-32768,-32768, 100,-32768,-32768, 125,
-32768,-32768, 129,-32768,-32768, 131,-32768,-32768, 137,-32768,
-32768, 149,-32768,-32768, 151,-32768,-32768, 155,-32768,-32768,
159,-32768,-32768, 168,-32768,-32768, 196,-32768,-32768,-32768,
64,-32768, 237,-32768, 239,-32768, 9,-32768, 4,-32768,
243,-32768, 256,-32768, 260,-32768, 264,-32768, 277,-32768,
349,-32768, 351,-32768, 262,-32768, 353,-32768, 355,-32768,
294,-32768, 176,-32768, 46,-32768, 480, 535, 194,-32768,
254,-32768, 84, 605, 586, 597, 593, 609, 613, 615,
625, 619, 600,-32768, 79,-32768, 607,-32768, 565,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768, 828, 834, 839, 841, 843, 845, 847,
849, 851, 853, 857, 859, 861, 863, 865, 868, 870,
227,-32768,-32768, 229,-32768,-32768, 245,-32768,-32768, 251,
-32768,-32768, 259,-32768,-32768, 261,-32768,-32768, 268,-32768,
-32768, 269,-32768,-32768, 275,-32768,-32768, 279,-32768,-32768,
280,-32768,-32768, 281,-32768,-32768, 283,-32768,-32768, 289,
-32768,-32768, 297,-32768,-32768, 299,-32768,-32768, 301,-32768,
-32768,-32768, 371,-32768, 373,-32768, 377,-32768, 443,-32768,
439,-32768, 441,-32768, 383,-32768, 445,-32768, 447,-32768,
449,-32768, 469,-32768, 471,-32768, 467,-32768, 486,-32768,
462,-32768, 490,-32768, 494, 617, 627, 635, 648, 656,
654, 660, 665, 669, 650, 671, 675, 682, 689, 691,
693, 703,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768, 67,
173,-32768
};

static const short yypgoto[] =
{
-32768,-32768,-32768,-32768,-32768, 45, -9,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768, 7,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768, -122,
-32768,-32768,-32768, -119,-32768,-32768,-32768, 62,-32768,-32768,
-32768,-32768,-32768,-32768,-32768, -106,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768, -45,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768, -35,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768, -321,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768, -113
};





static const short yytable[] =
{
130, 15, 131, 15, 132, 331, 133, 4, -169, -139,
329, 6, 13, -59, 141, 22, 13, 128, 184, 33,
-347, 185, 1, 31, 32, 387, 23, 404, -139, -139,
160, -347, 165, 30, 187, 55, 25, 35, 29, -169,
-169, 41, 139, 37, 110, -84, 112, 347, -59, -59,
-128, -59, 114, -139, 12, -139, 116, 17, 18, -84,
27, -84, 118, -22, -128, 325, -128, 570, -149, 120,
-22, -22, 74, 75, 76, 77, 78, 79, 80, 81,
82, -84, 122, 13, 124, 126, -84, -84, 13, -149,
-149, -84, -149, -84, 289, -84, 291, -84, 293, -84,
295, -84, 297, -84, 299, -84, 301, -84, 303, -84,
-169, -139, -169, -84, 14, -59, -128, -84, 14, 362,
363, -347, -347, -128, -128, 152, -128, 158, -128, 163,
-128, 180, -128, 305, -128, 19, -128, 307, -128, 309,
-128, -84, -128, 43, -128, 311, -39, -84, 377, 378,
13, 137, -128, 19, -159, -39, -39, 313, -39, 315,
-39, 142, -39, 317, -39, -22, 128, 319, 128, -347,
-149, -347, -39, 571, -39, 128, 321, 345, -347, 327,
-106, 328, -347, -159, -159, 14, -39, 333, -347, 334,
14, 335, 364, 336, -106, 337, -106, 338, 13, 339,
-159, 340, 186, 341, 323, 342, 217, 218, 219, 220,
221, 222, 223, 224, 225, 226, 227, 228, 229, 230,
231, 232, 233, 234, 384, 135, 402, 385, -49, 403,
38, 39, 83, 84, -106, 501, 128, 503, 128, -347,
128, -347, -39, -347, 128, 356, -106, -347, -39, -106,
-106, 143, 14, 505, -347, -49, -159, 128, 13, 507,
-347, 128, -49, 128, -347, 128, -347, 509, -347, 511,
-347, -347, -347, -347, -49, -347, 513, 515, 128, -347,
-347, -347, -106, 517, -347, 360, -347, 519, 521, 523,
-347, 525, 13, 357, 166, 343, 358, 527, -93, 143,
14, 45, 46, -347, 47, 529, 48, 531, 49, 533,
50, 386, 0, -347, 86, 87, 0, 352, 51, -347,
52, 359, 0, 365, 0, -347, 19, 0, 19, 0,
-49, 0, 53, 0, -347, 379, 0, 383, 0, 401,
-347, -347, -347, -347, -347, -347, 0, 0, -347, -347,
128, 0, 128, -347, 128, -347, 128, -347, 0, -347,
14, -347, -347, -93, -93, -347, -347, -347, -347, -347,
-347, 0, 128, 0, 128, -347, 0, -347, 128, 0,
0, -347, -347, -347, 128, 89, 90, -347, 54, 535,
0, 536, 0, 537, 14, 538, 0, 539, -347, 540,
-93, 541, -347, 542, 0, 543, 0, 544, -347, 545,
19, 546, -347, 547, 0, 548, 0, 549, -347, 550,
-347, 551, -347, 433, 434, 435, 436, 437, 438, 439,
440, 441, 442, 443, 444, 445, 446, 447, 448, 449,
128, 0, 128, -347, 128, -347, 128, -347, 128, -347,
128, -347, 0, -347, -347, -347, -347, -347, -347, -347,
-347, -347, -347, 128, 0, 0, -347, 0, 128, 13,
128, -347, 128, -347, 0, -347, -347, -347, -347, -347,
-347, 19, -347, -347, 13, 0, 0, 128, -347, -347,
-347, 128, 13, 0, -347, 128, 156, 0, -347, 0,
0, 0, 0, 157, 13, 349, 350, 0, 351, 0,
-347, 148, 149, 13, 0, 151, -347, 145, 0, 0,
0, 0, 0, 0, 0, 0, -347, 0, 0, 0,
-347, 0, 0, 0, -347, 13, 150, 0, 151, 13,
0, 0, 161, 162, -347, -347, -347, -347, -347, -347,
-347, -347, -347, -347, -347, -347, -347, -347, -347, 151,
-347, 0, 0, 0, 0, 0, 13, -347, -347, 13,
0, 14, -347, -347, -347, -347, -347, -347, 0, -347,
48, 13, 49, 48, 355, 49, 14, -347, 13, 0,
13, -347, -347, -347, 14, -347, -347, 13, 147, -347,
-347, 13, 166, 146, 13, 143, 14, 167, 168, 13,
0, 13, 151, 13, 169, 14, 170, 13, 171, 13,
172, 13, 173, 13, 174, 48, 175, 49, 176, 13,
177, 13, 198, 368, 178, 378, 143, 14, 179, 13,
143, 14, 389, 390, 552, 391, 367, 392, 370, 393,
369, 394, 13, 395, 13, 396, 553, 397, 13, 398,
13, 399, 54, 400, 13, 172, 371, 376, 14, 13,
0, 14, 372, 13, 0, 13, 373, 378, 554, 13,
381, 382, 143, 14, 375, 555, 13, 0, 374, 143,
14, 143, 14, 13, 0, 13, 0, 13, 143, 14,
0, 0, 143, 14, 0, 143, 14, 13, 92, 93,
143, 14, 0, 14, 143, 14, 95, 96, 143, 14,
143, 14, 143, 14, 143, 14, 0, 556, 0, 557,
143, 14, 143, 14, 0, 561, 98, 99, 0, 558,
143, 14, 101, 102, 104, 105, 559, 107, 108, 235,
236, 0, 560, 143, 14, 143, 14, 0, 562, 143,
14, 143, 14, 0, 563, 143, 14, 238, 239, 0,
143, 14, 0, 564, 143, 14, 143, 14, 241, 242,
143, 14, 565, 244, 245, 0, 566, 143, 14, 0,
567, 247, 248, 0, 143, 14, 143, 14, 143, 14,
250, 251, 568, 0, 19, 253, 254, 0, 143, 14,
256, 257, 19, 259, 260, 262, 263, 265, 266, 268,
269, 271, 272, 274, 275, 277, 278, 280, 281, 283,
284, 0, 19, 286, 287, 450, 451, 0, 19, 0,
19, 453, 454, 19, 0, 19, 456, 457, 459, 460,
462, 463, 465, 466, 468, 469, 471, 472, 474, 475,
477, 478, 0, 19, 480, 481, 483, 484, 486, 487,
489, 490, 492, 493, 19, 495, 496, 498, 499, 19,
0, 0, 0, 0, 0, 0, 0, 19, 0, 0,
0, 0, 0, 0, 0, 0, 19, 0, 0, 0,
0, 19, 0, 0, 0, 0, 19, 0, 0, 19,
0, 19, 0, 19, 0, 19, 0, 19, 0, 19,
0, 19, 0, 19, 0, 19, 0, 0, 0, 19,
0, 19, 0, 0, 0, 0, 0, 19, 0, 0,
0, 0, 19, 0, 19, 0, 19, 0, 19, 0,
19, 0, 19, 0, 19, 0, 19, 0, 0, 0,
19, 0, 19, 0, 19, 0, 19, 0, 19, 0,
0, 19, 0, 19
};

static const short yycheck[] =
{
113, 10, 115, 12, 117, 1, 1, 10, 4, 4,
1, 102, 4, 4, 127, 103, 4, 1, 140, 28,
4, 140, 3, 11, 12, 346, 8, 348, 23, 24,
136, 15, 138, 26, 140, 44, 6, 5, 104, 35,
36, 8, 1, 36, 8, 4, 8, 1, 39, 40,
4, 42, 8, 48, 9, 50, 8, 7, 8, 18,
1, 20, 8, 4, 18, 1, 20, 0, 4, 8,
11, 12, 65, 66, 67, 68, 69, 70, 71, 72,
73, 40, 8, 4, 8, 8, 45, 46, 4, 25,
26, 50, 28, 52, 8, 54, 8, 56, 8, 58,
8, 60, 8, 62, 8, 64, 8, 66, 8, 68,
106, 106, 108, 72, 106, 106, 70, 76, 106, 35,
36, 105, 106, 77, 78, 134, 80, 136, 82, 138,
84, 140, 86, 8, 88, 103, 90, 8, 92, 8,
94, 100, 96, 1, 98, 8, 4, 106, 69, 70,
4, 1, 106, 103, 4, 13, 14, 8, 16, 8,
18, 15, 20, 8, 22, 106, 1, 8, 1, 4,
106, 4, 30, 0, 32, 1, 8, 1, 4, 292,
4, 294, 17, 33, 34, 106, 44, 300, 21, 302,
106, 304, 108, 306, 18, 308, 20, 310, 4, 312,
50, 314, 140, 316, 8, 318, 199, 200, 201, 202,
203, 204, 205, 206, 207, 208, 209, 210, 211, 212,
213, 214, 215, 216, 346, 1, 348, 346, 4, 348,
7, 8, 7, 8, 58, 8, 1, 8, 1, 4,
1, 4, 100, 4, 1, 51, 70, 4, 106, 73,
74, 105, 106, 8, 19, 31, 106, 1, 4, 8,
4, 1, 38, 1, 4, 1, 4, 8, 4, 8,
105, 106, 105, 106, 50, 101, 8, 8, 1, 105,
106, 4, 106, 8, 41, 330, 49, 8, 8, 8,
51, 8, 4, 39, 40, 1, 42, 8, 4, 105,
106, 13, 14, 47, 16, 8, 18, 8, 20, 8,
22, 346, -1, 53, 7, 8, -1, 326, 30, 55,
32, 330, -1, 332, -1, 63, 103, -1, 103, -1,
106, -1, 44, -1, 57, 344, -1, 346, -1, 348,
105, 106, 105, 106, 105, 106, -1, -1, 105, 106,
1, -1, 1, 4, 1, 4, 1, 4, -1, 4,
106, 105, 106, 69, 70, 105, 106, 105, 106, 105,
106, -1, 1, -1, 1, 4, -1, 4, 1, -1,
-1, 4, 105, 106, 1, 7, 8, 4, 100, 502,
-1, 504, -1, 506, 106, 508, -1, 510, 27, 512,
106, 514, 29, 516, -1, 518, -1, 520, 59, 522,
103, 524, 61, 526, -1, 528, -1, 530, 65, 532,
43, 534, 67, 416, 417, 418, 419, 420, 421, 422,
423, 424, 425, 426, 427, 428, 429, 430, 431, 432,
1, -1, 1, 4, 1, 4, 1, 4, 1, 4,
1, 4, -1, 4, 105, 106, 105, 106, 105, 106,
105, 106, 79, 1, -1, -1, 4, -1, 1, 4,
1, 4, 1, 4, -1, 4, 105, 106, 105, 106,
37, 103, 105, 106, 4, -1, -1, 1, 105, 106,
4, 1, 4, -1, 4, 1, 31, -1, 4, -1,
-1, -1, -1, 38, 4, 25, 26, -1, 28, -1,
71, 23, 24, 4, -1, 50, 75, 17, -1, -1,
-1, -1, -1, -1, -1, -1, 81, -1, -1, -1,
83, -1, -1, -1, 85, 4, 48, -1, 50, 4,
-1, -1, 33, 34, 105, 106, 105, 106, 105, 106,
105, 106, 105, 106, 105, 106, 87, 95, 91, 50,
89, -1, -1, -1, -1, -1, 4, 105, 106, 4,
-1, 106, 105, 106, 105, 106, 105, 106, -1, 93,
18, 4, 20, 18, 49, 20, 106, 97, 4, -1,
4, 105, 106, 99, 106, 105, 106, 4, 21, 105,
106, 4, 40, 19, 4, 105, 106, 45, 46, 4,
-1, 4, 50, 4, 52, 106, 54, 4, 56, 4,
58, 4, 60, 4, 62, 18, 64, 20, 66, 4,
68, 4, 101, 47, 72, 70, 105, 106, 76, 4,
105, 106, 77, 78, 27, 80, 41, 82, 55, 84,
53, 86, 4, 88, 4, 90, 29, 92, 4, 94,
4, 96, 100, 98, 4, 58, 57, 67, 106, 4,
-1, 106, 59, 4, -1, 4, 61, 70, 43, 4,
73, 74, 105, 106, 65, 37, 4, -1, 63, 105,
106, 105, 106, 4, -1, 4, -1, 4, 105, 106,
-1, -1, 105, 106, -1, 105, 106, 4, 7, 8,
105, 106, -1, 106, 105, 106, 7, 8, 105, 106,
105, 106, 105, 106, 105, 106, -1, 71, -1, 75,
105, 106, 105, 106, -1, 85, 7, 8, -1, 79,
105, 106, 7, 8, 7, 8, 81, 7, 8, 7,
8, -1, 83, 105, 106, 105, 106, -1, 87, 105,
106, 105, 106, -1, 89, 105, 106, 7, 8, -1,
105, 106, -1, 91, 105, 106, 105, 106, 7, 8,
105, 106, 93, 7, 8, -1, 95, 105, 106, -1,
97, 7, 8, -1, 105, 106, 105, 106, 105, 106,
7, 8, 99, -1, 103, 7, 8, -1, 105, 106,
7, 8, 103, 7, 8, 7, 8, 7, 8, 7,
8, 7, 8, 7, 8, 7, 8, 7, 8, 7,
8, -1, 103, 7, 8, 7, 8, -1, 103, -1,
103, 7, 8, 103, -1, 103, 7, 8, 7, 8,
7, 8, 7, 8, 7, 8, 7, 8, 7, 8,
7, 8, -1, 103, 7, 8, 7, 8, 7, 8,
7, 8, 7, 8, 103, 7, 8, 7, 8, 103,
-1, -1, -1, -1, -1, -1, -1, 103, -1, -1,
-1, -1, -1, -1, -1, -1, 103, -1, -1, -1,
-1, 103, -1, -1, -1, -1, 103, -1, -1, 103,
-1, 103, -1, 103, -1, 103, -1, 103, -1, 103,
-1, 103, -1, 103, -1, 103, -1, -1, -1, 103,
-1, 103, -1, -1, -1, -1, -1, 103, -1, -1,
-1, -1, 103, -1, 103, -1, 103, -1, 103, -1,
103, -1, 103, -1, 103, -1, 103, -1, -1, -1,
103, -1, 103, -1, 103, -1, 103, -1, 103, -1,
-1, 103, -1, 103
};
#line 3 "/usr/share/bison/bison.simple"	/* stack depth 0 */
#line 78
union yyalloc
{
  short yyss;
  yystype yyvs;



};
#line 315
#line 373
int yy1char; yystype yy1lval; int yy1nerrs;


int
yy1parse ( )

{





  register int yystate;
  register int yyn;
  int yyresult;

  int yyerrstatus;

  int yychar1 = 0;
#line 402
  short	yyssa[200 ];
  short *yyss = yyssa;
  register short *yyssp;


  yystype yyvsa[200 ];
  yystype *yyvs = yyvsa;
  register yystype *yyvsp;
#line 424
  size_t yystacksize = 200 ;




  yystype yyval;






  int yylen;

  ;

  yystate = 0;
  yyerrstatus = 0;
  yy1nerrs = 0;
  yy1char = -2 ;






  yyssp = yyss;
  yyvsp = yyvs;



  goto yysetstate;




 yynewstate:



  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {

      size_t yysize = yyssp - yyss + 1;
#line 508
      if (yystacksize >= 10000 )
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > 10000 )
	yystacksize = 10000 ;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) malloc (((yystacksize) * (sizeof (short) + sizeof (yystype)) + (sizeof (union yyalloc) - 1)) );
	if (! yyptr)
	  goto yyoverflowlab;
	do { size_t yynewbytes; do { register size_t yyi; for (yyi = 0; yyi < ( yysize); yyi++) (&yyptr->yyss)[yyi] = ( yyss)[yyi]; } while (0); yyss = &yyptr->yyss; yynewbytes = yystacksize * sizeof (*yyss) + (sizeof (union yyalloc) - 1); yyptr += yynewbytes / sizeof (*yyptr); } while (0) ;
	do { size_t yynewbytes; do { register size_t yyi; for (yyi = 0; yyi < ( yysize); yyi++) (&yyptr->yyvs)[yyi] = ( yyvs)[yyi]; } while (0); yyvs = &yyptr->yyvs; yynewbytes = yystacksize * sizeof (*yyvs) + (sizeof (union yyalloc) - 1); yyptr += yynewbytes / sizeof (*yyptr); } while (0) ;




	if (yyss1 != yyssa)
	  free (yyss1);
      }



      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;





		  ;

      if (yyssp >= yyss + yystacksize - 1)
	goto yyabortlab ;
    }

  ;

  goto yybackup;





yybackup:







  yyn = yypact[yystate];
  if (yyn == -32768 )
    goto yydefault;






  if (yy1char == -2 )
    {
      ;
      yy1char = yy1lex () ;
    }



  if (yy1char <= 0)
    {
      yychar1 = 0;
      yy1char = 0 ;

      ;
    }
  else
    {
      yychar1 = ((unsigned)(yy1char) <= 362 ? yytranslate[yy1char] : 317) ;
#line 604
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > 973 || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];
#line 619
  if (yyn < 0)
    {
      if (yyn == -32768 )
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == 571 )
    goto yyacceptlab ;



	      ;


  if (yy1char != 0 )
    yy1char = -2 ;

  *++yyvsp = yy1lval ;






  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;





yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;





yyreduce:

  yylen = yyr2[yyn];
#line 679
  yyval = yyvsp[1-yylen];
#line 705
  switch (yyn) {

case 1:
#line 233 "src/xml_hist.y"	/* stack depth 0 */
{result_history = yyvsp[0].FLXT_history;;
break;}
case 4:





{printf("<?xml version=\"1.0\" ?>\n");;
break;}
case 6:

{printf("<?XML-ENCODING %s?>\n",yyvsp[0].s); free(yyvsp[0].s);;
break;}
case 10:





{printf("%s", yyvsp[0].s);;
break;}
case 12:

{printf("\n<?XML-ATT %s", yyvsp[0].s);;
break;}
case 13:
#line 258
{printf("?>\n");;
break;}
case 14:
#line 284
{printf("<HISTORY");;
break;}
case 15:
#line 286
{yyval.FLXT_history = yyvsp[0].FLXT_history;;
break;}
case 16:
{
printf("/>\n");
yyval.FLXT_history = empty_history();
;
break;}
case 17:
#line 293
{printf(">");;
break;}
case 18:
#line 295
{
printf("</HISTORY>\n");
yyval.FLXT_history = yyvsp[-1].FLXT_history;
;
break;}
case 19:
{yyval.FLXT_history = yyvsp[-1].FLXT_history;;
break;}
case 20:
#line 303
{yyval.FLXT_history = add_report_to_history(yyvsp[0].FLXT_report, yyvsp[-1].FLXT_history);;
break;}
case 21:
#line 304
{(yy1char = -2) ; (yyerrstatus = 0) ;;
break;}
case 22:
#line 305
{yyval.FLXT_history = empty_history();;
break;}
case 23:

{printf("\n<%s", "REPORT");;
break;}
case 24:
#line 311
{yyval.FLXT_report = yyvsp[0].FLXT_report;
break;}
case 25:
{
yyval.FLXT_report = empty_report();
printf("/>\n");
;
break;}
case 26:
#line 318
{printf(">");;
break;}
case 27:
#line 320
{
printf("</%s>\n", "REPORT");
yyval.FLXT_report = yyvsp[-1].FLXT_report;
;
break;}
case 28:
{yyval.FLXT_report = yyvsp[-1].FLXT_report;;
break;}
case 29:
#line 327
{yyval.FLXT_report = add_run_id_to_report(yyvsp[0].FLXT_run_id, yyvsp[-1].FLXT_report);;
break;}
case 30:
#line 328
{yyval.FLXT_report = add_scenario_file_to_report(yyvsp[0].FLXT_scenario_file, yyvsp[-1].FLXT_report);;
break;}
case 31:
#line 329
{yyval.FLXT_report = add_start_date_to_report(yyvsp[0].FLXT_start_date, yyvsp[-1].FLXT_report);;
break;}
case 32:
#line 330
{yyval.FLXT_report = add_end_date_to_report(yyvsp[0].FLXT_end_date, yyvsp[-1].FLXT_report);;
break;}
case 33:
#line 331
{yyval.FLXT_report = add_compiler_version_to_report(yyvsp[0].FLXT_compiler_version, yyvsp[-1].FLXT_report);;
break;}
case 34:
#line 332
{yyval.FLXT_report = add_scenario_to_report(yyvsp[0].FLXT_scenario, yyvsp[-1].FLXT_report);;
break;}
case 35:
#line 333
{yyval.FLXT_report = add_param_files_to_report(yyvsp[0].FLXT_param_files, yyvsp[-1].FLXT_report);;
break;}
case 36:
#line 334
{yyval.FLXT_report = add_test_to_report(yyvsp[0].FLXT_test, yyvsp[-1].FLXT_report);;
break;}
case 37:
#line 335
{yyval.FLXT_report = add_opt_report_error_to_report(yyvsp[0].FLXT_opt_report_error, yyvsp[-1].FLXT_report);;
break;}
case 38:
#line 336
{(yy1char = -2) ; (yyerrstatus = 0) ;;
break;}
case 39:
#line 337
{yyval.FLXT_report = empty_report();;
break;}
case 40:

{printf("<SCENARIO");;
break;}
case 41:
#line 343
{yyval.FLXT_scenario = yyvsp[0].FLXT_scenario;;
break;}
case 42:
{
printf("/>\n");
yyval.FLXT_scenario = empty_scenario();
;
break;}
case 43:
#line 350
{printf(">");;
break;}
case 44:
#line 352
{
printf("</SCENARIO>\n");
yyval.FLXT_scenario = yyvsp[-1].FLXT_scenario;
;
break;}
case 45:
{yyval.FLXT_scenario = yyvsp[-1].FLXT_scenario;;
break;}
case 46:
#line 360
{yyval.FLXT_scenario = add_host_name_to_scenario(yyvsp[0].FLXT_host_name, yyvsp[-1].FLXT_scenario);;
break;}
case 47:
#line 362
{yyval.FLXT_scenario = add_test_def_to_scenario(yyvsp[0].FLXT_test_def, yyvsp[-1].FLXT_scenario);;
break;}
case 48:
#line 363
{(yy1char = -2) ; (yyerrstatus = 0) ;;
break;}
case 49:
#line 364
{yyval.FLXT_scenario = empty_scenario();;
break;}
case 50:

{printf("<TEST_DEF");;
break;}
case 51:
#line 370
{yyval.FLXT_test_def = yyvsp[0].FLXT_test_def;;
break;}
case 52:
{
printf("/>\n");
yyval.FLXT_test_def = empty_test_def();
;
break;}
case 53:
#line 377
{printf(">");;
break;}
case 54:
#line 379
{
printf("</TEST_DEF>\n");
yyval.FLXT_test_def = yyvsp[-1].FLXT_test_def;
;
break;}
case 55:
{yyval.FLXT_test_def = yyvsp[-1].FLXT_test_def;;
break;}
case 56:
#line 387
{yyval.FLXT_test_def = add_test_path_to_test_def(yyvsp[0].FLXT_test_path, yyvsp[-1].FLXT_test_def);;
break;}
case 57:
#line 389
{yyval.FLXT_test_def = add_options_set_to_test_def(yyvsp[0].FLXT_options_set, yyvsp[-1].FLXT_test_def);;
break;}
case 58:
#line 390
{(yy1char = -2) ; (yyerrstatus = 0) ;;
break;}
case 59:
#line 391
{yyval.FLXT_test_def = empty_test_def();;
break;}
case 60:

{printf("\n<%s", "TEST");;
break;}
case 61:
#line 397
{yyval.FLXT_test = yyvsp[0].FLXT_test;;
break;}
case 62:
{
yyval.FLXT_test = empty_test();
printf("/>\n");
;
break;}
case 63:
#line 404
{printf(">");;
break;}
case 64:
#line 406
{
printf("</%s>\n", "TEST");
yyval.FLXT_test = yyvsp[-1].FLXT_test;
;
break;}
case 65:
{yyval.FLXT_test = yyvsp[-1].FLXT_test;;
break;}
case 66:
#line 413
{yyval.FLXT_test = add_test_path_to_test(yyvsp[0].FLXT_test_path, yyvsp[-1].FLXT_test);;
break;}
case 67:
#line 414
{yyval.FLXT_test = add_start_date_to_test(yyvsp[0].FLXT_start_date, yyvsp[-1].FLXT_test);;
break;}
case 68:
#line 415
{yyval.FLXT_test = add_end_date_to_test(yyvsp[0].FLXT_end_date, yyvsp[-1].FLXT_test);;
break;}
case 69:
#line 416
{yyval.FLXT_test = add_test_name_to_test(yyvsp[0].FLXT_test_name, yyvsp[-1].FLXT_test);;
break;}
case 70:
#line 417
{yyval.FLXT_test = add_host_name_to_test(yyvsp[0].FLXT_host_name, yyvsp[-1].FLXT_test);;
break;}
case 71:
#line 418
{yyval.FLXT_test = add_test_mode_to_test(yyvsp[0].FLXT_test_mode, yyvsp[-1].FLXT_test);;
break;}
case 72:
#line 419
{yyval.FLXT_test = add_level_to_test(yyvsp[0].FLXT_level, yyvsp[-1].FLXT_test);;
break;}
case 73:
#line 420
{yyval.FLXT_test = add_cc_options_to_test(yyvsp[0].FLXT_cc_options, yyvsp[-1].FLXT_test);;
break;}
case 74:
#line 421
{yyval.FLXT_test = add_cflags_to_test(yyvsp[0].FLXT_cflags, yyvsp[-1].FLXT_test);;
break;}
case 75:
#line 422
{yyval.FLXT_test = add_makefile_to_test(yyvsp[0].FLXT_makefile, yyvsp[-1].FLXT_test);;
break;}
case 76:
#line 423
{yyval.FLXT_test = add_make_options_to_test(yyvsp[0].FLXT_make_options, yyvsp[-1].FLXT_test);;
break;}
case 77:
#line 424
{yyval.FLXT_test = add_simulator_to_test(yyvsp[0].FLXT_simulator, yyvsp[-1].FLXT_test);;
break;}
case 78:
#line 425
{yyval.FLXT_test = add_sim_options_to_test(yyvsp[0].FLXT_sim_options, yyvsp[-1].FLXT_test);;
break;}
case 79:
#line 426
{yyval.FLXT_test = add_targets_to_test(yyvsp[0].FLXT_targets, yyvsp[-1].FLXT_test);;
break;}
case 80:
#line 427
{yyval.FLXT_test = add_compilation_to_test(yyvsp[0].FLXT_compilation, yyvsp[-1].FLXT_test);;
break;}
case 81:
#line 428
{yyval.FLXT_test = add_exec_to_test(yyvsp[0].FLXT_exec, yyvsp[-1].FLXT_test);;
break;}
case 82:
#line 429
{yyval.FLXT_test = add_opt_report_error_to_test(yyvsp[0].FLXT_opt_report_error, yyvsp[-1].FLXT_test);;
break;}
case 83:
#line 430
{(yy1char = -2) ; (yyerrstatus = 0) ;;
break;}
case 84:
#line 431
{yyval.FLXT_test = empty_test();;
break;}
case 85:

{printf("<TARGETS");;
break;}
case 86:
#line 437
{yyval.FLXT_targets = yyvsp[0].FLXT_targets;;
break;}
case 87:
{
printf("/>\n");
yyval.FLXT_targets = empty_targets();
;
break;}
case 88:
#line 444
{printf(">");;
break;}
case 89:
#line 446
{
printf("</TARGETS>\n");
yyval.FLXT_targets = yyvsp[-1].FLXT_targets;
;
break;}
case 90:
{yyval.FLXT_targets = yyvsp[-1].FLXT_targets;;
break;}
case 91:
#line 454
{yyval.FLXT_targets = add_target_to_targets(yyvsp[0].FLXT_target, yyvsp[-1].FLXT_targets);;
break;}
case 92:
#line 455
{(yy1char = -2) ; (yyerrstatus = 0) ;;
break;}
case 93:
#line 456
{yyval.FLXT_targets = empty_targets();;
break;}
case 94:


{printf("\n<%s", "COMPILATION");;
break;}
case 95:
#line 463
{yyval.FLXT_compilation = yyvsp[0].FLXT_compilation;;
break;}
case 96:
{
yyval.FLXT_compilation = empty_compilation();
printf("/>\n");
;
break;}
case 97:
#line 470
{printf(">");;
break;}
case 98:
#line 472
{
printf("</%s>\n", "COMPILATION");
yyval.FLXT_compilation = yyvsp[-1].FLXT_compilation;
;
break;}
case 99:
{yyval.FLXT_compilation = yyvsp[-1].FLXT_compilation;;
break;}
case 100:
#line 479
{yyval.FLXT_compilation = add_target_to_compilation(yyvsp[0].FLXT_target, yyvsp[-1].FLXT_compilation);;
break;}
case 101:
#line 480
{yyval.FLXT_compilation = add_cflags_to_compilation(yyvsp[0].FLXT_cflags, yyvsp[-1].FLXT_compilation);;
break;}
case 102:
#line 481
{yyval.FLXT_compilation = add_make_argv_to_compilation(yyvsp[0].FLXT_make_argv, yyvsp[-1].FLXT_compilation);;
break;}
case 103:
#line 482
{yyval.FLXT_compilation = add_start_date_to_compilation(yyvsp[0].FLXT_start_date, yyvsp[-1].FLXT_compilation);;
break;}
case 104:
#line 483
{yyval.FLXT_compilation = add_end_date_to_compilation(yyvsp[0].FLXT_end_date, yyvsp[-1].FLXT_compilation);;
break;}
case 105:
#line 484
{(yy1char = -2) ; (yyerrstatus = 0) ;;
break;}
case 106:
#line 485
{yyval.FLXT_compilation = empty_compilation();;
break;}
case 107:

{printf("\n<%s", "EXEC");;
break;}
case 108:
#line 491
{yyval.FLXT_exec = yyvsp[0].FLXT_exec;;
break;}
case 109:
{
yyval.FLXT_exec = empty_exec();
nb_execs++;
printf(" exec_num=\"%d\"/>\n", nb_execs);
;
break;}
case 110:
#line 499
{printf(">");;
break;}
case 111:
#line 501
{
nb_execs++;
printf("</%s exec_num=\"%d\">\n", "EXEC", nb_execs);
yyval.FLXT_exec = yyvsp[-1].FLXT_exec;
;
break;}
case 112:
{yyval.FLXT_exec = yyvsp[-1].FLXT_exec;;
break;}
case 113:
#line 509
{yyval.FLXT_exec = add_target_to_exec(yyvsp[0].FLXT_target, yyvsp[-1].FLXT_exec);;
break;}
case 114:
#line 510
{yyval.FLXT_exec = add_description_to_exec(yyvsp[0].FLXT_description, yyvsp[-1].FLXT_exec);;
break;}
case 115:
#line 511
{yyval.FLXT_exec = add_status_to_exec(yyvsp[0].FLXT_status, yyvsp[-1].FLXT_exec);;
break;}
case 116:
#line 512
{yyval.FLXT_exec = add_size_to_exec(yyvsp[0].FLXT_size, yyvsp[-1].FLXT_exec);;
break;}
case 117:
#line 513
{yyval.FLXT_exec = add_input_to_exec(yyvsp[0].FLXT_input, yyvsp[-1].FLXT_exec);;
break;}
case 118:
#line 514
{yyval.FLXT_exec = add_n_frames_to_exec(yyvsp[0].FLXT_n_frames, yyvsp[-1].FLXT_exec);;
break;}
case 119:
#line 515
{yyval.FLXT_exec = add_sample_p_frame_to_exec(yyvsp[0].FLXT_sample_p_frame, yyvsp[-1].FLXT_exec);;
break;}
case 120:
#line 516
{yyval.FLXT_exec = add_e_freq_to_exec(yyvsp[0].FLXT_e_freq, yyvsp[-1].FLXT_exec);;
break;}
case 121:
#line 517
{yyval.FLXT_exec = add_argv_to_exec(yyvsp[0].FLXT_argv, yyvsp[-1].FLXT_exec);;
break;}
case 122:
#line 518
{yyval.FLXT_exec = add_cycles_to_exec(yyvsp[0].FLXT_cycles, yyvsp[-1].FLXT_exec);;
break;}
case 123:
#line 519
{yyval.FLXT_exec = add_cycles_p_frame_to_exec(yyvsp[0].FLXT_cycles_p_frame, yyvsp[-1].FLXT_exec);;
break;}
case 124:
#line 520
{yyval.FLXT_exec = add_mips_to_exec(yyvsp[0].FLXT_mips, yyvsp[-1].FLXT_exec);;
break;}
case 125:
#line 521
{yyval.FLXT_exec = add_start_date_to_exec(yyvsp[0].FLXT_start_date, yyvsp[-1].FLXT_exec);;
break;}
case 126:
#line 522
{yyval.FLXT_exec = add_end_date_to_exec(yyvsp[0].FLXT_end_date, yyvsp[-1].FLXT_exec);;
break;}
case 127:
#line 523
{(yy1char = -2) ; (yyerrstatus = 0) ;;
break;}
case 128:
#line 524
{yyval.FLXT_exec = empty_exec();;
break;}
case 129:

{printf("<COMPILER_VERSION");;
break;}
case 130:
#line 530
{yyval.FLXT_compiler_version = yyvsp[0].FLXT_compiler_version;;
break;}
case 131:
{
printf("/>\n");
yyval.FLXT_compiler_version = empty_compiler_version();
;
break;}
case 132:
#line 537
{printf(">");;
break;}
case 133:
#line 539
{
printf("</COMPILER_VERSION>\n");
yyval.FLXT_compiler_version = yyvsp[-1].FLXT_compiler_version;
;
break;}
case 134:
{yyval.FLXT_compiler_version = yyvsp[-1].FLXT_compiler_version;;
break;}
case 135:
#line 547
{yyval.FLXT_compiler_version = add_host_type_to_compiler_version(yyvsp[0].FLXT_host_type, yyvsp[-1].FLXT_compiler_version);;
break;}
case 136:
#line 549
{yyval.FLXT_compiler_version = add_host_name_to_compiler_version(yyvsp[0].FLXT_host_name, yyvsp[-1].FLXT_compiler_version);;
break;}
case 137:
#line 551
{yyval.FLXT_compiler_version = add_tool_to_compiler_version(yyvsp[0].FLXT_tool, yyvsp[-1].FLXT_compiler_version);;
break;}
case 138:
#line 552
{(yy1char = -2) ; (yyerrstatus = 0) ;;
break;}
case 139:
#line 553
{yyval.FLXT_compiler_version = empty_compiler_version();;
break;}
case 140:

{printf("<TOOL");;
break;}
case 141:
#line 559
{yyval.FLXT_tool = yyvsp[0].FLXT_tool;;
break;}
case 142:
{
printf("/>\n");
yyval.FLXT_tool = empty_tool();
;
break;}
case 143:
#line 566
{printf(">");;
break;}
case 144:
#line 568
{
printf("</TOOL>\n");
yyval.FLXT_tool = yyvsp[-1].FLXT_tool;
;
break;}
case 145:
{yyval.FLXT_tool = yyvsp[-1].FLXT_tool;;
break;}
case 146:
#line 576
{yyval.FLXT_tool = add_tool_name_to_tool(yyvsp[0].FLXT_tool_name, yyvsp[-1].FLXT_tool);;
break;}
case 147:
#line 578
{yyval.FLXT_tool = add_tool_version_to_tool(yyvsp[0].FLXT_tool_version, yyvsp[-1].FLXT_tool);;
break;}
case 148:
#line 579
{(yy1char = -2) ; (yyerrstatus = 0) ;;
break;}
case 149:
#line 580
{yyval.FLXT_tool = empty_tool();;
break;}
case 150:

{printf("<PARAM_FILES");;
break;}
case 151:
#line 586
{yyval.FLXT_param_files = yyvsp[0].FLXT_param_files;;
break;}
case 152:
{
printf("/>\n");
yyval.FLXT_param_files = empty_param_files();
;
break;}
case 153:
#line 593
{printf(">");;
break;}
case 154:
#line 595
{
printf("</PARAM_FILES>\n");
yyval.FLXT_param_files = yyvsp[-1].FLXT_param_files;
;
break;}
case 155:
{yyval.FLXT_param_files = yyvsp[-1].FLXT_param_files;;
break;}
case 156:
#line 603
{yyval.FLXT_param_files = add_host_name_to_param_files(yyvsp[0].FLXT_host_name, yyvsp[-1].FLXT_param_files);;
break;}
case 157:
#line 605
{yyval.FLXT_param_files = add_param_file_to_param_files(yyvsp[0].FLXT_param_file, yyvsp[-1].FLXT_param_files);;
break;}
case 158:
#line 606
{(yy1char = -2) ; (yyerrstatus = 0) ;;
break;}
case 159:
#line 607
{yyval.FLXT_param_files = empty_param_files();;
break;}
case 160:

{printf("<PARAM_FILE");;
break;}
case 161:
#line 613
{yyval.FLXT_param_file = yyvsp[0].FLXT_param_file;;
break;}
case 162:
{
printf("/>\n");
yyval.FLXT_param_file = empty_param_file();
;
break;}
case 163:
#line 620
{printf(">");;
break;}
case 164:
#line 622
{
printf("</PARAM_FILE>\n");
yyval.FLXT_param_file = yyvsp[-1].FLXT_param_file;
;
break;}
case 165:
{yyval.FLXT_param_file = yyvsp[-1].FLXT_param_file;;
break;}
case 166:
#line 630
{yyval.FLXT_param_file = add_filename_to_param_file(yyvsp[0].FLXT_filename, yyvsp[-1].FLXT_param_file);;
break;}
case 167:
#line 632
{
printf("<RAWDATA>\n%s\n</RAWDATA>\n",yyvsp[0].FLXT_rawdata);
yyval.FLXT_param_file = add_rawdata_to_param_file(yyvsp[0].FLXT_rawdata, yyvsp[-1].FLXT_param_file);
;
break;}
case 168:
#line 636
{(yy1char = -2) ; (yyerrstatus = 0) ;;
break;}
case 169:
#line 637
{yyval.FLXT_param_file = empty_param_file();;
break;}
case 170:

{yyval.FLXT_attribute_seq_opt = add_attribute_to_attribute_seq_opt(yyvsp[0].FLXT_attribute, yyvsp[-1].FLXT_attribute_seq_opt);;
break;}
case 171:
#line 642
{yyval.FLXT_attribute_seq_opt = 0L ;;
break;}
case 172:
{printf(" %s", yyvsp[0].s); free(yyvsp[0].s);;
break;}
case 173:
#line 646
{printf(" %s=%s", yyvsp[-2].s, yyvsp[0].s); free(yyvsp[-2].s); free(yyvsp[0].s);;
break;}
case 174:

{printf("<RUN_ID");;
break;}
case 175:
#line 652
{yyval.FLXT_run_id = yyvsp[0].FLXT_run_id;;
break;}
case 176:
{yyval.FLXT_run_id = 0L ;;
break;}
case 177:
#line 656
{printf(">");;
break;}
case 178:
#line 658
{printf("</RUN_ID>\n"); yyval.FLXT_run_id = yyvsp[-1].s;;
break;}
case 179:

{printf("<SCENARIO_FILE");;
break;}
case 180:
#line 664
{yyval.FLXT_scenario_file = yyvsp[0].FLXT_scenario_file;;
break;}
case 181:
{yyval.FLXT_scenario_file = 0L ;;
break;}
case 182:
#line 668
{printf(">");;
break;}
case 183:
#line 670
{printf("</SCENARIO_FILE>\n"); yyval.FLXT_scenario_file = yyvsp[-1].s;;
break;}
case 184:

{printf("<START_DATE");;
break;}
case 185:
#line 676
{yyval.FLXT_start_date = yyvsp[0].FLXT_start_date;;
break;}
case 186:
{yyval.FLXT_start_date = 0L ;;
break;}
case 187:
#line 680
{printf(">");;
break;}
case 188:
#line 682
{printf("</START_DATE>\n"); yyval.FLXT_start_date = yyvsp[-1].s;;
break;}
case 189:

{printf("<END_DATE");;
break;}
case 190:
#line 688
{yyval.FLXT_end_date = yyvsp[0].FLXT_end_date;;
break;}
case 191:
{yyval.FLXT_end_date = 0L ;;
break;}
case 192:
#line 692
{printf(">");;
break;}
case 193:
#line 694
{printf("</END_DATE>\n"); yyval.FLXT_end_date = yyvsp[-1].s;;
break;}
case 194:

{printf("<OPT_REPORT_ERROR");;
break;}
case 195:
#line 700
{yyval.FLXT_opt_report_error = yyvsp[0].FLXT_opt_report_error;;
break;}
case 196:
{yyval.FLXT_opt_report_error = 0L ;;
break;}
case 197:
#line 704
{printf(">");;
break;}
case 198:
#line 706
{printf("</OPT_REPORT_ERROR>\n"); yyval.FLXT_opt_report_error = yyvsp[-1].s;;
break;}
case 199:

{printf("<HOST_TYPE");;
break;}
case 200:
#line 712
{yyval.FLXT_host_type = yyvsp[0].FLXT_host_type;;
break;}
case 201:
{yyval.FLXT_host_type = 0L ;;
break;}
case 202:
#line 716
{printf(">");;
break;}
case 203:
#line 718
{printf("</HOST_TYPE>\n"); yyval.FLXT_host_type = yyvsp[-1].s;;
break;}
case 204:

{printf("<HOST_NAME");;
break;}
case 205:
#line 724
{yyval.FLXT_host_name = yyvsp[0].FLXT_host_name;;
break;}
case 206:
{yyval.FLXT_host_name = 0L ;;
break;}
case 207:
#line 728
{printf(">");;
break;}
case 208:
#line 730
{printf("</HOST_NAME>\n"); yyval.FLXT_host_name = yyvsp[-1].s;;
break;}
case 209:

{printf("<TOOL_NAME");;
break;}
case 210:
#line 736
{yyval.FLXT_tool_name = yyvsp[0].FLXT_tool_name;;
break;}
case 211:
{yyval.FLXT_tool_name = 0L ;;
break;}
case 212:
#line 740
{printf(">");;
break;}
case 213:
#line 742
{printf("</TOOL_NAME>\n"); yyval.FLXT_tool_name = yyvsp[-1].s;;
break;}
case 214:

{printf("<TOOL_VERSION");;
break;}
case 215:
#line 748
{yyval.FLXT_tool_version = yyvsp[0].FLXT_tool_version;;
break;}
case 216:
{yyval.FLXT_tool_version = 0L ;;
break;}
case 217:
#line 752
{printf(">");;
break;}
case 218:
#line 754
{printf("</TOOL_VERSION>\n"); yyval.FLXT_tool_version = yyvsp[-1].s;;
break;}
case 219:

{printf("<FILENAME");;
break;}
case 220:
#line 760
{yyval.FLXT_filename = yyvsp[0].FLXT_filename;;
break;}
case 221:
{yyval.FLXT_filename = 0L ;;
break;}
case 222:
#line 764
{printf(">");;
break;}
case 223:
#line 766
{printf("</FILENAME>\n"); yyval.FLXT_filename = yyvsp[-1].s;;
break;}
case 224:

{printf("<TEST_PATH");;
break;}
case 225:
#line 772
{yyval.FLXT_test_path = yyvsp[0].FLXT_test_path;;
break;}
case 226:
{yyval.FLXT_test_path = 0L ;;
break;}
case 227:
#line 776
{printf(">");;
break;}
case 228:
#line 778
{printf("</TEST_PATH>\n"); yyval.FLXT_test_path = yyvsp[-1].s;;
break;}
case 229:

{printf("<OPTIONS_SET");;
break;}
case 230:
#line 784
{yyval.FLXT_options_set = yyvsp[0].FLXT_options_set;;
break;}
case 231:
{yyval.FLXT_options_set = 0L ;;
break;}
case 232:
#line 788
{printf(">");;
break;}
case 233:
#line 790
{printf("</OPTIONS_SET>\n"); yyval.FLXT_options_set = yyvsp[-1].s;;
break;}
case 234:

{printf("<TEST_NAME");;
break;}
case 235:
#line 796
{yyval.FLXT_test_name = yyvsp[0].FLXT_test_name;;
break;}
case 236:
{yyval.FLXT_test_name = 0L ;;
break;}
case 237:
#line 800
{printf(">");;
break;}
case 238:
#line 802
{printf("</TEST_NAME>\n"); yyval.FLXT_test_name = yyvsp[-1].s;;
break;}
case 239:

{printf("<TEST_MODE");;
break;}
case 240:
#line 808
{yyval.FLXT_test_mode = yyvsp[0].FLXT_test_mode;;
break;}
case 241:
{yyval.FLXT_test_mode = 0L ;;
break;}
case 242:
#line 812
{printf(">");;
break;}
case 243:
#line 814
{printf("</TEST_MODE>\n"); yyval.FLXT_test_mode = yyvsp[-1].s;;
break;}
case 244:

{printf("<LEVEL");;
break;}
case 245:
#line 820
{yyval.FLXT_level = yyvsp[0].FLXT_level;;
break;}
case 246:
{yyval.FLXT_level = 0L ;;
break;}
case 247:
#line 824
{printf(">");;
break;}
case 248:
#line 826
{printf("</LEVEL>\n"); yyval.FLXT_level = yyvsp[-1].s;;
break;}
case 249:

{printf("<CC_OPTIONS");;
break;}
case 250:
#line 832
{yyval.FLXT_cc_options = yyvsp[0].FLXT_cc_options;;
break;}
case 251:
{yyval.FLXT_cc_options = 0L ;;
break;}
case 252:
#line 836
{printf(">");;
break;}
case 253:
#line 838
{printf("</CC_OPTIONS>\n"); yyval.FLXT_cc_options = yyvsp[-1].s;;
break;}
case 254:

{printf("<CFLAGS");;
break;}
case 255:
#line 844
{yyval.FLXT_cflags = yyvsp[0].FLXT_cflags;;
break;}
case 256:
{yyval.FLXT_cflags = 0L ;;
break;}
case 257:
#line 848
{printf(">");;
break;}
case 258:
#line 850
{printf("</CFLAGS>\n"); yyval.FLXT_cflags = yyvsp[-1].s;;
break;}
case 259:

{printf("<MAKEFILE");;
break;}
case 260:
#line 856
{yyval.FLXT_makefile = yyvsp[0].FLXT_makefile;;
break;}
case 261:
{yyval.FLXT_makefile = 0L ;;
break;}
case 262:
#line 860
{printf(">");;
break;}
case 263:
#line 862
{printf("</MAKEFILE>\n"); yyval.FLXT_makefile = yyvsp[-1].s;;
break;}
case 264:

{printf("<MAKE_OPTIONS");;
break;}
case 265:
#line 868
{yyval.FLXT_make_options = yyvsp[0].FLXT_make_options;;
break;}
case 266:
{yyval.FLXT_make_options = 0L ;;
break;}
case 267:
#line 872
{printf(">");;
break;}
case 268:
#line 874
{printf("</MAKE_OPTIONS>\n"); yyval.FLXT_make_options = yyvsp[-1].s;;
break;}
case 269:

{printf("<SIMULATOR");;
break;}
case 270:
#line 880
{yyval.FLXT_simulator = yyvsp[0].FLXT_simulator;;
break;}
case 271:
{yyval.FLXT_simulator = 0L ;;
break;}
case 272:
#line 884
{printf(">");;
break;}
case 273:
#line 886
{printf("</SIMULATOR>\n"); yyval.FLXT_simulator = yyvsp[-1].s;;
break;}
case 274:

{printf("<SIM_OPTIONS");;
break;}
case 275:
#line 892
{yyval.FLXT_sim_options = yyvsp[0].FLXT_sim_options;;
break;}
case 276:
{yyval.FLXT_sim_options = 0L ;;
break;}
case 277:
#line 896
{printf(">");;
break;}
case 278:
#line 898
{printf("</SIM_OPTIONS>\n"); yyval.FLXT_sim_options = yyvsp[-1].s;;
break;}
case 279:

{printf("<TARGET");;
break;}
case 280:
#line 904
{yyval.FLXT_target = yyvsp[0].FLXT_target;;
break;}
case 281:
{yyval.FLXT_target = 0L ;;
break;}
case 282:
#line 908
{printf(">");;
break;}
case 283:
#line 910
{printf("</TARGET>\n"); yyval.FLXT_target = yyvsp[-1].s;;
break;}
case 284:

{printf("<MAKE_ARGV");;
break;}
case 285:
#line 916
{yyval.FLXT_make_argv = yyvsp[0].FLXT_make_argv;;
break;}
case 286:
{yyval.FLXT_make_argv = 0L ;;
break;}
case 287:
#line 920
{printf(">");;
break;}
case 288:
#line 922
{printf("</MAKE_ARGV>\n"); yyval.FLXT_make_argv = yyvsp[-1].s;;
break;}
case 289:

{printf("<DESCRIPTION");;
break;}
case 290:
#line 928
{yyval.FLXT_description = yyvsp[0].FLXT_description;;
break;}
case 291:
{yyval.FLXT_description = 0L ;;
break;}
case 292:
#line 932
{printf(">");;
break;}
case 293:
#line 934
{printf("</DESCRIPTION>\n"); yyval.FLXT_description = yyvsp[-1].s;;
break;}
case 294:

{printf("<STATUS");;
break;}
case 295:
#line 940
{yyval.FLXT_status = yyvsp[0].FLXT_status;;
break;}
case 296:
{yyval.FLXT_status = 0L ;;
break;}
case 297:
#line 944
{printf(">");;
break;}
case 298:
#line 946
{printf("</STATUS>\n"); yyval.FLXT_status = yyvsp[-1].s;;
break;}
case 299:

{printf("<SIZE");;
break;}
case 300:
#line 952
{yyval.FLXT_size = yyvsp[0].FLXT_size;;
break;}
case 301:
{yyval.FLXT_size = 0L ;;
break;}
case 302:
#line 956
{printf(">");;
break;}
case 303:
#line 958
{printf("</SIZE>\n"); yyval.FLXT_size = yyvsp[-1].s;;
break;}
case 304:

{printf("<INPUT");;
break;}
case 305:
#line 964
{yyval.FLXT_input = yyvsp[0].FLXT_input;;
break;}
case 306:
{yyval.FLXT_input = 0L ;;
break;}
case 307:
#line 968
{printf(">");;
break;}
case 308:
#line 970
{printf("</INPUT>\n"); yyval.FLXT_input = yyvsp[-1].s;;
break;}
case 309:

{printf("<N_FRAMES");;
break;}
case 310:
#line 976
{yyval.FLXT_n_frames = yyvsp[0].FLXT_n_frames;;
break;}
case 311:
{yyval.FLXT_n_frames = 0L ;;
break;}
case 312:
#line 980
{printf(">");;
break;}
case 313:
#line 982
{printf("</N_FRAMES>\n"); yyval.FLXT_n_frames = yyvsp[-1].s;;
break;}
case 314:

{printf("<SAMPLE_P_FRAME");;
break;}
case 315:
#line 988
{yyval.FLXT_sample_p_frame = yyvsp[0].FLXT_sample_p_frame;;
break;}
case 316:
{yyval.FLXT_sample_p_frame = 0L ;;
break;}
case 317:
#line 992
{printf(">");;
break;}
case 318:
#line 994
{printf("</SAMPLE_P_FRAME>\n"); yyval.FLXT_sample_p_frame = yyvsp[-1].s;;
break;}
case 319:

{printf("<E_FREQ");;
break;}
case 320:
#line 1000
{yyval.FLXT_e_freq = yyvsp[0].FLXT_e_freq;;
break;}
case 321:
{yyval.FLXT_e_freq = 0L ;;
break;}
case 322:
#line 1004
{printf(">");;
break;}
case 323:
#line 1006
{printf("</E_FREQ>\n"); yyval.FLXT_e_freq = yyvsp[-1].s;;
break;}
case 324:

{printf("<ARGV");;
break;}
case 325:
#line 1012
{yyval.FLXT_argv = yyvsp[0].FLXT_argv;;
break;}
case 326:
{yyval.FLXT_argv = 0L ;;
break;}
case 327:
#line 1016
{printf(">");;
break;}
case 328:
#line 1018
{printf("</ARGV>\n"); yyval.FLXT_argv = yyvsp[-1].s;;
break;}
case 329:

{printf("<CYCLES");;
break;}
case 330:
#line 1024
{yyval.FLXT_cycles = yyvsp[0].FLXT_cycles;;
break;}
case 331:
{yyval.FLXT_cycles = 0L ;;
break;}
case 332:
#line 1028
{printf(">");;
break;}
case 333:
#line 1030
{printf("</CYCLES>\n"); yyval.FLXT_cycles = yyvsp[-1].s;;
break;}
case 334:

{printf("<CYCLES_P_FRAME");;
break;}
case 335:
#line 1036
{yyval.FLXT_cycles_p_frame = yyvsp[0].FLXT_cycles_p_frame;;
break;}
case 336:
{yyval.FLXT_cycles_p_frame = 0L ;;
break;}
case 337:
#line 1040
{printf(">");;
break;}
case 338:
#line 1042
{printf("</CYCLES_P_FRAME>\n"); yyval.FLXT_cycles_p_frame = yyvsp[-1].s;;
break;}
case 339:

{printf("<MIPS");;
break;}
case 340:
#line 1048
{yyval.FLXT_mips = yyvsp[0].FLXT_mips;;
break;}
case 341:
{yyval.FLXT_mips = 0L ;;
break;}
case 342:
#line 1052
{printf(">");;
break;}
case 343:
#line 1054
{printf("</MIPS>\n"); yyval.FLXT_mips = yyvsp[-1].s;;
break;}
case 344:

{printf("DATA(%s)",yyvsp[0].s); yyval.s = yyvsp[0].s;;
break;}
case 345:
#line 1059
{yyval.s = yyvsp[-1].s;;
break;}
case 346:
#line 1060
{(yy1char = -2) ; (yyerrstatus = 0) ;;
break;}
case 347:
#line 1061
{yyval.s = strdup("");;
break;}
}
#line 705 "/usr/share/bison/bison.simple"	/* stack depth 0 */


  yyvsp -= yylen;
  yyssp -= yylen;
#line 724
  *++yyvsp = yyval;
#line 733
  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - 109 ] + *yyssp;
  if (yystate >= 0 && yystate <= 973 && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - 109 ];

  goto yynewstate;





yyerrlab:

  if (!yyerrstatus)
    {
      ++yy1nerrs ;
#line 799
	yy1error ("parse error");
    }
  goto yyerrlab1;





yyerrlab1:
  if (yyerrstatus == 3)
    {




      if (yy1char == 0 )
	goto yyabortlab ;

		  ;
      yy1char = -2 ;
    }




  yyerrstatus = 3;

  goto yyerrhandle;






yyerrdefault:
#line 849
yyerrpop:
  if (yyssp == yyss)
    goto yyabortlab ;
  yyvsp--;
  yystate = *--yyssp;
#line 872
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == -32768 )
    goto yyerrdefault;

  yyn += 1 ;
  if (yyn < 0 || yyn > 973 || yycheck[yyn] != 1 )
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == -32768 )
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == 571 )
    goto yyacceptlab ;

  ;

  *++yyvsp = yy1lval ;




  yystate = yyn;
  goto yynewstate;





yyacceptlab:
  yyresult = 0;
  goto yyreturn;




yyabortlab:
  yyresult = 1;
  goto yyreturn;




yyoverflowlab:
  yy1error ("parser stack overflow");
  yyresult = 2;


yyreturn:

  if (yyss != yyssa)
    free (yyss);

  return yyresult;
}
#line 1065 "src/xml_hist.y"	/* stack depth 0 */
