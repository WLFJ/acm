//
// Created by Wong Yeah Way on 2019/5/1.
//
#include<iostream>
#include<cstdio>
#include<cstring>
#include <queue>
using namespace std;
const int MAXN = 400 + 10;//点数的最大值
const int MAXM = 1200010;//边数的最大值
const int INF = 0x3f3f3f3f;
struct Edge{
    int to,next,cap,flow;
}edge[MAXM];//注意是MAXM
int tol;
int head[MAXN];
void init(){
    tol = 2;
    memset(head,-1,sizeof(head));
    }
void addedge(int u,int v,int w,int rw = 0){
    edge[tol].to = v; edge[tol].cap = w; edge[tol].flow = 0;
    edge[tol].next = head[u]; head[u] = tol++;
    edge[tol].to = u; edge[tol].cap = rw; edge[tol].flow = 0;
    edge[tol].next = head[v]; head[v] = tol++;
    }
int Q[MAXN];
int dep[MAXN],cur[MAXN],sta[MAXN];
bool bfs(int s,int t,int n){
    int front = 0,tail = 0;
    memset(dep,-1,sizeof(dep[0])*(n+1));
    dep[s] = 0;
    Q[tail++] = s;
    while(front < tail){
        int u = Q[front++];
        for(int i = head[u]; i != -1;i = edge[i].next){
            int v = edge[i].to;
            if(edge[i].cap > edge[i].flow && dep[v] == -1){
                dep[v] = dep[u] + 1;
                if(v == t)return true;
                Q[tail++] = v;
                }
            }
        }
    return false;
    }
int dinic(int s,int t,int n){
    int maxflow = 0;
    while(bfs(s,t,n)){
        for(int i = 0;i < n;i++)cur[i] = head[i];
        int u = s, tail = 0;
        while(cur[s] != -1){
            if(u == t){
                int tp = INF;
                for(int i = tail-1;i >= 0;i--)
                tp = min(tp,edge[sta[i]].cap-edge[sta[i]].flow)
                ;
                maxflow += tp;
                for(int i = tail-1;i >= 0;i--){
                    edge[sta[i]].flow += tp;
                    edge[sta[i]^1].flow -= tp;
                    if(edge[sta[i]].cap-edge[sta[i]].flow == 0)
                    tail = i;
                    }
                u = edge[sta[tail]^1].to;
                }
            else if(cur[u] != -1 && edge[cur[u]].cap > edge[cur[u
            ]].flow && dep[u] + 1 == dep[edge[cur[u]].to]){
                sta[tail++] = cur[u];
                u = edge[cur[u]].to;
                }
            else {
                while(u != s && cur[u] == -1)
                u = edge[sta[--tail]^1].to;
                cur[u] = edge[cur[u]].next;
                }
            }
        }
    return maxflow;
}
int main(void){
    /*
     * 一堆牛匹配一堆围栏
     * 要求怎么样匹配才能使得其利用的最多
     */
    int N, M;
    while(~scanf("%d%d", &N, &M)){
        init();
        for(int i=1; i<=N; i++){
            addedge(0, i, 1);
            int _n;
            scanf("%d", &_n);
            while(_n--){
                int stall;
                scanf("%d", &stall);
                stall += N;
                addedge(i, stall, 1);
            }
        }
        for(int i=N+1; i<=N+M; i++){
            addedge(i, N+M+1, 1);
        }
        int ans = dinic(0, N+M+1, N+M+2);
        printf("%d\n", ans);
    }
    return 0;
}