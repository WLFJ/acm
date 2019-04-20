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
ull dp[MAXN][MAXN];
ull Data[MAXN];
int main(void){
    int N;
    while(cin >> N && N){
        for(int i=1; i<=N; i++){
            cin >> Data[i];
        }
        memset(dp, 0, sizeof(dp));
        for(int i=1; i<=N; i++){
            for(int k=1; k<=N; k++){
                if(i == 1 || k == 1)dp[i][k] = Data[i];
                else{
                    //大数截断有很多种情况
                    //紧接在升序之后的小数字
                    if(Data[i-1] >= Data[i]) dp[i][k] = max(dp[i-1][k-1], Data[i]);
                    //小数字之后的升序数字
                    else if(Data[i-2] >= Data[i-1] && Data[i-1] < Data[i-2]) dp[i][k] = max(dp[i-2][k-2])
                }
            }
        }
        cout << dp[N][N] << endl;
    }
    return 0;
}