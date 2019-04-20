//
// Created by Wong Yeah Way on 2019/4/20.
//
#include<iostream>
using namespace std;
struct node{
    int a, b;
}Data[105];
int dp[105][105];
int s[105];
int main(void){
    //拿一个数组存s
    //那么就需要每次都max，这样可以保证取出的数字是最小的
    //背包大小m，需要的价值n，问能不能拿不到s个数字凑出这个n以上的数字
    //还是个无限背包（好解决，相当于多了一个来源状态
    int n, m, k, s_;
    while(cin >> n >> m >> k >> s_){
        //每种怪物都记录一下
        fill(dp[0], dp[0] + 104, 0);
        fill(s, s+105, 0);
        for(int i=1; i<=k; i++) cin >> Data[i].a >> Data[i].b;
        //数据输入完成
        for(int i=1; i<=k; i++){
            for(int j=0; j<=m; j++){
                if(s[i] == s_) continue;
                if(Data[i].b > j){
                    //继承之前的状态，这个位置不放
                    dp[i][j] = dp[i-1][j];
                    s[i] = s[i-1];
                }else{
                    //可以放，那就要看哪种最优了
                    dp[i][j] = max(max(dp[i-1][j - Data[i].b] + Data[i].a, dp[i][j - Data[i].b] + Data[i].a), dp[i-1][j]);
                    if(dp[i][j] != dp[i-1][j]){
                        if(dp[i][j] == dp[i-1][j - Data[i].b] + Data[i].a) s[i] = s[i-1] + 1;
                        else s[i] ++;
                    }else s[i] = s[i-1];//没改变
                }
            }
        }
        int ans = dp[k][m] - n;
        if(s[k] <= s_ && ans >= 0) cout << ans << endl;
        else cout << -1 << endl;
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <algorithm>
#include <queue>
#include <math.h>
#define INF 1e8

using namespace std;
int n,m,k,s;
int dp[100][100];
int a[100],aa[100];
int main(void)
{
    while (scanf("%d %d %d %d",&n,&m,&k,&s)!=EOF)
    {
        for (int i = 0;i < k;i++)
            scanf("%d %d",&a[i],&aa[i]);
        memset(dp,0,sizeof(dp));
        for (int i = 1;i <= s;i++)//最多杀怪数
        {
            for (int j = 0;j < k;j++)//怪的种数
            {
                for (int q = aa[j];q <= m;q++)//保留的忍耐度
                {
                    //三维数组优化
                    dp[i][q] = max(dp[i][q],dp[i-1][q-aa[j]]+a[j]);//状态转移方程
                }
            }
        }
        //dp里存放的是获取的经验值
        if(dp[s][m] < n)//凑不齐经验值
            cout<<-1<<endl;
        else
        {
            for (int i = 0;i <= m;i++)
            {
                if(dp[s][i]>=n)
                {
                    cout<<m-i<<endl;
                    break;
                }//找到最小的忍耐度，输出，结束
            }
        }
    }
    return 0;
}