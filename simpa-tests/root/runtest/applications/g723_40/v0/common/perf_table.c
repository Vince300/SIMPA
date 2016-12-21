
unsigned char encode_out[100];
unsigned char decode_out[100];

#ifdef _QA_PERF_
unsigned char INPUT_REF[]= 
	{97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112,
	 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};
unsigned char ENCODE_REF[]=
	{16, 66, 24, 231, 172, 246, 226, 172, 245, 222, 156, 243, 222, 123, 247, 222, 3, 0, 0, 0};
unsigned char DECODE_REF[]= 
	{107, 106, 105, 101, 100, 103, 102, 104, 105, 106, 107, 108, 109, 110, 111, 111,
	 113, 114, 114, 117, 117, 118, 118, 120, 121, 122, 125, 126, 127, 127, 254, 254};
#endif


#if defined(_QA_DECODER_) && defined(_QA_PERF_)
unsigned char *INPUT_DECODER = ENCODE_REF;
#else
unsigned char *INPUT_DECODER = encode_out;
#endif
