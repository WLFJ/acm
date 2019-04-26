//
// Created by Wong Yeah Way on 2019/4/26.
//
//floyd传递闭包
//如果某一个节点的出度+入读 = 顶点数目 - 1 则可以确定其排名
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int MAXN = 101;
int map[MAXN][MAXN];
int n, m;
void Floyd(){
    int i, j, k;
    for(k=1; k<=n; k++){
        for(i = 1; i<=n; i++){
            for(j=1; j<=n; j++){
                map[i][j] = map[i][j] || (map[i][k] && map[k][j]);
            }
        }
    }
}
int main(void){
    scanf("%d%d", &n, &m);
    memset(map, 0, sizeof(map));
    int i, j, u, v;
    for(i=0; i<m; i++){
        scanf("%d%d", &u, &v);
        map[u][v] = 1;
    }
    Floyd();
    int ans, res = 0;
    for(i=1; i<=n; i++){
        ans = 0;
        for(j=1; j<=n; j++){
            if(i == j) continue;
            else if(map[i][j] || map[j][i]) ans ++;
        }
        if(ans == n - 1) res ++;
    }
    printf("%d\n", res);
    return 0;
}
