/*-------------------------------------------------------------------------- 
* File:  msc8101.h
*
*
* Description:  
* Internal Memory Maps for the MSC8101.
*
* Notes:
* 1.  Different structures can be overlaid at the same offsets for the 
*     different modes of operation.
* 2.  Tested with the CodeWarrior for StarCore Compiler.  Please retest if
*     a different compiler is used.
* 3.  The ATM parameter RAM structure in this file (pram.atm) requires
*     that the data be packed.  This is accomplished within Codewarrior
*     (Production 1.0) in two ways.  The second method (b) is implemented
*     currently in this header file:  
*     a.  Pack everything 
*         <Edit><C for MSC8101 Settings...>
*         Code Generation 
*            Passthrough, Hard... 
*               To Front-End:  --nostructpad  (don't forget the 2 dashes)
*               (the default is blank or "--structpad"
*     b.  Pack only the structures that require packing by adding the
*         __PACK__ keyword in the structure declaration.
*
* History:
* 13 JUL 98    ggh    initial version
* 15 JAN 99    ggh    updated MCC structures
* 31 JUL 00    drs    Took out _Packed keywords. Took out atm structure from 
*                     t_PQ2IMM so can compile on 8101.
*  3 AUG 00    ies    Modified for MSC8101
*  8 AUG 00    drs    Clean up 
* 12 Jan 01    drs    Add comments about compiling with packed data structures
* 01 Feb 01    ies    Add Qbus Memory Map
* 21 Feb 01    mrr    Include typedefs.h, FCC defines, #ifndef, #define, #endif
* 07 Mar 01    ies    Add __PACK__ keyword, clean up, test with Production 1.0
*----------------------------------------------------------------------------*/
#ifndef _MSC8101_H 
#define _MSC8101_H

#include "typedefs.h"

/*--------------------------------------------------------------------------*/
/*                DEFINITION OF MSC8101 Qbus MEMORY MAP                     */
/*--------------------------------------------------------------------------*/
/*****************************************************************************
*
*  QBUS PERIPHERALS
*  
* QBUS registers for HDI16, EFCOP and PIC are defined in a data
* structure called "t_qbusIMM". This is not part of the t_8101IMM data
* structure and should thus not affect it.
* To access the QBUS registers using this structure do the following:
*
* 1. Declare a global QBUS pointer (just as the IMM pointer). The code
* below assumes this msc8101.h is included:
*    t_qbusIMM *QBUS;                  QBUS pointer
*
* 2. Initialize the QBUS pointer (just as you would the IMM pointer):
*    QBUS = (t_qbusIMM*)(QBUS_BASE);    pointer to PIC registers
* where
*    #define QBUS_BASE   0x00F00000  QBus map base address
*
* 3. Access the QBUS registers in the application code using pointer to the
* QBUS structure, example:
*   QBUS->hcr = 0x0001;
*   QBUS->hpcr = 0x0003;
*   QBUS->hotx_msb = 0x0001;
*   QBUS->hotx_lsb = 0x0001;
*   QBUS->horx_msb = 0x0001;
*   QBUS->horx_lsb = 0x0001;
*   QBUS->fdir = 0x0001;
*   QBUS->fctl = 0x0003;
*   QBUS->fstr = 0x0001;
*   QBUS->elira = 0x0003;
*   QBUS->elirf = 0x0003;
*   QBUS->ipra = 0x0001;
*   QBUS->iprb = 0x0001;
*****************************************************************************/
typedef struct 
{
/* Host Interface Port (HDI16) */
    VUWord16 hcr;            /* HDI16 Host Control Register */
    VUByte   Reserved1[30];  /* Reserved area */
    VUWord16 hpcr;           /* HDI16 Host Port Control Register */
    VUByte   Reserved2[30];  /* Reserved area */
    VUWord16 hsr;            /* HDI16 Host Status Register */
    VUByte   Reserved3[30];  /* Reserved area */
    VUWord16 hcvr;           /* HDI16 Host Command Vector Register */
    VUByte   Reserved4[30];  /* Reserved area */
    VUWord32 hotx_msb;       /* HDI16 Host Transmit Register MSB */
    VUWord32 hotx_lsb;       /* HDI16 Host Transmit Register LSB */
    VUByte   Reserved5[24];  /* Reserved area */
    VUWord32 horx_msb;       /* HDI16 Host receive Register MSB */
    VUWord32 horx_lsb;       /* HDI16 Host receive Register LSB */
    VUByte   Reserved6[2904];/* Reserved area*/

/* Enhanced Filter Co-processor (EFCOP) */
    VUWord32 fdir;           /* EFCOP Data Input Register */
    VUByte   Reserved7[28];  /* Reserved area*/
    VUWord32 fdor;           /* EFCOP Data Output Register*/
    VUByte   Reserved8[28];  /* Reserved area*/
    VUWord32 fkir;           /* EFCOP K-Constant Register*/
    VUByte   Reserved9[28];  /* Reserved area*/
    VUWord16 fcnt;           /* EFCOP Filter Count Register*/
    VUByte   Reserved10[30]; /* Reserved area*/
    VUWord16 fctl;           /* EFCOP Control Register*/
    VUByte   Reserved11[30]; /* Reserved area*/
    VUWord16 facr;           /* EFCOP ALU Control Register*/
    VUByte   Reserved12[30]; /* Reserved area*/
    VUWord16 fdba;           /* EFCOP Data Base Address*/
    VUByte   Reserved13[30]; /* Reserved area*/
    VUWord16 fcba;           /* EFCOP Coefficient Base Address*/
    VUByte   Reserved14[30]; /* Reserved area*/
    VUWord16 fdch;           /* EFCOP Decimation/Channel Count Register*/
    VUByte   Reserved15[30]; /* Reserved area*/
    VUWord16 fstr;           /* EFCOP Status Register*/
    VUByte   Reserved16[3806];   /* Reserved area*/
    
/* Peripheral Interrupt Controller (PIC) */
    VUWord16 elira;          /* PIC's Edge/Level-Trig. Irq Priority Reg. A*/
    VUByte   Reserved17[6];  /* Reserved area*/
    VUWord16 elirb;          /* PIC's Edge/Level-Trig. Irq Priority Reg. B*/
    VUByte   Reserved18[6];  /* Reserved area*/
    VUWord16 elirc;          /* PIC's Edge/Level-Trig. Irq Priority Reg. C*/
    VUByte   Reserved19[6];  /* Reserved area*/
    VUWord16 elird;          /* PIC's Edge/Level-Trig. Irq Priority Reg. D*/
    VUByte   Reserved20[6];  /* Reserved area*/
    VUWord16 elire;          /* PIC's Edge/Level-Trig. Irq Priority Reg. E*/
    VUByte   Reserved21[6];  /* Reserved area*/
    VUWord16 elirf;          /* PIC's Edge/Level-Trig. Irq Priority Reg. F*/
    VUByte   Reserved22[6];  /* Reserved area*/
    VUWord16 ipra;           /* PIC's Irq Pending Register A*/
    VUByte   Reserved23[6];  /* Reserved area*/
    VUWord16 iprb;           /* PIC's Irq Pending Register B*/
    VUByte   Reserved24[0xe2c6]; /* Reserved area*/
    
/* Qbus Banks */
    VUWord16 qbusmr0;        /* Qbus Mask Register 0*/
    VUWord16 qbusbr0;        /* Qbus Base Address Register 0*/
    VUWord16 qbusmr1;        /* Qbus Mask Register 1*/
    VUWord16 qbusbr1;        /* Qbus Base Address Register 1*/
    VUWord16 qbusmr2;        /* Qbus Mask Register 2*/
    VUWord16 qbusbr2;        /* Qbus Base Address Register 2*/
    VUByte   Reserved25[244];/* Reserved area*/

} t_qbusIMM;

/******************************************************************************
*
*  PARAMETER RAM (PRAM) FOR EACH PERIPHERAL
*  
*  Each subsection contains protocol-specific PRAM for each peripheral,
*  followed by the PRAM common to all protocols for that peripheral.  These 
*  structs are used as needed in the main MSC8101 memory map structure.  Note 
*  that different modes of operation will require the use of different PRAM 
*  structs, and that certain structs may overlay and conflict with the use of 
*  other PRAM areas.  Consult the MSC8101 Reference Manual for details as to 
*  what is unavailable when certain protocols are run on certain peripherals.
*
******************************************************************************/

/*---------------------------------------------------------------------------*/
/*                   SERIAL COMMUNICATION CONTROLLER (SCC)                   */
/*---------------------------------------------------------------------------*/

/*----------*/
/* SCC HDLC */
/*----------*/
typedef struct 
{
    VUByte   Reserved1[4];   /* Reserved area */
    VUWord32 c_mask;         /* CRC constant */
    VUWord32 c_pres;         /* CRC preset */
    VUWord16 disfc;          /* discarded frame counter */
    VUWord16 crcec;          /* CRC error counter */
    VUWord16 abtsc;          /* abort sequence counter */
    VUWord16 nmarc;          /* nonmatching address rx cnt */
    VUWord16 retrc;          /* frame transmission counter. */
                             /* For FCC this area is reserved. */
    VUWord16 mflr;           /* maximum frame length reg */
    VUWord16 max_cnt;        /* maximum length counter */
    VUWord16 rfthr;          /* received frames threshold */
    VUWord16 rfcnt;          /* received frames count */
    VUWord16 hmask;          /* user defined frm addr mask */
    VUWord16 haddr1;         /* user defined frm address 1 */
    VUWord16 haddr2;         /* user defined frm address 2 */
    VUWord16 haddr3;         /* user defined frm address 3 */
    VUWord16 haddr4;         /* user defined frm address 4 */
    VUWord16 tmp;            /* temp */
    VUWord16 tmp_mb;         /* temp */
} t_HdlcScc_Pram;

/*--------------*/
/* SCC Ethernet */
/*--------------*/
typedef struct 
{
    VUWord32 c_pres;         /* CRC preset */
    VUWord32 c_mask;         /* CRC constant mask*/
    VUWord32 crcec;          /* CRC error counter */
    VUWord32 alec;           /* alignment error counter */
    VUWord32 disfc;          /* discarded frame counter */
    VUWord16 pads;           /* Short frame pad character. */
    VUWord16 ret_lim;        /* Retry limit threshold. */
    VUWord16 ret_cnt;        /* Retry limit counter. */
    VUWord16 mflr;           /* maximum frame length reg */
    VUWord16 minflr;         /* minimum frame length reg */
    VUWord16 maxd1;          /* max DMA1 length register. */
    VUWord16 maxd2;          /* max DMA2 length register. */
    VUWord16 maxd;           /* Rx max DMA. */
    VUWord16 dma_cnt;        /* Rx DMA counter. */
    VUWord16 max_b;          /* max buffer descriptor byte count. */
    VUWord16 gaddr1;         /* group address filter */
    VUWord16 gaddr2;         /* group address filter */
    VUWord16 gaddr3;         /* group address filter */
    VUWord16 gaddr4;         /* group address filter */
    VUWord32 tbuf0_data0;    /* Saved area 0, current frame. */
    VUWord32 tbuf0_data1;    /* Saved area 1, current frame. */
    VUWord32 tbuf0_rba0;
    VUWord32 tbuf0_crc;
    VUWord16 tbuf0_bcnt;
    VUWord16 paddr1_h;       /* physical address (MSB) */
    VUWord16 paddr1_m;       /* physical address */
    VUWord16 paddr1_l;       /* physical address (LSB) */
    VUWord16 p_per;          /* persistence */
    VUWord16 rfbd_ptr;       /* Rx first BD pointer. */
    VUWord16 tfbd_ptr;       /* Tx first BD pointer. */
    VUWord16 tlbd_ptr;       /* Tx last BD pointer. */
    VUWord32 tbuf1_data0;    /* Saved area 0, next frame. */
    VUWord32 tbuf1_data1;    /* Saved area 1, next frame. */
    VUWord32 tbuf1_rba0;
    VUWord32 tbuf1_crc;
    VUWord16 tbuf1_bcnt;
    VUWord16 tx_len;         /* tx frame length counter */
    VUWord16 iaddr1;         /* individual address filter. */
    VUWord16 iaddr2;         /* individual address filter. */ 
    VUWord16 iaddr3;         /* individual address filter. */
    VUWord16 iaddr4;         /* individual address filter. */
    VUWord16 boff_cnt;       /* back-off counter */
    VUWord16 taddr_h;        /* temp address (MSB) */
    VUWord16 taddr_m;        /* temp address */
    VUWord16 taddr_l;        /* temp address (LSB) */
} t_EnetScc_Pram;

/*-----------*/
/* SCC UART  */
/*-----------*/
typedef struct 
{
    VUByte   Reserved1[8];   /* Reserved area */
    VUWord16 max_idl;        /* maximum idle characters */
    VUWord16 idlc;           /* rx idle counter (internal) */
    VUWord16 brkcr;          /* break count register */
    VUWord16 parec;          /* Rx parity error counter */
    VUWord16 frmec;          /* Rx framing error counter */
    VUWord16 nosec;          /* Rx noise counter */
    VUWord16 brkec;          /* Rx break character counter */
    VUWord16 brkln;          /* Receive break length */
    VUWord16 uaddr1;         /* address character 1 */
    VUWord16 uaddr2;         /* address character 2 */
    VUWord16 rtemp;          /* temp storage */
    VUWord16 toseq;          /* Tx out of sequence char */
    VUWord16 cc[8];          /* Rx control characters */
    VUWord16 rccm;           /* Rx control char mask */
    VUWord16 rccr;           /* Rx control char register */
    VUWord16 rlbc;           /* Receive last break char */
} t_UartScc_Pram;

/*-----------------*/
/* SCC Transparent */
/*-----------------*/
typedef struct  
{
    VUWord32 c_pres;         /* CRC preset */
    VUWord32 c_mask;         /* CRC constant */
} t_TransScc_Pram;

/*------------*/
/* SCC Bisync */
/*------------*/
typedef struct  
{
    VUByte   Reserved1[4];   /* Reserved area */
    VUWord32 crcc;           /* CRC Constant Temp Value */
    VUWord16 prcrc;          /* Preset Receiver CRC-16/LRC */
    VUWord16 ptcrc;          /* Preset Transmitter CRC-16/LRC */
    VUWord16 parec;          /* Receive Parity Error Counter */
    VUWord16 bsync;          /* BISYNC SYNC Character */
    VUWord16 bdle;           /* BISYNC DLE Character */
    VUWord16 cc[8];          /* Rx control characters */
    VUWord16 rccm;           /* Receive Control Character Mask */
} t_BisyncScc_Pram;

/*-----------------*/
/* SCC Common PRAM */
/*-----------------*/
typedef struct 
{
    VUWord16 rbase;          /* RX BD base address */
    VUWord16 tbase;          /* TX BD base address*/ 
    VUByte   rfcr;           /* Rx function code */
    VUByte   tfcr;           /* Tx function code */
    VUWord16 mrblr;          /* Rx buffer length */
    VUWord32 rstate;         /* Rx internal state */
    VUWord32 rptr;           /* Rx internal data pointer*/ 
    VUWord16 rbptr;          /* rb BD Pointer */
    VUWord16 rcount;         /* Rx internal byte count */
    VUWord32 rtemp;          /* Rx temp */
    VUWord32 tstate;         /* Tx internal state */
    VUWord32 tptr;           /* Tx internal data pointer */
    VUWord16 tbptr;          /* Tx BD pointer */
    VUWord16 tcount;         /* Tx byte count */
    VUWord32 ttemp;          /* Tx temp */
    VUWord32 rcrc;           /* temp receive CRC */
    VUWord32 tcrc;           /* temp transmit CRC */
    union 
    {
        t_HdlcScc_Pram    h;
        t_EnetScc_Pram    e;
        t_UartScc_Pram    u;
        t_TransScc_Pram   t;
        t_BisyncScc_Pram  b;
    } SpecificProtocol;
    VUByte COMPLETE_SIZE_OF_DPRAM_PAGE[0x5c];
} t_Scc_Pram;

/*---------------------------------------------------------------------------*/
/*                      FAST COMMUNICATION CONTROLLER (FCC)                  */
/*---------------------------------------------------------------------------*/

/*----------*/
/* FCC HDLC */
/*----------*/
typedef struct 
{
    VUByte   Reserved1[8];   /* Reserved area */
    VUWord32 c_mask;         /* CRC constant */
    VUWord32 c_pres;         /* CRC preset */
    VUWord16 disfc;          /* discarded frame counter */
    VUWord16 crcec;          /* CRC error counter */
    VUWord16 abtsc;          /* abort sequence counter */
    VUWord16 nmarc;          /* nonmatching address rx cnt */
    VUWord32 max_cnt;        /* maximum length counter */
    VUWord16 mflr;           /* maximum frame length reg */
    VUWord16 rfthr;          /* received frames threshold */
    VUWord16 rfcnt;          /* received frames count */
    VUWord16 hmask;          /* user defined frm addr mask */
    VUWord16 haddr1;         /* user defined frm address 1 */
    VUWord16 haddr2;         /* user defined frm address 2 */
    VUWord16 haddr3;         /* user defined frm address 3 */
    VUWord16 haddr4;         /* user defined frm address 4 */
    VUWord16 tmp;            /* temp */
    VUWord16 tmp_mb;         /* temp */
} t_HdlcFcc_Pram;

/*--------------*/
/* FCC Ethernet */
/*--------------*/
typedef struct 
{
    VUWord32 stat_bus;       /* Internal use buffer. */
    VUWord32 cam_ptr;        /* CAM address. */
    VUWord32 c_mask;         /* CRC constant mask */
    VUWord32 c_pres;         /* CRC preset */
    VUWord32 crcec;          /* CRC error counter */
    VUWord32 alec;           /* alignment error counter */
    VUWord32 disfc;          /* discarded frame counter */
    VUWord16 ret_lim;        /* Retry limit threshold. */
    VUWord16 ret_cnt;        /* Retry limit counter. */
    VUWord16 p_per;          /* persistence */
    VUWord16 boff_cnt;       /* back-off counter */
    VUWord32 gaddr_h;        /* group address filter, high */
    VUWord32 gaddr_l;        /* group address filter, low */
    VUWord16 tfcstat;        /* out of sequece Tx BD staus. */
    VUWord16 tfclen;         /* out of sequece Tx BD length. */
    VUWord32 tfcptr;         /* out of sequece Tx BD data pointer. */
    VUWord16 mflr;           /* maximum frame length reg */
    VUWord16 paddr1_h;       /* physical address (MSB) */
    VUWord16 paddr1_m;       /* physical address */
    VUWord16 paddr1_l;       /* physical address (LSB) */
    VUWord16 ibd_cnt;        /* internal BD counter. */
    VUWord16 ibd_start;      /* internal BD start pointer. */
    VUWord16 ibd_end;        /* internal BD end pointer. */
    VUWord16 tx_len;         /* tx frame length counter */
    VUByte   ibd_base[0x20]; /* internal micro code usage. */
    VUWord32 iaddr_h;        /* individual address filter, high */
    VUWord32 iaddr_l;        /* individual address filter, low */
    VUWord16 minflr;         /* minimum frame length reg */
    VUWord16 taddr_h;        /* temp address (MSB) */
    VUWord16 taddr_m;        /* temp address */
    VUWord16 taddr_l;        /* temp address (LSB) */
    VUWord16 pad_ptr;        /* pad_ptr. */
    VUWord16 cf_type;        /* RESERVED (flow control frame type coding) */
    VUWord16 cf_range;       /* flow control frame range. */
    VUWord16 max_b;          /* max buffer descriptor byte count. */
    VUWord16 maxd1;          /* max DMA1 length register. */
    VUWord16 maxd2;          /* max DMA2 length register. */
    VUWord16 maxd;           /* Rx max DMA. */
    VUWord16 dma_cnt;        /* Rx DMA counter. */
    
    /* counter: */
    VUWord32 octc;           /* received octets counter. */
    VUWord32 colc;           /* estimated number of collisions */
    VUWord32 broc;           /* received good packets of broadcast address */
    VUWord32 mulc;           /* received good packets of multicast address */
    VUWord32 uspc;           /* received packets shorter then 64 octets. */
    VUWord32 frgc;           /* as uspc + bad packets */
    VUWord32 ospc;           /* received packets longer then 1518 octets. */
    VUWord32 jbrc;           /* as ospc + bad packets  */
    VUWord32 p64c;           /* received packets of 64 octets. */
    VUWord32 p65c;           /* received packets of 65-128 octets. */
    VUWord32 p128c;          /* received packets of 128-255 octets. */
    VUWord32 p256c;          /* received packets of 256-511 octets. */
    VUWord32 p512c;          /* received packets of 512-1023 octets. */
    VUWord32 p1024c;         /* received packets of 1024-1518 octets. */
    VUWord32 cam_buf;        /* cam respond internal buffer. */
    VUWord16 rfthr;          /* received frames threshold */
    VUWord16 rfcnt;          /* received frames count */
} t_EnetFcc_Pram;

/*-----------------*/
/* FCC Common PRAM */
/*-----------------*/
typedef struct 
{
    VUWord16 riptr;          /* Rx internal temporary data pointer. */
    VUWord16 tiptr;          /* Tx internal temporary data pointer. */
    VUWord16 Reserved0;      /* Reserved */
    VUWord16 mrblr;          /* Rx buffer length */
    VUWord32 rstate;         /* Rx internal state */
    VUWord32 rbase;          /* RX BD base address */
    VUWord16 rbdstat;        /* Rx BD status and control */
    VUWord16 rbdlen;         /* Rx BD data length */
    VUWord32 rdptr;          /* rx BD data pointer */
    VUWord32 tstate;         /* Tx internal state */
    VUWord32 tbase;          /* TX BD base address */
    VUWord16 tbdstat;        /* Tx BD status and control */
    VUWord16 tbdlen;         /* Tx BD data length */
    VUWord32 tdptr;          /* Tx  data pointer */
    VUWord32 rbptr;          /* rx BD pointer */
    VUWord32 tbptr;          /* Tx BD pointer */
    VUWord32 rcrc;           /* Temp receive CRC */
    VUWord32 Reserved_1[0x1];
    VUWord32 tcrc;           /* Temp transmit CRC */
    union                    /* Protocol-Specific parameter ram */
    {
        t_HdlcFcc_Pram    h;
        t_EnetFcc_Pram    e;
    } SpecificProtocol;      
} t_Fcc_Pram;


/*---------------------------------------------------------------------------*/
/*                  MULTICHANNEL COMMUNICATION CONTROLLER (MCC)              */
/*---------------------------------------------------------------------------*/
/******************************************************************************
* Note that each MCC uses multiple logical channels.  We first define the     *
* PRAM for a logical channel (which can be used in either HDLC or Transparent *
* mode;  wherever there are differences, it is specified), followed by the    *
* PRAM for an MCC itself.                                                     *
******************************************************************************/

/*---------------------*/   
/* MCC Logical Channel */
/*---------------------*/
typedef struct
{
    VUWord32 tstate;         /* Tx internal state. */
    VUWord32 zistate;        /* Zero insertion machine state. */
    VUWord32 zidata0;        /* Zero insertion high. */
    VUWord32 zidata1;        /* Zero insertion low. */
    VUWord16 tbdflags;       /* Tx internal BD flags. */
    VUWord16 tbdcnt;         /* Tx internal byte count . */
    VUWord32 tbdptr;         /* Tx internal data pointer. */
    VUWord16 intmask;        /* Interrupt mask flags. */
    VUWord16 chamr;          /* channel mode register. */
    VUWord32 tcrc;           /* Transparent: reserved. */
                             /* Hdlc: Temp receive CRC. */
    VUWord32 rstate;         /* Rx internal state. */
    VUWord32 zdstate;        /* Zero deletion machine state. */
    VUWord32 zddata0;        /* Zero deletion high. */
    VUWord32 zddata1;        /* Zero deletion low. */
    VUWord16 rbdflags;       /* Rx internal BD flags. */
    VUWord16 rbdcnt;         /* Rx internal byte count . */
    VUWord32 rbdptr;         /* Rx internal data pointer. */
    VUWord16 maxrlen;        /* Transparent: Max receive buffer length. */
                             /* Hdlc: Max receive frame length. */
    VUWord16 sync_maxcnt;    /* Transparent: Receive synchronization pattern */
                             /* Hdlc: Max length counter. */
    VUWord32 rcrc;           /* Transparent: reserved. */
                             /* Hdlc: Temp receive CRC. */
} t_Mch_Pram;

/*--------------------------------------*/
/* SS7 MCC Parameters for SS7 protocol. */
/*--------------------------------------*/
typedef struct
{
    VUWord16 n;         /* Interupt threshold in octet counting mode (N = 16) */
    VUWord16 n_cnt;   /* Temporary down counter for N, initialized to N value */
                         /* if STD bit is set these two above described */
                    /*  registers are considered as VUWord32 jtsttem register */
    VUWord16 d;          /* Signal units per signal unit error ratio */
    VUWord16 jttdelay;   /* FISU transmission delay in case STD = 1 otherwise */
                         /*   Temporary down counter for D which must be */
                         /*   initialized to D value */
    VUWord32 mask1;      /* Mask for SU filtering */
    VUWord16 mask2;      /* Mask for SU filtering   */
    VUWord16 ss7_opt;    /* SS7 configuration register */
    VUWord32 lrb1_tmp;   /* Temporary storage  */
    VUWord16 lrb2_tmp;   /* Temporary storage */
    VUWord16 suerm;      /* Signal unit error rate monitor counter */
    VUWord32 lrb1;       /* Four first bytes of last received signal unit */
    VUWord16 lrb2;       /* Fifth byte of last received signal unit */
    VUWord16 t;          /* SUERM threshold value */
    VUWord32 lhdr;     /* The BSN, FSN, FIB fields of last transmitted signal */
                         /*   unit and result CRC */
    VUWord32 lhdr_tmp;   /* Temporary storage */
    VUWord32 efsuc;      /* Error-free signal unit counter */
    VUWord32 suec;       /* Signal unit error counter */
    VUWord32 ss7state;   /* Internal state of SS7 controller */
    VUWord32 jtsrtmp;    /* Temporary storage fo Time Stamp Register */
    VUWord16 jtrdelay;   /* FISU transmission delay */
    VUWord16 Reserved[3];/* Reserved area   */
} t_SS7Mch_Pram;

/*--------------------------------------*/  
/* MCC Logical Channel Extra Parameters */
/*--------------------------------------*/
typedef struct
{
    VUWord16 tbase;          /* TxBD base address. */
    VUWord16 tbptr;          /* Current TxBD pointer. */
    VUWord16 rbase;          /* RxBD base address. */
    VUWord16 rbptr;          /* Current RxBD pointer. */
} t_MchXtra_Pram;

/*----------*/  
/* MCC PRAM */
/*----------*/
typedef struct
{
    VUWord32 mccbase;        /* A pointer to starting address of BD rings. */
    VUWord16 mccstate;       /* Controller state. */
    VUWord16 mrblr;          /* Maximum receive buffer length. */
    VUWord16 grfthr;         /* Global receive frame threshold. */
    VUWord16 grfcnt;         /* Global receive frame counter. */
    VUWord32 rinttmp;        /* Temp location for rx interrupt table entry. */
    VUWord32 data0;          /* Temporary location for holding data. */
    VUWord32 data1;          /* Temporary location for holding data. */
    VUWord32 tintbase;       /* Transmit interrupt table base address. */
    VUWord32 tintptr;        /* Transmit interrupt table pointer. */ 
    VUWord32 tinttmp;        /* Temp location for rx interrupt table entry. */
    VUWord16 sctpbase;       /* Pointer to the super channel transmit table */
    VUByte   res0[0x2];      /* Reserved area */
    VUWord32 c_mask32;       /* CRC constant. */
    VUWord16 xtrabase;       /* Pointer to the beginning of extra parameters  */
    VUWord16 c_mask16;       /* CRC constant. */
    VUWord32 rinttmp0;       /* Temp location for rx interrupt table entry. */ 
    VUWord32 rinttmp1;       /* Temp location for rx interrupt table entry. */
    VUWord32 rinttmp2;       /* Temp location for rx interrupt table entry. */
    VUWord32 rinttmp3;       /* Temp location for rx interrupt table entry. */
    VUWord32 rintbase0;      /* Rx interrupt table base address. */
    VUWord32 rintptr0;       /* Rx interrupt table pointer. */
    VUWord32 rintbase1;      /* Rx interrupt table base address. */
    VUWord32 rintptr1;       /* Rx interrupt table pointer. */
    VUWord32 rintbase2;      /* Rx interrupt table base address. */
    VUWord32 rintptr2;       /* Rx interrupt table pointer. */
    VUWord32 rintbase3;      /* Rx interrupt table base address. */
    VUWord32 rintptr3;       /* Rx interrupt table pointer. */
    VUByte   pad[0xa0];      /* Pad to fill 256 bytes */
} t_Mcc_Pram;


/*---------------------------------------------------------------------------*/
/*                              ATM PARAMETER RAM                            */
/*---------------------------------------------------------------------------*/

/*--------------------------------------*/ 
/* Address Compression parameters table */
/*--------------------------------------*/
typedef __PACK__ struct AddressCompressionPram   
{
    VUWord32 VptBase;        /* VP-level addressing table base address */
    VUWord32 VctBase;        /* VC-level addressing table base address */
    VUWord32 Vpt1Base;       /* VP1-level addressing table base address  */
    VUWord32 Vct1Base;       /* VC1-level addressing table base address */
    VUWord16 VpMask;         /* VP mask for address compression look-up */
} t_AddressCompressionPram;

/*-------------------------------*/
/* External CAM parameters table */
/*-------------------------------*/
typedef __PACK__ struct ExtCamPram  
{
    VUWord32 ExtCamBase;     /* Base address of the external CAM */
    VUByte   Reserved00[4];  /* Reserved */
    VUWord32 ExtCam1Base;    /* Base address of the external CAM1 */
    VUByte   Reserved01[6];  /* Reserved */
} t_ExtCamPram;

/*---------------------------*/  
/* ATM mode parameters table */
/*---------------------------*/
typedef __PACK__ struct AtmPram 
{
    VUByte   Reserved0[64];  /* Reserved */
    VUWord16 RxCellTmpBase;  /* Rx cell temporary base address */
    VUWord16 TxCellTmpBase;  /* Tx cell temporary base address */
    VUWord16 UdcTmpBase;     /* UDC temp base address (in UDC mode only) */
    VUWord16 IntRctBase;     /* Internal RTC base address */
    VUWord16 IntTctBase;     /* Internal TCT base address */
    VUWord16 IntTcteBase;    /* Internal ACT base address */
    VUByte   Reserved1[4];   /* reserved four bytes */
    VUWord32 ExtRctBase;     /* External RTC base address */
    VUWord32 ExtTctBase;     /* External TCT base address */
    VUWord32 ExtTcteBase;    /* External ACT base address */
    VUWord16 UeadOffset;     /* The offset in half-wordunits of the UEAD */
                             /*   entry in the UDC extra header. Should be */
                             /*   even address. If little-endian format is */
                            /*   used, the UeadOffset is of the little-endian */
                             /*   format. */
    VUByte   Reserved2[2];   /* Reserved */
    VUWord16 PmtBase;        /* Performance monitoring table base address */
    VUWord16 ApcParamBase;   /* APC Parameters table base address */
    VUWord16 FbpParamBase;   /* Free buffer pool parameters base address */
    VUWord16 IntQParamBase;  /* Interrupt queue parameters table base */
    VUByte   Reserved3[2];
    VUWord16 UniStatTableBase; /* UNI statistics table base */
    VUWord32 BdBaseExt;        /* BD ring base address extension */
    union                    /* Packing is required for this union */
    {
        t_AddressCompressionPram   AddrCompression;
        t_ExtCamPram               ExtCam;
    } AddrMapping;           /* Address look-up mechanism  */
    VUWord16 VciFiltering;   /* VCI filtering enable bits. If bit i is set, */
                             /*   the cell with VCI=i will be sent to the */
                             /*   raw cell queue. The bits 0-2 and 5 should */
                             /*   be zero. */
    VUWord16 Gmode;          /* Global mode */
    VUWord16 CommInfo1;      /* Information field associated w/last host comm */
    VUWord16 CommInfo2;      /* Information field associated w/last host comm */
    VUWord16 CommInfo3;      /* Information field associated w/last host comm */
    VUByte   Reserved201;    /* Reserved */
    VUByte   Reserved202;    /* Reserved */
    VUByte   Reserved203;    /* Reserved */
    VUByte   Reserved204;    /* Reserved */
    VUWord32 CRC32Preset;    /* Preset for CRC32 */
    VUWord32 CRC32Mask;      /* Constant mask for CRC32 */
    VUWord16 AAL1SnpTableBase; /* AAl1 SNP protection look-up table base */
    VUWord16 Reserved5;      /* Reserved */
    VUWord32 SrtsBase;       /* External SRTS logic base address. For AAL1 */
                             /*   only. Should be 16 bytes aligned */
    VUWord16 IdleBase;       /* Idle cell base address */
    VUWord16 IdleSize;       /* Idle cell size: 52, 56, 60, 64 */
    VUWord32 EmptyCellPayload; /* Empty cell payload (little-indian) */
    
    /* ABR specific only */
    VUWord32 Trm; /* Upper bound on time between F-RM cells for active source */
    VUWord16 Nrm; /* Controls the maximum data cells sent for each F-RM cell. */
    VUWord16 Mrm; /* Controls bandwidth between F-RM, B-RM and user data cell */
    VUWord16 Tcr;                /* Tag cell rate */
    VUWord16 AbrRxTcte;       /* ABR reserved area address (2-UWord16aligned) */
    
    /* The additional parameters which follow are required by the AAL1 */
    /* microcode as described in the AAL1 Chip Emulation Service (CES) */
    /* Enhancement */
    VUWord32 RxDesBaseExt;       /* External Rx queue descriptors */
                                 /*                   base address */
    VUWord32 RxUdcBase;          /* Rx UDC header table base address. */
                                 /*                   Only for AAL2 VC's  */
    VUWord32 TxUdcBase;          /* Tx UDC header table base address */
                                 /*                   for AAL2 VC's */
    VUWord32 RESERVED6[4];
    VUByte   Ocassr;             /* Outgoing CAS status Register */
    VUByte   Reserved7[3];
    VUWord16 AAL2PadBase;        /* AAL2 padding data base address */
    VUByte   RESERVED8[10];
    VUWord32 TcellTmpBaseExt;    /* Tx cell tmp base address */
    VUWord16 InCasBlockBase;     /* Incoming CAS block base   */
    VUWord16 OutCasBlockBase;    /* outgoing CAS block base */  
    VUWord16 AAL1IntStattBase;   /* AAL1 internal statistics table */
                                 /*                   base address */
    VUWord16 AAL1DummyCellBase;  /* AAL1 dummy cell base address */
    VUWord16 Catb;               /* CES adaptive threshold table */
                                 /*                   base address */
    VUWord16 RESERVED9; 
    VUWord32 AAL1ExtStattBase;   /* AAL1 external statistics */
                                 /*                   table base */
    VUByte   RESERVED10[8];
    VUWord32 UpcBase;            /* -Temp- UPC Policer base address  */
} t_Atm_Pram;

/*---------------------------------------------------------------------------*/
/*                      SERIAL MANAGEMENT CHANNEL  (SMC)                     */
/*---------------------------------------------------------------------------*/
typedef struct  
{
    VUWord16 rbase;          /* Rx BD Base Address */
    VUWord16 tbase;          /* Tx BD Base Address */
    VUByte   rfcr;           /* Rx function code */
    VUByte   tfcr;           /* Tx function code */
    VUWord16 mrblr;          /* Rx buffer length */
    VUWord32 rstate;         /* Rx internal state */
    VUWord32 rptr;           /* Rx internal data pointer */
    VUWord16 rbptr;          /* rb BD Pointer */
    VUWord16 rcount;         /* Rx internal byte count */
    VUWord32 rtemp;          /* Rx temp */
    VUWord32 tstate;         /* Tx internal state */
    VUWord32 tptr;           /* Tx internal data pointer */
    VUWord16 tbptr;          /* Tx BD pointer */
    VUWord16 tcount;         /* Tx byte count */
    VUWord32 ttemp;          /* Tx temp */
    
    /* SMC UART-specific PRAM */
    VUWord16 max_idl;        /* Maximum IDLE Characters */
    VUWord16 idlc;           /* Temporary IDLE Counter */
    VUWord16 brkln;          /* Last Rx Break Length */
    VUWord16 brkec;          /* Rx Break Condition Counter */
    VUWord16 brkcr;          /* Break Count Register (Tx) */
    VUWord16 r_mask;         /* Temporary bit mask   */
    VUWord32 SDMAtemp;       /* SDMA temp */
} t_Smc_Pram;


/*---------------------------------------------------------------------------*/
/*                            IDMA PARAMETER RAM                             */
/*---------------------------------------------------------------------------*/
typedef struct  
{
    VUWord16 ibase;          /* IDMA BD Base Address */
    VUWord16 dcm;            /* DMA channel mode register */
    VUWord16 ibdptr;         /* next bd ptr */
    VUWord16 DPR_buf;        /* ptr to internal 64 byte buffer */
    VUWord16 BUF_inv;        /* The quantity of data in DPR_buf */
    VUWord16 SS_max;         /* Steady State Max. transfer size */
    VUWord16 DPR_in_ptr;     /* write ptr for the internal buffer */
    VUWord16 sts;            /* Source Transfer Size */
    VUWord16 DPR_out_ptr;    /* read ptr for the internal buffer */
    VUWord16 seob;           /* Source end of burst */
    VUWord16 deob;           /* Destination end of burst */
    VUWord16 dts;            /* Destination Transfer Size */
    VUWord16 RetAdd;         /* return address when ERM==1 */
    VUWord16 Reserved;       /* reserved */
    VUWord32 BD_cnt;         /* Internal byte count */
    VUWord32 S_ptr;          /* source internal data ptr */
    VUWord32 D_ptr;          /* destination internal data ptr */
    VUWord32 istate;         /* Internal state */
} t_Idma_Pram;


/*-------------------------------------------------------------------*/
/*                    INTER-INTEGRATED CIRCUIT  (I2C)                */
/*-------------------------------------------------------------------*/
typedef struct 
{
    VUWord16 rbase;          /* RX BD base address */
    VUWord16 tbase;          /* TX BD base address */
    VUByte   rfcr;           /* Rx function code */
    VUByte   tfcr;           /* Tx function code */
    VUWord16 mrblr;          /* Rx buffer length */
    VUWord32 rstate;         /* Rx internal state */
    VUWord32 rptr;           /* Rx internal data pointer */
    VUWord16 rbptr;          /* rb BD Pointer */
    VUWord16 rcount;         /* Rx internal byte count */
    VUWord32 rtemp;          /* Rx temp */
    VUWord32 tstate;         /* Tx internal state */
    VUWord32 tptr;           /* Tx internal data pointer */
    VUWord16 tbptr;          /* Tx BD pointer */
    VUWord16 tcount;         /* Tx byte count */
    VUWord32 ttemp;          /* Tx temp */
} t_I2c_Pram;

/*---------------------------------------------------------------------------*/
/*                       SERIAL PERIPHERAL INTERFACE  (SPI)                  */
/*---------------------------------------------------------------------------*/
typedef struct  
{
    VUWord16 rbase;          /* Rx BD Base Address */
    VUWord16 tbase;          /* Tx BD Base Address */
    VUByte   rfcr;           /* Rx function code */
    VUByte   tfcr;           /* Tx function code */
    VUWord16 mrblr;          /* Rx buffer length */
    VUWord32 rstate;         /* Rx internal state */
    VUWord32 rptr;           /* Rx internal data pointer */
    VUWord16 rbptr;          /* Rx BD Pointer */
    VUWord16 rcount;         /* Rx internal byte count */
    VUWord32 rtemp;          /* Rx temp */
    VUWord32 tstate;         /* Tx internal state */
    VUWord32 tptr;           /* Tx internal data pointer */
    VUWord16 tbptr;          /* Tx BD pointer */
    VUWord16 tcount;         /* Tx byte count */
    VUWord32 ttemp;          /* Tx temp */
    VUByte   Reserved[8];
} t_Spi_Pram;

/*---------------------------------------------------------------------------*/
/*                      RISC TIMER PARAMETER RAM                             */
/*---------------------------------------------------------------------------*/
typedef struct  
{
    VUWord16 tm_base;        /* RISC timer table base adr */
    VUWord16 tm_ptr;         /* RISC timer table pointer */
    VUWord16 r_tmr;          /* RISC timer mode register */
    VUWord16 r_tmv;          /* RISC timer valid register */
    VUWord32 tm_cmd;         /* RISC timer cmd register */
    VUWord32 tm_cnt;         /* RISC timer internal cnt */
}  t_timer_pram;

/*--------------------------------------------------------------------------*/
/*                  ROM MICROCODE PARAMETER RAM AREA                        */
/*--------------------------------------------------------------------------*/
typedef struct  
{
    VUWord16 rev_num;        /* Ucode Revision Number  */
    VUWord16 d_ptr;          /* MISC Dump area pointer */
} t_ucode_pram;

/*--------------------------------------------------------------------------*/
/*                MAIN DEFINITION OF MSC8101 INTERNAL MEMORY MAP            */
/*--------------------------------------------------------------------------*/
typedef struct 
{

/* cpm_ram */
    t_Mch_Pram  mch_pram[256];      /* MCC logical channels parameter ram */
    VUByte      Reserved0[0x4000];  /* Reserved area */
    
/* DPR_BASE+0x8000 */
/*---------------------------------------------------------------------*/
/* A note about the pram union:                                        */
/* The pram area has been broken out three ways for clean access into  */
/* certain peripherals' spaces.  This arrangement allows programmers   */
/* flexibility of usage in terms of being able to change which         */
/* peripheral is being accessed by simply changing an array value.     */
/* Given the interweaving of certain peripherals' pram areas, this     */
/* would not be possible with only one large pram structure.           */
/*                                                                     */
/* SERIALS  - For accessing SCC, non-ATM FCC, and MCC pram             */
/* ATM      - For accessing ATM FCC pram                               */
/* STANDARD - For accessing timers, revnum, d_ptr, RAND, and the pram  */
/*            base pointers of the SMCs, IDMAs, SPI, and I2C           */
/*---------------------------------------------------------------------*/
    union 
    {
    
    /* for access to the PRAM structs for SCCs, FCCs, and MCCs */ 
        struct serials 
        {
            t_Scc_Pram scc_pram[4];
            t_Fcc_Pram fcc_pram[3];
            t_Mcc_Pram mcc_pram[2];
            VUByte     Reserved1[0x700];
        } serials;
        
    /* for access to ATM PRAM structs */
        struct atm
        {
	    VUByte Reserved2[0x400];
	    t_Atm_Pram atm_pram[2];
	    VUByte Reserved3[0xa00];  
        } atm;
        
    /* for access to the memory locations holding user-defined 
       base addresses of PRAM for SMCs, IDMA, SPI, and I2C. */     
       struct standard
       {
            VUByte scc1[0x100];
            VUByte scc2[0x100];
            VUByte scc3[0x100];
            VUByte scc4[0x100];
            VUByte fcc1[0x100];
            VUByte fcc2[0x100];
            VUByte fcc3[0x100];
            VUByte mcc1[0x80];
            VUByte Reserved_0[0x7c];
            VUByte smc1[0x2];
            VUByte idma1[0x2];
            VUByte mcc2[0x80];
            VUByte Reserved_1[0x7c];
            VUByte smc2[0x2];
            VUByte idma2[0x2];
            VUByte Reserved_2[0xfc];
            VUByte spi[0x2];
            VUByte idma3[0x2];
            VUByte Reserved_3[0xe0];
            VUByte timers[0x10];
            VUByte Rev_num[0x2];
            VUByte D_ptr[0x2];
            VUByte Reserved_4[0x4];
            VUByte rand[0x4];
            VUByte i2c[0x2];
            VUByte idma4[0x2];
            VUByte Reserved_5[0x500];
        } standard;
        
    } pram;
    
    VUByte  Reserved11[0x2000];      /* Reserved area */
    VUByte  cpm_ram_dpram_3[0x1000]; /* Internal RAM */
    VUByte  Reserved12[0x4000];      /* Reserved area */

/* DPR_BASE+0x10000*/
/* siu */
    VUWord32 siu_siumcr;         /* SIU Module Configuration Register */
    VUWord32 siu_sypcr;          /* System Protection Control Register */
    VUByte   Reserved13[0x6];    /* Reserved area */
    VUWord16 siu_swsr;           /* Software Service Register */

/* buses */
    VUByte   Reserved14[0x14];   /* Reserved area */
    VUWord32 bcr;                /* Bus Configuration Register */
    VUByte   ppc_acr;            /* Arbiter Configuration Register */
    VUByte   Reserved15[0x3];    /* Reserved area */
    VUWord32 ppc_alrh;           /* Arbitration Level Reg. (First clients) */
    VUWord32 ppc_alrl;           /* Arbitration Level Reg. (Next clients) */
    VUByte   lcl_acr;            /* LCL Arbiter Configuration Register */
    VUByte   Reserved16[0x3];    /* Reserved area */
    VUWord32 lcl_alrh;      /* LCL Arbitration Level Reg. (First clients) */
    VUWord32 lcl_alrl;      /* LCL Arbitration Level Register (Next clients) */
    VUWord32 tescr1;        /* PPC bus transfer error status control reg. 1 */
    VUWord32 tescr2;        /* PPC bus transfer error status control reg. 2 */
    VUWord32 ltescr1;       /* Local bus transfer error status control reg. 1 */
    VUWord32 ltescr2;       /* Local bus transfer error status control reg. 2 */
    VUWord32 pdtea;              /* PPC bus DMA Transfer Error Address */
    VUByte   pdtem;              /* PPC bus DMA Transfer Error MSNUM  */
    VUByte   Reserved17[0x3];    /* Reserved area */
    VUWord32 ldtea;              /* PPC bus DMA Transfer Error Address */
    VUByte   ldtem;              /* PPC bus DMA Transfer Error MSNUM  */
    VUByte   Reserved18[0x3];    /* Reserved area */
    VUWord32 pdmtea;             /* PPC bus DMA Transfer Error Address */
    VUByte   pdmter;             /* PPC bus DMA Transfer Error RQNUM */
    VUByte   Reserved95[0x3];    /* Reserved area */
    VUWord32 ldmtea;             /* Local PPC bus DMA Transfer Error Address */
    VUByte   ldmter;             /* Local PPC bus DMA Transfer Error RQNUM */
    VUByte   Reserved96[0x93];   /* Reserved area     */

/* memc */
    struct memc_regs {
        VUWord32 br;             /* Base Register */
        VUWord32 or;             /* Option Register */
    } memc_regs[12];
    VUByte   Reserved19[0x8];    /* Reserved area */
    VUWord32 memc_mar;           /* Memory Address Register */
    VUByte   Reserved20[0x4];    /* Reserved area */
    VUWord32 memc_mamr;          /* Machine A Mode Register */
    VUWord32 memc_mbmr;          /* Machine B Mode Register */
    VUWord32 memc_mcmr;          /* Machine C Mode Register */
    VUByte   Reserved21[0x8];    /* Reserved area */
    VUWord16 memc_mptpr;         /* Memory Periodic Timer Prescaler */
    VUByte   Reserved22[0x2];    /* Reserved area */
    VUWord32 memc_mdr;           /* Memory Data Register */
    VUByte   Reserved23[0x4];    /* Reserved area */
    VUWord32 memc_psdmr;         /* PowerPC Bus SDRAM machine Mode Register */
    VUByte   Reserved97[0x4];    /* Reserved area */
    VUByte   memc_purt;          /* PowerPC Bus assigned VUPM Refresh Timer */
    VUByte   Reserved24[0x3];    /* Reserved area */
    VUByte   memc_psrt;          /* PowerPC Bus assigned SDRAM Refresh Timer */
    VUByte   Reserved25[0xb];    /* Reserved area */
    VUWord32 memc_immr;          /* Internal Memory Map Register */
    VUByte   Reserved98[0x74];   /* Reserved area */

/* si_timers */
    VUWord16 si_timers_tmcntsc;  /* Time Counter Status and Control Register */
    VUByte   Reserved30[0x2];    /* Reserved area */
    VUWord32 si_timers_tmcnt;    /* Time Counter Register */
    VUByte   Reserved99[0x4];    /* Reserved area */
    VUWord32 si_timers_tmcntal;  /* Time Counter Alarm Register */
    VUByte   Reserved31[0x10];   /* Reserved area */
    VUWord16 si_timers_piscr;   /* Periodic Interrupt Status and Control Reg. */
    VUByte   Reserved32[0x2];    /* Reserved area */
    VUWord32 si_timers_pitc;     /* Periodic Interrupt Count Register */
    VUWord32 si_timers_pitr;     /* Periodic Interrupt Timer Register */
    VUByte   Reserved33[0x4b4];  /* Reserved area */

/* dma */
    VUWord32 dchcr[16];          /* DMA Channel Configuration Register */
    VUByte   Reserved100[0x40];  /* Reserved area */
    VUWord32 dma_dimr;           /* DMA Internal Mask Register */
    VUWord32 dma_dstr;           /* DMA Status Register */
    VUByte   dma_dtear;          /* DMA TEA Status Register */
    VUByte   Reserved102[0x3];   /* Reserved area */
    VUByte   dma_dpcr;           /* DMA Pin Configuration Register */
    VUByte   Reserved103[0x3];   /* Reserved area */
    VUWord32 dma_demr;           /* DMA External Mask Register */
    VUByte   Reserved104[0x6c];  /* Reserved area */
    struct dma_dcpram            /* DMA Channel Parameter RAM */
    {
        VUWord32 bd_addr;        /* Buffer Descriptor Address */
        VUWord32 bd_size;        /* Buffer Descriptor Transfer Size */
        VUWord32 bd_attr;        /* Buffer Descriptor Attributes */
        VUWord32 bd_bsize;       /* Buffer Descriptor Base Size */
    } dma_dcpram[64];
    
/* ic */
    VUWord16 ic_sicr;            /* Interrupt Configuration Register */
    VUByte   Reserved36[0x2];    /* Reserved area */
    VUWord32 ic_sivec;           /* CP Interrupt Vector Register */
    VUWord32 ic_sipnr_h;         /* Interrupt Pending Register (HIGH) */
    VUWord32 ic_sipnr_l;         /* Interrupt Pending Register (LOW) */
    VUWord32 ic_siprr;           /* SIU Interrupt Priority Register */
    VUWord32 ic_scprr_h;         /* Interrupt Priority Register (HIGH) */
    VUWord32 ic_scprr_l;         /* Interrupt Priority Register (LOW) */
    VUWord32 ic_simr_h;          /* Interrupt Mask Register (HIGH) */
    VUWord32 ic_simr_l;          /* Interrupt Mask Register (LOW) */
    VUWord32 ic_siexr;           /* External Interrupt Control Register */
    VUByte   Reserved37[0x18];   /* Reserved area */
    VUWord16 ic_sicr_ext;        /* SIU Interrupt Configuration Register */
    VUByte   Reserved106[0x2];   /* Reserved area */
    VUWord32 ic_sivec_ext;       /* CP Interrupt Vector Register */
    VUWord32 ic_sipnr_h_ext;     /* Interrupt Pending Register (HIGH) */
    VUWord32 ic_sipnr_l_ext;     /* Interrupt Pending Register (LOW) */
    VUWord32 ic_siprr_ext;       /* SIU Interrupt Priority Register */
    VUWord32 ic_scprr_h_ext;     /* Interrupt Priority Register (HIGH) */
    VUWord32 ic_scprr_l_ext;     /* Interrupt Priority Register (LOW) */
    VUWord32 ic_simr_h_ext;      /* Interrupt Mask Register (HIGH) */
    VUWord32 ic_simr_l_ext;      /* Interrupt Mask Register (LOW) */
    VUWord32 ic_siexr_ext;       /* External Interrupt Control Register */
    VUByte   Reserved107[0x18];  /* Reserved area */
     
/* clocks */
    VUWord32 clocks_sccr;        /* System Clock Control Register */
    VUByte   Reserved38[0x4];    /* Reserved area */
    VUWord32 clocks_scmr;        /* System Clock Mode Register */
    VUByte   Reserved39[0x4];    /* Reserved area */
    VUWord32 clocks_rsr;         /* Reset Status Register */
    VUByte   Reserved40[0x6C];   /* Reserved area */

/* io_ports */
    struct io_regs 
    {
        VUWord32 pdir;           /* Port A-D Data Direction Register */
        VUWord32 ppar;           /* Port A-D Pin Assignment Register */
        VUWord32 psor;           /* Port A-D Special Operation Register */
        VUWord32 podr;           /* Port A-D Open Drain Register */
        VUWord32 pdat;           /* Port A-D Data Register */
        VUByte   Reserved41[0xc];/* Reserved area */
    } io_regs[4];

/* cpm_timers */
    VUByte   cpm_timers_tgcr1;   /* Timer Global Configuration Register */
    VUByte   Reserved42[0x3];    /* Reserved area */
    VUByte   cpm_timers_tgcr2;   /* Timer Global Configuration Register */
    VUByte   Reserved43[0xb];    /* Reserved area */
    VUWord16 cpm_timers_tmr1;    /* Timer Mode Register */
    VUWord16 cpm_timers_tmr2;    /* Timer Mode Register */
    VUWord16 cpm_timers_trr1;    /* Timer Reference Register */
    VUWord16 cpm_timers_trr2;    /* Timer Reference Register */
    VUWord16 cpm_timers_tcr1;    /* Timer Capture Register */
    VUWord16 cpm_timers_tcr2;    /* Timer Capture Register */
    VUWord16 cpm_timers_tcn1;    /* Timer Counter */
    VUWord16 cpm_timers_tcn2;    /* Timer Counter */
    VUWord16 cpm_timers_tmr3;    /* Timer Mode Register */
    VUWord16 cpm_timers_tmr4;    /* Timer Mode Register */
    VUWord16 cpm_timers_trr3;    /* Timer Reference Register */
    VUWord16 cpm_timers_trr4;    /* Timer Reference Register */
    VUWord16 cpm_timers_tcr3;    /* Timer Capture Register */
    VUWord16 cpm_timers_tcr4;    /* Timer Capture Register */
    VUWord16 cpm_timers_tcn3;    /* Timer Counter */
    VUWord16 cpm_timers_tcn4;    /* Timer Counter */
    VUWord16 cpm_timers_ter[4];  /* Timer Event Register */
    VUByte   Reserved44[0x260];  /* Reserved area */

/* sdma general */
    VUByte   sdma_sdsr;          /* SDMA Status Register */
    VUByte   Reserved45[0x3];    /* Reserved area */
    VUByte   sdma_sdmr;          /* SDMA Mask Register */
    VUByte   Reserved46[0x3];    /* Reserved area */

/* idma */
    VUByte   idma_idsr1;         /* IDMA Status Register */
    VUByte   Reserved47[0x3];    /* Reserved area */
    VUByte   idma_idmr1;         /* IDMA Mask Register */
    VUByte   Reserved48[0x3];    /* Reserved area */
    VUByte   idma_idsr2;         /* IDMA Status Register */
    VUByte   Reserved49[0x3];    /* Reserved area */
    VUByte   idma_idmr2;         /* IDMA Mask Register */
    VUByte   Reserved50[0x3];    /* Reserved area */
    VUByte   idma_idsr3;         /* IDMA Status Register */
    VUByte   Reserved51[0x3];    /* Reserved area */
    VUByte   idma_idmr3;         /* IDMA Mask Register */
    VUByte   Reserved52[0x3];    /* Reserved area */
    VUByte   idma_idsr4;         /* IDMA Status Register */
    VUByte   Reserved53[0x3];    /* Reserved area */
    VUByte   idma_idmr4;         /* IDMA Mask Register */
    VUByte   Reserved54[0x2c3];  /* Reserved area */
    
/* fcc */
    struct fcc_regs 
    {
        VUWord32 gfmr;           /* FCC General Mode Register */
        VUWord32 psmr;           /* FCC Protocol Specific Mode Register */
        VUWord16 todr;           /* FCC Transmit On Demand Register */
        VUByte   Reserved55[0x2];/* Reserved area */
        VUWord16 dsr;            /* FCC Data Sync. Register */
        VUByte   Reserved56[0x2];/* Reserved area */
        VUWord32 fcce;           /* FCC Event Register */
        VUWord32 fccm;           /* FCC Mask Register */
        VUByte   fccs;           /* FCC Status Register */
        VUByte   Reserved57[0x3];/* Reserved area */
        VUWord32 ftirr;          /* FCC Transmit Partial Rate Register */
    } fcc_regs[3];
    VUByte   Reserved58[0x290];  /* Reserved area */
    
/* brgs 5-8 */
    VUWord32 brgs_brgc5;         /* BRG Configuration Register */
    VUWord32 brgs_brgc6;         /* BRG Configuration Register */
    VUWord32 brgs_brgc7;         /* BRG Configuration Register */
    VUWord32 brgs_brgc8;         /* BRG Configuration Register */
    VUByte   Reserved59[0x260];  /* Reserved area */
    
/* i2c */
    VUByte   i2c_i2mod;          /* IC Mode Register */
    VUByte   Reserved60[0x3];    /* Reserved area */
    VUByte   i2c_i2add;          /* IC Address Register */
    VUByte   Reserved61[0x3];    /* Reserved area */
    VUByte   i2c_i2brg;          /* IC BRG Register */
    VUByte   Reserved62[0x3];    /* Reserved area */
    VUByte   i2c_i2com;          /* IC Command Register */
    VUByte   Reserved63[0x3];    /* Reserved area */
    VUByte   i2c_i2cer;          /* IC Event Register */
    VUByte   Reserved64[0x3];    /* Reserved area */
    VUByte   i2c_i2cmr;          /* IC Mask Register */
    VUByte   Reserved65[0x14b];  /* Reserved area */
    
/* cpm */
    VUWord32 cpm_cpcr;           /* Communication Processor Command Register */
    VUWord32 cpm_rccr;           /* RISC Configuration Register */
    VUByte   Reserved66[0xe];    /* Reserved area  */
    VUWord16 cpm_rter;           /* RISC Timers Event Register */
    VUByte   Reserved67[0x2];    /* Reserved area */
    VUWord16 cpm_rtmr;           /* RISC Timers Mask Register */
    VUWord16 cpm_rtscr;          /* RISC Time-Stamp Timer Control Register */
    VUByte   Reserved108[0x2];   /* Reserved area */
    VUWord32 cpm_rtsr;           /* RISC Time-Stamp Register */
    VUByte   Reserved68[0xc];    /* Reserved area */

/* brgs 1-4 */
    VUWord32 brgs_brgc1;         /* BRG Configuration Register */
    VUWord32 brgs_brgc2;         /* BRG Configuration Register */
    VUWord32 brgs_brgc3;         /* BRG Configuration Register */
    VUWord32 brgs_brgc4;         /* BRG Configuration Register */
    
/* scc */
    struct scc_regs_8101
    {
        VUWord32 gsmr_l;         /* SCC General Mode Register */
        VUWord32 gsmr_h;         /* SCC General Mode Register */
        VUWord16 psmr;           /* SCC Protocol Specific Mode Register */
        VUByte   Reserved69[0x2];/* Reserved area */
        VUWord16 todr;           /* SCC Transmit-On-Demand Register */
        VUWord16 dsr;            /* SCC Data Synchronization Register */
        VUWord16 scce;           /* SCC Event Register */
        VUByte   Reserved70[0x2];/* Reserved area */
        VUWord16 sccm;           /* SCC Mask Register */
        VUByte   Reserved71;     /* Reserved area */
        VUByte   sccs;           /* SCC Status Register */
        VUByte   Reserved72[0x8];/* Reserved area */
    } scc_regs[4];
    
/* smc */
    struct smc_regs_8101
    {
        VUByte   Reserved73[0x2];/* Reserved area */
        VUWord16 smcmr;          /* SMC Mode Register */
        VUByte   Reserved74[0x2];/* Reserved area */
        VUByte   smce;           /* SMC Event Register */
        VUByte   Reserved75[0x3];/* Reserved area */
        VUByte   smcm;           /* SMC Mask Register */
        VUByte   Reserved76[0x5];/* Reserved area */
    } smc_regs[2];
    
/* spi */
    VUWord16 spi_spmode;         /* SPI Mode Register */
    VUByte   Reserved77[0x4];    /* Reserved area */
    VUByte   spi_spie;           /* SPI Event Register */
    VUByte   Reserved78[0x3];    /* Reserved area */
    VUByte   spi_spim;           /* SPI Mask Register */
    VUByte   Reserved79[0x2];    /* Reserved area */
    VUByte   spi_spcom;          /* SPI Command Register */
    VUByte   Reserved80[0x52];   /* Reserved area */
    
/* cpm_mux */
    VUByte   cpm_mux_cmxsi1cr;   /* CPM MUX SI Clock Route Register */
    VUByte   Reserved81;         /* Reserved area */
    VUByte   cpm_mux_cmxsi2cr;   /* CPM MUX SI Clock Route Register */
    VUByte   Reserved82;         /* Reserved area */
    VUWord32 cpm_mux_cmxfcr;     /* CPM MUX FCC Clock Route Register */
    VUWord32 cpm_mux_cmxscr;     /* CPM MUX SCC Clock Route Register */
    VUByte   cpm_mux_cmxsmr;     /* CPM MUX SMC Clock Route Register */
    VUByte   Reserved83;         /* Reserved area */
    VUWord16 cpm_mux_cmxuar;     /* CPM MUX VUTOPIA Address Register */
    VUByte   Reserved84[0x10];   /* Reserved area */

/* si */
    struct si_regs 
    {
        VUWord16 sixmr[4];       /* SI TDM Mode Registers A-D */
        VUByte   sigmr;          /* SI Global Mode Register */
        VUByte   Reserved85;     /* Reserved area */
        VUByte   sicmdr;         /* SI Command Register */
        VUByte   Reserved86;     /* Reserved area */
        VUByte   sistr;          /* SI Status Register */
        VUByte   Reserved87;     /* Reserved area */
        VUWord16 sirsr;          /* SI RAM Shadow Address Register */
        VUWord16 mcce;           /* MCC Event Register */
        VUByte   Reserved88[0x2];/* Reserved area */
        VUWord16 mccm;           /* MCC Mask Register */
        VUByte   Reserved89[0x2];/* Reserved area */
        VUByte   mccf;           /* MCC Configuration Register */
        VUByte   Reserved90[0x7];/* Reserved area */
    } si_regs[2];
    VUByte   Reserved91[0x4a0];  /* Reserved area */
    
/* si_ram */
    struct si_ram 
    {
        VUWord16 tx_siram[0x100];   /* SI Transmit Routing RAM */
        VUByte   Reserved92[0x200]; /* Reserved area */
        VUWord16 rx_siram[0x100];   /* SI Receive Routing RAM */
        VUByte   Reserved93[0x200]; /* Reserved area */
    } si_ram[2];
    VUByte   Reserved94[0x1000];    /* Reserved area */

}  t_8101IMM;

/*-------------------------------------------------------------------------*/
/*                     MSC8101 CONSTANTS AND DEFINITIONS                   */
/*-------------------------------------------------------------------------*/

#define PORTA   0               /* Index into Parallel I/O Regs Array */   
#define PORTB   1               /* Index into Parallel I/O Regs Array  */      
#define PORTC   2               /* Index into Parallel I/O Regs Array  */      
#define PORTD   3               /* Index into Parallel I/O Regs Array */
                                 
#define PAGE1   0               /* Index 1 into PRAM Array */
#define PAGE2   1               /* Index 2 into PRAM Array */
#define PAGE3   2               /* Index 3 into PRAM Array */
#define PAGE4   3               /* Index 4 into PRAM Array */

#define SCC1    0               /* SCC1 Index into SCC PRAM Array   */
#define SCC2    1               /* SCC2 Index into SCC PRAM Array  */         
#define SCC3    2               /* SCC3 Index into SCC PRAM Array  */ 
#define SCC4    3               /* SCC4 Index into SCC PRAM Array */

#define FCC1    0               /* FCC1 Index into FCC PRAM Array  */
#define FCC2    1               /* FCC2 Index into FCC PRAM Array  */        
#define FCC3    2               /* FCC3 Index into FCC PRAM Array */

#endif
