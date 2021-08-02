#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

#define QUEUE_EMPTY INT_MIN

struct queue
{
    int *arr;
    int front;
    int rear;
    size_t capacity;
};
typedef struct queue queue;

#endif // QUEUE_H_INCLUDED
