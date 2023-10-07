#include<stdio.h>
#include<stdlib.h>

#define D 3	    //排序位数

typedef struct Node{
    int key[D];     //排序码用数组表示
    int info;
    struct Node*next;      //指向下一个待排序元素
}PNode;

typedef struct{
    PNode*f;
    PNode*e;
}Queue;             //队列结构，f和e分别是头指针和尾指针

void radixSort(PNode*plist,int d,int r){
    /*
        *plist为待排序元素的链表头指针，
        d为排序码的位数，
        r为排序码的基数，即优先级数
    */
    
    int i,j,k;
    PNode*head=plist->next;                             //head为收集链表的头指针，此时尚未进行过收集操作
    PNode*p=head;
    Queue q[r];                                         //初始化长度为r的队列数组，每个队列表示一个优先级
    for(i=d-1;i>=0;--i){                                //先从优先级最低的一位开始排序
        for(j=0;j<r;++j){q[j].f=NULL;q[j].e=NULL;}      //清空队列
        
        //获取未排序的最低位进行分配操作
        p=head;
        while(p!=NULL){
            k=p->key[i];                                
            if(q[k].f==NULL)q[k].f=p;                   //若当前队列为空则把待分配元素放队列首位
            else (q[k].e)->next=p;                        //若不为空则把待分配元素追加到队列的尾部
            q[k].e=p;                                   //分配元素后，更新尾指针
            p=p->next;
        }                                               
        
        //接下来进行收集操作
        for(j=0;q[j].f==NULL;++j);                      //寻找第一个非空队列
        head=q[j].f;                                    //把第一个非空队列的头指针作为收集链表的头指针
        p=q[j].e;                                       //获取非空队列的尾指针用于连接下一个非空队列
        for(++j;j<r;++j)                                //依次把其他非空队列的元素连接到收集链表中
            if(q[j].f!=NULL){
                p->next=q[j].f;
                p=q[j].e;
            }
        p->next=NULL;
    }
    plist->next=head;                                   //最后把排好序的链表连接回头指针上
}

int main(){
    int i=0;int n=5;int j;
    PNode*plist=(PNode*)malloc(sizeof(PNode));
    PNode*p=plist;
    while(i<n){
        PNode*q=(PNode*)malloc(sizeof(PNode));
        for(j=0;j<D;++j) scanf("%d",&q->key[j]);
        q->next=NULL;
        p->next=q;
        p=p->next;
        ++i;
    }

    radixSort(plist,D,10);
    
    p=plist->next;
    while(p!=NULL){
        for(j=0;j<D;++j) printf("%d",p->key[j]);
        printf("\n");
        p=p->next;
    }
    return 0;
}

