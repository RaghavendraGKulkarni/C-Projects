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
};
typedef struct treeNode treeNode;

struct BST
{
    treeNode* root;
    int size;
};
typedef struct BST BST;

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
    printf("1.Insert an element into the BST\n");
    printf("2.Delete an element from the BST\n");
    printf("3.Print the traversals on the BST\n");
    printf("4.Check if an element is present in the BST\n");
    printf("5.Print the maximum element in the BST\n");
    printf("6.Print the minimum element in the BST\n");
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
    return t;
}

void insert(BST *tree,int ele)
{
    treeNode *t=getTreeNode(ele),*cur;
    if(tree->root==NULL)
        tree->root=t;
    else
    {
        cur=tree->root;
        while(1)
        {
            if(t->element<cur->element)
            {
                if(cur->left==NULL)
                {
                    cur->left=t;
                    break;
                }
                else
                    cur=cur->left;
            }
            else
            {
                if(cur->right==NULL)
                {
                    cur->right=t;
                    break;
                }
                else
                    cur=cur->right;
            }
        }
    }
    tree->size++;
    return;
}

void delete(BST *tree,int ele)
{
    treeNode *cur=tree->root,*par=NULL,*succ,*temp;
    if(tree->size==0)
        return;
    while(cur && cur->element!=ele)
    {
        par=cur;
        if(ele<cur->element)
            cur=cur->left;
        else
            cur=cur->right;
    }
    if(cur==NULL)
    {
        printf("Element not found in the Binary Search Tree\n\n");
        return;
    }
    if(cur->left==NULL)
        temp=cur->right;
    else if(cur->right==NULL)
        temp=cur->left;
    else
    {
        succ=cur->right;
        while(succ->left)
            succ=succ->left;
        succ->left=cur->left;
        temp=cur->right;
    }
    if(par==NULL)
        tree->root=temp;
    else if(cur==par->left)
        par->left=temp;
    else
        par->right=temp;
    free(cur);
    tree->size--;
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

void deallocate(BST *tree)
{
    stack s={NULL,0};
    treeNode* cur=tree->root;
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

int* preorder(BST tree,int *traversal)
{
    int size=0;
    stack s={NULL,0};
    treeNode* cur;
    if(tree.root)
        push(&s,tree.root);
    traversal=(int*)malloc(sizeof(int));
    while(!empty(&s))
    {
        cur=top(&s);
        pop(&s);
        if(cur->right!=NULL)
            push(&s,cur->right);
        if(cur->left!=NULL)
            push(&s,cur->left);
        traversal=(int*)realloc(traversal,(size+1)*sizeof(int));
        traversal[size++]=cur->element;
    }
    s.size=0;
    return traversal;
}

int* inorder(BST tree,int* traversal)
{
    int size=0;
    stack s={NULL,0};
    treeNode* cur=tree.root;
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

int* postorder(BST tree,int *traversal)
{
    int size=0;
    stack s={NULL,0};
    treeNode* cur=tree.root;
    traversal=(int*)malloc(sizeof(int));
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
                traversal=(int*)realloc(traversal,(size+1)*sizeof(int));
                traversal[size++]=cur->element;
                cur=NULL;
            }
        }
    }while(!empty(&s));
    s.size=0;
    return traversal;
}

treeNode* search(BST tree,int ele)
{
    treeNode* cur=tree.root;
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

int max(BST tree)
{
    treeNode* cur=tree.root;
    while(cur && cur->right)
        cur=cur->right;
    if(cur==NULL)
        return MAXIMUM_NOT_FOUND;
    return cur->element;
}

int min(BST tree)
{
    treeNode* cur=tree.root;
    while(cur && cur->left)
        cur=cur->left;
    if(cur==NULL)
        return MINIMUM_NOT_FOUND;
    return cur->element;
}

int main()
{
    BST tree={NULL,0};
    int choice,ele,*traversal,i;
    do
    {
        menu();
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:printf("Enter the element:");
                    scanf("%d",&ele);
                    insert(&tree,ele);
                    printf("\n");
                    break;
            case 2:printf("Enter the element:");
                    scanf("%d",&ele);
                    delete(&tree,ele);
                    printf("\n");
                    break;
            case 3:printf("Preorder Traversal :- ");
                    traversal=preorder(tree,traversal);
                    for(i=0;i<tree.size;i++)
                        printf("%d ",traversal[i]);
                    printf("\nInorder Traversal :- ");
                    traversal=inorder(tree,traversal);
                    for(i=0;i<tree.size;i++)
                        printf("%d ",traversal[i]);
                    printf("\nPostorder Traversal :- ");
                    traversal=postorder(tree,traversal);
                    for(i=0;i<tree.size;i++)
                        printf("%d ",traversal[i]);
                    printf("\n\n");
                    break;
            case 4:printf("Enter the element:");
                    scanf("%d",&ele);
                    if(search(tree,ele))
                        printf("The element is present in the tree\n\n");
                    else
                        printf("The element is not present in the tree\n\n");
                    break;
            case 5:ele=max(tree);
                    if(ele==MAXIMUM_NOT_FOUND)
                        printf("Tree is empty. No maximum exists\n\n");
                    else
                        printf("Maximum in the tree = %d\n\n",ele);
                    break;
            case 6:ele=min(tree);
                    if(ele==MINIMUM_NOT_FOUND)
                        printf("Tree is empty. No minimum exists\n\n");
                    else
                        printf("Minimum in the tree = %d\n\n",ele);
                    break;
            case 7:deallocate(&tree);
                    break;
            default:printf("Please enter valid input\n\n");
                    break;
        }
    }while(choice!=7);
    return 0;
}
