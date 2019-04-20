//
// Created by Wong Yeah Way on 2019/4/20.
//
#include<iostream>
#include<string.h>
const int MAXN = 1000 + 10;
using namespace std;
int Data[MAXN], dp[MAXN];
int main(void){
    int N;
    while(cin >> N){
        for(int i=1; i<=N; i++)cin >> Data[i],dp[i] = 1;
        int ans = 1;
        for(int i=1; i<=N; i++){
            for(int j=1; j<i; j++){
                if(Data[j] < Data[i]){
                    dp[i] = max(dp[j] + 1, dp[i]);//注意！DP找最大值的时候要把所有的都看过去才行！
                    ans = max(ans, dp[i]);
                }
            }
        }
        cout << dp[N] << endl;
    }

    return 0;
}
