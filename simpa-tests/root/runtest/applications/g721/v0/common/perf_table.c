
unsigned char encode_out[100];
unsigned char decode_out[100];

#ifdef _QA_PERF_
unsigned char INPUT_REF[]="abcdefghijklmnopqrstuvwxyz";
unsigned char ENCODE_REF[]="ИИШЩЇЋ№нноооп";
unsigned char DECODE_REF[]="trolhfhghkkllnnrosuuvvwwzy";
#endif


#if defined(_QA_DECODER_) && defined(_QA_PERF_)
unsigned char *INPUT_DECODER = ENCODE_REF;
#else
unsigned char *INPUT_DECODER;
#endif
