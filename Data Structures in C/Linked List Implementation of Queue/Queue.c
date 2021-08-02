#include "Queue.h"

void menu()
{
    printf("----------------MENU----------------\n");
    printf("1.Push an element into the queue\n");
    printf("2.Pop an element from the queue\n");
    printf("3.Print the front element of the queue\n");
    printf("4.Print the rear element of the queue\n");
    printf("5.Check if the queue is empty\n");
    printf("6.Exit\n");
    printf("Enter your choice:");
    return;
}

node* getNode(int ele)
{
    node *t=(node*)malloc(sizeof(node));
    if(t==NULL)
    {
        printf("Ran out of memory\n\n");
        exit(0);
    }
    t->element=ele;
    t->next=NULL;
    return t;
}

void push(queue *q,int ele)
{
    node *t=getNode(ele);
    if(q->front==NULL && q->rear==NULL)
        q->front=t;
    else
        q->rear->next=t;
    q->rear=t;
    return;
}

void pop(queue *q)
{
    if(q->front==NULL && q->rear==NULL)
        printf("Queue is empty\n");
    else if(q->front!=q->rear)
    {
        node *t=q->front->next;
        free(q->front);
        q->front=t;
        q->size--;
    }
    else
    {
        free(q->front);
        q->front=NULL;
        q->rear=NULL;
    }
    return;
}

int front(queue *q)
{
    if(q->front==NULL && q->rear==NULL)
        return QUEUE_EMPTY;
    return q->front->element;
}

int rear(queue *q)
{
    if(q->front==NULL && q->rear==NULL)
        return QUEUE_EMPTY;
    return q->rear->element;
}

bool empty(queue *q)
{
    return q->front==NULL && q->rear==NULL;
}

void deallocate(queue *q)
{
    while(!empty(q))
        pop(q);
    return;
}
