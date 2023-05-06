/*
算法基本思想：
	对图G=(V,E),构造T=(V,NULL)，T为一个无边的非连通图；且T中每个节点自成一个连通子图
	循环操作：
		从E中选择权值最小的边e，且该边必须满足其顶点处于两个连通子图中，将e加入T的边集
	当T中所有点均处在同一个连通子图上终止，此时T即为最小生成树
*/

#include<stdio.h>
#include<stdlib.h>

#define MAX 10000000

typedef struct {
	int start_vex, stop_vex; //边的起点和终点
	int weight;             //边的权值
}Edge;

int Kruskal(int (*G)[6], Edge mst[], int n) {	//n为图的顶点总数，mst存放最小生成树的边
	int num = 0;
	int start, stop, minWeight;
	//使用一个整数数组status[n]记录各个节点所属的连通子图（并查集的应用）
	int *status = (int *)malloc(sizeof(int)*n);
	//初始时各顶点的代表顶点就是本身，构造过程中修改为代表顶点的下标
	for (int i = 0; i < n; ++i)
		status[i] = i;
	while (num < n - 1) {
		minWeight = MAX;
		//遍历无向图中所有的边节点，寻找最短的边，i从第0到n-2个节点，j从第1到n-1个节点，即可遍历完所有的边
		for (int i = 0; i < n - 1; ++i)
			for (int j = 0; j < n; ++j)
				if (G[i][j] < minWeight) {
					start = i; stop = j;     //更新start为最短边的起点，stop为终点
					minWeight = G[i][j];
				}
		if (minWeight == MAX)  return 0;
		//判断加入最短边是否产生回路
		if (status[start] != status[stop]) {
			mst[num].start_vex = start;
			mst[num].stop_vex = stop;
			mst[num].weight = minWeight;
			++num;
			int j = status[stop];
			for (int i = 0; i < n; ++i) {           //更新stop及与stop相连的所有节点的代表节点
				if (status[i] == j)
					status[i] = status[start];
			}
		}
		//屏蔽此次寻得的最短边，因为不论该边是否被加入最小生成树都无法再使用了（没加入说明会构成环/已加入则无法重复加入）
		G[start][stop] = MAX;
	}
	return 1;
}

int main() {
	//图的邻接矩阵表示
	int Graph[6][6] = {
		{0,10,MAX,MAX,19,21},
		{10,0,5,6,MAX,11},
		{MAX,5,0,6,MAX,MAX},
		{MAX,6,6,0,18,14},
		{19,MAX,MAX,18,0,33},
		{21,11,MAX,14,33,0}
	};
	Edge *mst = (Edge*)malloc(sizeof(Edge) * 5);	//最小生成树的边节点个数为总顶点数-1
	int ans = Kruskal(Graph, mst, 6);
	if (ans) {
		printf("构造最短生成树成功！\n");
		for (int i = 0; i < 5; i++)
			printf("起点：%d,终点：%d,边权值为%d\n", mst[i].start_vex, mst[i].stop_vex,mst[i].weight );
	}
	/*结果如下
	构造最短生成树成功！
	起点：1,终点：2,边权值为5
	起点：1,终点：3,边权值为6
	起点：0,终点：1,边权值为10
	起点：1,终点：5,边权值为11
	起点：3,终点：4,边权值为18
	*/
	return 0;
}