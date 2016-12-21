
unsigned char encode_out[100];
unsigned char decode_out[100];

#ifdef _QA_PERF_
unsigned char INPUT_REF[]= 
	{97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112,
	 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};
unsigned char ENCODE_REF[]=
	{36,  73, 146, 109, 109, 219, 190, 125, 255,  63,   0,   0};
unsigned char DECODE_REF[]= 
	{119, 118, 117, 115, 113, 111, 108, 104, 105, 106, 105, 109, 110, 110, 110, 110,
	 110, 118, 113, 112, 120, 114, 121, 123, 124, 125, 127, 127, 254, 254, 254, 254};
#endif


#if defined(_QA_DECODER_) && defined(_QA_PERF_)
unsigned char *INPUT_DECODER = ENCODE_REF;
#else
unsigned char *INPUT_DECODER = encode_out;
#endif
