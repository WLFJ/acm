//
// Created by Wong Yeah Way on 2019/5/2.
//
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
#include <string>
using namespace std;
const int MAXN = 800 + 10;//点数的最大值
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
map<string, int> idGenerator;
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
                    tp = min(tp,edge[sta[i]].cap-edge[sta[i]].flow);
                maxflow += tp;
                for(int i = tail-1;i >= 0;i--){
                    edge[sta[i]].flow += tp;
                    edge[sta[i]^1].flow -= tp;
                    if(edge[sta[i]].cap-edge[sta[i]].flow == 0)
                        tail = i;
                }
                u = edge[sta[tail]^1].to;
            }
            else if(cur[u] != -1 && edge[cur[u]].cap > edge[cur[u]].flow && dep[u] + 1 == dep[edge[cur[u]].to]){
                sta[tail++] = cur[u];
                u = edge[cur[u]].to;
            }else {
                while(u != s && cur[u] == -1)
                    u = edge[sta[--tail]^1].to;
                cur[u] = edge[cur[u]].next;
            }
        }
    }
    return maxflow;
}
inline int getID(){
    string input;
    cin >> input;
    //实现一个获得唯一id的函数
    if(idGenerator.find(input) == idGenerator.end()){
        idGenerator[input] = (int)idGenerator.size() + 1;
    }
    return idGenerator[input];
}
int main(){
    //按照题目说的，首先从s引出各种插头，然后中间连接电器，再从电器引出来
    //对于转换器，中间连边就好；用set生成id
    queue<int> conn;
    int n;
    scanf("%d", &n);
    init();
    int t = 0;
    while(n--){
        int id = getID();
        addedge(0, id, 1);
        //cout << 0 << " 11 " << id << endl;
    }
    scanf("%d", &n);
    //不行！因为里面可能出现新的没见过的插头！
    int ans = n;
    while(n--){
        //要连接从插座到用电器的边
        int b = getID(), a = getID();
        conn.push(b);//记录用电器id
        addedge(a, b, INF);
        //cout << a << " 22 " << b << endl;
    }
    scanf("%d", &n);
    while(n--){
        //插座之间可以乱连接
        int a = getID(), b = getID();
        addedge(b, a, INF);
        //cout << a << " 33 " << b << endl;
    }
    t = (int)idGenerator.size() + 1;
    while(!conn.empty()){
        addedge(conn.front(), t, 1);
        //cout << conn.front() << " 44 " << t << endl;
        conn.pop();
    }
    ans -= dinic(0, t, tol);
    //询问不能插入的设备
    cout << ans << endl;
    return 0;
}
