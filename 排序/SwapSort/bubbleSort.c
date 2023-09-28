#include<stdio.h>
#include<stdlib.h>
/*
    冒泡交换排序：
        将第一个元素和第二个元素比较，若前者大于后者则交换；
        然后继续对第二个元素与第三个元素比较……依次类推；
        每轮排序将当前未排序元素中的最大值移到未排序序列的最后一位，成为已排序元素的一部分
*/
typedef struct{
    int key;    //排序码
    int info;   //文件信息
}RecordNode;

typedef struct{
    int n;
    RecordNode*record;
}SortObject;                                //把所有待排序文件封装起来

void bubbleSort(SortObject*p){
    int i,j,swap;
    RecordNode temp,*data=p->record;
    for(i=0;i<p->n-1;++i){
        swap=0;                             //初始化交换标志，0表示未发生交换
        for(j=0;j<p->n-i-1;++j)                //第i轮排序确定第n-i个位置的元素,j遍历到n-i-1的位置即可,此时j+1=n-i，两者可以正常交换
        {
            if(data[j+1].key<data[j].key){
                temp=data[j+1];
                data[j+1]=data[j];
                data[j]=temp;
                swap+=1;
            }
        }
        //printf("%d\n",swap);
        if(!swap)break;                     //若在此轮排序中没有发生交换，则说明已经有序，排序终止
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
    
    bubbleSort(&f);
    for(i=0;i<num;i++)
        printf("%d  ",f.record[i].key);
    return 0;
}
