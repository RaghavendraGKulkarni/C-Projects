#include "Stack.c"

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
            case 5:deallocate(&s);
                    break;
            default:printf("Please enter valid input\n\n");
                    break;
        }
    }while(choice!=5);
    return 0;
}
