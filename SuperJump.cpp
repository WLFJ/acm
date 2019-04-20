//
// Created by Wong Yeah Way on 2019/4/20.
//

/*
 * 相当于求最大的连续上升子序列
 */
#include<iostream>
#include<cstring>
using namespace std;
const int MAXN = 1000 + 10;
typedef unsigned long long ull;
ull dp[MAXN];
ull Data[MAXN];
int main(void){
    int N;
    while(cin >> N && N){
        for(int i=1; i<=N; i++){
            cin >> Data[i];
        }
        memset(dp, 0, sizeof(dp));
        //之前那道题的DP是求夹杂在其中的上升公共子序列数目，和现在这个还是不一样
        ull ans = Data[1];
        dp[1] = Data[1];
        for(int i=2; i<=N; i++){
            for(int j=1; j<=i; j++){
                if(Data[j] < Data[i])//如果第一个数字大，第二个数字小，那么第二个数字就无法放进来！
                    dp[i] = max(dp[i], dp[j] + Data[i]);
                if(dp[i] == dp[j] + Data[i]) cout << Data[i] << " ";
            }
            //经过调试，这样就把1拿进来了
            dp[i] = max(dp[i], Data[i]);
            if(dp[i] == Data[i]) cout << dp[i] << " ";
            ans = max(ans, dp[i]);
        }
        cout << ans << endl;
    }
    return 0;
}