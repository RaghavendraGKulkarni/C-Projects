#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int* insert(int *keys,int *size,int key)
{
    int i,v;
    keys=(int*)realloc(keys,(*size+1)*sizeof(int));
    if(keys==NULL)
    {
        printf("Memory not allocated\n");
        exit(0);
    }
    keys[(*size)++]=key;
    i=(*size)-2;
    v=key;
    while(i>=0 && keys[i]>=v)
    {
        keys[i+1]=keys[i];
        i--;
    }
    keys[i+1]=v;
    return keys;
}
bool find(int *keys,int size,int key)
{
    int left=0,right=size-1,mid;
    printf("Finding %d\n",key);
    while(left<=right)
    {
        mid=left+(right-left)/2;
        if(keys[mid]==key)
            return true;
        if(keys[mid]<key)
            left=mid+1;
        else
            right=mid-1;
    }
    return false;
}
int greaterThan(int* keys,int size,int key)
{
    int left=0,right=size-1,mid,ans=0;
    while(left<=right)
    {
        mid=(left+right)/2;
        if(keys[mid]<key)
            left=mid+1;
        else if(keys[mid]==key)
        {
            while(mid<size && keys[mid]==key)
                mid++;
            ans+=(right-mid+1);
            break;
        }
        else
        {
            ans+=(right-mid+1);
            right=mid-1;
        }
    }
    return ans;
}
int smallerThan(int *keys,int size,int key)
{
    int left=0,right=size-1,mid,ans=0;
    while(left<=right)
    {
        mid=(left+right)/2;
        if(keys[mid]>key)
            right=mid-1;
        else if(keys[mid]==key)
        {
            while(mid>=0 && keys[mid]==key)
                mid--;
            ans+=(mid-left+1);
            break;
        }
        else
        {
            ans+=(mid-left+1);
            left=mid+1;
        }
    }
    return ans;
}
int* erase(int *keys,int *size,int key)
{
    int i,j;
    i=smallerThan(keys,*size,key);
    j=(*size)-greaterThan(keys,*size,key);
    while(j<(*size))
        keys[i++]=keys[j++];
    (*size)=i;
    keys=(int*)realloc(keys,(*size)*sizeof(int));
    return keys;
}
int count(int *keys,int size,int key)
{
    int i,j;
    i=smallerThan(keys,size,key);
    j=size-greaterThan(keys,size,key);
    return j-i;
}
int nextElement(int *keys,int size,int key)
{
    int i;
    i=size-greaterThan(keys,size,key);
    if(i<size)
        return keys[i];
    return INT_MAX;
}
int previousElement(int *keys,int size,int key)
{
    int i;
    i=smallerThan(keys,size,key);
    if(i>0)
        return keys[i-1];
    return INT_MIN;
}
int main()
{
    int size=0,*keys,i,key;
    keys=(int*)malloc(sizeof(int));
    for(i=0;i<20;i++)
        keys=insert(keys,&size,rand()%100);
    for(i=0;i<size;i++)
        printf("%d ",keys[i]);
    printf("\n");
    key=rand()%100;
    if(find(keys,size,key))
        printf("%d is present in the multiset\n",key);
    else
        printf("%d is not present in the multiset\n",key);
    key=rand()%100;
    printf("%d elements are greater than %d\n",greaterThan(keys,size,key),key);
    key=rand()%100;
    printf("%d elements are smaller than %d\n",smallerThan(keys,size,key),key);
    key=keys[rand()%size];
    keys=erase(keys,&size,key);
    printf("%d erased from the multiset\n",key);
    key=keys[rand()%size];
    printf("%d occurrences of %d in the multiset\n",count(keys,size,key),key);
    key=keys[rand()%size];
    printf("%d is the next greater element to %d in the multiset\n",nextElement(keys,size,key),key);
    key=keys[rand()%size];
    printf("%d is the previous smaller element to %d in the multiset\n",previousElement(keys,size,key),key);
    free(keys);
    return 0;
}
