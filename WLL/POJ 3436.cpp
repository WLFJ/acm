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
#pragma comment (linker,"/STACK:102400000,102400000")

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
int n, m;
struct  Point {
    int x, y;
    Point (int x, int y): x(x), y(y) {}//写个构造函数方便创建
};
int cal(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);//原来是直接计算两点之间的距离！
}
char tu[105][105];
vector<Point>men;
vector<Point>home;
int main() {
    while(~sff(n, m), n + m) {//读入地图的大小
        F.init();
        men.clear();
        home.clear();
        for (int i = 0 ; i < n ; i++) {
            scanf("%s", tu[i]);
            for (int j = 0 ; j < m ; j++) {
                if (tu[i][j] == 'm') men.push_back(Point(i, j));
                if (tu[i][j] == 'H') home.push_back(Point(i, j));
            }
        }
        //上面是放点
        int s=0,len1=men.size(),len2=home.size(),t;
        t=len1+len2+1;
        for (int i=0 ;i<len1 ;i++)
            for (int j=0 ;j<len2 ;j++)
                F.add(i+1,j+1+len1,1,cal(men[i],home[j]));
        for (int i=1 ;i<=len1 ;i++) F.add(0,i,1,0);//把头连上
        for (int i=1 ;i<=len2 ;i++) F.add(i+len1,t,1,0);//尾连上
        int cost = 0;
        F.solve(s, t, cost);
        printf("%d\n", cost);
    }
    return 0;
}