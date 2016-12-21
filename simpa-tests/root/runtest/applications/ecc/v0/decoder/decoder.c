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
	do something practical.  It reads data from stdin in 248(INPUT_DECODER) or
	256(decode_out) blocks, and writes the corresponding encoded/decoded
	block onto stdout.  An encoded block contains 248 data bytes, one
	length byte, six redundancy bytes, and a capital G byte as a sync
	marker to round it out to 256 bytes.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <data.h>
#include <ecc.h>
#include <probing.h>


#ifdef _GENREF
unsigned char DECODE_REF[NUMBER];
#endif 

#ifdef _QA_PERF_
extern int pass_fail[2];        /* (~[0] -> coder, ~[1] -> decoder) */
                                /*   =(0 ->fail, 1 -> pass) */
extern int error_pass_fail[2][2];
#else /*_QA_PERF_ */
extern FILE *f_coded, *f_output;
#endif

extern void rsencode (unsigned char m[249], unsigned char c[255]);
extern void rsdecode (unsigned char code[255], unsigned char mesg[249],int *errcode); 
extern int check_data(unsigned char result[], unsigned char expect[], int );
extern void output_data();

void decode ()
{
 
  int i, j,  bo, len;
  unsigned char msgs[249], cod[255];
  unsigned char block[256];
  int k;
  int frame=0,bytes_written=0;

  FILE /**Istream , *Ostream ,*/ *ErrFile = stderr;


  j = 0;
  k = 0;  


#if defined(_QA_PERF_) 
  while (/*getc (Istream)*/ INPUT_DECODER[k] == 71)
#else
  while ( fread(&block,1,256,f_coded) &&(block[0] == 71))
#endif
	{
		/** start probing if necessary **/
		START_PROBING_DECODER;
#ifdef _DEBUG_APPLI_
        printf("COD ");for(i=0;i<256;i++) printf("%c", block[i]); printf("\n");
#endif
#ifndef _QA_PERF_
	printf("dec, frame=%d, %d bytes written\n",frame++,bytes_written);
#endif
				
#if defined(_QA_PERF_)
	  k++;
      for (i = 254; i > -1; i--)
			cod[i] = INPUT_DECODER[k++] ;
#else	
	  k=1;
      for (i = 254; i > -1; i--)
			cod[i] = block[k++] ;
#endif
      j++;
      rsdecode (cod, msgs, &bo);

#ifndef RUN_BOARD

      if (bo > 0 && bo < 4)
	 fprintf (ErrFile, "ecc: %d byte error in block %d.\n", bo, j);

      if (bo == 4)
	 fprintf (ErrFile, "ecc: unrecoverable error in block %d.\n", j);
#endif 

      len = msgs[248];
      for (i = 0; i < len; i++)
			decode_out[i+(j-1)*248]=msgs[i];

#ifndef _QA_PERF_
      fwrite(&decode_out[(j-1)*248], sizeof(char), len, f_output);
      bytes_written += len*sizeof(char);
#endif
#ifdef _DEBUG_APPLI_
      printf("DEC ");for(i=0;i<256;i++) printf("%c", decode_out[(j-1)*248 + i]); printf("\n");
#endif
	      /** stop probing if necessary **/
		STOP_PROBING_DECODER;
		
   }

#ifdef _QA_PERF_
     if ((i =  check_data(decode_out, DECODE_REF , NUMBER)) == -1) pass_fail[1]=1;
     else {
     	pass_fail[1]=0;
     	error_pass_fail[1][0]=1+(int)(i/248);
     	error_pass_fail[1][1]=1+(int)i - (int)(i/248)*248;
     }
#endif

}
