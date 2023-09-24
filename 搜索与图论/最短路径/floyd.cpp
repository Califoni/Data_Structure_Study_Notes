#include<stdlib.h>
#include<stdio.h>
/*
    基本思想：
        该算法以关系矩阵为基础，
        把关系矩阵看作没有经过任何中间节点，直接可以到达的每一对顶点间的最短路径的完整表示
        然后经过多次迭代，每次增加一个新的节点，
        在允许该节点作为中间节点的条件下，计算每一对顶点间的最短路径的缩短变化，直到把所有节点考虑进去为止
*/
#define VN 4
#define MAXINT 1000

typedef struct{
    char vexs[VN];          //顶点信息
    float arcs[VN][VN];     //边权信息
}Graph;

typedef struct{
    float a[VN][VN];        //存放每对顶点间最短路径长度
    int nextvex[VN][VN];    //存放vi到vj最短路径上vi的后继节点的下标值
}shortPath;

void floyd(Graph*g,shortPath*p){
    int i,j,k;
    //初始化最短路径
    for(i=0;i<VN;++i)
        for(j=0;j<VN;++j){                                  //初始化最短路径中节点的后继节点下标值
            if(g->arcs[i][j]!=MAXINT)p->nextvex[i][j]=j;
            else p->nextvex[i][j]=-1;                       //节点之间不连通，则令后继为-1
            p->a[i][j]=g->arcs[i][j];
        }
    
    
    for(k=0;k<VN;++k)           //依次加入各个顶点作为中间节点
        for(i=0;i<VN;++i)       //接下来遍历每一对顶点
            for(j=0;j<VN;++j)
            {
                if(p->a[i][j]>(p->a[i][k]+p->a[k][j])){
                    p->a[i][j]=(p->a[i][k]+p->a[k][j]);       //由于加入了k作为中间节点，故i->j最短路径实际为i->k->j，显然最短路径上i的后继节点下标应更新为i->k最短路径的后继节点下标值
                    p->nextvex[i][j]=p->nextvex[i][k];
                }
            }
}

void find_shortest_path(shortPath*p,Graph*g){
    int m,n;
    for(int i=0;i<VN;++i){                              //遍历nextvex数组，寻找每个节点到其他节点的最短路径
        printf("\n以%c为源的最短路径：\n",g->vexs[i]);
        for(int j=0;j<VN;++j){                          //寻找节点g->vexs[i]到节点g->vexs[j]的最短路径
            if(p->a[i][j]<MAXINT){                      //两节点连通
                printf("最短路径长度为%1.f:\t",p->a[i][j]);
                printf("%c",g->vexs[i]);                //输出最短路径上的节点
                m=i;n=j;
                while(p->nextvex[m][n]!=m){             //当前出发节点与目标节点不同，若出发节点与目标节点相同则说明已经到达g->vexs[j]，最短路径节点已经全部输出
                    printf("->%c",g->vexs[p->nextvex[m][n]]);
                    m=p->nextvex[m][n];                 //更新出发节点到最短路径中当前节点的后继节点
                }    
            }
            else printf("%c到%c之间不存在通路",g->vexs[i],g->vexs[j]);
            printf("\n");
        }
    }
}

int main(){
    
    //初始化图信息
    Graph g;
    g.vexs[0]='a';
    g.vexs[1]='b';
    g.vexs[2]='c';
    g.vexs[3]='d';
   
    for(int i=0;i<VN;++i)
        for(int j=0;j<VN;++j)
            g.arcs[i][j]=MAXINT;
    g.arcs[0][1]=5;
    g.arcs[0][3]=10;
    g.arcs[1][3]=2;
    g.arcs[2][0]=3;
    g.arcs[3][1]=12;
    g.arcs[3][2]=3;
    g.arcs[0][0]=0;     //注意，此处需要把每个节点到自己的距离更新为0，否则遇到环路时出现b->d->b比b->b距离小的情况，从而导致最短路径出错
    g.arcs[1][1]=0;
    g.arcs[2][2]=0;
    g.arcs[3][3]=0;

    
    shortPath*path=(shortPath*)malloc(sizeof(shortPath));
    floyd(&g,path);
    
    printf("nextvex数组如下所示：\n");
    for(int i=0;i<VN;++i)
    {
        for(int j=0;j<VN;++j)
            printf("%d  ",path->nextvex[i][j]);
        printf("\n");
    }     

    find_shortest_path(path,&g);        // 寻找所有节点的最短路径并输出
    
    return 0;
}
