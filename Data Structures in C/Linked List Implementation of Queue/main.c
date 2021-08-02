#include "Queue.c"

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
