#include "Stack.h"

void menu()
{
    printf("----------------MENU----------------\n");
    printf("1.Push an element into the stack\n");
    printf("2.Pop an element from the stack\n");
    printf("3.Print the top element of the stack\n");
    printf("4.Check if the stack is empty\n");
    printf("5.Exit\n");
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

void push(stack *s,int ele)
{
    node *t=getNode(ele);
    t->next=s->top;
    s->top=t;
    s->size++;
    return;
}

void pop(stack *s)
{
    if(s->top==NULL)
        printf("Stack is empty\n");
    else
    {
        node *t=s->top->next;
        free(s->top);
        s->top=t;
        s->size--;
    }
    return;
}

int top(stack *s)
{
    if(s->top==NULL)
        return STACK_EMPTY;
    return s->top->element;
}

bool empty(stack *s)
{
    return s->top==NULL;
}

void deallocate(stack *s)
{
    while(!empty(s))
        pop(s);
    return;
}
