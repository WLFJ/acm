//
// Created by Wong Yeah Way on 2019/5/1.
//
/*
 * 有N个仓库存放化学药品，M条边运送，边带有开销
 * 现在让找两条路，不能有重边，当然这两条路的运送开销要最小
 * 还可能有没有解的情况（无非有孤岛，或者出现哑铃型）
 * 不知道板子能不能帮我解决这个问题啊
 */
/*
 * 寻找两条完全不同的路，使得费用最小
 */
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN = 10000;
const int MAXM = 100000;
const int INF = 0x3f3f3f3f;
struct Edge{
    int to,next,cap,flow,cost;
}edge[MAXM];
int head[MAXN],tol;
int pre[MAXN],dis[MAXN];
bool vis[MAXN];
int N;//节点总个数，节点编号从0∼N-1
void init(int n){
    N = n;
    tol = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int cap,int cost){
    edge[tol].to = v;
    edge[tol].cap = cap;
    edge[tol].cost = cost;
    edge[tol].flow = 0;
    edge[tol].next = head[u];
    head[u] = tol++;
    edge[tol].to = u;
    edge[tol].cap = 0;
    edge[tol].cost = -cost;
    edge[tol].flow = 0;
    edge[tol].next = head[v];
    head[v] = tol++;
}
bool spfa(int s,int t){
    queue<int>q;
    for(int i = 0;i < N;i++){
        dis[i] = INF;
        vis[i] = false;
        pre[i] = -1;
    }
    dis[s] = 0;
    vis[s] = true;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1;i = edge[i].next){
            int v = edge[i].to;
            if(edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge
            [i].cost )
            {
                dis[v] = dis[u] + edge[i].cost;
                pre[v] = i;
                if(!vis[v]){
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    if(pre[t] == -1)return false;
    else return true;
}
//返回的是最大流，cost 存的是最小费用
int minCostMaxflow(int s,int t,int &cost){
    int flow = 0;
    cost = 0;
    int cnt = 0;
    while(spfa(s,t)){
        int Min = INF;
        for(int i = pre[t];i != -1;i = pre[edge[i^1].to]){
            if(Min > edge[i].cap - edge[i].flow)
                Min = edge[i].cap - edge[i].flow;
        }
        for(int i = pre[t];i != -1;i = pre[edge[i^1].to]){
            edge[i].flow += Min;
            edge[i^1].flow -= Min;
            cost += edge[i].cost * Min;//关键在这里，我们应该等到两条路都找到的时候再相加！
            //怎样判断这个循环是不是到最后了呢？不断判断的是s到t的连通性
        }
        //到这里就已经找到一条s到t的最短路了！
        flow += Min;
        cnt++;
    }
    if(cnt != 2)cost = -1;
    return flow;
}

int main(void){
    int N, M, kase = 1;
    while(~scanf("%d%d", &N, &M),M+N){
        int s = 1, t = N+2;
        init(N+3);
        addedge(s, 2, 2, 0);
        for(int i=1; i<=M; i++){
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            addedge(u+2, v+2, 1, w);
        }
        addedge(t-1, t, 2, 0);
        int ans;
        minCostMaxflow(s, t, ans);
        if(ans == -1)printf("Instance #%d: Not possible\n", kase++);
        else printf("Instance #%d: %d\n", kase++, ans);
    }
    return 0;
}