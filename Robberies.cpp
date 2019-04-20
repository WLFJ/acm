//
// Created by Wong Yeah Way on 2019/4/20.
//
/*
 * 相当于限制了背包的容量
 * 注意！浮点数没说是两位！只能拿金额当作背包容量，计算最小的抓捕概率
 */
/*此题关键是找到背包的容量和价值*/
#include<stdio.h>
#include<math.h>
#include<string.h>
#define MAX(a,b) (a>b?a:b)
int main()
{
    int T, i, j, n, M[110];
    float P, p[110], dp[10010];//用float 类型就行了， 用double 类型会导致数据缺失。
    scanf("%d",&T);
    while(T--)
    {
        memset(dp,0,sizeof(dp));//要对数组进行初始化
        int sum = 0;
        scanf("%f%d",&P,&n);
        P = 1 - P;//成功逃走的概率
        for(i = 1; i <= n; i++)
        {
            scanf("%d%f",&M[i],&p[i]);
            sum += M[i];//算出银行总钱数
            p[i] = (1 - p[i]);
        }
        dp[0] = 1;//未抢劫一分钱那么逃走的概率就为1
        for(i = 1; i <= n; i++)
        {
            for(j = sum; j >= M[i]; j--)
            {
                dp[j] = MAX(dp[j],dp[j - M[i]] * p[i]);//这里的每次成功的概率需要进行乘法运算，因为是两次成功的概率所以是乘法
            }
        }
        for(i = sum; i >= 0; i--)
        {
            if(dp[i] >= P)
            {
                break;//找出可以成功逃走并且逃走概率不超过警戒值
            }
        }
        printf("%d\n",i);
    }
    return 0;
}