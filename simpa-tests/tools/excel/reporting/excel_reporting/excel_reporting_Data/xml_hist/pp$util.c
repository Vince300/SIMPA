#line 1 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\util.c"	/* stack depth 0 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdio.h"	/* stack depth 1 */
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
#line 11 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdio.h"	/* stack depth 1 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\size_t.h"	/* stack depth 3 */
#line 28
		typedef unsigned int size_t;
#line 21 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\null.h"	/* stack depth 3 */
#line 22 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\eof.h"	/* stack depth 3 */
#line 23 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\va_list.h"	/* stack depth 3 */
#line 20
	typedef char * va_list;
#line 24 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\file_struc.h"	/* stack depth 3 */
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
#line 30 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdio_api.h"	/* stack depth 3 */
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
#line 31 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdio.posix.h"	/* stack depth 3 */
#line 23
	int __cdecl fileno(FILE *) __attribute__((nothrow)) ;


		FILE *	__cdecl fdopen(int , const char *) __attribute__((nothrow)) ;



		int __cdecl _fileno(FILE *) __attribute__((nothrow)) ;
		FILE * __cdecl _fdopen(int, const char *) __attribute__((nothrow)) ;
#line 34 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 2 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Win32\\Include\\extras_stdio_win32.h"	/* stack depth 3 */
#line 1 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Win32\\Include\\startup.win32.h"	/* stack depth 4 */
#line 14
 extern int  _doserrno;


int	__cdecl __set_errno(unsigned long);




unsigned long __cdecl __dup_core(void *handle, void **dup_handle);



int * __cdecl __get_MSL_init_count(void);
#line 12 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_Extras\\MSL_Win32\\Include\\extras_stdio_win32.h"	/* stack depth 3 */
#line 38 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\cstdio"	/* stack depth 2 */






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
#line 17 "D:\\Program Files\\Metrowerks\\CodeWarrior_922\\MSL\\MSL_C\\MSL_Common\\Include\\stdio.h"	/* stack depth 1 */
#line 11 "D:\\cygwin\\home\\qatools\\new_qa\\testtools\\excel\\reporting\\src\\util.c"	/* stack depth 0 */
#line 36
int strp_cmp(const void *s1, const void *s2) {
        return strcmp(*(char**)s1, *(char**)s2);
}
