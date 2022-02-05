#ifndef stack_H
#define stack_H

#include <stdlib.h>

#include "bool.h"

struct stack
{
    long long unsigned int m_capacity;
    long long unsigned int m_size;
    int *m_values;
};

typedef struct stack stack;

/*
 *@requires enough memory to construct a stack of variable capacity
 *@assigns new stack and array of size capacity to store values
 *@ensures tmp is a valid stack
*/
stack * newstack();

/*
 *@requires p is a valid pointer to a valid stack
 *@assigns nothing
 *@ensures status if *p is or not empty
*/
int isEmpty(stack const *p);

/*
 *@requires p is a valid pointer to a valid stack, if stack is full, more memory will be required
 *@assigns put x in p->m_values[p->size], can also assign more memory to store values
 *@ensures *p is still a valid stack
*/
void pushBack(stack *p, int const x);

/*
 *@requires *p is a valid stack and is not empty
 *@assigns nothing
 *@ensures top of stack *p
*/
int top(stack const *p);

/*
 *@requires *p is a valid stack
 *@assigns size of m_values if too big
 *@ensures top of stack and *p is still valid
*/
int popBack(stack *p);

/*
 *@requires p is a valid stack
 *@assigns free memory used by *p
 *@ensures *p doesn't exist anymore in memory and p = NULL
*/
void deletestack(stack *p);

#endif //stack_H