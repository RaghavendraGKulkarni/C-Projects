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

int main()
{
    queue q={NULL,NULL,0};
    int choice,ele;
    do
    {
        menu();
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:printf("Enter the element:");
                    scanf("%d",&ele);
                    push(&q,ele);
                    printf("\n");
                    break;
            case 2:pop(&q);
                    printf("\n");
                    break;
            case 3:ele=front(&q);
                    if(ele==QUEUE_EMPTY)
                        printf("Queue is empty\n\n");
                    else
                        printf("Front of the queue contains %d\n\n",ele);
                    break;
            case 4:ele=rear(&q);
                    if(ele==QUEUE_EMPTY)
                        printf("Queue is empty\n\n");
                    else
                        printf("Rear of the queue contains %d\n\n",ele);
                    break;
            case 5:if(empty(&q))
                        printf("Yes,the queue is empty\n\n");
                    else
                        printf("No,the queue is not empty\n\n");
                    break;
            case 6:deallocate(&q);
                    break;
            default:printf("Please enter valid input\n\n");
                    break;
        }
    }while(choice!=6);
    return 0;
}
