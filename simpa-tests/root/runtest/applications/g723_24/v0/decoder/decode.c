/*
 * decode.c
 *
 * CCITT ADPCM decoder
 *
 * Usage : decode [-3|4|5] [-a|u|l] < infile > outfile
 */
#include <stdio.h>
#include <g72x.h>
#include <data.h>

#include <probing.h>


/* !: The following statements are added */
extern unsigned char ENCODE_REF[];
extern unsigned char DECODE_REF[];

extern unsigned char decode_out[];

#ifdef _QA_PERF_
extern int pass_fail[2];
extern int error_pass_fail[2][2];
#else
extern FILE *f_input, *f_coded, *f_output;
#endif

int deccount=0;
extern int nb_coded;
extern int check_data(unsigned char *, unsigned char *, int);

/*
 * Unpack input codes and pass them back as bytes.
 * Returns 1 if there is residual input, returns -1 if eof, else returns 0.
 */
int
unpack_input(
	unsigned char		*code,
	int			bits)
{
	static unsigned int	in_buffer = 0;
	static int			in_bits = 0;
	unsigned char		in_byte;
	int i;


	if (in_bits < bits) {
	
#if defined(_QA_PERF_) && !defined(_QA_CODER_DECODER_)
	nb_coded=CODED_SIZE;
#endif

#if defined(_QA_CODER_DECODER_)	
		if (deccount>=nb_coded) {
 			*code = 0;
			return (-1);
		}
		in_byte = encode_out[deccount++];
#elif defined(_QA_PERF_)
		if (deccount>=nb_coded) {
 			*code = 0;
			return (-1);
		}
		in_byte = INPUT_DECODER[deccount++];
#else
		if (fread(&in_byte, sizeof (char), 1, f_coded) != 1) {
			*code = 0; 
			return (-1);
		}
#endif
#ifdef _DEBUG_APPLI_
		printf("input : %c (%d)\n",in_byte,in_byte);
#endif		
		in_buffer |= (in_byte << in_bits);
		in_bits += 8;
	}
	*code = in_buffer & ((1 << bits) - 1);
	in_buffer >>= bits;
	in_bits -= bits;
	return (in_bits > 0);
}


/* !: main(
	int			argc,
	char			**argv) */

/* !: The above function statement is replaced by the following */
void decode()
{
	short			sample;
	unsigned char		code;
	int			n;
	struct g72x_state	state;
	int			out_coding;
	int			out_size;
	int			(*dec_routine)();
	int			dec_bits;

/* !: The following statement is added */
	int			i=0,j;
	int 	frame=0,bytes_written=0;
	
	g72x_init_state(&state);
	out_coding = AUDIO_ENCODING_ULAW;
	out_size = sizeof (char);
	dec_routine = g723_24_decoder;
	dec_bits = 3;

	/* Process encoding argument, if any */

/* !: The following statement is noted */
/* !:  
	while ((argc > 1) && (argv[1][0] == '-')) {
		switch (argv[1][1]) {
		case '3':
			dec_routine = g723_24_decoder;
			dec_bits = 3;
			break;
		case '4':
			dec_routine = g721_decoder;
			dec_bits = 4;
			break;
		case '5':
			dec_routine = g723_40_decoder;
			dec_bits = 5;
			break;
		case 'u':
			out_coding = AUDIO_ENCODING_ULAW;
			out_size = sizeof (char);
			break;
		case 'a':
			out_coding = AUDIO_ENCODING_ALAW;
			out_size = sizeof (char);
			break;
		case 'l':
			out_coding = AUDIO_ENCODING_LINEAR;
			out_size = sizeof (short);
			break;
		default:
#ifndef RUN_BOARD
  fprintf(stderr, "CCITT ADPCM Decoder -- usage:\n");
  fprintf(stderr, "\tdecode [-3|4|5] [-a|u|l] < infile > outfile\n");
  fprintf(stderr, "where:\n");
  fprintf(stderr, "\t-3\tProcess G.723 24kbps (3-bit) input data\n");
  fprintf(stderr, "\t-4\tProcess G.721 32kbps (4-bit) input data [default]\n");
  fprintf(stderr, "\t-5\tProcess G.723 40kbps (5-bit) input data\n");
  fprintf(stderr, "\t-a\tGenerate 8-bit A-law data\n");
  fprintf(stderr, "\t-u\tGenerate 8-bit u-law data [default]\n");
  fprintf(stderr, "\t-l\tGenerate 16-bit linear PCM data\n");
#endif
			exit(1);
		}
		argc--;
		argv++;
	}
        */

	/* Read and unpack input codes and process them */
	while (unpack_input(&code, dec_bits) >= 0) {

		/** start probing if necessary **/
		START_PROBING_DECODER;
		
#ifndef _QA_PERF_
                printf("dec, frame=%d, %d bytes written\n",frame++,bytes_written);
#endif
		sample = (*dec_routine)(code, out_coding, &state);
		if (out_size == 2) {
			decode_out[i++] = sample;
#ifndef _QA_PERF_
			fwrite(&sample, out_size, 1, f_output); 
#endif
		} else {
			code = (unsigned char)sample;
			decode_out[i++] = code;
#ifdef _DEBUG_APPLI_
			printf("outputD: %c (%d)\n",code,code);
#endif
#ifndef _QA_PERF_
			fwrite(&code, out_size, 1, f_output); 
			bytes_written += 1*out_size;
#endif
		}
		/** stop probing if necessary **/
		STOP_PROBING_DECODER;
		
	}
/* !: The following statement is added */
#ifdef _QA_PERF_

	j=check_data(decode_out, DECODE_REF, OUTPUT_SIZE);
    if (j == -1) pass_fail[1]=1;
    else {
     	pass_fail[1]=0;
     	error_pass_fail[1][0]=1+j;
     	error_pass_fail[1][1]=1;
    }
#endif

/* !: The following statement is noted */
/* !:	fclose(stdout); */
}
