/*
    ecc Version 1.2  by Paul Flaherty (paulf@stanford.edu)
    Copyright (C) 1993 Free Software Foundation, Inc.

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
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/


/* ecc.c
	Basic Software Tool for Encoding and Decoding Files.

	This is a simple stream encoder which uses the rslib routines to
	do something practical.  It reads data from stdin in 248(encode_out) or
	256(decode_out) blocks, and writes the corresponding encoded/decoded
	block onto stdout.  An encoded block contains 248 data bytes, one
	length byte, six redundancy bytes, and a capital G byte as a sync
	marker to round it out to 256 bytes.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "data.h"

#include "probing.h"

#ifdef RUN_BOARD
int volatile *my_pp = (int *)0x7ff00;
#endif


#ifdef _GENREF
unsigned char ENCODE_REF[CODE_NUMBER];
unsigned char DECODE_REF[NUMBER];
#endif 

int pass_fail[2]={0,0};         /* (~[0] -> coder, ~[1] -> decoder) */
                                /*   =(0 ->fail, 1 -> pass) */
int error_pass_fail[2][2]={{0,0},{0,0}};

#ifndef _QA_PERF_
FILE *f_input, *f_coded, *f_output;
#endif

extern void encode();
extern void decode();

void ver();
void rsencode (unsigned char m[249], unsigned char c[255]);
void rsdecode (unsigned char code[255], unsigned char mesg[249],int *errcode); 
int check_data(unsigned char result[], unsigned char expect[], int );
void output_data();
  
int main (int argc, char **argv)
{

/* start the global probing if necessary */
START_PROBING_PROGRAM;		
CLEAR_SRBIT_IF_NPR;

#ifndef _QA_PERF_
 #ifdef _QA_CODER_
 if (argc!=3) {puts("usage : program   input_file   bitstream_file  "); exit(1);}
 if (!(f_input = (FILE *) fopen(argv[1],"rb"))) {puts("can't open input file");exit(1);}
 if (!(f_coded = (FILE *) fopen(argv[2],"wb"))) {puts("can't open bitstream file");exit(1);}
 f_output= NULL;
 #elif _QA_DECODER_
 if (argc!=3) {puts("usage : program   input_file   output_file  "); exit(1);}
 f_input = NULL;
 if (!(f_coded = (FILE *) fopen(argv[1],"rb"))) {puts("can't open input file");exit(1);}
 if (!(f_output= (FILE *) fopen(argv[2],"wb"))) {puts("can't open output file");exit(1);}
 #elif _QA_CODER_DECODER_
 if (argc!=4) {puts("usage : program   input_file   coded_file   output_file  "); exit(1);}
 if (!(f_input = (FILE *) fopen(argv[1],"rb"))) {puts("can't open input file");exit(1);}
 if (!(f_coded = (FILE *) fopen(argv[2],"wb"))) {puts("can't open bitstream file");exit(1);}
 if (!(f_output= (FILE *) fopen(argv[3],"wb"))) {puts("can't open output file");exit(1);}
 #endif
#endif

#if defined(_QA_CODER_)
    pass_fail[1] = 1;	/* decoder not tested */
    encode ();
#elif defined(_QA_DECODER_)
    pass_fail[0] = 1;	/* coder not tested */
    decode ();
#elif defined(_QA_CODER_DECODER_)
    encode ();
 #ifndef _QA_PERF_
    fclose(f_coded);
    if (!(f_coded = (FILE *) fopen(argv[2],"rb"))) {puts("can't open coded file");exit(1);}
 #endif
    decode ();
#endif

#ifndef _QA_PERF_
    fclose(f_input);
    fclose(f_coded);
    fclose(f_output);
#endif

#ifdef _GENREF
	output_data();
#else

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
 #endif
  
#endif
/* stop the global probing if necessary */
STOP_PROBING_PROGRAM;		

	exit (0);
}

int check_data(unsigned char result[], unsigned char expected[],int n)
{
	int i;
	
#ifdef _DEBUG_APPLI_
	printf("check the %d outputs...\n",n);
#endif
	for( i=0; i<n; i++)
	{
	#ifdef _GENREF
			expected[i] = result[i];
	#else
	/* this is added because of a bug of m568c */
	  if((int)expected[i]<0)
	    expected[i]+=256;
	  if(result[i] != expected[i]) {
		return (i);
	  }
	#endif
	}
	return (-1);
}

#ifdef _GENREF
void output_data()
{
#ifndef RUN_BOARD
	FILE *Ostream;
	int i;

	if((Ostream=fopen("data.h","a+"))==NULL)
		printf("can not open data.h");
	
	fputs("\nunsigned char ENCODE_REF[]=\"",Ostream);
	fprintf(Ostream,"%s\";\n",ENCODE_REF);
 
	fputs("\nunsigned char DECODE_REF[]=\"",Ostream);
	fprintf(Ostream,"%s\";\n",DECODE_REF);

	fclose(Ostream);
	for(i=0;i<NUMBER;i++)
	{
		if(DECODE_REF[i]!=INPUT_REF[i])
		{
			printf("FAILED DECODE!=INPUT\n");
			exit(1);
		}
	}
	printf("PASSED\n");
#endif
}

#endif

	
