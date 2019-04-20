//
// Created by Wong Yeah Way on 2019/4/20.
//
#include<iostream>
using namespace std;
const int MAXV = 1000 + 10, MAXN = 1000 + 10;
typedef unsigned long long ull;
ull dp[MAXN][MAXV];
ull w[MAXN], v[MAXN];
int main(void){
    int T;
    cin >> T;
    while(T--){
        int N, V;
        cin >> N >> V;
        fill(dp[0], dp[0] + MAXN * MAXN, 0);
        for(int i=1; i<=N; i++) cin >> w[i];
        for(int i=1; i<=N; i++) cin >> v[i];
        //输入完成
        for(int i=1; i<=N; i++){
            for(int j = 0; j<=V; j++){//背包体积必须要从0开始！
                if(j < v[i]) dp[i][j] = dp[i-1][j];
                else
                    dp[i][j] = max(dp[i-1][j-v[i]]+w[i], dp[i-1][j]);
            }
        }
        cout << dp[N][V] << endl;
    }
    return 0;
}
