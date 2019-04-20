//
// Created by Wong Yeah Way on 2019/4/20.
//
#include<iostream>
using namespace std;
const int MAXN = 100 + 10;
int F[MAXN];
int main(void){
    int C;
    cin >> C;
    while(C--){
        int N;//数塔高度
        cin >> N;
        fill(F, F+N, 0);
        //对于第K层值最大，我们需要知道k-1层最大
        //f[k] = max(f[k-1], f[k] + num);
        int num;
        for(int k=1; k<=N; k++){
            cin >> num;
            F[k] = max(F[k-1]+num, F[k]);
        }
        cout << F[N] << endl;
    }

    return 0;
}