#include<stdio.h>
#include<stdlib.h>

#define VERTICES 6
//并查集检测图结构中是否存在环
//初始化parent数组
void Initial(int parent[]){
    for (int i=0;i<VERTICES;i++)
        parent[i]=-1;
}

int find_root(int x,int parent[]){
    int x_root=x;
    //当x_root的父节点为-1时，说明x_root没有父节点了，即自身就是当前所在树的根节点，否则就不断寻找父节点
    while(parent[x_root]!=-1)
        x_root=parent[x_root];
    return x_root;
}

/*边构造并查集边检测是否存在环
发现环则立刻返回0，停止构建并查集
返回值为1说明没发现环
*/
int union_vertices(int x,int y,int parent[],int rank[])
{
    int x_root=find_root(x,parent);
    int y_root=find_root(y,parent);
    //分别寻找x和y的根节点，若发现二者根节点相同，说明xy已经是连通的两个顶点，则此时又有一条边连通xy，则形成环结构
    if(x_root==y_root){
        return 0;
    }
    else{                                       //x，y根节点不同，说明二者之前处于两个不连通的集合中，此时将二者连通即可，表示连通的操作就是选其中一个节点，将其根节点更新为另一节点的根节点
        //如下为优化的并查集合并操作，即将高度更低的树拼接到高度更高的树，这样树的总高度就不会增加，若二者高度相等则任意拼接，总高度+1
        if(rank[x_root]>rank[y_root])           //如果x所在树高度更高，则把y所在树作为一个分支拼接到x所在树的根节点
            parent[y_root]=x_root;
        else if(rank[y_root]>rank[x_root])      //y所在树高度更高，则把x所在树作为一个分支拼接到y所在树的根节点
            parent[x_root]=y_root;
        else{
            parent[x_root]=y_root;              //二者所在树高度一样，任意拼接都可，把高度+1
            rank[y_root]++;
        }
    }
    return 1;
}

int main(){
    int parent[VERTICES]={0};
    int rank[VERTICES]={0};     //标识每个节点的子树高度，用于拼接时使得高度较低的树拼接到高度较高的树，避免不必要的高度增加，使得不必要的搜索的时间复杂度上升
    Initial(parent);
    //无向图的边集，{0，1}说明节点0和1连通
    int Edges[6][2]={
        {0,1},{1,2},{1,3},
        {3,4},{2,5},{5,4}
    };
    
    for(int i=0;i<6;i++){
        int a=union_vertices(Edges[i][0],Edges[i][1],parent,rank);
        if(a==0){
            printf("Cycle Detected!\n");
            break;
        }
    }
    for(int i=0;i<VERTICES;i++)
        printf("%d  ",parent[i]);
    //结果为1,-1,1,1,1,1
    //printf("No Cycle Found.\n");
    
    return 0;
}