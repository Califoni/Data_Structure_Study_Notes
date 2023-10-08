#include<stdio.h>
#include<stdlib.h>
//归并排序（非递归实现）
typedef struct{
    int key;    //排序码
    int info;   //文件信息
}RecordNode;

typedef struct{
    int n;
    RecordNode*record;
}SortObject;

void merge(RecordNode*r,RecordNode*r1,int low,int mid,int high){    //合并两个有序文件
    int i,j,k;
    i=low;j=mid+1;k=low;
    while(i<=mid&&j<=high){
        if(r[i].key<r[j].key) r1[k++]=r[i++];
        else r1[k++]=r[j++];
    }
    while(i<=mid)r1[k++]=r[i++];
    while(j<=high)r1[k++]=r[j++];
}

void mergePass(RecordNode*r,RecordNode*r1,int length,int n){    //每趟排序把所有文件进行一次归并，n为待排序元素总数
    int i,low,mid,high;
    i=0;
    while(i+2*length-1<n){                                      //在满足条件的前提下，每次合并两个长度均为length的有序文件
        low=i;mid=i+length-1;high=i+2*length-1;
        merge(r,r1,low,mid,high);
        i+=2*length;
    }                                                           
    if(i+length<n)                                              //剩下两个待排序文件，其中一个长度不足length
    {
        low=i;mid=i+length-1;high=n-1;
        merge(r,r1,low,mid,high);
    }
    else
        while(i<n) {r1[i]=r[i];++i;}                            //仅剩下一个待排序文件，直接复制即可
}

void mergeSort(SortObject*p){
    int n=p->n;
    RecordNode r1[n];                                           //初始化一个长度为n的数组用于存放归并排序的元素
    int length=1;
    while(length<n){
        mergePass(p->record,r1,length,n);
        length*=2;
        mergePass(r1,p->record,length,n);                       //此步前若length>=2，则会直接把r1复制到r中，因此不需要条件判断if(length<n)
        length*=2;
    }
}

int main(){
    //初始化
    int num=5;                                                  //文件数量5
    int i=0;
    
    RecordNode*q=(RecordNode*)malloc(sizeof(RecordNode[num]));  //开辟文件数组并获取其指针
    while(i<num){                                               //输入排序码
        scanf("%d",&q[i].key);
        ++i;
    }
    SortObject f;
    f.n=num;
    f.record=q;
    
    mergeSort(&f);
    for(i=0;i<num;i++)
        printf("%d  ",f.record[i].key);
    return 0;
}
