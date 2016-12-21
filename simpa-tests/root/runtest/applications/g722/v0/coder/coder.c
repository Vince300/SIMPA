#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <g722.h>

#include <probing.h>

/************************************************************/
/*                  LOCAL FUNCTION PROTOTYPES               */
/************************************************************/
int encode(int,int); 
int quantl(int el,int detl);

/************************************************************/
/* G722 ENCODE FUNCTION two ints in, one 8 bit output       */
/************************************************************/

/* put input samples in xin1 = first value, xin2 = second value */
/* returns il and ih stored together */

int encode(int xin1,int xin2)
{
    int i;
    int *h_ptr,*tqmf_ptr,*tqmf_ptr1;
    long int xa,xb;
    int decis;

	/** start probing if necessary **/
	START_PROBING_CODER;
	
/* transmit quadrature mirror filters implemented here */
    h_ptr = h;
    tqmf_ptr = tqmf;
    xa = (long)(*tqmf_ptr++) * (*h_ptr++);
    xb = (long)(*tqmf_ptr++) * (*h_ptr++);
/* main multiply accumulate loop for samples and coefficients */
    for(i = 0 ; i < 10 ; i++) {
        xa += (long)(*tqmf_ptr++) * (*h_ptr++);
        xb += (long)(*tqmf_ptr++) * (*h_ptr++);
    }
/* final mult/accumulate */
    xa += (long)(*tqmf_ptr++) * (*h_ptr++);
    xb += (long)(*tqmf_ptr) * (*h_ptr++);

/* update delay line tqmf */
    tqmf_ptr1 = tqmf_ptr - 2;
    for(i = 0 ; i < 22 ; i++) *tqmf_ptr-- = *tqmf_ptr1--;
    *tqmf_ptr-- = xin1;
    *tqmf_ptr = xin2;

/* scale outputs */
    xl = (xa + xb) >> 15;
    xh = (xa - xb) >> 15;

/* end of quadrature mirror filter code */

/* starting with lower sub band encoder */

/* filtez - compute predictor output section - zero section */
    szl = filtez(delay_bpl,delay_dltx);

/* filtep - compute predictor output signal (pole section) */
    spl = filtep(rlt1,al1,rlt2,al2);

/* compute the predictor output value in the lower sub_band encoder */
    sl = szl + spl;
    el = xl - sl;

/* quantl: quantize the difference signal */
    il = quantl(el,detl);

/* invqxl: computes quantized difference signal */
/* for invqbl, truncate by 2 lsbs, so mode = 3 */
    dlt = ((long)detl*qq4_code4_table[il >> 2]) >> 15;

/* logscl: updates logarithmic quant. scale factor in low sub band */
    nbl = logscl(il,nbl);

/* scalel: compute the quantizer scale factor in the lower sub band */
/* calling parameters nbl and 8 (constant such that scalel can be scaleh) */
    detl = scalel(nbl,8);

/* parrec - simple addition to compute recontructed signal for adaptive pred */
    plt = dlt + szl;

/* upzero: update zero section predictor coefficients (sixth order)*/
/* calling parameters: dlt, dlt1, dlt2, ..., dlt6 from dlt */
/*  bpli (linear_buffer in which all six values are delayed */
/* return params:      updated bpli, delayed dltx */
    upzero(dlt,delay_dltx,delay_bpl);

/* uppol2- update second predictor coefficient apl2 and delay it as al2 */
/* calling parameters: al1, al2, plt, plt1, plt2 */
    al2 = uppol2(al1,al2,plt,plt1,plt2);

/* uppol1 :update first predictor coefficient apl1 and delay it as al1 */
/* calling parameters: al1, apl2, plt, plt1 */
    al1 = uppol1(al1,al2,plt,plt1);

/* recons : compute recontructed signal for adaptive predictor */
    rlt = sl + dlt;

/* done with lower sub_band encoder; now implement delays for next time*/
    rlt2 = rlt1;
    rlt1 = rlt;
    plt2 = plt1;
    plt1 = plt;

/* high band encode */

    szh = filtez(delay_bph,delay_dhx);

    sph = filtep(rh1,ah1,rh2,ah2);

/* predic: sh = sph + szh */
    sh = sph + szh;
/* subtra: eh = xh - sh */
    eh = xh - sh;

/* quanth - quantization of difference signal for higher sub-band */
/* quanth: in-place for speed params: eh, deth (has init. value) */
    if(eh >= 0) {
        ih = 3;     /* 2,3 are pos codes */
    }
    else {
        ih = 1;     /* 0,1 are neg codes */
    }
    decis = (564L*(long)deth) >> 12L;
    if(abs(eh) > decis) ih--;     /* mih = 2 case */

/* invqah: compute the quantized difference signal, higher sub-band*/
    dh = ((long)deth*qq2_code2_table[ih]) >> 15L ;

/* logsch: update logarithmic quantizer scale factor in hi sub-band*/
    nbh = logsch(ih,nbh);

/* note : scalel and scaleh use same code, different parameters */
    deth = scalel(nbh,10);

/* parrec - add pole predictor output to quantized diff. signal */
    ph = dh + szh;

/* upzero: update zero section predictor coefficients (sixth order) */
/* calling parameters: dh, dhi, bphi */
/* return params: updated bphi, delayed dhx */
    upzero(dh,delay_dhx,delay_bph);

/* uppol2: update second predictor coef aph2 and delay as ah2 */
/* calling params: ah1, ah2, ph, ph1, ph2 */
    ah2 = uppol2(ah1,ah2,ph,ph1,ph2);

/* uppol1:  update first predictor coef. aph2 and delay it as ah1 */
    ah1 = uppol1(ah1,ah2,ph,ph1);

/* recons for higher sub-band */
    yh = sh + dh;

/* done with higher sub-band encoder, now Delay for next time */
    rh2 = rh1;
    rh1 = yh;
    ph2 = ph1;
    ph1 = ph;
	
    	/** stop probing if necessary **/
    	STOP_PROBING_CODER;
    
/* multiplex ih and il to get signals together */
    return(il | (ih << 6));
}



/* quantl - quantize the difference signal in the lower sub-band */
int quantl(int el,int detl)
{
    int ril,mil;
    long int wd,decis;

/* abs of difference signal */
    wd = abs(el);
/* determine mil based on decision levels and detl gain */
    for(mil = 0 ; mil < 30 ; mil++) {
        decis = (decis_levl[mil]*(long)detl) >> 15L;
        if(wd <= decis) break;
    }
/* if mil=30 then wd is less than all decision levels */
    if(el >= 0) ril = quant26bt_pos[mil];
    else ril = quant26bt_neg[mil];
    return(ril);

}
