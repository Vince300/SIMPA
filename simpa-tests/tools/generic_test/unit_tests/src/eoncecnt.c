#include <stdio.h>

#ifdef _MSC8101ADS_

/*#include <prototype.h>*/
#include <msc8101.h>
#include <eoncecnt.h>

unsigned long 	cycles_total=0x00000000;
unsigned long 	cycles_coder_total=0x00000000,cycles_decoder_total=0x00000000;
unsigned long 	cycles_coder_min=0x7FFFFFFF,cycles_decoder_min=0x7FFFFFFF;
unsigned long 	cycles_coder_max=0x00000000,cycles_decoder_max=0x00000000;
unsigned long  	nb_frame_total=0,nb_frame_coder=0,nb_frame_decoder=0;

/* =========================================== Setting for SC140 Core*/
/* -------------------------------------------- For cycles count */
unsigned long volatile vuliCycle_count;	


/* -------------------------------------------- Status & control */
unsigned long  volatile *pESR        = _P2W(0x00);
unsigned long  volatile *pEMCR       = _P2W(0x01);
unsigned long  volatile *pERCV_LSB   = _P2W(0x02);
unsigned long  volatile *pERCV_MSB   = _P2W(0x03);
unsigned long  volatile *pETRSMT_LSB = _P2W(0x04);
unsigned long  volatile *pETRSMT_MSB = _P2W(0x05);
unsigned short volatile *pEE_CTRL    = _P1W(0x06);
unsigned long volatile *pPC_EXCP    = _P2W(0x07);
unsigned long volatile *pPC_NEXT    = _P2W(0x08);
unsigned long volatile *pPC_LAST    = _P2W(0x09);
unsigned long volatile *pPC_DETECT  = _P2W(0x0A);

/* Offset 0x0B~0x0F are reserved */
/* -------------------------------------------- Control Register */
unsigned short volatile *pEDCA4_CTRL = _P1W(0x14);
/* Offset 0x16~0x17 are reserved */
/* ------------------------------------------- Reference Value A */
unsigned long volatile *pEDCA4_REFA = _P2W(0x1C);
/* Offset 0x1E~0x1F are reserved */
/* ------------------------------------------- Reference Value B */
unsigned long volatile *pEDCA4_REFB = _P2W(0x25);
/* Offset 0x26~0x2F are reserved */
/* ----------------------------------------------- Mask Register */
unsigned long volatile *pEDCA4_MASK = _P2W(0x34);
/* Offset 0x36~0x37 are reserved */

/* --------------------------------------------- Counter reg&val */
unsigned short volatile *pECNT_CTRL = _P1W(0x40);
unsigned long  volatile *pECNT_VAL  = _P2W(0x41);
unsigned long  volatile *pECNT_EXT  = _P2W(0x42);
/* Offset 0x43~0x47 are reserved */

/* -------------------------------------------- Selector reg&val */
unsigned char  volatile *pESEL_CTRL = _P1B(0x48);
unsigned short volatile *pESEL_DM   = _P1W(0x49);
unsigned short volatile *pESEL_DI   = _P1W(0x4A); 
/* Offset 0x4B is reserved */
unsigned short volatile *pESEL_ETB  = _P1W(0x4C);
unsigned short volatile *pESEL_DTB  = _P1W(0x4D);
/* Offset 0x4E~0x4F are reserved */

				/*---------------------- */
				/*  EOnCE Initialization */
				/*---------------------- */
												
void start_count_function(unsigned long *func)
{
    /*---------------------------------------------Initialization*/
    EE_CTRL   = 0x0000;
    ESEL_CTRL = 0x00;
    ESEL_DM   = 0x0000;
    ESEL_DI   = 0x0000;
    ESEL_ETB  = 0x0000;
    ESEL_DTB  = 0x0000;
    
    /*---------------------- Set up EOnCE Channel 4 to start timer*/
    ECNT_VAL = 0xFFFFFFFF;
    ECNT_CTRL = 0x005C;	/*. 5: The event counter is disabled. enabled when an event is detected by the EDCA4.*/
    					/*. C: Count core clocks.*/

    /*--------------------------- EDCA4 Setting for cycle counting*/
    EDCA4_REFA = (unsigned long) func;    
    EDCA4_CTRL = 0x3C03;
    
    EDCA4_MASK = 0xFFFFFFFF; /*Default is 0xffffffff.Just in case*/
    
    EE_CTRL = 0x0000;
}


void stop_count_function(void)
{   
	vuliCycle_count = (0xFFFFFFFF - ECNT_VAL);
}


void init_hw_time_counter()
{
    /*---------------------------------------------Initialization*/
    EE_CTRL   = 0x0000;
    ESEL_CTRL = 0x00;
    ESEL_DM   = 0x0000;
    ESEL_DI   = 0x0000;
    ESEL_ETB  = 0x0000;
    ESEL_DTB  = 0x0000;
    
    /*---------------------- Set up EOnCE Channel 4 to start timer*/
    ECNT_VAL = 0xFFFFFFFF;
    ECNT_CTRL = 0x00FC;		/*. F: The event counter is enabled.*/
    						/*. C: Count core clocks.*/
    vuliCycle_count = 0;	/* reset the SW counter. */

    /*--------------------------- EDCA4 Setting for cycle counting*/
    EDCA4_MASK = 0xFFFFFFFF; /*Default is 0xffffffff.Just in case*/
    
    EE_CTRL = 0x0000;
}


void go_on_count(int init_nb)
{
    /*---------------------------------------------Initialization*/
    EE_CTRL   = 0x0000;
    ESEL_CTRL = 0x00;
    ESEL_DM   = 0x0000;
    ESEL_DI   = 0x0000;
    ESEL_ETB  = 0x0000;
    ESEL_DTB  = 0x0000;
    
    /*---------------------- Set up EOnCE Channel 4 to start timer*/
    ECNT_VAL = 0xFFFFFFFF - init_nb;
    ECNT_CTRL = 0x00FC;		/*. F: The event counter is enabled.*/
    						/*. C: Count core clocks.*/

    /*--------------------------- EDCA4 Setting for cycle counting*/
    EDCA4_MASK = 0xFFFFFFFF; /*Default is 0xffffffff.Just in case*/
    EE_CTRL = 0x0000;
}



void stop_hw_time_counter(void)
{   
    ECNT_CTRL = 0x000C;		/*. 0: The event counter is enabled.*/
    						/*. C: Count core clocks.*/
	vuliCycle_count = (0xFFFFFFFF - ECNT_VAL);
}
#endif /*_MSC8101ADS_*/



