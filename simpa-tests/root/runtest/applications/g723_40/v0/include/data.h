
extern unsigned char encode_out[100];
extern unsigned char decode_out[100];
extern unsigned char *INPUT_DECODER;

#ifdef _QA_PERF_

#define INPUT_SIZE 26
#define CODED_SIZE 20
#define OUTPUT_SIZE 26
extern unsigned char INPUT_REF[];

extern unsigned char ENCODE_REF[];

extern unsigned char DECODE_REF[];

#endif
