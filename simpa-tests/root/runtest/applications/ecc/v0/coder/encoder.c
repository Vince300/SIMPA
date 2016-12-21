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
#include "ecc.h"
#include "probing.h"


#ifdef _GENREF
unsigned char ENCODE_REF[CODE_NUMBER];
#endif 

#ifdef _QA_PERF_
extern int pass_fail[2];        /* (~[0] -> coder, ~[1] -> decoder) */
                                /*   =(0 ->fail, 1 -> pass) */
extern int error_pass_fail[2][2];
#else /*_QA_PERF_ */
extern FILE *f_input, *f_coded;
#endif

extern void rsencode (unsigned char m[249], unsigned char c[255]);
extern void rsdecode (unsigned char code[255], unsigned char mesg[249],int *errcode); 
extern int check_data(unsigned char result[], unsigned char expect[], int );
extern void output_data();

void encode ()
{
	unsigned char msg[249], coded[255];
	unsigned char coded_frame[256];
	int i, readme;
	int n=NUMBER;
	int readed=0;
	int k;
	int bytes_written=0, frame=0;	
	
	for (i = 0; i < 249; i++)
		msg[i] = 0;

	readme = 248;
	k=0;
	
	while (readed < NUMBER)
    {
		/** start probing if necessary **/
		START_PROBING_CODER;
		
#ifndef _QA_PERF_
		printf("cod, frame=%d, %d bytes written\n",frame++,bytes_written);
#endif
	   
	    	if(n >= 248)
			readme = 248;
		else
			readme = n;
 			
#ifdef _QA_PERF_
		for(i=0;i<readme;i++) 
			msg[i] = INPUT_REF[i+readed];	
#else		
		fread(&msg, sizeof(char), readme, f_input);
#endif		
#ifdef _DEBUG_APPLI_ 
		printf("IN ");for(i=0;i<readme;i++) printf("%c", msg[i]); printf("\n");
#endif
		msg[248] = readme;
		readed = readed + readme;
		n-=readme;
      
		rsencode (msg, coded);

		coded_frame[0]='G';
                for (i = 254; i > -1; i--)
			  coded_frame[255-i]= coded[i] ;

#ifndef _QA_PERF_
		fwrite(&coded_frame[0],sizeof(char),255+1,f_coded);
		bytes_written+=256 * sizeof(char);
#else
		for (i = 0; i < 256; i++, k++)
			encode_out[k] = coded_frame[i];
#endif
#ifdef _DEBUG_APPLI_
                printf("COD ");for(i=0;i<256;i++) printf("%c", coded_frame[i]); printf("\n");
#endif
		/** stop probing if necessary **/
		STOP_PROBING_CODER;
		
     }
#ifdef _QA_PERF_
     if ((i = check_data(encode_out, ENCODE_REF , CODE_NUMBER)) == -1) pass_fail[0]=1;
     else {
     	pass_fail[0]=0;
     	error_pass_fail[0][0]=1+(int)(i/256);
     	error_pass_fail[0][1]=1+(int)i - (int)(i/256)*256;
     }
#endif	
}
