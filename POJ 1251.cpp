//
// Created by Wong Yeah Way on 2019/4/25.
//
//粘板子就是爽
 /*
 * Kruskal 算法求 MST
 */
#include<cstdio>

#include<cstring>

#include<algorithm>

#include<iostream>
 using namespace std;
 const int MAXN=110;//最大点数
 const int MAXM=10000;//最大边数
 int F[MAXN];//并查集使用
 struct Edge{
     int u,v,w;
     }edge[MAXM];//存储边的信息，包括起点/终点/权值
 int tol;//边数，加边前赋值为 0
 void addedge(int u,int v,int w){
     edge[tol].u=u;
     edge[tol].v=v;
     edge[tol++].w=w;
     }
 //排序函数，讲边按照权值从小到大排序
 bool cmp(Edge a,Edge b){
     return a.w<b.w;
     }
 int find(int x){
     if(F[x]==-1)return x;
     else return F[x]=find(F[x]);
     }
 //传入点数，返回最小生成树的权值，如果不连通返回 -1
 int Kruskal(int n){
     memset(F,-1,sizeof(F));
     sort(edge,edge+tol,cmp);
     int cnt=0;//计算加入的边数
     int ans=0;
     for(int i=0;i<tol;i++){
         int u=edge[i].u;
         int v=edge[i].v;
         int w=edge[i].w;
         int t1=find(u);
         int t2=find(v);
         if(t1!=t2){
             ans+=w;
             F[t1]=t2;
             cnt++;
             }
         if(cnt==n-1)break;
         }
     if(cnt<n-1)return -1;//不连通
     else return ans;
     }
int main(void){
    int N;
    while(cin >> N && N){
        tol = 0;
        N--;
        while(N--){
            char start;int n;
            cin >> start >> n;
            int s = start ^ 'A';
            while(n--){
                char end; int e, w;
                cin >> end >> w;
                e = end ^ 'A';
                addedge(s, e, w);
            }
        }
        cout << Kruskal(N + 1) << endl;
    }

     return 0;
 }