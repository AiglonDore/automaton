#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

stack * newStack()
{
    stack *tmp=malloc(sizeof(stack));
    if (tmp == NULL)
    {
        fprintf(stderr,"Unable to allocate memory. Major failure. Exiting program.\n");
        exit(EXIT_FAILURE);
    }
    tmp->m_capacity = 50;//Initial capacity
    tmp->m_size=0;
    tmp->m_values = malloc(50*sizeof(int));
    if (tmp->m_values == NULL)
    {
        fprintf(stderr,"Unable to allocate memory. Major failure. Exiting program.\n");
        free(tmp);
        exit(EXIT_FAILURE);
    }
    return tmp;
}

bool isEmpty(stack const *p)
{
    return p->m_size == 0;
}

void pushBack(stack *p, int const x)
{
    if (p->m_size == p->m_capacity)
    {
        p->m_capacity = 2*p->m_capacity +1;
        int *tmp = malloc(p->m_capacity * sizeof(int));
        if (tmp == NULL)
        {
            fprintf(stderr,"Unable to allocate memory. Major failure. Exiting program.\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < p->m_size; i++)
        {
            tmp[i]=p->m_values[i];
        }
        free(p->m_values);
        p->m_values = tmp;
    }
    p->m_values[p->m_size] = x;
    p->m_size++;  
}

int top(stack const *p)
{
    if (isEmpty(p))
    {
        fprintf(stderr,"Accessing top of empty stack. Aborting.\n");
        exit(EXIT_FAILURE);
    }
    return p->m_values[p->m_size-1];
}

int popBack(stack *p)
{
    int x = top(p);
    p->m_size--;
    if (p->m_size < p->m_capacity / 2)
    {
        p->m_capacity /=2;
        int *tmp = malloc(sizeof(int)*p->m_capacity);
        if (tmp == NULL)
        {
            fprintf(stderr,"Unable to allocate memory. Major failure. Exiting program.\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < p->m_size; i++)
        {
            tmp[i]=p->m_values[i];
        }
        free(p->m_values);
        p->m_values=tmp;
    }
    return x;
}

void deleteStack(stack *p)
{
    free(p->m_values);
    free(p);
    p =NULL;
}