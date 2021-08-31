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

int main()
{
    stack s={NULL,0};
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
                    printf("\n");
                    break;
            case 2:pop(&s);
                    printf("\n");
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
