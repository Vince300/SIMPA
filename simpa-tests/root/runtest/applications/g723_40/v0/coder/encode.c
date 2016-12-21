/*
 * encode.c
 *
 * CCITT ADPCM encoder
 *
 * Usage : encode [-3|4|5] [-a|u|l] < infile > outfile
 */
#include <stdio.h>
#include <g72x.h>
#include <data.h>

#include <probing.h>


/* !: The following statements are added */
extern unsigned char ENCODE_REF[];
extern unsigned char DECODE_REF[];
extern unsigned char INPUT_REF[];

#ifdef _QA_PERF_
extern int pass_fail[2];
extern int error_pass_fail[2][2];
#else
extern FILE *f_input, *f_coded, *f_output;
#endif

int bytes_written=0;

int enccount=0;
extern int nb_coded;

extern int check_data(unsigned char *, unsigned char *, int);

/*
 * Pack output codes into bytes and write them to stdout.
 * Returns 1 if there is residual output, else returns 0.
 */
int
pack_output(
	unsigned		code,
	int			bits)
{
	static unsigned int	out_buffer = 0;
	static int			out_bits = 0;
	unsigned char		out_byte;

	out_buffer |= (code << out_bits);
	out_bits += bits;
	if (out_bits >= 8) {
		out_byte = out_buffer & 0xff;
		out_bits -= 8;
		out_buffer >>= 8;
		encode_out[enccount++] = out_byte;
		nb_coded += 1; 					/* one more coded value */
		#ifdef _DEBUG_APPLI_
		 printf("outputC: %c (%d)\n",out_byte,out_byte);
		#endif		
		#ifndef _QA_PERF_
		 fwrite(&out_byte, sizeof(char), 1, f_coded);
		 bytes_written += 1*sizeof(char);
		#endif
	}
	return (out_bits > 0);
}

/* !:
main(
	int			argc,
	char			**argv
	)*/

/* !: The above function statement is replaced by the following */
void encode()
{
	struct g72x_state	state;
	unsigned char	sample_char;
	short			sample_short;
	unsigned char	code;
	int				resid;
	int				in_coding;
	int				in_size;
	unsigned		*in_buf;
	int				(*enc_routine)();
	int				enc_bits;
	int 			val;

/* !: The following statement is added */
	int			i,j;
	int 	frame=0;
	
	g72x_init_state(&state);

	/* Set defaults to u-law input, G.721 output */
	in_coding = AUDIO_ENCODING_ULAW;
	in_size = sizeof (char);
	in_buf = (unsigned *)&sample_char;
	enc_routine = g723_40_encoder;
	enc_bits = 5;

	/* Process encoding argument, if any */

/* !: The following statement is noted */
/* !:
	while ((argc > 1) && (argv[1][0] == '-')) {
		switch (argv[1][1]) {
		case '3':
			enc_routine = g723_24_encoder;
			enc_bits = 3;
			break;
		case '4':
			enc_routine = g721_encoder;
			enc_bits = 4;
			break;
		case '5':
			enc_routine = g723_40_encoder;
			enc_bits = 5;
			break;
		case 'u':
			in_coding = AUDIO_ENCODING_ULAW;
			in_size = sizeof (char);
			in_buf = (unsigned *)&sample_char;
			break;
		case 'a':
			in_coding = AUDIO_ENCODING_ALAW;
			in_size = sizeof (char);
			in_buf = (unsigned *)&sample_char;
			break;
		case 'l':
			in_coding = AUDIO_ENCODING_LINEAR;
			in_size = sizeof (short);
			in_buf = (unsigned *)&sample_short;
			break;
		default:
#ifndef RUN_BOARD
  fprintf(stderr, "CCITT ADPCM Encoder -- usage:\n");
  fprintf(stderr, "\tencode [-3|4|5] [-a|u|l] < infile > outfile\n");
  fprintf(stderr, "where:\n");
  fprintf(stderr, "\t-3\tGenerate G.723 24kbps (3-bit) data\n");
  fprintf(stderr, "\t-4\tGenerate G.721 32kbps (4-bit) data [default]\n");
  fprintf(stderr, "\t-5\tGenerate G.723 40kbps (5-bit) data\n");
  fprintf(stderr, "\t-a\tProcess 8-bit A-law input data\n");
  fprintf(stderr, "\t-u\tProcess 8-bit u-law input data [default]\n");
  fprintf(stderr, "\t-l\tProcess 16-bit linear PCM input data\n");
#endif
			exit(1);
		}
		argc--;
		argv++;
	}
	*/

#ifdef _QA_PERF_
	/* Read input file and process */
	for (i=0; i<INPUT_SIZE; i++) {
		/** start probing if necessary **/
		START_PROBING_CODER;

		sample_char = INPUT_REF[i];
		#ifdef _DEBUG_APPLI_
		printf("input : %c (%d)\n", sample_char, sample_char);
		#endif
		code = (*enc_routine)(in_size == 2 ? sample_short : sample_char,
		    in_coding, &state);
		resid = pack_output(code, enc_bits);
		/** stop probing if necessary **/
		STOP_PROBING_CODER;
	}
#else
	/* Read input file and process */
	while ((val=fread(&sample_char, in_size, 1, f_input)) == 1) {

		/** start probing if necessary **/
		START_PROBING_CODER;
	 		
        printf("cod, frame=%d, %d bytes written\n",frame++,bytes_written);
#ifdef _DEBUG_APPLI_
		printf("input : %c (%d) %d\n", sample_char, sample_char,val);
#endif
		code = (*enc_routine)(in_size == 2 ? sample_short : sample_char,
		    in_coding, &state);
		resid = pack_output(code, enc_bits);
		/** stop probing if necessary **/
		STOP_PROBING_CODER;
		
	}
#endif

	/* Write zero codes until all residual codes are written out */
	while (resid) {
		resid = pack_output(0, enc_bits);
	}
	
/* !: The following statement is added */
#ifdef _QA_PERF_
	j=check_data(encode_out, ENCODE_REF, CODED_SIZE);
	if (j == -1) pass_fail[0]=1;
	else{
     	pass_fail[0]=0;
     	error_pass_fail[0][0]=1+j;
     	error_pass_fail[0][1]=1;
     }
#endif

/* !: The following statement is noted */
/* !:	fclose(stdout); */

}
