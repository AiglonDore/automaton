#ifndef AUTOMATON_H
#define AUTOMATON_H
#include <stdlib.h>
#include <stdio.h>

#include "stack.h"
#include "bool.h"
struct automaton
{
    int nbStates;
    int **actions;
    int *reduit1;
    char *reduit2;
    int **decale;
    int **branchement;
    stack *states;
};

typedef struct automaton automaton;

/*
 *@requires filename is a valid pointer
 *@assigns automaton and the whole program with the others functions
 *@ensures automaton is correctly created
*/
automaton *createAutomaton(char const *filename);

/*
 *@requires aut is a valid automaton
 *@assigns free memory used by automaton
 *@ensures used memory for aut is now free
*/
void clearAutomaton(automaton *aut);

/*
 *@requires tmp must be valid
 *@assigns tmp->nbStates, tmp->reduit1, tmp->reduit2, tmp->actions
 *@ensures checks if file is a valid automaton file
*/
bool readFile(FILE * const file, automaton *tmp);

/*
 *@requires automaton is valid and its states stack exists
 *@assigns automaton->stack
 *@ensures automaton is still valid and its stack of states is empty
*/
void clearStatesStack(automaton *aut);
#endif //AUTOMATON_H