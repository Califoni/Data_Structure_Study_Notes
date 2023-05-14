#include<stdio.h>
#include<stdlib.h>

#define MAX 1000000
//哈夫曼树节点的结构
struct HtNode{
    int ww;                 //权值
    int parent,llink,rlink; //父指针和左右子指针
};
struct HtTree{
    int m;      //外部节点个数
    int root;   //最后结果中树根的索引
    struct HtNode* ht;  //存放2*m-1个节点的数组
};
typedef struct HtTree Pht;

void huffman(int m,int *w,Pht*tree){
    //申请2*m-1个节点空间
    tree->ht=(struct HtNode*)malloc(sizeof(struct HtNode)*(2*m-1));
    //初始化节点的属性，将需要构造成哈夫曼树的m个节点放在前m个空间
    for(int i=0;i<2*m-1;i++){
        tree->ht[i].parent=-1;
        tree->ht[i].llink=-1;
        tree->ht[i].rlink=-1;
        if(i<m)tree->ht[i].ww=w[i];
        else tree->ht[i].ww=-1;
    }
    //x1存放最小值的索引，x2存放次小值索引，m1存放最小值，m2存放次小值
    int x1,x2,m1,m2;
    for(int i=0;i<m-1;i++){//总共构造m-1次
        m1=MAX;m2=MAX;
        for(int j=0;j<m+i;j++){
            if(tree->ht[j].ww<m1&&tree->ht[j].parent==-1){
                m2=m1;x2=x1;        //找到比原最小值更小的，则原最小值更新为次小值
                m1=tree->ht[j].ww;
                x1=j;
            }
            else if(tree->ht[j].ww<m2&&tree->ht[j].parent==-1){
                m2=tree->ht[j].ww;x2=j;    //找到比原次小值更小但大于原最小值的数，只更新原次小值
            }
        }
        //寻找完毕，将构造的二叉树的根节点在数组中依次往后放一位，同时更新相关节点属性
        tree->ht[m+i].ww=m1+m2;
        tree->ht[m+i].llink=x1;
        tree->ht[m+i].rlink=x2;
        tree->ht[x1].parent=m+i;
        tree->ht[x2].parent=m+i;
    }
    //容易知道最后整棵哈夫曼树的根节点就是数组最后一个位置即索引为2*m-2
    tree->root=2*m-2;
}


int main(){
    //测试一下哈夫曼树代码
    int w[13]={2,3,5,7,11,13,17,19,23,29,31,37,41};
    Pht*tree=(Pht*)malloc(sizeof(Pht));
    int m=sizeof(w)/sizeof(int);
    huffman(m,w,tree);
    for (int i=m;i<2*m-1;i++){
        printf("%d ",tree->ht[i].ww);
    }
    //结果是5,10,17,24,34,42,53,65,78,95,143,238
    return 0;
}