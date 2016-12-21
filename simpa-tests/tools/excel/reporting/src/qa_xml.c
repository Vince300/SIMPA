/************************************************************************************************************************/
/* QA_XML MODULE                                                                                       			*/
/*                                                                                                                      */
/* AUTHORS : Yves GUERTE, 10 September 2004                                                                             */
/*                                                                                                                      */
/* CONTENT : Functions that output XML formatted data                                                                   */
/*                                                                                                                      */
/* 															*/
/*															*/
/************************************************************************************************************************/
#include <stdlib.h>
#include <stddef.h>
#include "qa_xml.h"



// ---------------- Configuration ----------------------------------------
// indentation at each level of inclusion in objects
static char indent[] = "  " ;



// ---------------- local variables ----------------------------------------
// level of inclusion in objects
static char     *xml_current[MAX_XML_LEVEL]   = { NULL } ;
static int      xml_level       = -1 ;



// ---------------- useful functions ----------------------------------------

// Removes surrounding quotes
void no_quote_surr(char s[]) {

        // beginning of s
        char *sb ;
        
        // computed new length of s
        int n ;
        
        // We skip beginning spaces
        for (sb = s ; *sb ; sb++) {
                if ((*sb != ' ') && (*sb != '\t')) break ;
        }
        
        // We skip ending spaces
        for (n = strlen(sb) - 1 ; n >= 0 ; n--) {
                if ((sb[n] != ' ') && (sb[n] != '\t')) break ;
        }
        // We remove surrounded quotes
        if (n > 1) {
                if (    ((sb[0] == '\'') && (sb[n] == '\''))
                     || ((sb[0] == '"')  && (sb[n] == '"' )) ) {
                        sb++ ;
                        n -= 2 ;
                }
        }
        // Do we have to move data ?
        if (sb != s)
                memmove(s, sb, n * sizeof(char)) ;
        
        s[n+1] = '\0' ;
        
} // end of no_quote_surr(char s[])

// --------------------------------------------------------
// print indentation spaces
static void print_indent(FILE *stream, int n) {
        int i ;
        for (i = 1 ; i <= n ; i++)
                fputs(indent, stream) ;
        return ;
} // end of print_indent(FILE *stream, int n)

// --------------------------------------------------------
// string to lowercase
static char *strduptolower(const char s[]) {
        int   i ;
        int   l = strlen(s) ;
        char *r = malloc(sizeof(char) * l + 1) ;
        
        for (i = 0 ; i<= l ; i++) {
                r[i] = tolower(s[i]) ;
        }
        r[l+1] = '\0' ;
        return r ;
}
// --------------------------------------------------------
static void strtolower(char s[]) {
        char *r = s ;
        
        while (*r) {
                *r = tolower(*r) ;
                r++ ;
        }
}


/**************************************************************************************************************************
* FUNCTION:     pxml_header
*
* DESCRIPTION:  prints to file the header of an XML format file
*
* INPUTS:       file handler
*
* OUTPUTS:      
*
* RETURNS:      
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         10 September 2004
***************************************************************************************************************************/
void pxml_header(FILE *stream) {
        
        fputs("<?xml version=\"1.0\" ?>\n", stream) ;
        return ;
}



/**************************************************************************************************************************
* FUNCTION:     pxml_begin_tag
*
* DESCRIPTION:  prints to an XML formatted file the beginning tag of an object
*
* INPUTS:       file handler, tag name, optional XML object parameters
*
* OUTPUTS:      
*
* RETURNS:      
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         10 September 2004
***************************************************************************************************************************/
void pxml_begin_tag(FILE *stream, const char tag_name[], ...) {
        
        // optional supplementary args are strings
        va_list pa = {} ;
        
        char *p1, *p2 ;
        
        va_start(pa, tag_name) ;
        
        // We indent
        print_indent(stream, xml_level + 1) ;
        
        fputs("<", stream) ;
        fputs(tag_name, stream) ;
        
        // We print optional tag parameters
        while ((p1 = va_arg(pa, char*)) != NULL) {
                if ((p2 = va_arg(pa, char*)) != NULL) {
                        p2 = strdup(p2) ;
                        no_quote_surr(p2) ;
                        fputs(" ",      stream) ;
                        fputs(p1,       stream) ;
                        fputs("=\"",    stream) ;
                        fputs(p2,       stream) ;
                        fputs("\"",     stream) ;
                        free(p2) ;
                }
        }
        fputs(">\n", stream) ;
        fflush(stream);
        xml_level++;
        xml_current[xml_level] = strdup(tag_name) ;
        
        va_end(pa) ;
        return ;
}



/**************************************************************************************************************************
* FUNCTION:     pxml_end_tag
*
* DESCRIPTION:  prints to an XML formatted file the end tag of an object
*
* INPUTS:       file handler, tag name
*
* OUTPUTS:      warning if the ending tag does not correspond to the current object
*
* RETURNS:      
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         10 September 2004
***************************************************************************************************************************/
void pxml_end_tag(FILE *stream, const char tag_name[]) {
        
        char *current ;
        
        if (xml_level >= 0) {
                current = xml_current[xml_level--] ;
                
                print_indent(stream, xml_level + 1) ;
                fputs("</",     stream) ;
                fputs(tag_name, stream) ;
                fputs(">\n",    stream) ;
                
                if (strcasecmp(tag_name, current) != 0) {
                        fprintf(stderr, "WARNING: closing %s instead of %s.\n", tag_name, current ) ;
                }
                free(current) ;
        }
        else {
                fprintf(stderr, "WARNING: no tag to close\n") ;
        }
        fflush(stream);
        return ;
}



/**************************************************************************************************************************
* FUNCTION:     pxml_end_current_tag
*
* DESCRIPTION:  prints to an XML formatted file the end tag of the current object
*
* INPUTS:       file handler
*
* OUTPUTS:      warning if there is no current object
*
* RETURNS:      
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         10 September 2004
***************************************************************************************************************************/
void pxml_end_current_tag(FILE *stream) {
        
        char *current ;

        if (xml_level >= 0) {
                current = xml_current[xml_level--] ;
                print_indent(stream, xml_level + 1) ;
                fputs("</",     stream) ;
                fputs(current,  stream) ;
                fputs(">\n",    stream) ;
                free(current) ;
        }
        else {
                fprintf(stderr, "WARNING: no tag to close\n") ;
        }
        fflush(stream);
        return ;
}



/**************************************************************************************************************************
* FUNCTION:     pxml_empty_tag
*
* DESCRIPTION:  prints to an XML formatted file an object with optional parameters but no content
*
* INPUTS:       file handler, tag name, optional XML object parameters
*
* OUTPUTS:      
*
* RETURNS:      
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         10 September 2004
***************************************************************************************************************************/
void pxml_empty_tag(FILE *stream, const char tag_name[], ...) {
        
        // optional supplementary args are strings
        va_list pa = {} ;
        char *p1, *p2 ;
        
        va_start(pa, tag_name) ;
        
        // We indent
        print_indent(stream, xml_level + 1) ;
        
        fputs("<",      stream) ;
        fputs(tag_name, stream) ;
        
        // We print optional tag parameters
        while ((p1 = va_arg(pa, char *)) != NULL) {
                if ((p2 = va_arg(pa, char *)) != NULL) {
                        p2 = strdup(p2) ;
                        no_quote_surr(p2) ;
                        fputs(" ",      stream) ;
                        fputs(p1,       stream) ;
                        fputs("=\"",    stream) ;
                        fputs(p2,       stream) ;
                        fputs("\"",     stream) ;
                        free(p2) ;
                }
        }
        fputs("/>\n", stream) ;
        
        va_end(pa) ;
        return ;
}



/**************************************************************************************************************************
* FUNCTION:     pxml_until_tag_level
*
* DESCRIPTION:  prints to an XML formatted file the end tags of the current and all the containing objects
*               until the object level in parameters
*
* INPUTS:       file handler, object level
*
* OUTPUTS:      
*
* RETURNS:      
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         10 September 2004
***************************************************************************************************************************/
void pxml_until_tag_level(FILE *stream, int level) {

        char *current ;
        int  i ;
        
        for (i = xml_level ; i == level + 1 ; i--) {
                
                current = xml_current[xml_level--] ;
                
                // We indent
                print_indent(stream, xml_level + 1) ;
                
                fputs("</",     stream) ;
                fputs(current,  stream) ;
                fputs(">\n",    stream) ;
                free(current) ;
        }
        fflush(stream);
        return ;
}



/**************************************************************************************************************************
* FUNCTION:     pxml_until_in_tag
*
* DESCRIPTION:  prints to an XML formatted file the end tags of the current and all the containing objects
*               until the object name in parameters
*
* INPUTS:       file handler, tag name
*
* OUTPUTS:      
*
* RETURNS:      
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         10 September 2004
***************************************************************************************************************************/
void pxml_until_in_tag(FILE *stream, const char tag_name[]) {
        
        char *current ;
        
        if (xml_level >= 0) {
        
                current = xml_current[xml_level] ;
                
                while (strcasecmp(current, tag_name) != 0) {
                        pxml_end_current_tag(stream) ;
                        if (xml_level < 0) break ;
                        current = xml_current[xml_level] ;
                }
        }
        fflush(stream);
        return ;
}



/**************************************************************************************************************************
* FUNCTION:     pxml_push_tags
*
* DESCRIPTION:  push name in the heap of name of encapsuled objects. As beginning an object but without file output.
*
* INPUTS:       tag name, optional list of others tag names.
*
* OUTPUTS:      
*
* RETURNS:      
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         10 September 2004
***************************************************************************************************************************/
void pxml_push_tags(const char tag_name[], ...) {
        
        // tmp tag_name
        const char *t = tag_name ;
        
        // optional supplementary args are strings
        va_list pa = {} ;

        va_start(pa, tag_name) ;

        while (t != NULL) {
                
                xml_level++;
                xml_current[xml_level] = strdup(t) ;
                
                t = va_arg(pa, char *) ;
        }
        
        va_end(pa) ;
        return ;
}



/**************************************************************************************************************************
* FUNCTION:     pxml_atomic_element
*
* DESCRIPTION:  prints to an XML formatted file an object with a simple string content
*               
* INPUTS:       file handler, object name, object value
*
* OUTPUTS:      
*
* RETURNS:      
***************************************************************************************************************************
* RESTRICTIONS:
* BUGS:
***************************************************************************************************************************
* AUTHOR:       Yves GUERTE
* DATE:         10 September 2004
***************************************************************************************************************************/
void pxml_atomic_element(FILE *stream, const char name[], const char value[], ...) {
        
        // optional supplementary args are strings
        va_list pa = {} ;
        
        char *p1, *p2 ;
        
        va_start(pa, value) ;
        
        // We indent
        print_indent(stream, xml_level + 1) ;
        
        fputs("<", stream) ;
        fputs(name, stream) ;
        
        // We print optional tag parameters
        while ((p1 = va_arg(pa, char*)) != NULL) {
                if ((p2 = va_arg(pa, char*)) != NULL) {
                        p2 = strdup(p2) ;
                        no_quote_surr(p2) ;
                        fputs(" ",      stream) ;
                        fputs(p1,       stream) ;
                        fputs("=\"",    stream) ;
                        fputs(p2,       stream) ;
                        fputs("\"",     stream) ;
                        free(p2) ;
                }
        }
        fputs(">",      stream) ;
        fputs(value,    stream) ;
        fputs("</",     stream) ;
        fputs(name,     stream) ;
        fputs(">\n",    stream) ;
        fflush(stream);
        
        va_end(pa) ;
        return ;
}

// ------------------ End of library ----------------------------------

