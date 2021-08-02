#include "Stack.h"

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
