#ifndef CHARARRAY_H
#define CHARARRAY_H
#include <stdlib.h>
#include <stdio.h>

/*
 *@requires str is a valid pointer
 *@assigns nothing
 *@ensures i contains the size of str
*/
int size(char const str[]);

/*
 *@requires str is a valid pointer
 *@assigns new string of same size as str
 *@ensures new string is a copy of str
*/ 
char * copy(char const* str);

/*
 *@requires nothing
 *@assigns string str1+str2
 *@ensures str1 and str2 concatenated
*/
char * concatenate(char const* str1, char const* str2);

/*
 *@requires nothing
 *@assigns substring from begin and of size legnth (null char when out of index)
 *@ensures substring with perhpas null chars
*/
char * substring(char const* str, int const begin,int const length);
#endif //CHARARRAY_H