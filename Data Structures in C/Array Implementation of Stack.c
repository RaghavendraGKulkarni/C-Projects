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

void menu()
{
    printf("------MENU------\n");
    printf("1.Push an element into the stack\n");
    printf("2.Pop an element from the stack\n");
    printf("3.Print the top element of the stack\n");
    printf("4.Check if the stack is empty\n");
    printf("5.Exit\n");
    printf("Enter your choice:");
    return;
}

void push(stack *s,int element)
{
    if(s->size==s->capacity)
    {
        s->capacity++;
        s->arr=(int*)realloc(s->arr,s->capacity*sizeof(int));
    }
    s->arr[s->size++]=element;
    return;
}

void pop(stack *s)
{
    if(s->size==0)
        printf("Stack is empty\n");
    s->size--;
    return;
}

int top(stack *s)
{
    if(s->size==0)
        return STACK_EMPTY;
    return s->arr[s->size-1];
}

bool empty(stack *s)
{
    return s->size==0;
}

void deallocate(stack *s)
{
    free(s->arr);
    s->size=0;
    s->capacity=0;
    return;
}

int main()
{
    stack s={(int*)malloc(sizeof(int)),0,0};
    int choice,ele;
    do
    {
        menu();
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:printf("Enter the element:");
                    scanf("%d",&ele);
                    push(&s,ele);
                    break;
            case 2:pop(&s);
                    break;
            case 3:ele=top(&s);
                    if(ele==STACK_EMPTY)
                        printf("Stack is empty\n\n");
                    else
                        printf("Top of the stack contains %d\n\n",ele);
                    break;
            case 4:if(empty(&s))
                        printf("Yes,the stack is empty\n\n");
                    else
                        printf("No,the stack is not empty\n\n");
                    break;
            case 5:deallocate(&s);
                    break;
            default:printf("Please enter valid input\n\n");
                    break;
        }
    }while(choice!=5);
    return 0;
}
