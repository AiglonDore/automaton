#ifndef DOT_H
#define DOT_H
#include<stdio.h>
#include "automaton.h"
/*
 *@requires atm is valid and filename has extension .aut
 *@assigns contruct new filename for dot. Assigns errno is case of failure to open dot file
 *@ensures file .dot has the description of the automaton if dot file is correctly opened. Ensures that *atm is still valid
*/
void processDot(automaton const* atm,char const *filename);
#endif //DOT_H