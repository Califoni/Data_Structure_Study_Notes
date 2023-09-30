#include<stdlib.h>
#include<stdio.h>

void swap(int tree[],int a,int b){
    int temp=tree[a];
    tree[a]=tree[b];
    tree[b]=temp;
    return;
}

//实现大根堆，即父节点的值比左右子节点的值大
//参数num表示树的总结点数，i表示对第i个节点进行操作
void heapify(int tree[],int num,int i){
    if(i>=num)return;
    int max=i;  //max为根节点，左右子节点三者中最大值的索引
    int c1=2*i+1;
    int c2=2*i+2;
    if(c1<num&&tree[c1]>tree[max]){
        max=c1;
    }
    if(c2<num&&tree[c2]>tree[max]){
        max=c2;
    }
    //如果根节点不是最大值，那么需要对二叉树元素进行交换
    if(i!=max){
        //将数组中索引为max和索引为i对应的值进行交换
        swap(tree,max,i);
        //因为tree[max]对应的值发生了变化，所以需要对其对应的子树再次进行排序操作
        heapify(tree,num,max);
    }
}

//对于一个完全无序的完全二叉树来说，要将其构造成堆，则要从下往上从最后一个非叶子结点进行heapify操作，直到根节点
void build_heap(int tree[],int num){
    //获得最后一个节点的索引
    int last_node=num-1;
    //最后一个节点的父节点索引，即最后一个非叶子结点
    int parent=(last_node-1)/2;
    //发现从该父节点开始往前依次做heapify操作即可对全部子树直到整棵树实现heapify
    for(int i=parent;i>=0;i--){
        heapify(tree,num,i);
    }
}


//实现堆排序
void heap_sort(int tree[],int num){
    build_heap(tree,num);
    //每次把最后一个节点和第一个节点进行交换，由于大根堆的性质，此时最后一个节点必为最大值，然后把排好序的最后一个节点排除在外，从头开始对整个二叉树进行heapify，重复上述操作直到树的根节点
    for(int i=num-1;i>0;i--){
        swap(tree,i,0);
        heapify(tree,i,0);
    }
}

int main(){
    //使用数组表示完全二叉树，其节点遵循以下规律，第i个节点的父节点索引为(i-1)/2，左右子节点的索引为2*i+1和2*i+2
    int tree[]={2,5,3,1,10,4};
    int n=sizeof(tree)/sizeof(int);
    
    heap_sort(tree,n);
    for(int i=0;i<n;i++){
        printf("%d\n",tree[i]);
    }
    
    return 0;
}
