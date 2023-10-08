#include<stdio.h>
#include<stdlib.h>


void Merge(int a1,int a2,int b1,int b2,int *arr){
    int i=a1;int j=b1;
    int k=0;
    int *tmp=(int *)malloc(sizeof(int)*(b2-a1+1));
    while(i<=a2&&j<=b2){
        if(arr[i]<arr[j]){tmp[k]=arr[i];i++;}
        else {tmp[k]=arr[j];j++;}
        k++;
    }
    while(i<=a2)tmp[k++]=arr[i++];
    while(j<=b2)tmp[k++]=arr[j++];
    //更新arr数组从a1到b2的部分
    for(i=a1,j=0;i<=b2;i++,j++){
        arr[i]=tmp[j];
    }
    
    return;
}

void MergeSort(int l,int r,int *arr)
{
    if(l>=r)return;
    int mid=(l+r)/2;
    MergeSort(l,mid,arr);
    MergeSort(mid+1,r,arr);
    Merge(l,mid,mid+1,r,arr);
    return;
}


int main(){
    int n;//数组的元素个数
    scanf("%d",&n);
    int *arr=(int *)malloc(sizeof(int)*n);
    for(int i=0;i<n;++i)scanf("%d",&arr[i]);
    MergeSort(0,n-1,arr);
    for(int i=0;i<n;i++){
        printf("%d  ",arr[i]);
    }
    return 0;
}
