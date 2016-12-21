/************************************************************************************************************************/
/* QA_XML HEADER                                                                                       			*/
/*                                                                                                                      */
/* AUTHORS : Yves GUERTE, 10 September 2004                                                                             */
/*                                                                                                                      */
/* CONTENT : Functions that output XML formatted data                                                                   */
/*                                                                                                                      */
/* 															*/
/*															*/
/************************************************************************************************************************/
#ifndef __QA_XML__
#define __QA_XML__

#include <stdarg.h>
#include "common_yacc_lex.h"

// Maximum number of imbricated XML objects
#define MAX_XML_LEVEL 100

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
void pxml_header(FILE *stream) ;



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
void pxml_begin_tag(FILE *stream, const char tag_name[], ...) ;



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
void pxml_end_tag(FILE *stream, const char tag_name[]) ;



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
void pxml_end_current_tag(FILE *stream) ;



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
void pxml_empty_tag(FILE *stream, const char tag_name[], ...) ;



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
void pxml_until_tag_level(FILE *stream, int level) ;



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
void pxml_until_in_tag(FILE *stream, const char tag_name[]) ;



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
void pxml_push_tags(const char tag_name[], ...) ;



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
void pxml_atomic_element(FILE *stream, const char name[], const char value[], ...) ;


#endif
// defined __QA_XML__
