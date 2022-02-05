#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loop.h"
#include "dot.h"
#include "automaton.h"
#include "bool.h"//Fournit un type bool

#define TOO_MANY_ARGUMENTS 2
#define NO_FILE 3
#define UNKOWN_OPTION 5

/*
 *@requires pointers are valid
 *@assigns *filename and *dot
 *@ensures options are read and *filename holds the file name and *dot is correct
*/
void scanOptions(int argc, char *argv[], char **filename, bool *dot)
{
    if (argc == 1)
    {
        fprintf(stderr,"No file to be read.\n");
        exit(NO_FILE);
    }
    if (argc > 3)
    {
        fprintf(stderr,"Only 1 or 2 arguments are expected.\n");
        exit(TOO_MANY_ARGUMENTS);
    }
    if (argc == 2)
    {
        *filename = argv[1];
    }
    else//Cas où argc = 3
    {
        if (!strcmp(argv[1],"-no-dot") || !strcmp(argv[1],"--no-dot"))
        {
            printf("Option \"-no-dot\" used. No DOT file will be produced.\n");
            *dot = false;
            *filename = argv[2];
        }
        else if (!strcmp(argv[2],"-no-dot")||!strcmp(argv[2],"--no-dot"))
        {
            printf("Option \"-no-dot\" used. No DOT file will be produced.\n");
            *dot = false;
            *filename = argv[1];
        }
        else
        {
            fprintf(stderr,"Unknown options used. Aborting task.\n");
            exit(UNKOWN_OPTION);
        }
    }
}

int main(int argc, char *argv[])
{
    printf("Welcome to automaton LR1!\n");
    char *filename = NULL;
    bool dot = true;
    scanOptions(argc,argv,&filename,&dot);
    automaton *automatonUsed = createAutomaton(filename);//Cette fonction vérifie automatiquement si la mémoire peut être allouée ou non. Le pointeur retourné est focément différent de NULL
    if (dot) processDot(automatonUsed,filename);
    processLoop(automatonUsed);
    clearAutomaton(automatonUsed);
    printf("See you next time! :)\n");
    return EXIT_SUCCESS;
}