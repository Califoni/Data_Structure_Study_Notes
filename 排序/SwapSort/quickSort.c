#include<stdio.h>
#include<stdlib.h>
/*
    快速排序（分区交换排序）：
        在待排序的n个记录中任取一个记录作为分区标准，
        把所有小于该排序码的记录移到左边，大于该排序码的记录移到右边，中间放所选记录，则为一趟排序；
        对前后两个子序列分别重复上述过程
*/
typedef struct{
    int key;    //排序码
    int info;   //文件信息
}RecordNode;

typedef struct{
    int n;
    RecordNode*record;
}SortObject;

void quickSort(SortObject*p,int l,int r){
    if(l>=r)return;
    int i,j;
    i=l;j=r;
    RecordNode temp,*data=p->record;
    temp=data[i];
    while(i<j){
        while(i<j&&data[j].key>temp.key)--j;    //从右往左寻找第一个小于分区元素的元素
        if(i<j) data[i++]=data[j];              //若找到该元素，则将其移动到分区元素左边
        while(i<j&&data[i].key<temp.key)++i;    //从左往右寻找第一个大于分区元素的元素
        if(i<j) data[j--]=data[i];              //若找到该元素，则将其移动到分区元素右边
    }
    data[i]=temp;
    quickSort(p,l,i-1);                         //递归处理左右区间
    quickSort(p,i+1,r);
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
    
    quickSort(&f,0,f.n-1);
    for(i=0;i<num;i++)
        printf("%d  ",f.record[i].key);
    return 0;
}
