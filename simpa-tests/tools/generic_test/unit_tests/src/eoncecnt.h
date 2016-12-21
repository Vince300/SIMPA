/*======================================================================
     EONCE Registers definition.

	  Copyright(c) Dai@SE&SS,NCSG,Motorola.
	  derived from 

 ======================================================================*/


#ifndef __DH_EONCE_H
#define __DH_EONCE_H
  

extern unsigned long cycles_total;
extern unsigned long cycles_coder_total,cycles_decoder_total;
extern unsigned long cycles_coder_min,cycles_decoder_min;
extern unsigned long cycles_coder_max,cycles_decoder_max;
extern unsigned long nb_frame_total,nb_frame_coder,nb_frame_decoder;


void start_count_function(unsigned long*);
void stop_count_function(void);

void init_hw_time_counter(void);
void stop_hw_time_counter(void);

/* =========================================== Setting for SC140 Core*/

/* -------------------------------------------- Status & control */
extern unsigned long  volatile *pESR        ;
extern unsigned long  volatile *pEMCR       ;
extern unsigned long  volatile *pERCV_LSB   ;
extern unsigned long  volatile *pERCV_MSB   ;
extern unsigned long  volatile *pETRSMT_LSB ;
extern unsigned long  volatile *pETRSMT_MSB ;
extern unsigned short volatile *pEE_CTRL    ;
extern unsigned long volatile *pPC_EXCP    ;
extern unsigned long volatile *pPC_NEXT    ;
extern unsigned long volatile *pPC_LAST    ;
extern unsigned long volatile *pPC_DETECT  ;
extern unsigned short volatile *pEDCA4_CTRL ;
extern unsigned long volatile *pEDCA4_REFA  ;
extern unsigned long volatile *pEDCA4_REFB  ;
extern unsigned long volatile *pEDCA4_MASK  ;
extern unsigned short volatile *pECNT_CTRL  ;
extern unsigned long  volatile *pECNT_VAL   ;
extern unsigned long  volatile *pECNT_EXT   ;
extern unsigned char  volatile *pESEL_CTRL  ;
extern unsigned short volatile *pESEL_DM    ;
extern unsigned short volatile *pESEL_DI    ;
extern unsigned short volatile *pESEL_ETB   ;
extern unsigned short volatile *pESEL_DTB   ;
extern unsigned short volatile *pESEL_DTB   ;
extern unsigned long  volatile vuliCycle_count;	/* for Cycle Count */

#define __EONCE_RBA	0xEFFE00
#define _P2W(off) ((unsigned long  volatile*)(__EONCE_RBA + off*4 ))
#define _P1W(off) ((unsigned short volatile*)(__EONCE_RBA + off*4 ))
#define _P1B(off) ((unsigned char  volatile*)(__EONCE_RBA + off*4 ))
#define _GA(location)	((unsigned long volatile *)(location))

/* =========================================== Setting for SC140 Core*/

/* -------------------------------------------- Status & control */

#define ERCV	   *pERCV_LSB
#define ERCV_LSB  *pERCV_LSB
#define ERCV_MSB  *pERCV_MSB
#define EDCA4_CTRL *pEDCA4_CTRL 
#define EDCA4_REFA *pEDCA4_REFA
#define EDCA4_REFB *pEDCA4_REFB
#define EDCA4_MASK *pEDCA4_MASK
#define ECNT_CTRL *pECNT_CTRL
#define ECNT_VAL *pECNT_VAL
#define ECNT_EXT *pECNT_EXT
#define EE_CTRL	*pEE_CTRL
#define PC_EXCP	*pPC_EXCP
#define PC_NEXT	*pPC_NEXT
#define PC_LAST	*pPC_LAST
#define PC_DETECT *pPC_DETECT

#define ESEL_CTRL	*pESEL_CTRL
#define ESEL_DM	*pESEL_DM
#define ESEL_DI	*pESEL_DI
#define ESEL_ETB	*pESEL_ETB
#define ESEL_DTB	*pESEL_DTB
#define ETRSMT_LSB *pETRSMT_LSB
#define ETRSMT_MSB *pETRSMT_MSB
#define EDCA4_CTRL	*pEDCA4_CTRL
#define EDCA4_MASK	*pEDCA4_MASK


#endif




