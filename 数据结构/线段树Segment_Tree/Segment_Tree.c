#include<stdio.h>
#define MAX_LEN 1000

/*线段树的构建
1.算法说明
    基于数组arr构建线段树tree，
    将线段树构建成完全二叉树的形式因此可以用数组表示，
    根节点与左右子节点的索引关系可表示为：
    对于根节点为i，则其左子节点索引为2*i+1，右子节点索引2*i+2

2.参数说明
    start为数组的起点，
    end为数组的终点,
    node为线段树的当前节点在tree中的索引，
    tree[node]存储的值为arr[start]~arr[end]的元素之和
*/
void build_tree(int arr[],int tree[],int node,int start,int end){
    if(start==end)
    {
        tree[node]=arr[start];
        return;
    }
    int left_node=2*node+1;		//当前节点对应的左子节点
    int right_node=2*node+2;	//当前节点对应的右子节点
    int mid=(start+end)/2;
    build_tree(arr,tree,left_node,start,mid);		//左子节点tree[left_node]存储arr[start]~arr[mid]元素之和	
    build_tree(arr,tree,right_node,mid+1,end);		//右子节点tree[right_node]存储arr[mid+1]~arr[end]元素之和
    tree[node]=tree[left_node]+tree[right_node];
}

/*更新操作
参数说明：
    idx指要修改的数组arr的索引
    val将数组arr[idx]的值改为val
算法说明：
    1.每次先判断当前要修改的数属于arr的前半部分还是后半部分，
    由arr的前半部分对应线段树的左子树，后半部分对应线段树的右子树，
    因此可递归到对左右子树进行更新
    
    2.当前节点的值就是更新后的左右子树节点的值之和
    
    3.设置递归出口：
        当start==end时说明找到了数组中要更改的索引在线段树中的位置，直接将tree[node]的值更新为val即可
*/
void update_tree(int arr[],int tree[],int node,int start,int end,int idx,int val){
    if(start==end){
        arr[idx]=val;
        tree[node]=val;
        return;
    }
    int mid=(start+end)/2;
    int left_node=2*node+1;
    int right_node=2*node+2;
    if(idx>=start&&idx<=mid){
        update_tree(arr,tree,left_node,start,mid,idx,val);
    }
    else{
        update_tree(arr,tree,right_node,mid+1,end,idx,val);
    }
    tree[node]=tree[left_node]+tree[right_node];
}

/*求和操作
参数说明：
    L和R分别指进行求和操作的数据区间的左右端点
算法说明：
    1.每次都将当前数组区间的求和结果划分为左右区间的求和结果之和，
    即在线段树中对应对左右节点进行选定区间求和
    2.设置递归出口：
        a.若数组求和区间左边界L > 被划分的区间的右边界end，那么说明该被划分区间不属于求和区间，返回0
        b.若数组求和区间右边界R > 被划分到区间的左边界start，同理返回0
        c.若有被划分区间正好在数组求和区间当中，即L>=start且end<=R，则直接返回被划分区间元素之和，
        对应于线段树也就是该节点的值tree[node]
        d.对应于某一划分区间中只有一个元素属于求和区间的情况，则有当start==end时返回该元素值
*/
int query_tree(int arr[],int tree[],int node,int start,int end,int L,int R){
    if(end<L||start>R){
        return 0;
    }
    else if(start>=L&&end<=R){
        return tree[node];
    }
    else if(start==end){
        return tree[node];
    }
    int mid=(start+end)/2;
    int left_node=2*node+1;
    int right_node=2*node+2;
    int sum_left=query_tree(arr,tree,left_node,start,mid,L,R);
    int sum_right=query_tree(arr,tree,right_node,mid+1,end,L,R);
    return sum_left+sum_right;
}

int main(){
    int arr[6]={1,3,5,7,9,11};
    int tree[MAX_LEN]={0};
    int size=sizeof(arr)/sizeof(int);
    
    build_tree(arr,tree,0,0,size-1);
    for(int i=0;i<15;i++){
        printf("tree[%d]=%d\n",i,tree[i]);
    }
    //首元素为36
    printf("\n");
    update_tree(arr,tree,0,0,size-1,4,6);
    for(int i=0;i<15;i++){
        printf("tree[%d]=%d\n",i,tree[i]);
    }
    //首元素为33
    
    int s=query_tree(arr,tree,0,0,size-1,2,5);
    printf("\ns=[%d]",s);
    //结果为29
    return 0;
}