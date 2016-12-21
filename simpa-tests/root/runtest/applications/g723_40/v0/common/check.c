#include <stdio.h>

extern int volatile *my_pp;


int check_data(unsigned char result[], unsigned char expected[],int n)
{
    int i;
    for( i=0; i<n; i++)
    {
		#ifdef _GENREF
		  expected[i] = result[i];
		#else
		  if((int)expected[i]<0)
		    expected[i]+=256;
		  if (result[i] != expected[i]) {
	   	  		return (i);
	   	  }
		#endif
    }
    return (-1);
}             
