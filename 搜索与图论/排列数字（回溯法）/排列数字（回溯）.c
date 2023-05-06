/*
题目来源：acwing.com
题目如下：
给定一个整数 n，将数字 1∼n 排成一排，将会有很多种排列方法。现在，请你按照字典序将所有的排列方法输出。

输入格式
共一行，包含一个整数 n。

输出格式
按字典序输出所有排列方案，每个方案占一行。

数据范围
1≤n≤7

输入样例：
3
输出样例：
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
*/

#include<stdio.h>
#include<stdlib.h>
const int N=7;
int path[N];    //存放每一次排列的结果

//使用（暴力搜索/深度遍历）的思想
/*
参数说明：
    n表示共有n个数字进行排列，
    idx表示当前处在第idx的位置进行选择数字，
    比如n=3时对第一个位置有3种选择，则此时idx=1
*/
void dfs(int n,int idx,bool*st){    
    if(idx==n){
        for(int i=0;i<n;i++)
            printf("%d ",path[i]);
        printf("\n");
    }
    else{
        for(int i=1;i<=n;i++){
            if(st[i]!=true){    //说明此时数字i没被使用过
                st[i]=true;
                path[idx]=i;    //将第idx位置的数字置为i，进入下一个位置的选择
                dfs(n,idx+1,st);
                st[i]=false;	//每次输出一种排序后回溯到之前的节点，需要恢复现场
            }
        }
    }
}

int main(){
    int n;  
    scanf("%d",&n);
    bool *st=(bool*)malloc(sizeof(bool)*(n+1));  //表示每个数字是否被使用，被使用则置为true
    dfs(n,0,st);
    return 0;
}