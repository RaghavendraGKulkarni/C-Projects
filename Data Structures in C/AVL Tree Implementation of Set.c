#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

#define ELEMENT_NOT_FOUND INT_MIN
#define MINIMUM_NOT_FOUND INT_MIN+1
#define MAXIMUM_NOT_FOUND INT_MAX

struct treeNode
{
    int element;
    struct treeNode* left;
    struct treeNode* right;
    int height;
};
typedef struct treeNode treeNode;

struct set
{
    treeNode* root;
    int size;
};
typedef struct set set;

struct stackNode
{
    treeNode *node;
    struct stackNode* next;
};
typedef struct stackNode stackNode;

struct stack
{
    stackNode* top;
    int size;
};
typedef struct stack stack;

void menu()
{
    printf("----------------MENU----------------\n");
    printf("1.Insert an element into the Set\n");
    printf("2.Delete an element from the Set\n");
    printf("3.Print the elements of the Set\n");
    printf("4.Check if an element is present in the Set\n");
    printf("5.Print the maximum element of the Set\n");
    printf("6.Print the minimum element of the Set\n");
    printf("7.Exit\n");
    printf("Enter your choice:");
    return;
}

treeNode* getTreeNode(int ele)
{
    treeNode* t=(treeNode*)malloc(sizeof(treeNode));
    if(t==NULL)
    {
        printf("Ran out of Memory\n\n");
        exit(0);
    }
    t->element=ele;
    t->left=NULL;
    t->right=NULL;
    t->height=0;
    return t;
}

int height(treeNode* node)
{
    return (node==NULL)? -1 : node->height ;
}

int balance(treeNode* node)
{
    return height(node->left)-height(node->right);
}

int max(int a,int b)
{
    if(a>=b)
        return a;
    return b;
}

treeNode* rightRotate(treeNode* node)
{
    treeNode* l=node->left;
    treeNode* lr=l->right;
    l->right=node;
    node->left=lr;
    node->height=max(height(node->left),height(node->right))+1;
    l->height=max(height(l->left),height(l->right))+1;
    return l;
}

treeNode* leftRotate(treeNode* node)
{
    treeNode* r=node->right;
    treeNode* rl=r->left;
    r->left=node;
    node->right=rl;
    node->height=max(height(node->left),height(node->right))+1;
    r->height=max(height(r->left),height(r->right))+1;
    return r;
}

treeNode* insertNode(treeNode* node,int ele)
{
    if(node==NULL)
        return getTreeNode(ele);
    if(ele<node->element)
        node->left=insertNode(node->left,ele);
    else if(ele>node->element)
        node->right=insertNode(node->right,ele);
    else
        return node;
    node->height=1+max(height(node->left),height(node->right));
    int bal=balance(node);
    if(bal>1 && ele<node->left->element)
        return rightRotate(node);
    if(bal<-1 && ele>node->right->element)
        return leftRotate(node);
    if(bal>1 && ele>node->left->element)
    {
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    if(bal<-1 && ele<node->right->element)
    {
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void insert(set *st,int ele)
{
    st->root=insertNode(st->root,ele);
    st->size++;
    return;
}

treeNode* deleteNode(treeNode* node,int ele)
{
    if(node==NULL)
        return node;
    if(ele<node->element)
        node->left=deleteNode(node->left,ele);
    else if(ele>node->element)
        node->right=deleteNode(node->right,ele);
    else
    {
        if((node->left==NULL) || (node->right==NULL))
        {
            treeNode* temp=node->left?node->left:node->right;
            if(temp==NULL)
            {
                temp=node;
                node=NULL;
            }
            else
                *node=*temp;
            free(temp);
        }
        else
        {
            treeNode* temp=node->right;
            while(temp->left!=NULL)
                temp=temp->left;
            node->element=temp->element;
            node->right=deleteNode(node->right,temp->element);
        }
    }
    if(node==NULL)
        return node;
    node->height=1+max(height(node->left),height(node->right));
    int bal=balance(node);
    if(bal>1 && balance(node->left)>=0)
        return rightRotate(node);
    if(bal>1 && balance(node->left)<0)
    {
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    if(bal<-1 && balance(node->right)<=0)
        return leftRotate(node);
    if(bal<-1 && balance(node->right)>0)
    {
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void delete(set *st,int ele)
{
    st->root=deleteNode(st->root,ele);
    st->size--;
    return;
}

void push(stack *s,treeNode *ele)
{
    stackNode *t=(stackNode*)malloc(sizeof(stackNode));
    if(t==NULL)
    {
        printf("Ran out of memory\n\n");
        exit(0);
    }
    t->node=ele;
    t->next=s->top;
    s->top=t;
    s->size++;
    return;
}

void pop(stack *s)
{
    if(s->top==NULL)
        return;
    else
    {
        stackNode *t=s->top->next;
        free(s->top);
        s->top=t;
        s->size--;
    }
    return;
}

treeNode* top(stack *s)
{
    if(s->top==NULL)
        return NULL;
    return s->top->node;
}

bool empty(stack *s)
{
    return s->top==NULL;
}

void deallocate(set *st)
{
    stack s={NULL,0};
    treeNode* cur=st->root;
    do
    {
        while(cur)
        {
            if(cur->right)
                push(&s,cur->right);
            push(&s,cur);
            cur=cur->left;
        }
        if(!empty(&s))
        {
            cur=top(&s);
            pop(&s);
            if(cur->right && !empty(&s) && top(&s)==cur->right)
            {
                pop(&s);
                push(&s,cur);
                cur=cur->right;
            }
            else
            {
                free(cur);
                cur=NULL;
            }
        }
    }while(!empty(&s));
    s.size=0;
    return;
}

int* inorder(set st,int* traversal)
{
    int size=0;
    stack s={NULL,0};
    treeNode* cur=st.root;
    traversal=(int*)malloc(sizeof(int));
    do
    {
        while(cur)
        {
            push(&s,cur);
            cur=cur->left;
        }
        if(!empty(&s))
        {
            cur=top(&s);
            pop(&s);
            traversal=(int*)realloc(traversal,(size+1)*sizeof(int));
            traversal[size++]=cur->element;
            cur=cur->right;
        }
    }while(cur || !empty(&s));
    s.size=0;
    return traversal;
}

treeNode* search(set st,int ele)
{
    treeNode* cur=st.root;
    while(cur!=NULL)
    {
        if(cur->element==ele)
            break;
        else if(cur->element<ele)
            cur=cur->right;
        else
            cur=cur->left;
    }
    return cur;
}

int maxElement(set st)
{
    treeNode* cur=st.root;
    while(cur && cur->right)
        cur=cur->right;
    if(cur==NULL)
        return MAXIMUM_NOT_FOUND;
    return cur->element;
}

int minElement(set st)
{
    treeNode* cur=st.root;
    while(cur && cur->left)
        cur=cur->left;
    if(cur==NULL)
        return MINIMUM_NOT_FOUND;
    return cur->element;
}

int main()
{
    set st={NULL,0};
    int choice,ele,*traversal,i;
    do
    {
        menu();
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:printf("Enter the element:");
                    scanf("%d",&ele);
                    insert(&st,ele);
                    printf("\n");
                    break;
            case 2:printf("Enter the element:");
                    scanf("%d",&ele);
                    delete(&st,ele);
                    printf("\n");
                    break;
            case 3:printf("The set contains ");
                    traversal=inorder(st,traversal);
                    for(i=0;i<st.size;i++)
                        printf("%d ",traversal[i]);
                    printf("\n\n");
                    break;
            case 4:printf("Enter the element:");
                    scanf("%d",&ele);
                    if(search(st,ele))
                        printf("The element is present in the set\n\n");
                    else
                        printf("The element is not present in the set\n\n");
                    break;
            case 5:ele=maxElement(st);
                    if(ele==MAXIMUM_NOT_FOUND)
                        printf("Set is empty. No maximum exists\n\n");
                    else
                        printf("Maximum in the set = %d\n\n",ele);
                    break;
            case 6:ele=minElement(st);
                    if(ele==MINIMUM_NOT_FOUND)
                        printf("Set is empty. No minimum exists\n\n");
                    else
                        printf("Minimum in the set = %d\n\n",ele);
                    break;
            case 7:deallocate(&st);
                    break;
            default:printf("Please enter valid input\n\n");
                    break;
        }
    }while(choice!=7);
    return 0;
}
