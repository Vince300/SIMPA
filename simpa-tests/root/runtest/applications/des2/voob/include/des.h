/* typedefs used for DES */

typedef struct IMMENSE {unsigned long l,r;} immense;
typedef struct GREAT {unsigned short l,c,r;} great;



/* function prototypes used for DES */

void des(immense inp, immense key,int *newkey,int isw,immense *out) ;
unsigned long getbit(immense source, int bitno, int nbits) ;
void ks(immense key, int n, great *kn) ;
void cyfun(unsigned long ir, great k, unsigned long *iout) ;
