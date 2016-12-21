/******************************************************
 ** System Interface calls for Simulation
 **
 **/

#pragma dont_inline on

extern int errno(void);

#define OsExit  1
#define OsRead  3
#define OsWrite 4

#define OsStdin  0
#define OsStdout 1
#define OsStderr 2

void _ExitProcess(void)
{ asm("  li   r0,OsExit");
  asm("  sc");
}



void __init_hardware(void)
{ return; }

void __flush_cache(void)
{ return; }

void __init_user(void)
{ return; }



int  os_read(int fd,char* buf,int cnt)
{ asm("  li   r0,OsRead");
  asm("  sc");
  asm("  bnslr+");
  asm("  b  errno");
}

int  os_write(int fd,char* buf,int cnt)
{ asm("  li   r0,OsWrite");
  asm("  sc");
  asm("  bnslr+");
  asm("  b  errno");
}

int  InitializeUART(void)
{ return 0; }

int ReadUARTN( char* buf, int cnt )
{ os_read( OsStdin,buf,cnt ); 
  return 0; }

int WriteUARTN( char* buf, int cnt )
{ os_write( OsStdout,buf,cnt ); 
  return 0; }

#pragma dont_inline reset
