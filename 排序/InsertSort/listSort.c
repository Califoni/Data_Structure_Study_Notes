#include<stdio.h>
#include<stdlib.h>
//表插入排序
//文件结构体初始化，每个文件结构包含一个排序码key，一个文件数据info，一个指向下一个文件的指针
typedef struct Node{
    int key;
    int info;
    struct Node*next;
}ListNode;

/*
    用单链表实现插入排序算法需要指针如下：
    *now:       待插入元素的指针
    *prenow:    待插入元素的前一个元素的指针，将待插入元素脱离链表时需要
    *p:         从头遍历链表元素的指针，已排序元素与待插入元素比较大小时需要
    *pre:       p指向元素的前一个元素的指针，插入元素时需要
*/
void listSort(ListNode*head){
    ListNode*now,*pre,*p,*prenow;
    prenow=head->next;
    if(prenow==NULL)return;                     //链表不含元素不用排序
    now=head->next->next;                       //从第一个元素开始排序  
    if(now==NULL)return;                        //链表只含单个元素不用排序
    
    while(now!=NULL){
        pre=head;                               //缺少此行会导致无法将最小的元素插入到第一个位置！
        p=head->next;
        while(p!=now&&p->key<=now->key){
            pre=p;
            p=p->next;
        }
        if(p==now){                             //插入元素位置不要调整的情况
            prenow=now;
            now=now->next;
        }
        else{                                   //插入元素位置需要调整的情况
            prenow->next=now->next;             //把当前待插入元素脱离链表
            now->next=p;                        //将当前待插入元素插入在链表中的正确位置
            pre->next=now;
            now=prenow->next;            
        }
    }
}

int main(){
    //文件链表初始化
    ListNode*head=(ListNode*)malloc(sizeof(ListNode));  //初始化头节点
    int num=5;
    int i=0;
    ListNode*q=head;
    while(i<num){                               //初始化五个待排序的文件节点
        ListNode*p=(ListNode*)malloc(sizeof(ListNode));
        p->next=NULL;
        scanf("%d",&p->key);
        q->next=p;
        q=q->next;
        ++i;
    }

    listSort(head);
    while(head->next!=NULL){
        printf("%d   ",head->next->key);
        head=head->next;   
    }
    return 0;
}
