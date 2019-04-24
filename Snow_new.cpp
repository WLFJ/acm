//
// Created by Wong Yeah Way on 2019/4/21.
//
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 100 + 10;
const int Next[][2] = {0,1,1,0,-1,0,0,-1};
int maze[MAXN][MAXN], Len[MAXN][MAXN];
int R, C;
int dp(int x, int y){
    if(Len[x][y]) return Len[x][y];
    int maxL = 0;
    for(int i=0; i<4; i++){
        int nextX = x + Next[i][0];
        int nextY = y + Next[i][1];
        if(nextX < 0 || nextX >= R || nextY < 0 || nextY >= C) continue;
        if(maze[nextX][nextY] < maze[x][y]){
            int l = dp(nextX, nextY);
            maxL = max(maxL, l);
        }
    }
    Len[x][y] = maxL + 1;
    return Len[x][y];
}
int main(void){
    while(cin >> R >> C){
        memset(Len, 0, sizeof(Len));
        for(int i=0; i<R; i++){
            for(int j=0; j<C; j++){
                scanf("%d", &maze[i][j]);
            }
        }
        //数据处理完成！
        int ans = -1;
        for(int i=0; i<R; i++){
            for(int j=0; j<C; j++){
                ans = max(ans, dp(i, j));
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
