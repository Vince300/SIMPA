#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <g722.h>

#include <probing.h>


/************************************************************/
/*                  LOCAL FUNCTION PROTOTYPES               */
/************************************************************/
void decode(int);


/************************************************************/
/* G722 DECODE FUNCTION, result in xout1 and xout2          */
/************************************************************/
void decode(int input)
{
    int i;
    long int xa1,xa2;    /* qmf accumulators */
    int *h_ptr,*ac_ptr,*ac_ptr1,*ad_ptr,*ad_ptr1;

	/** start probing if necessary **/
	START_PROBING_DECODER;
		

/* split transmitted word from input into ilr and ih */
    ilr = input & 0x3f;
    ih = input >> 6;

/* LOWER SUB_BAND DECODER */

/* filtez: compute predictor output for zero section */
    dec_szl = filtez(dec_del_bpl,dec_del_dltx);

/* filtep: compute predictor output signal for pole section */
    dec_spl = filtep(dec_rlt1,dec_al1,dec_rlt2,dec_al2);

    dec_sl = dec_spl + dec_szl;

/* invqxl: compute quantized difference signal for adaptive predic */
    dec_dlt = ((long)dec_detl*qq4_code4_table[ilr >> 2]) >> 15;

/* invqxl: compute quantized difference signal for decoder output */
    dl = ((long)dec_detl*qq6_code6_table[ilr]) >> 15;

    rl = dl + dec_sl;

/* logscl: quantizer scale factor adaptation in the lower sub-band */
    dec_nbl = logscl(ilr,dec_nbl);

/* scalel: computes quantizer scale factor in the lower sub band */
    dec_detl = scalel(dec_nbl,8);

/* parrec - add pole predictor output to quantized diff. signal */
/* for partially reconstructed signal */
    dec_plt = dec_dlt + dec_szl;

/* upzero: update zero section predictor coefficients */
    upzero(dec_dlt,dec_del_dltx,dec_del_bpl);

/* uppol2: update second predictor coefficient apl2 and delay it as al2 */
    dec_al2 = uppol2(dec_al1,dec_al2,dec_plt,dec_plt1,dec_plt2);

/* uppol1: update first predictor coef. (pole setion) */
    dec_al1 = uppol1(dec_al1,dec_al2,dec_plt,dec_plt1);

/* recons : compute recontructed signal for adaptive predictor */
    dec_rlt = dec_sl + dec_dlt;


/* done with lower sub band decoder, implement delays for next time */
    dec_rlt2 = dec_rlt1;
    dec_rlt1 = dec_rlt;
    dec_plt2 = dec_plt1;
    dec_plt1 = dec_plt;

/* HIGH SUB-BAND DECODER */

/* filtez: compute predictor output for zero section */
    dec_szh = filtez(dec_del_bph,dec_del_dhx);

/* filtep: compute predictor output signal for pole section */
    dec_sph = filtep(dec_rh1,dec_ah1,dec_rh2,dec_ah2);

/* predic:compute the predictor output value in the higher sub_band decoder */
    dec_sh = dec_sph + dec_szh;

/* invqah: in-place compute the quantized difference signal */
    dec_dh = ((long)dec_deth*qq2_code2_table[ih]) >> 15L ;

/* logsch: update logarithmic quantizer scale factor in hi sub band */
    dec_nbh = logsch(ih,dec_nbh);

/* scalel: compute the quantizer scale factor in the higher sub band */
    dec_deth = scalel(dec_nbh,10);

/* parrec: compute partially recontructed signal */
    dec_ph = dec_dh + dec_szh;

/* upzero: update zero section predictor coefficients */
    upzero(dec_dh,dec_del_dhx,dec_del_bph);

/* uppol2: update second predictor coefficient aph2 and delay it as ah2 */
    dec_ah2 = uppol2(dec_ah1,dec_ah2,dec_ph,dec_ph1,dec_ph2);

/* uppol1: update first predictor coef. (pole setion) */
    dec_ah1 = uppol1(dec_ah1,dec_ah2,dec_ph,dec_ph1);

/* recons : compute recontructed signal for adaptive predictor */
    rh = dec_sh + dec_dh;

/* done with high band decode, implementing delays for next time here */
    dec_rh2 = dec_rh1;
    dec_rh1 = rh;
    dec_ph2 = dec_ph1;
    dec_ph1 = dec_ph;

/* end of higher sub_band decoder */

/* end with receive quadrature mirror filters */   
    xd = rl - rh;
    xs = rl + rh;

/* receive quadrature mirror filters implemented here */
    h_ptr = h;
    ac_ptr = accumc;
    ad_ptr = accumd;
    xa1 = (long)xd * (*h_ptr++);
    xa2 = (long)xs * (*h_ptr++);
/* main multiply accumulate loop for samples and coefficients */
    for(i = 0 ; i < 10 ; i++) {
        xa1 += (long)(*ac_ptr++) * (*h_ptr++);
        xa2 += (long)(*ad_ptr++) * (*h_ptr++);
    }
/* final mult/accumulate */
    xa1 += (long)(*ac_ptr) * (*h_ptr++);
    xa2 += (long)(*ad_ptr) * (*h_ptr++);

/* scale by 2^14 */
    xout1 = (short)(xa1 >> 14);
    xout2 = (short)(xa2 >> 14);
	if ((xout1==0x7fff)||(xout1==0xffff8000)||
		(xout2==0x7fff)||(xout2==0xffff8000)) 
			printf("output clamped\n");
	/* update delay lines */
    ac_ptr1 = ac_ptr - 1;
    ad_ptr1 = ad_ptr - 1;
    for(i = 0 ; i < 10 ; i++) {
        *ac_ptr-- = *ac_ptr1--;
        *ad_ptr-- = *ad_ptr1--;
    }
    *ac_ptr = xd;
    *ad_ptr = xs;

	/** stop probing if necessary **/
	STOP_PROBING_DECODER;
		

}
