//
// Created by Wong Yeah Way on 2019/5/2.
//
/*
 * 先翻译题目吧
 * 在他的销售区域有N个商店，从他这里进货，他有M个供货商
 * 提供了K种商品，需要最少的运送费用
 *
 * 输入
 * 多组输入
 * N M K
 * 下面N行 每行K个数字（0到3）
 * 代表商店的需求量
 * 之后M行
 * 每行K个数字 也是0~3 代表这里存放的各种商品数量
 * 之后是K个矩阵
 * 每一个都是N*M的
 * 每一个数字代表行代表商店 列代表仓库 运送的花费
 * 0 0 0输入结束
 * 如果能满足需求，则输出最小花费，否则-1
 *
 * 这道题的输入太可怕了
 * 每一个仓库都有几种商品，分别连接在另一边商店的需求之上
 */
#include <cstdio>
#include <cstring>
#include <queue>
#include <cmath>
#include <algorithm>
#include <set>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>
#define pi acos(-1.0)
#define eps 1e-6
#define fi first
#define se second
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define bug         printf("******\n")
#define mem(a,b)    memset(a,b,sizeof(a))
#define fuck(x)     cout<<"["<<x<<"]"<<endl
#define f(a)        a*a
#define sf(n)       scanf("%d", &n)
#define sff(a,b)    scanf("%d %d", &a, &b)
#define sfff(a,b,c) scanf("%d %d %d", &a, &b, &c)
#define pf          printf
#define FRE(i,a,b)  for(i = a; i <= b; i++)
#define FREE(i,a,b) for(i = a; i >= b; i--)
#define FRL(i,a,b)  for(i = a; i < b; i++)
#define FRLL(i,a,b) for(i = a; i > b; i--)
#define FIN freopen("DATA.txt","r",stdin)
#define lowbit(x)   x&-x
//#pragma comment (linker,"/STACK:102400000,102400000")

using namespace std;
const int maxn = 1e5 + 10;
typedef long long LL;
const int MX = 505;
const int inf = 0x3f3f3f3f;
const int MXE = MX * MX * 4;

struct MinCost_MaxFlow {
    struct Edge {
        int v, w, nxt;
        int cost;
    } E[MXE];
    int head[MX], tot, level[MX], pre[MX], d[MX];
    bool vis[MX];
    void init() {
        memset(head, -1, sizeof(head));
        tot = 0;
    }
    void add(int u, int v, int w, int cost) {
        E[tot].v = v;
        E[tot].w = w;
        E[tot].cost = cost;
        E[tot].nxt = head[u];
        head[u] = tot++;
        E[tot].v = u;
        E[tot].w = 0;
        E[tot].cost = -cost;
        E[tot].nxt = head[v];
        head[v] = tot++;
    }
    bool spfa(int s, int t) {
        memset(vis, 0, sizeof(vis));
        memset(d, 0x3f, sizeof(d));
        memset(pre, -1, sizeof(pre));
        queue<int>q;
        q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (int i = head[u]; ~i; i = E[i].nxt) {
                int w = E[i].w, v = E[i].v, cost = E[i].cost;
                if (w > 0 && d[v] > d[u] + cost) {
                    d[v] = d[u] + cost;
                    pre[v] = i;
                    if (!vis[v]) {
                        q.push(v);
                        vis[v] = 1;
                    }
                }
            }
        }
        //如果是最小费用可行流则要这一句(要求费用最小,不要求流量最大)
        //if (d[t] > 0) return false;
        return pre[t] != -1;
    }
    int solve(int s, int t, int &cost) {
        int flow = 0;
        cost = 0;
        while (spfa(s, t)) {
            int minFlow = inf;
            for (int i = pre[t]; ~i; i = pre[E[i ^ 1].v])
                minFlow = min(minFlow, E[i].w);
            for (int i = pre[t]; ~i; i = pre[E[i ^ 1].v]) {
                cost += minFlow * E[i].cost;
                E[i].w -= minFlow;
                E[i ^ 1].w += minFlow;
            }
            flow += minFlow;
        }
        return flow;
    }
} F;
int main(void){
    int N, M, K;MinCost_MaxFlow Solver;
    while(~sfff(N, M, K)){
        Solver.init();
        //我觉得商店应该建在下游
        //先处理N行的商店需求量（也便是先建立流量边）
        /*
         * 建图约定
         * 开始位置1 结束位置2
         * 用于表示不同商店的接口 2+k k代表第几个商品
         * 商店 2+K+i
         * 仓库 2+K+N+i
         */
        for(int i=1; i<=N; i++){
            //现在要建立的是接口->商店
            for(int j=1; j<=K; j++){
                int need;
                sf(need);
                if(need)
                Solver.add(2+j, 2+K+i, need, 0);
            }
            //商店->T
            Solver.add(2+K+i, 2, inf, 0);//应该收到多少流量？满足条件的应该是接口->商店的所有边都满足了，之后再计算一下
        }
        for(int i=1; i<=M; i++){
            //现在处理的是货物的存量
            for(int j=1; j<=K; j++){
                //仓库-》接口
                int stock;
                sf(stock);
                if(stock)
                    Solver.add(2+K+N+i, 2+j, stock, 0);
            }
            //S->仓库
            Solver.add(1, 2+K+N+i, inf, 0);
        }
        //下面需要根据物品矩阵来添加边的cost
        //因为不会处理前向星，我先去学习一下……要不然离线处理？？？
    }


    return 0;
}
