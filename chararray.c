#include "chararray.h"

#include <stdio.h>

int size(char const str[])
{
    int i = 0;
    while (str[i] != '\0')
    //Toute chaine de caractère finit par "\0". Comme l'indice augmente à chaque tour de boucle, on va forcément rencontrer un \0 à un moment
    {
        ++i;
    }
    return i;
}

char * copy(char const* str)
{
    int length=size(str);
    char *tmp=malloc(length*sizeof(char));
    if (tmp==NULL)
    {
        fprintf(stderr,"Unable to allocate memory. Major failure. Exiting program.");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < length; i++)
    {
        tmp[i]=str[i];
    }
    return tmp;
}

char * concatenate(char const* str1, char const* str2)
{
    int size1=size(str1), size2=size(str2);
    char *tmp = malloc((size1+size2)*sizeof(char));
    for (int i = 0; i < size1; i++)
    {
        tmp[i]=str1[i];
    }
    for (int i = 0; i < size2; i++)
    {
        tmp[i+size1] = str2[i];
    }
    return tmp;
}

/*
 *@requires nothing
 *@assigns nothing
 *@ensures min(a,b)
*/
int minimum(int const a, int const b)
{
    if (a>=b)
    {
        return b;
    }
    return a;
}

char * substring(char const* str, int const begin,int const length)
{
    int n=size(str);
    char *tmp=calloc(length,sizeof(char));
    for (int i = begin; i < minimum(n,begin+length); i++)
    {
        tmp[i-begin]=str[i];
    }
    return tmp;
}