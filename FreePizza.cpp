#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 100000 + 10;
int dp[MAXN][15];
int main(void){
    int n;
    while(scanf("%d", &n) , n){
        int maxT = 0;
        memset(dp, 0, sizeof(dp));
        for(int i=0; i<n; i++){
            int x,t;
            scanf("%d%d", &x, &t);
            dp[t][x]++;
            maxT = max(maxT, t);
        }
        for(int i=maxT - 1; i >= 0; i --){
            dp[i][0] += max(dp[i+1][0], dp[i+1][1]);
            for(int j=1; j<11; j++){
                dp[i][j] += max(dp[i+1][j-1], max(dp[i+1][j], dp[i+1][j+1]));
            }
        }
        printf("%d\n", dp[0][5]);
    }
    return 0;
}