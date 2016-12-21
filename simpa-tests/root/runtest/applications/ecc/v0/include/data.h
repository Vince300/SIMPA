 
#define NB_FRAMES_PERF_MODE 2
#define NUMBER 248 * NB_FRAMES_PERF_MODE
#define CODE_NUMBER (256*((NUMBER-1)/248+1))


#ifdef _QA_PERF_
#if defined(_QA_CODER_) || defined(_QA_CODER_DECODER_)
extern unsigned char INPUT_REF[];
#endif

extern unsigned char ENCODE_REF[];

#if defined(_QA_DECODER_) || defined(_QA_CODER_DECODER_)
extern unsigned char DECODE_REF[];
#endif
#endif


extern unsigned char encode_out[];
extern unsigned char decode_out[];
extern unsigned char *INPUT_DECODER;

