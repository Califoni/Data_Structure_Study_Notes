#include<stdio.h>
#include<stdlib.h>

//直接插入排序

typedef struct{
    int key;    //排序码
    int info;   //文件信息
}RecordNode;

typedef struct{
    int n;
    RecordNode*record;
}SortObject;

void insertSort(SortObject*p){
    int i,j;
    RecordNode temp;
    RecordNode*data=p->record;
    
    for(i=1;i<p->n;++i){
    temp=data[i];
        for(j=i-1;j>=0&&temp.key<data[j].key;j--)   //从后往前一一比较，寻找插入位置
                data[j+1]=data[j];  //元素后移
    if(j!=i-1)data[j+1]=temp;   //若出现元素调整，调整结束后将插入元素插入到正确位置
    }
}

int main(){
    //初始化
    int num=5;
    int i=0;

    RecordNode*q=(RecordNode*)malloc(sizeof(RecordNode[num]));
    while(i<num){
        scanf("%d",&q[i].key);
        ++i;
    }
    SortObject f;
    f.n=num;
    f.record=q;
    
    insertSort(&f);
    for(i=0;i<num;i++)
        printf("%d  ",f.record[i].key);
    return 0;
}
