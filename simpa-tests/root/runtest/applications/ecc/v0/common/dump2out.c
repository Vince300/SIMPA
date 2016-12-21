#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
 FILE *inp;
 char s[80];

 if( (inp = fopen(argv[1],"r")) == NULL)
  {
   fprintf(stderr,"error -> cannot open file %s\n",argv[1]);
   return 1;
  }

 fscanf(inp,"%s",s);
 fscanf(inp,"%s",s);

 s[0] = '0';

 if(atoi(s) == 1)
   printf("PASSED\n"); else
 if(atoi(s) == 2)
   printf("FAILED (diff)\n"); else
 printf("FAILED (unknown problem, possibly board's problem)\n");
 
 fclose (inp);

 return 0;
} 

