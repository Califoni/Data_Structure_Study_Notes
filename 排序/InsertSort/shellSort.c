#include<stdio.h>
#include<stdlib.h>
/*
    shell排序（缩小增量法）：
        初始化增量d1,将全部记录分成d1个组，所有距离为d1倍数的记录放在一组中，先在各组内排序；
        将各组分别排序一次视为一轮排序，一轮排序结束后再取d2<d1重复上述分组和排序；
        直到di=1即所有记录放在同一组中为止
*/
typedef struct{
    int key;    //排序码
    int info;   //文件信息
}RecordNode;

typedef struct{
    int n;
    RecordNode*record;
}SortObject;

void shellSort(SortObject*p,int d){                             //d为初始增量
    int i,j,inc;
    RecordNode temp,*data=p->record;
    for(inc=d;inc>0;inc/=2){                                    //inc为此轮排序的增量
        for(i=inc;i<p->n;++i){                                  //每轮排序同时对各组（每个增量序列）进行操作    
            temp=data[i];
            for(j=i-inc;j>=0&&temp.key<data[j].key;j-=inc)      //将当前待插入元素与其所在的增量序列中的前一个元素比较大小，若小则继续往前比较
                data[j+inc]=data[j];                            //同时把较大元素后移
            data[j+inc]=temp;                                   //比较结束，将待插入元素插入正确的位置
        }
        
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
    
    shellSort(&f,f.n/2);
    for(i=0;i<num;i++)
        printf("%d  ",f.record[i].key);
    return 0;
}
