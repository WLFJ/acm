//
// Created by Wong Yeah Way on 2019/4/20.
//
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 100000 + 10;
typedef unsigned long long ull;
ull dp[MAXN];
struct node{
    ull x, T;
    friend bool operator < (const node n1, const node n2){
        return n1.T < n2.T;
    }
}pizza[MAXN];
int main(void){
    int n;
    while(cin >> n){
        for(int i=1; i<=n; i++) scanf("%d%e", &pizza[i].x, &pizza[i].T);
        sort(pizza, pizza + n);
        //保证时间是有序的
        //我要拿最多的馅饼，就要放弃一些。哪些馅饼会被放弃呢
        //似乎应该DP时间，再当前时间内计算需要的
        //还需要判断在规定时间内能否赶到

        for(int i=1; i<=n; i++){

        }
    }

    return 0;
}
