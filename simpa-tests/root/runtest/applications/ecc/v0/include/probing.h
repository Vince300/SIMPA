
#if defined(_QA_SWPROBING_) || defined(_MSC8101ADS_) || defined(_MSC8102ADS_)

	#include <qa_probing.h>

#else

	# define START_PROBING_PROGRAM	/* nothing to probe with */
	# define START_PROBING_CODER    /* nothing to probe with */
	# define STOP_PROBING_CODER     /* nothing to probe with */
	# define START_PROBING_DECODER  /* nothing to probe with */
	# define STOP_PROBING_DECODER   /* nothing to probe with */
	# define STOP_PROBING_PROGRAM	/* nothing to probe with */

#endif



#if defined(_CW_NO_PROTO_REPLACE_) || (defined(_ENTERPRISE_C_) && !defined(_USE_CW_PROTO_)) /*NPR or BASICOP*/

	# define CLEAR_SRBIT_IF_NPR    asm("    bmclr    #<4,sr.l             ; clear the sr bit if npr or basic_op has been chosen"); \
           asm("    nop "); \
           asm("    nop ");

#else

	# define CLEAR_SRBIT_IF_NPR

#endif
