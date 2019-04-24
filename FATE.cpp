//
// Created by Wong Yeah Way on 2019/4/20.
//

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
            scanf("%d %d",&a[i],&aa[i]);//输入数据
        memset(dp,0,sizeof(dp));
        for (int i = 1;i <= s;i++) {
            for (int j = 0; j < k; j++) {
                for (int q = aa[j]; q <= m; q++) {
                    dp[i][q] = max(dp[i][q], dp[i - 1][q - aa[j]] + a[j]);//状态转移方程
                }
            }
        }
        //dp里存放的是获取的经验值
        if(dp[s][m] < n)//凑不齐经验值……我认为这里应该找最大值比较啊
            //实际上不是的，因为我们最多要杀S的怪物，那么如果S都不能满足，其他的更不能满足了
            cout<<-1<<endl;
        else
        {
            for(int i=0; i<= m; i++) cout << dp[s][i] <<" ";
            cout << endl;
            for (int i = 0;i <= m;i++)
            {//下面要寻找忍耐度，题目问的是最大忍耐度
                //那么i指的是消耗的忍耐度，也就是说用给定的忍耐度减去最小的消耗忍耐度就是我们的所求
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