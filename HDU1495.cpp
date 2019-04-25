//
// Created by Wong Yeah Way on 2019/4/25.
//

#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
typedef unsigned long long ull;
struct statue{
    ull a, b, c, times;
    //short lastPosition;
};
int main(void){
    ull A, B, C;
    queue<statue> q;
    while(cin >> A >> B >> C, A+B+C){
        while(!q.empty())q.pop();
        if(A & 1) cout << "NO" << endl;
        else{
            //将所有的倒果汁可能都列举出来
            //记录一下上一次操作是从哪里来的，别回去了
            statue _begin;
            _begin.a = A;
            _begin.b = 0;
            _begin.c = 0;
            _begin.times = 0;
            q.push(_begin);
            while(!q.empty()){
                statue curS = q.front();
                q.pop();
                //检测一下是否满足题意
                if((curS.a == A >> 1 && curS.b == A >> 1) || (curS.a == A >> 1 && curS.c == A >> 1) || (curS.b == A >> 1 && curS.c == A >> 1)){
                    cout << curS.times << endl;
                    break;
                }
                //下面开始模拟倒饮料

                //这些是倒回A的
                //B到A
                statue nextS = curS;
                nextS.a += nextS.b;
                nextS.b = 0;
                nextS.times ++;
                q.push(nextS);
                //C到A
                nextS = curS;
                nextS.a += nextS.c;
                nextS.c = 0;
                nextS.times ++;
                q.push(nextS);

                //下面是到B的，注意B容量变化
                //A到B
                nextS = curS;
                nextS.b += nextS.a;
                if(nextS.b > B){
                    nextS.a = nextS.b - B;
                    nextS.b = B;
                }else nextS.a = 0;
                nextS.times ++;
                q.push(nextS);
                //C到B
                nextS = curS;
                nextS.b += nextS.c;
                if(nextS.b > B){
                    nextS.c = nextS.b - B;
                    nextS.b = B;
                }else nextS.c = 0;
                nextS.times ++;
                q.push(nextS);
//数据不是很大，记得加标记就好……
                //下面是到C的
                //A到C
                nextS = curS;
                nextS.c += nextS.a;
                if(nextS.c > C){
                    nextS.a = nextS.c - C;
                    nextS.c = B;
                }else nextS.a = 0;
                nextS.times ++;
                q.push(nextS);
                //B到C
                nextS = curS;
                nextS.c += nextS.b;
                if(nextS.c > C){
                    nextS.b = nextS.c - C;
                    nextS.c = B;
                }else nextS.b = 0;
                nextS.times ++;
                q.push(nextS);
            }
        }
    }
    return 0;
}