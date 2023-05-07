/*
题目来源：acwing.com
题目如下：
n− 皇后问题是指将 n 个皇后放在 n×n 的国际象棋棋盘上，使得皇后不能相互攻击到，即任意两个皇后都不能处于同一行、同一列或同一斜线上。
现在给定整数 n，请你输出所有的满足条件的棋子摆法。

输入格式
	共一行，包含整数 n。

输出格式
	每个解决方案占 n 行，每行输出一个长度为 n 的字符串，用来表示完整的棋盘状态。
	其中 . 表示某一个位置的方格状态为空，Q 表示某一个位置的方格上摆着皇后。
	每个方案输出完成后，输出一个空行。
注意：行末不能有多余空格。
	输出方案的顺序任意，只要不重复且没有遗漏即可。

数据范围
1≤n≤9

输入样例：
4

输出样例：
.Q..
...Q
Q...
..Q.

..Q.
Q...
...Q
.Q..
*/

/*
题解：
	大体思想：
		使用深度遍历的方法搜索所有的可能结果，亦可理解为暴力搜索。边搜索边进行判断这种情况是否可行，若不可行则直接返回，即不再往下进行搜索，该操作称为剪枝。
	实现细节：
		1.数据结构构思：用一个二维数组matrix保存棋盘。按行搜索，故行必定不冲突，则只需要设置三个bool数组，分别监控 列冲突col[]、正对角线冲突st[]、反对角线冲突rst[]。
		2.数组初始化：经过计算容易知道对于n*n的矩阵来说，它包含n列->col[n],分别包含2*n-1个正对角线和反对角线->st[2*n-1],rst[2*n-1]
		3.每次按行遍历矩阵matrix，若当前行找到一个位置（i,j）可以放置皇后时，更新matrix[i][j]以及对应的监控数组col/st/rst,然后进入下一行寻找可行位置，
		若当前行找不到可行位置了则回退到上一行
		4.一个难点是如何监控对角线是否冲突，发现同一个对角线上的元素满足如下性质：
			同一个正对角线(左下右上)上的元素matrix[i][j],有i+j相等
			同一个反对角线(左上右下)上的元素matrix[i][j],有i-j相等
			因此只要将matrix[i][j]更新为'Q'（放置皇后）时，将st[i+j]和rst[i-j]同时更新为true(已被占领)即可
			需要注意的是对于matrix[0][1]之类的i<j的元素求i-j有i-j<0,即rst[i-j]数组越界，
			极端情况是matrix[0][n-1],此时	i-j=-(n-1)	因此把i-j上移到i-j+(n-1)即可。
*/
#include<stdio.h>
#include<stdlib.h>

void dfs(int n,char**matrix,bool*st,bool*rst,bool*col,int Row) {	//当前遍历第Row行
	if (Row == n) {			//递归出口，到最后一行有可行情况直接输出结果
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				printf("%c", matrix[i][j]);
			printf("\n");
		}
		printf("\n");
		return;
	}
	int i = Row;
	for (int j = 0; j < n; ++j) {
		if (col[j] == false && st[i + j] == false && rst[i - j + n-1] == false) {
			matrix[i][j] = 'Q';
			col[j] = true;st[i + j] = true;rst[i - j + n-1] = true;
			dfs(n, matrix, st, rst, col,++Row,0);
			//回溯，恢复现场进行下一种情况的判断
			--Row;
			matrix[i][j] = '.';
			col[j] = false; st[i + j] = false; rst[i - j + n - 1] = false;
		}
	}
	return;
}

int main() {
	int n;
	scanf("%d", &n);
	//构建n*n的棋盘，每个位置初始化为'.'
	char**matrix = (char**)malloc(sizeof(char*)*n);
	for (int i = 0; i < n; i++)
	{
		matrix[i] = (char*)malloc(sizeof(char)*n);
		for (int j = 0; j < n; j++)matrix[i][j] = '.';
	}
	//构建两个布尔类型的数组用于判断对角线是否会冲突,初始化为false表示未冲突
	bool*st = (bool*)malloc(sizeof(bool)*(2 * n - 1));
	bool*rst = (bool*)malloc(sizeof(bool)*(2 * n - 1));
	//按行遍历，所以行必不会冲突，故只需要列数组判断冲突
	bool*col= (bool*)malloc(sizeof(bool)*n);
	for (int i = 0; i < n; ++i) col[i] = false;
	for (int i = 0; i < 2*n-1; ++i) st[i] = rst[i] = false;

	dfs(n, matrix, st, rst,col,0);
	return 0;
}