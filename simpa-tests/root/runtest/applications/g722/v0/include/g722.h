
extern int encode(int,int);
extern void decode(int);
extern int filtez(int *bpl,int *dlt);
extern void upzero(int dlt,int *dlti,int *bli);
extern int filtep(int rlt1,int al1,int rlt2,int al2);
extern int quantl(int el,int detl);
extern int invqxl(int il,int detl,int *code_table,int mode);
extern int logscl(int il,int nbl);
extern int scalel(int nbl,int shift_constant);
extern int uppol2(int al1,int al2,int plt,int plt1,int plt2);
extern int uppol1(int al1,int apl2,int plt,int plt1);
extern int invqah(int ih,int deth);
extern int logsch(int ih,int nbh);
extern void reset();

/* variables for transimit quadrature mirror filter here */
extern int tqmf[24];
/* QMF filter coefficients:
scaled by a factor of 4 compared to G722 CCITT recomendation */
extern int h[24];
extern int xl,xh;
/* variables for receive quadrature mirror filter here */
extern int accumc[11],accumd[11];
/* outputs of decode() */
extern short xout1,xout2;
extern int xs,xd;
/* variables for encoder (hi and lo) here */
extern int il,szl,spl,sl,el;
extern int qq4_code4_table[16];
extern int qq5_code5_table[32];
extern int qq6_code6_table[64];
extern int delay_bpl[6];
extern int delay_dltx[6];
extern int wl_code_table[16];
extern int wl_table[8];
extern int ilb_table[32];
extern int         nbl;                  /* delay line  */
extern int         al1,al2;
extern int         plt,plt1,plt2;
extern int         rs;
extern int         dlt;
extern int         rlt,rlt1,rlt2;
/* decision levels - pre-multiplied by 8, 0 to indicate end */
extern int decis_levl[30];
extern int         detl;
/* quantization table 31 long to make quantl look-up easier,
last entry is for mil=30 case when wd is max */
extern int quant26bt_pos[31];
/* quantization table 31 long to make quantl look-up easier,
last entry is for mil=30 case when wd is max */
extern int quant26bt_neg[31];
extern int         deth;
extern int         sh;         /* this comes from adaptive predictor */
extern int         eh;
extern int qq2_code2_table[4];
extern int wh_code_table[4];
extern int         dh,ih;
extern int         nbh,szh;
extern int         sph,ph,yh,rh; 
extern int         delay_dhx[6];
extern int         delay_bph[6];
extern int         ah1,ah2;
extern int         ph1,ph2;
extern int         rh1,rh2;
/* variables for decoder here */
extern int         ilr,yl,rl;
extern int         dec_deth,dec_detl,dec_dlt;
extern int         dec_del_bpl[6];
extern int         dec_del_dltx[6];
extern int     dec_plt,dec_plt1,dec_plt2;
extern int     dec_szl,dec_spl,dec_sl;
extern int     dec_rlt1,dec_rlt2,dec_rlt;
extern int     dec_al1,dec_al2;
extern int     dl;
extern int     dec_nbl,dec_yh,dec_dh,dec_nbh;
/* variables used in filtez */
extern int         dec_del_bph[6];
extern int         dec_del_dhx[6];
extern int         dec_szh;
/* variables used in filtep */
extern int         dec_rh1,dec_rh2;
extern int         dec_ah1,dec_ah2;
extern int         dec_ph,dec_sph;
extern int     dec_sh,dec_rh;
extern int     dec_ph1,dec_ph2;
