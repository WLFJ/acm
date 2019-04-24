//
// Created by Wong Yeah Way on 2019/4/21.
//
#include<iostream>
#include<cstring>
using namespace std;
const int MAXN = 100 + 10;
int a[MAXN], aa[MAXN];
int dp[MAXN][MAXN];
int main(void){
    int n, m, k, s;
    while(cin >> n >> m >> k >> s){
        //先保存数据
        for(int i=0; i<k; i++){
            cin >> a[i] >> aa[i];
        }
        memset(dp, 0, sizeof(dp));
        for(int i=1; i<=s; i++){
            for(int j=0; j<k; j++){
                for(int q=aa[j]; q<=m; q++){//注意！这里拿到的是j而不是i！
                    dp[i][q] = max(dp[i][q], dp[i-1][q-aa[j]] + a[j]);//注意这里是背包优化！所以上一次的数据就是当前要覆盖位置的数据！
                }
            }
        }
        if(dp[s][m] < n){//先看看最多能不能凑够经验值
            cout << -1 << endl;
        }else{
            //为什么数据会多2？
            //for(int i=0; i<= m; i++) cout << dp[s][i] <<" ";
            //cout << endl;
            //现在要找消耗忍耐度最少的方案
            for(int i=0; i<=m; i++){
                if(dp[s][i] >= n){
                    //cout << dp[s][i] << "!" << endl;
                    cout << m - i << endl;
                    break;
                }
            }
        }
    }

    return 0;
}
