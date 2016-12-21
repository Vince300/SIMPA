#include <stdlib.h>
#include <stdio.h>

#include <rtdspc.h>
#include <g722.h>

#include <probing.h>

#ifdef RUN_BOARD

int volatile *my_pp = (int *)0x7ff00;

#endif

#ifndef _ENTERPRISE_C_
static int bigendianness;
#endif

/* Main program for g722 encode and decode demo for PC */

    extern int encode(int,int);
    extern void decode(int);
    extern void reset();

/* outputs of the decode function */
    extern short xout1,xout2;

#ifdef _QA_PERF_
 #define MAX_FRAME_PERF 20
 #define INPUT_SIZE    (MAX_FRAME_PERF*2)
 #define CODED_SIZE    (MAX_FRAME_PERF  )
 #define OUTPUT_SIZE   (MAX_FRAME_PERF*2)

 #if defined(_QA_CODER_) || defined(_QA_CODER_DECODER_)
	short Input_coder[] =
	{
	    0,    0,	    0,    0,	    0,   -1,	   -3,   -1,	    3,    3,
	    0,    0,	    1,    0,	    0,    0,	    0,    0,	    0,    0,
	    0,    0,	    0,    0,	    0,    0,	    0,    0,	    0,    0,
	    0,    0,	    0,    0,	    0,    0,	    0,    0,	    0,   -1,
	};
	short Output_coder[CODED_SIZE];
 #endif
 
 short Ref_coder[] = 
 {
	253,	253,	253,	 94,	247,	186,	250,	189,	250,	155,
	116,	180,	253,	253,	222,	247,	250,	253,	250,	250,
 };

 #if defined(_QA_DECODER_) || defined(_QA_CODER_DECODER_)
	#ifdef _QA_CODER_DECODER_
	short *Input_decoder = Output_coder;
	#else
	short *Input_decoder = Ref_coder;
	#endif

	short Output_decoder[OUTPUT_SIZE];
	short Ref_decoder[] = 
	{
	    0,    0,	    0,    0,	    0,    0,	   -1,    0,	    0,   -1,
	   -1,    0,	   -1,   -1,	    0,    0,	   -1,   -3,	   -1,   -4,
	    1,   -3,	   -1,   -1,	    1,   -3,	    0,   -1,	    0,   -3,
	   -3,   -2,	    3,    1,	    0,   -2,	    2,   -2,	    0,   -3,
	};
 #endif
 
#endif /* _QA_PERF_ */


/*
#if defined(_MODEL)
*/    /* Tasking */
/*
void pass()
{
#pragma asm
    move #1,r0
    move #1,r0
    debug
    move #1,r0
    move #1,r0
#pragma endasm
}
void fail()
{
#pragma asm
    move #7,r7
    move #7,r7
    debug
    move #7,r7
    move #7,r7
#pragma endasm
}
#else
void pass()
{
    __asm(" move #1,r0");
    __asm(" move #1,r0");
    __asm(" debug");
    __asm(" move #1,r0");
    __asm(" move #1,r0");
}
void fail()
{
    __asm(" move #7,r7");
    __asm(" move #7,r7");
    __asm(" debug");
    __asm(" move #7,r7");
    __asm(" move #7,r7");
}
#endif
*/


/****************************************************************/
/*                  return the endianness of the processor                  */
/****************************************************************/
int is_big_endian()
{       /* Are we little or big endian?  From Harbison&Steele.  */
  union {
     long l;
     char c[sizeof (long)];
  } u ;

  u.l = 1 ;
  return (u.c[sizeof (long) - 1] == 1) ;
}


int get_samples(FILE *input, short *s)
{
	static int index=0;
	int i,val;
	
	#ifdef _QA_PERF_		
		#ifdef _QA_DECODER_
			if ((index+1)>CODED_SIZE) return 0;
			s[0]=Input_decoder[index];
			index++;
			return (1);
		#else /* CODER or CODER_DECODER */
			if ((index+2)>INPUT_SIZE) return 0;
			s[0]=Input_coder[index];
			index++;
			s[1]=Input_coder[index];
			index++;
			return (2);
		#endif
	#else	/* PERF */
		#ifdef _QA_DECODER_
			val = fread((short *)s,sizeof(short),1,input);
		#else /* CODER or CODER_DECODER */
			val = fread((short *)s,sizeof(short),2,input);
		#endif
		
		#ifdef _ENTERPRISE_C_
		#ifdef BIG_ENDIAN
			for (i=0; i<val; i++)
				s[i] = ( ((s[i]&0xff)<<8) + ((s[i]>>8)&0xff) );
		#endif
		#else
			if (bigendianness) {
				for (i=0; i<val; i++)
					s[i] = ( ((s[i]&0xff)<<8) + ((s[i]>>8)&0xff) );
			}
		#endif
		return (val);
		
	#endif	/* PERF */
}

int put_samples(FILE *f_output, short *s)
{
	static int index=0;
	int i,val;
	
	#ifdef _QA_PERF_
		#ifdef _QA_CODER_
			if ((index+1)>INPUT_SIZE) return 0;
			Output_coder[index]=s[0];
			index++;
			return (1);
		#else /* DECODER or CODER_DECODER */
			if ((index+2)>OUTPUT_SIZE) return 0;
			Output_decoder[index]=s[0];
			index++;
			Output_decoder[index]=s[1];
			index++;
			return (2);
		#endif
	#else	/* PERF */
		
		#ifdef _QA_CODER_
			val = 1;
		#else /* DECODER or CODER_DECODER */
			val = 2;
		#endif

		#ifdef _ENTERPRISE_C_
		#ifdef BIG_ENDIAN
			for (i=0; i<val; i++)
				s[i] = ( ((s[i]&0xff)<<8) + ((s[i]>>8)&0xff) );
		#endif
		#else
			if (bigendianness) {
				for (i=0; i<val; i++)
					s[i] = ( ((s[i]&0xff)<<8) + ((s[i]>>8)&0xff) );
			}
		#endif
		
		val = fwrite((short *)s,sizeof(short),val,f_output);
		
		return (val);
		
	#endif	/* PERF */
}

#ifdef _QA_PERF_
void verify()
{
	int wrongC=0, wrongD=0, i1, i2;
	
	#if defined(_QA_CODER_) || defined(_QA_CODER_DECODER_)
		for (i1=0;i1<CODED_SIZE;i1++) {
			if (Output_coder[i1]!=Ref_coder[i1]) {wrongC++;break;}
		}
		#ifdef RUN_BOARD 
    		*my_pp = wrongC+1; 	/* 1 if the test passed, 2 if it doesn't. */
		#endif
	#endif
	
	#if defined(_QA_DECODER_) || defined(_QA_CODER_DECODER_)
		for (i2=0;i2<OUTPUT_SIZE;i2++) {
			if (Output_decoder[i2]!=Ref_decoder[i2]) {wrongD++;break;}
		}
		#ifdef RUN_BOARD 
    		*my_pp = wrongD+1; 	/* 1 if the test passed, 2 if it doesn't.*/
		#endif
	#endif

	if ((!wrongC) && (!wrongD)) puts("PASS");
	else {
		printf("FAIL");
		if (wrongC) printf("(Cod: Fr=%d,Smp=%d)",i1,1);
		if (wrongD) printf("(Dec: Fr=%d,Smp=%d)",i2/2+1,i2%2+1);
	}
}
#endif

int main(int argc, char *argv[])
{
	short in[2],coded,out[2];
	short tmp;
	FILE  *f_input = NULL;
	FILE  *f_output= NULL;
	FILE  *f_temp= NULL;
	int  bytes_written_Cod=0,bytes_written_Dec=0;
	int bytes_coded=0,frame=0;
	
	START_PROBING_PROGRAM;
	CLEAR_SRBIT_IF_NPR;

	#ifndef _ENTERPRISE_C_
	bigendianness= is_big_endian();
	#endif
	
/* open the files */ 
	#ifndef _QA_PERF_
	#ifdef _QA_CODER_DECODER_
		if (argc!=4) 
			{printf("\n  usage: %s   inputfile   codedfile   outputfile\n\n",argv[0]);
			exit(1);}
		f_input=fopen(argv[1],"rb");
		f_temp=fopen(argv[2],"wb");
		f_output=fopen(argv[3],"wb");
	#else
		if (argc!=3) 
			{printf("\n  usage: %s   inputfile   outputfile\n\n",argv[0]);
			exit(1);}
		f_input=fopen(argv[1],"rb");
		f_output=fopen(argv[2],"wb");
	#endif
	#endif
	
/* reset, initialize required memory */
    reset();
	
#if defined(_QA_CODER_)
    while ( get_samples(f_input, (short*)in) )
    {
		#ifndef _QA_PERF_
			printf("cod, frame=%d, %d bytes written\n", frame,bytes_written_Cod);
		#endif
		coded=encode(in[0], in[1]);
		#ifdef _DEBUG_APPLI_
			printf("Fr=%d) input[0..1] = {%d,%d}     \t coded = %d  \n", frame, in[0], in[1], coded);
		#endif
		frame++;
		put_samples(f_output, (short*)&coded);
		bytes_written_Cod += 1*sizeof(short);
    }

#elif defined(_QA_DECODER_)

    while ( get_samples(f_input, (short*)&coded) )
    {
		#ifndef _QA_PERF_
			printf("cod, frame=%d, %d bytes written\n", frame,bytes_written_Dec);
		#endif
		decode(coded);
		out[0] = xout1;
		out[1] = xout2;
		#ifdef _DEBUG_APPLI_
			printf("Fr=%d) coded = %d      \t  output[0..1]={%d,%d} \n", frame++, coded, xout1, xout2);
		#endif
		put_samples(f_output, (short*)out);
		bytes_written_Dec += 2*sizeof(short);
    }
#elif defined(_QA_CODER_DECODER_)

    while ( get_samples(f_input, (short*)in) )
    {
		#ifndef _QA_PERF_
			printf("cod, frame=%d, %d bytes written\n", frame,bytes_written_Cod);
			printf("dec, frame=%d, %d bytes written\n", frame,bytes_written_Dec);
		#endif
		coded=encode(in[0], in[1]);
		
		#ifndef _QA_PERF_
			tmp = coded;
			#ifdef _ENTERPRISE_C_
			#ifdef BIG_ENDIAN
				tmp = ( ((coded&0xff)<<8) + ((coded>>8)&0xff) );
			#endif
			#else
				if (bigendianness) 
					tmp = ( ((coded&0xff)<<8) + ((coded>>8)&0xff) );
			#endif
			fwrite((short *)&tmp,sizeof(short),1,f_temp);	
			bytes_written_Cod += 1*sizeof(short);
		#else
			Output_coder[bytes_coded]=coded;
			bytes_coded ++;
		#endif /* _QA_PERF_ */
		
		decode(coded);
		out[0] = xout1;		
		out[1] = xout2;
		#ifdef _DEBUG_APPLI_
			printf("Fr=%d) input[0..1] = {%d,%d}     \t coded = %d      \t  output[0..1]={%d,%d} \n", frame++, in[0], in[1], coded, out[0], out[1]);
		#endif
		
		put_samples(f_output, (short*)out);
		bytes_written_Dec += 2*sizeof(short);
    }
#else 
#error no target specified!
#endif
    
	#ifdef _QA_PERF_
	verify();
	#else
	fclose(f_input);
	fclose(f_output);
	#endif
	
	STOP_PROBING_PROGRAM;
	
	exit(0);
}
