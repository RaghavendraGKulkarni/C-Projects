#include "Queue.h"

void menu()
{
    printf("-----------------MENU-----------------\n");
    printf("1.Push an element into the queue\n");
    printf("2.Pop an element from the queue\n");
    printf("3.Print the front element of the queue\n");
    printf("4.Print the rear element of the queue\n");
    printf("5.Check if the queue is empty\n");
    printf("6.Exit\n");
    printf("Enter your choice:");
    return;
}

void push(queue *q,int element)
{
    if(q->capacity==0)
    {
        q->capacity=1;
        q->arr=(int*)malloc(sizeof(int));
    }
    else if((q->rear-q->front)%q->capacity==q->capacity-1)
    {
        if(q->front<=q->rear)
        {
            q->capacity++;
            q->arr=(int*)realloc(q->arr,(q->capacity)*sizeof(int));
        }
        else
        {
            q->capacity++;
            q->arr=(int*)realloc(q->arr,(q->capacity)*sizeof(int));
            printf("Reallocated\n");
            for(int i=q->capacity-2;i>=q->front;i--)
                q->arr[i+1]=q->arr[i];
            q->front++;
        }
    }
    q->rear=(q->rear+1)%q->capacity;
    q->arr[q->rear]=element;
    return;
}

void pop(queue *q)
{
    if(q->rear<0)
        printf("Queue is empty\n");
    else if(q->rear==q->front)
    {
        q->front=0;
        q->rear=-1;
    }
    else
        q->front=(q->front+1)%q->capacity;
    return;
}

int front(queue *q)
{
    if(q->rear<0)
        return QUEUE_EMPTY;
    return q->arr[q->front];
}

int rear(queue *q)
{
    if(q->rear<0)
        return QUEUE_EMPTY;
    return q->arr[q->rear];
}

bool empty(queue *q)
{
    return q->rear<0;
}

void deallocate(queue *q)
{
    free(q->arr);
    q->front=0;
    q->rear=-1;
    q->capacity=0;
    return;
}
