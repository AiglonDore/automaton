#ifndef LOOP_H
#define LOOP_H
#include<stdio.h>
#include "automaton.h"
#include "chararray.h"

/*
 *@requires used must be a valid automaton
 *@assigns states of the automaton (used->states)
 *@ensures used is still an automaton
*/
void processLoop(automaton *used);

/*
 *@requires automaton must be valid and its actions can only return 0, 1, 2 or 3
 *@assigns states of aut
 *@ensures automaton is still valid
*/
void processWord(automaton * used, char *word);
#endif //LOOP_H