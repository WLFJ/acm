//
// Created by Wong Yeah Way on 2019/4/16.
//
/*
 * 还是Supermarket这道题目
 * 之前的做法是通过从后往前枚举结束时间，看一下当前供选择的列表里的最优解
 * 或者我们可以拿上利润最大的商品往时间轴上插入，如果时间冲突了就要插入到当前时间的前一位
 * 那么并查集维护的是什么呢？
 * 截止时间到最终时间的映射
 * 在插入后，会把这个时间对应的实际时间预映射到当前被占用时间的前一位
 * 那么如果前一位时间已经被占用呢？
 * 刚开始的时候每一位时间都是被自己占用，后来通过不断的插入，并不会出现两个元素插入到同一个位置
 * 因为：在可能出现冲突的位置准备插入的时候，并查集会进行路径压缩，将冲突位置（之前已经插入过元素的位置）压缩到新的不冲突位置！
 * 很神奇哇
 */
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 10000 + 10;
int Parent[MAXN];
struct goods{
    int px, dx;
    friend bool operator < (const goods g1, const goods g2){
        return g1.px > g2.px;//从大到小排列
    }
}Shop[MAXN];
int Find(int a){
    if(a == Parent[a]) return a;
    else return Parent[a] = Find(Parent[a]);
}
void Init(int n){
    for(int i=0; i<=n; i++){
        Parent[i] = i;
    }
}
int main(void){
    int N;
    while(~scanf("%d", &N)){
        int maxDeadline = 0;
        for(int i=0; i<N; i++){
            scanf("%d%d", &Shop[i].px, &Shop[i].dx);
            maxDeadline = max(Shop[i].dx, maxDeadline);
        }
        Init(maxDeadline);//一定要理解透彻集合中维护的是时间，不是并查集中元素的数量……！
        sort(Shop, Shop+N);
        int ans = 0;
        for(int i=0; i<N; i++){
            int p = Find(Shop[i].dx);
            if(p > 0){
                ans += Shop[i].px;
                Parent[p] = p - 1;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}