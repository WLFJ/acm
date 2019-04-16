//
// Created by Wong Yeah Way on 2019/4/16.
//

/*
 * 超市有一堆销售的商品，当商品在dx之前可以得到利润px，
 * 销售一件商品需要一单位时间，
 * 通过时间表销售商品，
 * 我们自然希望能够获得最大利润
 * 例如
 * 对于商品a b c d，
 * （利润，截止时间）50 2
 *                  10 1
 *                  20 2
 *                  30 1
 * 下面是一种可能的销售策略
 * 对于{d,a} d在0~1售出，a在1~2售出
 * 在本例中最佳的销售策略是{d, a}
 * 把题目抽象一下，从不断变小的权重中拿出最小权重的最大数字
 * 对于第二个例子刚开始
 * 20-1 2-1 10-3 100-2 8-2 5-20 50-10
 * 选出1中最大的数字 20
 * 2-0 10-2 100-1 8-1 5-19 50-9
 * 选出1中最大的 100
 * 10-1 5-18 50-8
 * 选出1中最大的 10
 * 5-17 50-7
 * 选出1中最大的 50
 * 5-10
 * 选出1中最大的 5
 * 结束，答案为185
 *
 * 我们可以枚举时间，然后从每一段时间里面选择利润最大的
 */

#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXN = 10000 + 10;
struct goods{
    int px, dx;
    /*
    friend bool operator <  (const goods g1, const goods g2){
        //先比较时间，时间小的靠前，时间相同则比较利润，利润大的靠前
        if(g1.dx != g2.dx) return g1.dx < g2.dx;
        else return g1.px > g2.px;
    }
     */
    friend bool operator <  (const goods g1, const goods g2){
        //先比较时间，时间小的靠前，时间相同则比较利润，利润大的靠前
        return g1.dx > g2.dx;
    }
}Shop[MAXN];
int main(void){
    int n;
    while(~scanf("%d", &n)){
        int maxDeadline = 0;
        for(int i=0; i<n; i++){
            scanf("%d%d", &Shop[i].px, &Shop[i].dx);
            maxDeadline = max(Shop[i].dx, maxDeadline);
        }
        sort(Shop, Shop + n);
        //每个时间只取一个
        int p = 0;
        int ans = 0;
        /*
         * 错误的写法
        for(int t=1; t <= maxDeadline && p < n; t++){
            if(Shop[p].dx == t){
                ans += Shop[p++].px;
                while(Shop[p].dx == t) p++;
            }
        }
         */
        //上面的写法是有问题的……
        /*
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;

const int N = 10005;
struct Node{
    int px, dx;
    friend bool operator<(const Node&a,const Node&b){
        return a.dx>b.dx;
    }
}arr[N];

priority_queue<int,vector<int>,less<int> >q;

int n;

int main(){
    while(~scanf("%d",&n)){
        int maxTime=0;
        for(int i=0; i<n; ++i){
            scanf("%d%d",&arr[i].px, &arr[i].dx);
            if(arr[i].dx>maxTime) maxTime = arr[i].dx;
        }
        sort(arr,arr+n);//按照截止时间排序。截止时间大的在前
        int ans = 0, pos=0;
        while(!q.empty()) q.pop();
        可是为什么是这样？怎样保证时间是有效的？
        可以理解为从1——maxtime，每一个时间段卖哪个商品？
        也可以理解为每一个时刻可供选择售卖的商品有哪些？
        显然从最后开始卖，可供的选择是最少的
        如果从前往后去看的话，随着时间的推移，会有一些选择的商品已经过期了，并且可供选择的是从多变少的不容易看
        for(int t=maxTime; t>=1; --t){//从后往前枚举结束时间
            while(pos<n&&arr[pos].dx>=t){//如果当前的时间大于截止时间，放入堆中
                q.push(arr[pos++].px);
            }
            if(!q.empty()){
                ans += q.top();//拿堆顶最大的元素
                q.pop();
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
         */
        priority_queue<int> q;
        for(int t=maxDeadline; t>=1; --t){//从后往前枚举结束时间
            while(p<n&&Shop[p].dx>=t){//如果当前的时间大于截止时间，放入堆中
                q.push(Shop[p++].px);
            }
            if(!q.empty()){
                ans += q.top();//拿堆顶最大的元素
                q.pop();
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}
