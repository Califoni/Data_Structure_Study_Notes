#include<stdio.h>
#include<stdlib.h>
/*
    堆排序：
        1.实现heapify操作：从当前节点开始，从上至下，将其与左右子节点中较大的一个交换，然后对被交换的子节点重复进行该操作，直到没有子节点为止
        2.实现build_heap建堆：从最后一个非叶子结点开始，从后往前依次对每个非叶子结点做heapify操作，直到根节点为止
        3.heapSort堆排序：每次将当前堆的堆顶元素与堆的最后一个元素交换位置，确定当前堆中最大元素位置，将其从堆中分离后重建堆
*/
typedef struct{
    int key;    //排序码
    int info;   //文件信息
}RecordNode;

typedef struct{
    int n;
    RecordNode*record;
}SortObject;                                //把所有待排序文件封装起来

void heapify(SortObject*p,int size,int i){
    //heap.c中的heapify操作是递归实现的，这里是非递归实现
    int max=i;                                                  //max表示当前非叶子节点的索引
    int child=2*i+1;
    RecordNode temp,*data=p->record;
    temp=data[max];
    while(child<size-1){                                        //若child>size-1说明当前节点是叶子节点，没有子节点与其进行比较
        if((child+1<size-1)&&data[child].key<data[child+1].key)
            child+=1;                                           //寻找左右子节点中较大的子节点
        if(data[child].key>data[max].key)
            {
                data[max]=data[child];                          //将较大的子节点元素与当前节点交换
                max=child;child=2*max+1;                        //交换完元素位置后更新当前非叶子结点的索引max以及其的子节点索引child
            }
        else break;
    }
    data[max]=temp;
}

void heapSort(SortObject*p){
    int i;
    int n=p->n;
    RecordNode temp,*data=p->record;
                                                                //使用数组表示完全二叉树，其节点遵循以下规律，第i个节点的父节点索引为(i-1)/2，左右子节点的索引为2*i+1和2*i+2
    for(i=(n-2)/2;i>=0;i--) heapify(p,n,i);                     //建立堆，从最后一个非叶子节点从后往前做heapify    
    for(i=n-1;i>0;--i){
        temp=data[i];                                           //将当轮排序中最大元素与堆中的最后一个元素交换
        data[i]=data[0];
        data[0]=temp;                           
        heapify(p,i,0);                                         //将最大元素分离，重建堆
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
    
    heapSort(&f);
    for(i=0;i<num;i++)
        printf("%d  ",f.record[i].key);
    return 0;
}
