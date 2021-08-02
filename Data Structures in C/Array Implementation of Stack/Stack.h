#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

#define STACK_EMPTY INT_MIN

struct stack
{
    int *arr;
    int size;
    int capacity;
};
typedef struct stack stack;

#endif // STACK_H_INCLUDED
