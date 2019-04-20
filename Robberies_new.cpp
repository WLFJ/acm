//
// Created by Wong Yeah Way on 2019/4/20.
//
#include<string.h>
#include<cstdio>
#include<iostream>
using namespace std;
int v[110];
float dp[10010], w[110];
int main(void){
    int T;
    scanf("%d", &T);
    while(T--){
        memset(dp, 0, sizeof(dp));
        float P = 0;
        int sum = 0, n;
        scanf("%f%d", &P, &n);
        P = 1 - P;
        for(int i=1; i<=n; i++){
            scanf("%d%f", &v[i], &w[i]);
            sum += v[i];//为什么要计算总钱数 因为要用优化数组
            w[i] = 1 - w[i];//为什么要计算成逃跑成功的概率？因为计算最大的成功概率便于写程序！
        }
        dp[0] = 1;//注意dp也是要有初始值的
        //01背包倒向维护
        for(int i=1; i<=n; i++){
            for(int j = sum; j>=v[i]; j--){
                dp[j] = max(dp[j], dp[j - v[i]] * w[i]);//因为这里我们希望使用max。反正概率要考虑一下有相反的情况
            }
        }
        int i;
        for(i=sum; i>=0; i--){
            if(dp[i] >= P) break;
        }
        printf("%d\n", i);
    }
    return 0;
}