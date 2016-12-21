/********************/
/** PROBING MACROS **/
/********************/
#ifdef _ENTERPRISE_C_

#ifdef _QA_SWPROBING_

# define START_PROBING_PROGRAM  /* */
# define START_PROBING_CODER   asm("PROFILE_BEGIN_%C_code_1_frame:");
# define STOP_PROBING_CODER    asm("PROFILE_END_%C_code_1_frame:");
# define START_PROBING_DECODER asm("PROFILE_BEGIN_%C_decode_1_frame:");
# define STOP_PROBING_DECODER  asm("PROFILE_END_%C_decode_1_frame:");
# define STOP_PROBING_PROGRAM  	/* */

#elif _MSC8101ADS_
#include <eoncecnt.h>
# define START_PROBING_PROGRAM    {\
			init_hw_time_counter();	/* start for the program */\
			/*printf("A: cycles_total=%u   vuliCycle_count=%u \n",cycles_total,vuliCycle_count);*/\
			cycles_total = 0;\
			}
# define START_PROBING_CODER    {\
			stop_hw_time_counter();		/* stop for the program */\
			/*printf("B: cycles_total=%u   vuliCycle_count=%u \n",cycles_total,vuliCycle_count);*/\
			cycles_total += vuliCycle_count;\
			init_hw_time_counter();		/* start coding a frame */\
			}
# define STOP_PROBING_CODER   {\
			stop_hw_time_counter();		/* stop coding a frame */\
			/*printf("C: cycles_total=%u   vuliCycle_count=%u \n",cycles_total,vuliCycle_count);*/\
			cycles_total += vuliCycle_count;\
			cycles_coder_total += vuliCycle_count;\
			cycles_coder_min = (cycles_coder_min<vuliCycle_count)?cycles_coder_min:vuliCycle_count;\
			cycles_coder_max = (cycles_coder_max>vuliCycle_count)?cycles_coder_max:vuliCycle_count;\
			nb_frame_coder++;\
			init_hw_time_counter();\
			}		/* go on for the program */

# define START_PROBING_DECODER  {\
			stop_hw_time_counter();		/* stop for the program */\
			/*printf("D: cycles_total=%u   vuliCycle_count=%u \n",cycles_total,vuliCycle_count);*/\
			cycles_total += vuliCycle_count;\
			init_hw_time_counter();		/* start decoding a frame */\
			}
# define STOP_PROBING_DECODER   {\
			stop_hw_time_counter();		/* stop decoding a frame */\
			/*printf("E: cycles_total=%u   vuliCycle_count=%u \n",cycles_total,vuliCycle_count);*/\
			cycles_total += vuliCycle_count;\
			cycles_decoder_total += vuliCycle_count;\
			cycles_decoder_min = (cycles_decoder_min<vuliCycle_count)?cycles_decoder_min:vuliCycle_count;\
			cycles_decoder_max = (cycles_decoder_max>vuliCycle_count)?cycles_decoder_max:vuliCycle_count;\
			nb_frame_decoder++;\
			init_hw_time_counter();\
			}		/* go on for the program */
# define STOP_PROBING_PROGRAM  {			/* stop for the program */\
			stop_hw_time_counter();\
			/*printf("F: cycles_total=%u   vuliCycle_count=%u \n",cycles_total,vuliCycle_count);*/\
			cycles_total += vuliCycle_count;\
			nb_frame_total = (nb_frame_coder!=0)?nb_frame_coder:nb_frame_decoder;\
			printf("-> number of cycles run the program : %u for %u frames (%u cycles/frame) \n",\
				cycles_total, nb_frame_total, cycles_total/nb_frame_total);\
			if (cycles_coder_max>=cycles_coder_min)\
				printf("- - -> number of cycles to code %u frames:   %u (Min=%u  Max=%u  Mean=%u)\n",\
					 nb_frame_coder, cycles_coder_total, cycles_coder_min, cycles_coder_max, cycles_coder_total/nb_frame_coder);\
			if (cycles_decoder_max>=cycles_decoder_min)\
				printf("- - -> number of cycles to decode %u frames: %u (Min=%u  Max=%u  Mean=%u)\n",\
					 nb_frame_decoder, cycles_decoder_total, cycles_decoder_min, cycles_decoder_max, cycles_decoder_total/nb_frame_decoder);\
			}

#else

# define START_PROBING_PROGRAM	/* nothing to probe with */
# define START_PROBING_CODER    /* nothing to probe with */
# define STOP_PROBING_CODER     /* nothing to probe with */
# define START_PROBING_DECODER  /* nothing to probe with */
# define STOP_PROBING_DECODER   /* nothing to probe with */
# define STOP_PROBING_PROGRAM	/* nothing to probe with */

#endif
#else /* not _ENTERPRISE_C_*/

# define START_PROBING_PROGRAM	/* nothing to probe if not enterprise */
# define START_PROBING_CODER    /* nothing to probe if not enterprise */
# define STOP_PROBING_CODER     /* nothing to probe if not enterprise */
# define START_PROBING_DECODER  /* nothing to probe if not enterprise */
# define STOP_PROBING_DECODER   /* nothing to probe if not enterprise */
# define STOP_PROBING_PROGRAM	/* nothing to probe if not enterprise */

#endif /*_ENTERPRISE_C_*/

