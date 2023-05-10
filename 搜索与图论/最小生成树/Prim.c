/*
算法基本思想：
	对于图G=(V,E),令T=(U,TE)为其最小生成树（初始为空）
	初始化：
		先从V中任意取一个点v0加入U中，此时U={v0},TE=NULL
	循环操作：
		寻找U中所有点的关联边，保留其中若干边，被保留的边必须具备如下性质：
			可知每条边有两个关联顶点，易知上述所有边的一个关联顶点属于集合U,则被保留的边的另一个顶点必定属于集合(V-U)，即被保留边的两个顶点属于两个不同集合
		然后在被保留的边中寻找权值最小的将其加入TE，关联的另一个顶点加入U
		观察新加入最小生成树的顶点a到其他属于V-U的顶点的距离，若小于原先距离则进行更换
	当U=V时结束循环
*/

#include<stdio.h>
#include<stdlib.h>

#define MAX 1e8

typedef struct{
    int start_vex,stop_vex; //边的起点和终点
    int weight;             //边的权值
}Edge;

void Prim(int(*G)[6],Edge*mst,int n){
    int i;
    for(i=0;i<n-1;++i){
        mst[i].start_vex=0;
        mst[i].stop_vex=i+1;    //初始化为v0到v(i+1)的边信息
        mst[i].weight=G[0][i+1];
    }
    
    int min,j,vx,vy;  Edge e;
    for(i=0;i<n-1;++i){
        min=i;
        for(j=i;j<n-1;++j)      //寻找当前集合U到V-U顶点的最短边
            if(mst[min].weight>mst[j].weight)
                min=j;
        e=mst[min];             //更新mst[i],即将最短边加入最小生成树
        mst[min]=mst[i];
        mst[i]=e;
        vx=mst[i].stop_vex;     //记录新加入最小生成树的顶点
        for(j=i+1;j<n-1;++j){   //最小生成树0~i的边都已经确定了，因此从i+1开始调整
            vy=mst[j].stop_vex; //发现新加入的顶点到对应顶点更短，进行调整
            if(G[vx][vy]<mst[j].weight){
                mst[j].weight=G[vx][vy];
                mst[j].start_vex=vx;
            }
        }
    }
    return;
}

int main(){
    //图的邻接矩阵表示
    int Graph[6][6]={
        {0,10,MAX,MAX,19,21},
        {10,0,5,6,MAX,11},
        {MAX,5,0,6,MAX,MAX},
        {MAX,6,6,0,18,14},
        {19,MAX,MAX,18,0,33},
        {21,11,MAX,14,33,0}
    };
    //初始化最小生成树的总边数为n-1
    Edge *mst=(Edge*)malloc(sizeof(Edge)*5);
    Prim(Graph,mst,6);
    
    for(int i=0;i<5;i++)
        printf("起点：%d,终点：%d,权值：%d\n",mst[i].start_vex,mst[i].stop_vex,mst[i].weight);
    /*结果如下：
    起点：0,终点：1,权值：10
    起点：1,终点：2,权值：5
    起点：1,终点：3,权值：6
    起点：1,终点：5,权值：11
    起点：3,终点：4,权值：18
    */
    return 0;
}