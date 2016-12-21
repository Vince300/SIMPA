#include "data.h"


#ifdef _QA_PERF_
#if defined(_QA_CODER_) || defined(_QA_CODER_DECODER_)
unsigned char INPUT_REF[]="sddasdjuyefvjyrisdklshfkvidfgjfghfjghjffkgjtifkgjfkgjffgghhasdfgfkgjfkgjrkgdfkgsdkfksdfjksdjfldjfdsfjdkfjkdjflsdjflsdjfklsdfjsdkfjsdkfjsdkfjsdkfjksdfjsdlfjsdljfdkfjsdkfjsdkjfsdfjdlfjdlsjfdkljfdkjfklsddklsfjsdklfjsdljfljfsdklfsdkljlsdjflsdjfldsjflsdsddasdjuyefvjyrisdklshfkvidfgjfghfjghjffkgjtifkgjfkgjffgghhasdfgfkgjfkgjrkgdfkgsdkfksdfjksdjfldjfdsfjdkfjkdjflsdjflsdjfklsdfjsdkfjsdkfjsdkfjsdkfjksdfjsdlfjsdljfdkfjsdkfjsdkjfsdfjdlfjdlsjfdkljfdkjfklsddklsfjsdklfjsdljfljfsdklfsdkljlsdjflsdjfldsjflsd";
/*unsigned char INPUT_REF[]="sddasdjuyefvjyrisdklshfkvidfgjfghfjghjffkgjtifkgjfkgjffgghhasdfgfkgjfkgjrkgdfkgsdkfksdfjksdjfldjfdsfjdkfjkdjflsdjflsdjfklsdfjsdkfjsdkfjsdkfjsdkfjksdfjsdlfjsdljfdkfjsdkfjsdkjfsdfjdlfjdlsjfdkljfdkjfklsddklsfjsdklfjsdljfljfsdklfsdkljlsdjflsdjfldsjflsd";*/
#endif 
 
unsigned char ENCODE_REF[]="Gsddasdjuyefvjyrisdklshfkvidfgjfghfjghjffkgjtifkgjfkgjffgghhasdfgfkgjfkgjrkgdfkgsdkfksdfjksdjfldjfdsfjdkfjkdjflsdjflsdjfklsdfjsdkfjsdkfjsdkfjsdkfjksdfjsdlfjsdljfdkfjsdkfjsdkjfsdfjdlfjdlsjfdkljfdkjfklsddklsfjsdklfjsdljfljfsdklfsdkljlsdjflsdjfldsjflsd�<$Ud�Gsddasdjuyefvjyrisdklshfkvidfgjfghfjghjffkgjtifkgjfkgjffgghhasdfgfkgjfkgjrkgdfkgsdkfksdfjksdjfldjfdsfjdkfjkdjflsdjflsdjfklsdfjsdkfjsdkfjsdkfjsdkfjksdfjsdlfjsdljfdkfjsdkfjsdkjfsdfjdlfjdlsjfdkljfdkjfklsddklsfjsdklfjsdljfljfsdklfsdkljlsdjflsdjfldsjflsd�<$Ud�";
/*unsigned char ENCODE_REF[]="Gsddasdjuyefvjyrisdklshfkvidfgjfghfjghjffkgjtifkgjfkgjffgghhasdfgfkgjfkgjrkgdfkgsdkfksdfjksdjfldjfdsfjdkfjkdjflsdjflsdjfklsdfjsdkfjsdkfjsdkfjsdkfjksdfjsdlfjsdljfdkfjsdkfjsdkjfsdfjdlfjdlsjfdkljfdkjfklsddklsfjsdklfjsdljfljfsdklfsdkljlsdjflsdjfldsjflsd�<$Ud�G
ddasdjuyefvjyrisdklshfkvidfgjfghfjghjffkgjtifkgjfkgjffgghhasdfgfkgjfkgjrkgdfkgsdkfksdfjksdjfldjfdsfjdkfjkdjflsdjflsdjfklsdfjsdkfjsdkfjsdkfjsdkfjksdfjsdlfjsdljfdkfjsdkfjsdkjfsdfjdlfjdlsjfdkljfdkjfklsddklsfjsdklfjsdljfljfsdklfsdkljlsdjflsdjfldsjflsd7ʷɯ��";*/


#if defined(_QA_DECODER_) || defined(_QA_CODER_DECODER_)
unsigned char DECODE_REF[]="sddasdjuyefvjyrisdklshfkvidfgjfghfjghjffkgjtifkgjfkgjffgghhasdfgfkgjfkgjrkgdfkgsdkfksdfjksdjfldjfdsfjdkfjkdjflsdjflsdjfklsdfjsdkfjsdkfjsdkfjsdkfjksdfjsdlfjsdljfdkfjsdkfjsdkjfsdfjdlfjdlsjfdkljfdkjfklsddklsfjsdklfjsdljfljfsdklfsdkljlsdjflsdjfldsjflsdsddasdjuyefvjyrisdklshfkvidfgjfghfjghjffkgjtifkgjfkgjffgghhasdfgfkgjfkgjrkgdfkgsdkfksdfjksdjfldjfdsfjdkfjkdjflsdjflsdjfklsdfjsdkfjsdkfjsdkfjsdkfjksdfjsdlfjsdljfdkfjsdkfjsdkjfsdfjdlfjdlsjfdkljfdkjfklsddklsfjsdklfjsdljfljfsdklfsdkljlsdjflsdjfldsjflsdjflsdjflsdjfldjldjfldjflsdjflsdjfldjlsdfjlsdjfkdfjdkjkd";
/*unsigned char DECODE_REF[]="sddasdjuyefvjyrisdklshfkvidfgjfghfjghjffkgjtifkgjfkgjffgghhasdfgfkgjfkgjrkgdfkgsdkfksdfjksdjfldjfdsfjdkfjkdjflsdjflsdjfklsdfjsdkfjsdkfjsdkfjsdkfjksdfjsdlfjsdljfdkfjsdkfjsdkjfsdfjdlfjdlsjfdkljfdkjfklsddklsfjsdklfjsdljfljfsdklfsdkljlsdjflsdjfldsjflsd
ddasdjuyefvjyrisdklshfkvidfgjfghfjghjffkgjtifkgjfkgjff";*/
#endif
#endif

unsigned char encode_out[CODE_NUMBER];
unsigned char decode_out[NUMBER];

#if defined(_QA_CODER_DECODER_)
unsigned char *INPUT_DECODER=encode_out;
#elif defined(_QA_PERF_) 
unsigned char *INPUT_DECODER=ENCODE_REF;
#else
unsigned char *INPUT_DECODER;
#endif

