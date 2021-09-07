#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct heap
{
    int *arr;
    int size;
    int capacity;
};
typedef struct heap heap;

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
    printf("1.Insert an element into the Min Heap\n");
    printf("2.Delete given element from the Min Heap\n");
    printf("3.Delete the minimum element from the Min Heap\n");
    printf("4.Print the minimum element in the Min Heap\n");
    printf("5.Check if the Min Heap is empty\n");
    printf("6.Exit\n");
    printf("Enter your choice:");
    return;
}

void heapify(heap *h)
{
    int i,v,k,j;
    bool isHeap;
    for(i=h->size/2;i>0;i--)
    {
        k=i;
        v=h->arr[k];
        isHeap=false;
        while(!isHeap && 2*k<=h->size)
        {
            j=2*k;
            if(j<h->size && h->arr[j]>h->arr[j+1])
                j++;
            if(v<=h->arr[j])
                isHeap=true;
            else
            {
                h->arr[k]=h->arr[j];
                k=j;
            }
        }
        h->arr[k]=v;
    }
    return;
}

void push(heap *h,int element)
{
    if(h->size+1==h->capacity)
    {
        h->capacity++;
        h->arr=(int*)realloc(h->arr,h->capacity*sizeof(int));
    }
    h->arr[++h->size]=element;
    heapify(h);
    printf("\n");
    return;
}

void enqueue(queue *q,int ele)
{
    node *t=(node*)malloc(sizeof(node));
    if(t==NULL)
    {
        printf("Ran out of memory\n\n");
        exit(0);
    }
    t->element=ele;
    t->next=NULL;
    if(q->front==NULL && q->rear==NULL)
        q->front=t;
    else
        q->rear->next=t;
    q->rear=t;
    return;
}

void dequeue(queue *q)
{
    if(q->front==NULL && q->rear==NULL)
        return;
    if(q->front!=q->rear)
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
        return 0;
    return q->front->element;
}

bool queueEmpty(queue *q)
{
    return q->front==NULL && q->rear==NULL;
}

int search(heap *h,int element)
{
    queue q={NULL,NULL,0};
    int cur,index=-1;
    enqueue(&q,1);
    while(!queueEmpty(&q) && index<0)
    {
        cur=front(&q);
        dequeue(&q);
        if(h->arr[cur]==element)
            index=cur;
        else if(h->arr[cur]>element)
        {
            if(2*cur<=h->size)
                enqueue(&q,2*cur);
            if(2*cur+1<=h->size)
                enqueue(&q,2*cur+1);
        }
    }
    return index;
}

void pop(heap *h,int index)
{
    int temp;
    temp=h->arr[index];
    h->arr[index]=h->arr[h->size];
    h->arr[h->size]=temp;
    h->size--;
    heapify(h);
    return;
}

void popGivenElement(heap *h,int element)
{
    int index=search(h,element);
    if(index<0)
        printf("Element not present in the heap\n\n");
    else
        pop(h,index);
    printf("\n");
    return;
}

void popMaximum(heap *h)
{
    pop(h,1);
    printf("\n");
    return;
}

int maximum(heap *h)
{
    return h->arr[1];
}

bool empty(heap *h)
{
    return h->size==0;
}

void deallocate(heap *h)
{
    free(h->arr);
    h->size=0;
    h->capacity=0;
    return;
}

int main()
{
    heap h={(int*)malloc(sizeof(int)),0,1};
    int choice,ele;
    do
    {
        menu();
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:printf("Enter the element:");
                    scanf("%d",&ele);
                    push(&h,ele);
                    break;
            case 2:printf("Enter the element:");
                    scanf("%d",&ele);
                    popGivenElement(&h,ele);
                    break;
            case 3:popMaximum(&h);
                    break;
            case 4:if(empty(&h))
                        printf("The heap is empty\n\n");
                    else
                        printf("Minimum in the heap is %d\n\n",maximum(&h));
                    break;
            case 5:if(empty(&h))
                        printf("Yes, the heap is empty\n\n");
                    else
                        printf("No, the heap is not empty\n\n",maximum(&h));
                    break;
            case 6:deallocate(&h);
                    break;
            default:printf("Please enter valid input\n\n");
                    break;
        }
    }while(choice!=6);
    return 0;
}
