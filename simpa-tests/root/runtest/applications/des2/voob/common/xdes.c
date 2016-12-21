/* Driver for routine DES */

#include <stdio.h>
#include <string.h>

#include "des.h"

/* Converts character representing hexadecimal number to its integer
value in a machine-independent way. */
int hex2int(char ch)
{
	return ch >= '0' && ch <= '9' ? (int) (ch-'0') : (int) (ch-'A'+10);
}

/* Inverse of hex2int */
char int2hex(int i)
{
	return i <= 9 ? (char) (i+'0') : (char) (i-10+'A');
}

/* Reverse bits of type immense */
void reverse(immense *input)
{
	immense temp;
	int i;

	temp.r=temp.l=0L;
	for (i=1;i<=32;i++) {
		temp.r = (temp.r <<= 1) | ((*input).l & 1L);
		temp.l = (temp.l <<= 1) | ((*input).r & 1L);
		(*input).r >>= 1;
		(*input).l >>= 1;
	}
	(*input).r=temp.r;
	(*input).l=temp.l;
}

extern unsigned long bit[];

int main(int argc, char *argv[])
{
	int i,idirec,j,m,mm,nciphr,newkey;
	immense iin,iout,key;
	char hin[18],hkey[18],hout[18],hcmp[18];
	char verdct[8],txt[61],txt2[9];
	char *Finp_name, *Fout_name;
	FILE *Finp, *Fout;
	
	idirec=0;

	if (argc!=3) {
		printf("\n\t Usage : bin/coder.exe  inputfile  outputfile\n\n");
		exit(1);
	}
	Finp_name = argv[1];
	Fout_name = argv[2];
	
	if ((Finp = (FILE *) fopen(Finp_name,"r")) == NULL)
	{
		printf("cannot open the input file %s\n",Finp_name);
		return 1;
	}
#ifdef OUTPUT_TEXT
	if ((Fout = (FILE *) fopen(Fout_name,"w")) == NULL)
	{
		printf("cannot open the output file %s\n",Fout_name);
		return 1;
	}
#else
	if ((Fout = (FILE *) fopen(Fout_name,"wb")) == NULL)
	{
		printf("cannot open the output file %s\n",Fout_name);
		return 1;
	}
#endif

	fgets(txt,60,Finp);
#ifdef OUTPUT_TEXT
	fprintf(Fout,"\n%s",txt);
#endif
	for (;;) {
		fgets(txt,60,Finp);
#ifdef OUTPUT_TEXT
		fprintf(Fout,"%s",txt);
#endif
		fscanf(Finp,"%d %*s ",&nciphr);
		if (feof(Finp)) break;
		fgets(txt2,8,Finp);
		if (strncmp(txt2,"encode",6) == 0) idirec=0;
		if (strncmp(txt2,"decode",6) == 0) idirec=1;
		do {
#ifdef OUTPUT_TEXT
			fprintf(Fout,"%8s %20s %20s %15s\n","key","plaintext",
				"expected cipher","actual cipher");*/
#endif
			mm=16;
			if (nciphr < 16) mm=nciphr;
			nciphr -= 16;
			for (m=1;m<=mm;m++) {
				fscanf(Finp,"%s %s %s ",hkey+1,hin+1,hcmp+1);
				iin.l=iin.r=key.l=key.r=0L;
				for (i=1,j=9;i<=8;i++,j++) {
					iin.l=(iin.l <<= 4) | hex2int(hin[i]);
					key.l=(key.l <<= 4) | hex2int(hkey[i]);
					iin.r=(iin.r <<= 4) | hex2int(hin[j]);
					key.r=(key.r <<= 4) | hex2int(hkey[j]);
				}
				newkey=1;
				reverse(&iin);
				reverse(&key);
				des(iin,key,&newkey,idirec,&iout);
				reverse(&iout);
				for (i=8,j=16;i>=1;i--,j--) {
					hout[i]=int2hex((int) (iout.l & 0xf));
					hout[j]=int2hex((int) (iout.r & 0xf));
					iout.l >>= 4;
					iout.r >>= 4;
				}
				hout[17]='\0';
				strncmp(hcmp+1,hout+1,16) == 0 ?
					strcpy(verdct,"o.k.") :
					strcpy(verdct,"wrong");
#ifdef OUTPUT_TEXT
				fprintf(Fout,"%16s %16s %16s %16s %s\n",
					hkey+1,hin+1,hcmp+1,hout+1,verdct);
#else
                fwrite(hout+1,sizeof(char),16,Fout);
#endif
			}
			/* printf("Press RETURN to continue ...\n"); */
			/* getchar(); */
		} while (nciphr > 0);
	}
	return 0;
}
