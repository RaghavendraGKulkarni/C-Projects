#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

#define STACK_EMPTY INT_MIN

struct node
{
    int element;
    struct node* next;
};
typedef struct node node;

struct stack
{
    node* top;
    int size;
};
typedef struct stack stack;

#endif // STACK_H_INCLUDED
