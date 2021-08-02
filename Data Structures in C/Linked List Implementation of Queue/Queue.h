#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

#define QUEUE_EMPTY INT_MIN

struct node
{
    int element;
    struct node* next;
};
typedef struct node node;

struct queue
{
    node* front;
    node* rear;
    int size;
};
typedef struct queue queue;

#endif // QUEUE_H_INCLUDED
