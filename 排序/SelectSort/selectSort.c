#include<stdio.h>
#include<stdlib.h>
//直接选择排序:每次从未排序元素中选择最小元素放到已排序元素的尾部
typedef struct{
    int key;    //排序码
    int info;   //文件信息
}RecordNode;

typedef struct{
    int n;
    RecordNode*record;
}SortObject;                                //把所有待排序文件封装起来

void selectSort(SortObject*p){
    int i,j,idx;                            //idx为最小元素的索引
    RecordNode temp,*data=p->record;
    for(i=0;i<p->n-1;++i){
        idx=i;
        for(j=i+1;j<p->n;++j)
            if(data[j].key<data[idx].key)
                idx=j;                      //寻找最小元素
        if(idx!=i){                         //如果需要交换
            temp=data[i];
            data[i]=data[idx];
            data[idx]=temp;
        }
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
    
    selectSort(&f);
    for(i=0;i<num;i++)
        printf("%d  ",f.record[i].key);
    return 0;
}
