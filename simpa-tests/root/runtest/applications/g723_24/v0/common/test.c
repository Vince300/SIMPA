/* test.c:
   test the encoder and the decoder.	
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUMBER 26
#define CODE_NUMBER 52

#ifdef _QA_PERF_
#include "data.h"
#endif

int pass_fail[2]={0,0};         // (~[0] -> coder, ~[1] -> decoder)
                                //   =(0 ->fail, 1 -> pass)
int error_pass_fail[2][2]={{0,0},{0,0}};

#ifndef _QA_PERF_
FILE 	*f_input = NULL;
FILE	*f_coded = NULL;
FILE	*f_output= NULL;
#endif

#ifdef RUN_BOARD
int volatile *my_pp = (int *)0x7ff00;
#endif

extern void encode();
extern void decode();
void output_data();
  
int  main (int argc, char **argv)
{
#ifndef _QA_PERF_
 #ifdef _QA_CODER_
 if (argc!=3) {puts("usage : program   input_file   coded_file  "); exit(1);}
 f_input = fopen(argv[1],"rb");
 f_coded = fopen(argv[2],"wb");
 f_output= NULL;
 #elif _QA_DECODER_
 if (argc!=3) {puts("usage : program   coded_file   output_file  "); exit(1);}
 f_input = NULL;
 f_coded = fopen(argv[1],"rb");
 f_output= fopen(argv[2],"wb");
 #elif _QA_CODER_DECODER_
 if (argc!=4) {puts("usage : program   input_file   coded_file   output_file  "); exit(1);}
 f_input = fopen(argv[1],"rb");
 f_coded = fopen(argv[2],"wb");
 f_output= fopen(argv[3],"wb");
 #endif
#endif

#if defined(_QA_CODER_)
	pass_fail[1]=1;		/* decoder not tested */
    encode ();
#elif defined(_QA_DECODER_)
	pass_fail[0]=1;		/* coder not tested */
    decode ();
#elif defined(_QA_CODER_DECODER_)
    encode ();
    decode ();
#endif

#ifdef _GENREF
	output_data();
#endif

#ifdef _QA_PERF_
  if (pass_fail[0] && pass_fail[1]) {
	  #ifdef RUN_BOARD
	    *my_pp = 1;
	  #else
	     puts("PASS");
	  #endif 
  }
  else {
  	#ifdef RUN_BOARD
	    *my_pp = 2;
    #else
	   printf("FAIL");
	   if (!pass_fail[0]) printf("(Cod: Fr%d Sp%d)",error_pass_fail[0][0],error_pass_fail[0][1]);
	   if (!pass_fail[1]) printf("(Dec: Fr%d Sp%d)",error_pass_fail[1][0],error_pass_fail[1][1]);
	   puts("");
	#endif
	
  }
#else
 if (f_input)  fclose(f_input);
 if (f_coded)  fclose(f_coded);
 if (f_output) fclose(f_output);
#endif
return (1);
}

