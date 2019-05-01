//
// Created by Wong Yeah Way on 2019/5/1.
//
#include<iostream>
#include<cstdio>
#include<cstring>
#include <queue>
using namespace std;
/*
* SAP 算法（矩阵形式）
* 结点编号从0 开始
*/
const int MAXN=1100;
int maze[MAXN][MAXN];
int gap[MAXN],dis[MAXN],pre[MAXN],cur[MAXN];
int sap(int start,int end,int nodenum){
    memset(cur,0,sizeof(cur));
    memset(dis,0,sizeof(dis));
    memset(gap,0,sizeof(gap));
    int u=pre[start]=start,maxflow=0,aug=-1;
    gap[0]=nodenum;
    while(dis[start]<nodenum){
        loop:
        for(int v=cur[u];v<nodenum;v++)
        if(maze[u][v] && dis[u]==dis[v]+1){
            if(aug==-1 || aug>maze[u][v])aug=maze[u][v];
            pre[v]=u;
            u=cur[u]=v;
            if(v==end){
                maxflow+=aug;
                for(u=pre[u];v!=start;v=u,u=pre[u]){
                    maze[u][v]-=aug;
                    maze[v][u]+=aug;
                    }
                aug=-1;
                }
            goto loop;
            }
        int mindis=nodenum-1;
        for(int v=0;v<nodenum;v++)
            if(maze[u][v]&&mindis>dis[v]){
            cur[u]=v;
            mindis=dis[v];
            }
        if((--gap[dis[u]])==0)break;
            gap[dis[u]=mindis+1]++;
            u=pre[u];
        }
    return maxflow;
}
inline void addedge(int u, int v, int w){
    maze[u][v] = w;
}
int main(void){
    /*
     * 本题的痛点在哪里？
     * 首先便是图的同构。我们在拿到题之后先把关系用图表示出来，然后把元素的次序换一换，例如本题，
     * 先最直观的牛->食物+饮料，这样从牛开始流水自然是不行，水会把所有牛的边都瞎jb走一遍，
     * 本题的要求之一是饮料和食物各选择一个，这是一个关键信息，【各选择一个】等价于【先选择一个，再选择一个】
     * 这就说明建图时要把事物放在左边，饮料放在右边。
     * 现在我们解决了牛选择种类的问题，也便一次我们一定能选择一种事物和一种饮料，但是问题是我们需要一种手段来标记，如果这头牛
     * 已经选择了，那就不能再选择了（现在的模型因为牛是一个点，所以会有多重边共一头牛的问题）
     * 解决办法就是把牛也变成一条流量为1的边!这样当牛选择了食物饮料之后就满流无法再选择了！
     * 这样建图之后，输入流量为牛的数目，输出流量为能够满足的最多牛数目！
     *
     * 难道这个板子不能建立断边嘛？？？
     * dinic板子还需要增加重边检测的功能，如果有重边了就别tm再加了
     */
    int N, F, D;
    scanf("%d%d%d", &N, &F, &D);
    int s=1, t=s+F+2*N+D+1+1;
    for(int i=s+1;i<=s+F;i++)addedge(s, i, 1);//开始到食物
    for(int i=s+F+2*N+1;i<=s+F+2*N+D;i++)addedge(i, t, 1);//饮料到终点
    for(int i=1;i<=N;i++)addedge(s+F+2*i-1, s+F+2*i, 1);//牛之间
    for(int i=1; i<=N; i++){
        int nF, nD;
        scanf("%d%d", &nF, &nD);
        while(nF--){
            int food;
            scanf("%d", &food);
            addedge(s+food, s+F+2*i-1, 1);
        }
        while(nD--){
            int drink;
            scanf("%d", &drink);
            addedge(s+F+2*i, s+F+2*N+drink, 1);
        }
    }
    int ans = sap(s, t, t+1);
    printf("%d\n", ans);
    return 0;
}