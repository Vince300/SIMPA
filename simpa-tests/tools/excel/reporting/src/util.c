/************************************************************************************************************************/
/* CMP_OUT MODULE                                                                                                       */
/*                                                                                                                      */
/* AUTHORS : Yves GUERTE, 29 November 2004                                                                              */
/*                                                                                                                      */
/* CONTENT : Useful functions                                                                                           */
/*                                                                                                                      */
/*                                                                                                                      */
/*                                                                                                                      */
/************************************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>






/**************************************************************************************************************************
* FUNCTION:     strp_cmp
*
* DESCRIPTION:  strcmp for 2 pointers to strings,
*               used by qsort in norm_cc_opt for sorting an array of strings
*
* INPUTS:       2 pointers to strings
*
* OUTPUTS:      
*
* RETURNS:      -1 / 0 / 1 in the same way than strcmp
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         30 August 2004
***************************************************************************************************************************/
int strp_cmp(const void *s1, const void *s2) {
        return strcmp(*(char**)s1, *(char**)s2);
}


/**************************************************************************************************************************
* FUNCTION:     my_malloc
*
* DESCRIPTION:  used to trace malloc calls
*
* INPUTS:       size_t
*
* OUTPUTS:      size required
*
* RETURNS:      void*
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         29 Nvember 2004
***************************************************************************************************************************/
void *my_malloc(const size_t s, const int l) {
	fprintf(stderr, "malloc(%d) line %d\n", s, l);
	return malloc(s);
}


/**************************************************************************************************************************
* FUNCTION:     basename
*
* DESCRIPTION:  like unix basename
*
* INPUTS:       pointer to string that is a path
*
* OUTPUTS:      
*
* RETURNS:      
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         15 February 2005
***************************************************************************************************************************/
// Characters for directories separators in a path
const char SEPARATORS[] = "/\\";

const char *basename(const char *s) {
    int i = strlen(s) - 1;
    const char *r = s;
    
    while (i >= 0) {
        if (strchr(SEPARATORS, r[i]) != NULL) {
            return(r+i+1);
        }
        i--;
    }
    return(r);
}


/**************************************************************************************************************************
* FUNCTION:     same_dirname
*
* DESCRIPTION:  search if last dirname of 2 paths are the same
*
* INPUTS:       2 pointers to strings
*
* OUTPUTS:      
*
* RETURNS:      0 / 1 if true
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         15 February 2005
***************************************************************************************************************************/

int same_dirname(const char *s1, const char *s2) {
    int is_same = 1;
    int l1 = strlen(s1);
    int i  = l1 - 1;
    int l2 = strlen(s2);
    const char *ss1, *ss2;
    
    if (l1 > l2) {
        ss1 = s1 + (l1 - l2);
        ss2 = s2;
        // We will use only l
        i = l2 - 1;
    }
    else {
        ss1 = s1;
        ss2 = s2 + (l2 - l1);
    }
    
    while (i >= 0) {
        // is current char a separator ?
        if (strchr(SEPARATORS, ss1[i]) != NULL) {
            // a separator too ?
            if (strchr(SEPARATORS, ss2[i]) != NULL) {
                // same dirname
                break;
            }
            else {
                is_same = 0;
                break;
            }
        }
        if (ss1[i] != ss2[i]) {
            is_same = 0;
            break;
        }
        i--;
    }
    return is_same;
}



