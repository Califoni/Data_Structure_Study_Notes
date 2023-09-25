#include<stdio.h>
#include<stdlib.h>
//二分法插入排序
typedef struct{
    int key;    //排序码
    int info;   //文件信息
}RecordNode;

typedef struct{
    int n;
    RecordNode*record;
}SortObject;

void binSort(SortObject*p){
    int left,right,mid;
    int i,j;
    RecordNode*data=p->record;
    RecordNode temp;
    for(i=1;i<p->n;++i){                    //从头插入各个元素,data[0]的插入无需做任何调整，因此从i=1开始遍历
        left=0;right=i-1;
        while(left<=right){                 //二分法寻找插入位置
            mid=(left+right)/2;
            if(data[i].key>data[mid].key)   left=mid+1;
            else    right=mid-1;
        }
        if(left!=i){                        //left是二分法寻找到的插入位置的索引，若left==i说明顺序表中元素不用调整，直接插入
            temp=data[i];
            for(j=i-1;j>=left;j--){         //比当前插入元素大的元素后移，只需要从data[i-1]往前遍历依次后移就可以，因为data[i-1]->data[i],data[i]之后的未排序元素在这次插入中不受影响
                data[j+1]=data[j];          //实际上移动的是文件，而不是排序码key
            }
            data[left]=temp;
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
    
    binSort(&f);
    for(i=0;i<num;i++)
        printf("%d  ",f.record[i].key);
    return 0;
}
