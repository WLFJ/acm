//
// Created by Wong Yeah Way on 2019/4/20.
//
#include<iostream>
using namespace std;
const int MAXN = 1000 + 10;
int dp[MAXN];
int Data[MAXN];
int main(void){
    //计算升序数组的个数
    int N;
    while(cin >> N && N){
        fill(dp, dp + N + 1, 1);//最重要的就是注意dp的初始条件
        for(int i=1; i<=N; i++)cin >> Data[i];
        //输入数据完成
        int ans = 0;
        for(int i=1; i<=N; i++){
            for(int j=1;j<=i;j++){
                if(Data[j] < Data[i]){
                    dp[i] = max(dp[j] + 1, dp[i]);
                    ans = max(ans, dp[i]);
                }
            }
        }
        cout << ans << endl;
        //for(int i=0; i<=N; i++)cout << dp[i] << " ";
    }
    return 0;
}