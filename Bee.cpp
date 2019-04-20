//
// Created by Wong Yeah Way on 2019/4/20.
//
#include<iostream>
using namespace std;
int main(void){
    int N;
    cin >> N;
    unsigned long long F[55];
    F[1] = 1;
    F[2] = 1;
    while(N--){
        /*
         * F[2] = 1
         * F[3] = 1
         * F[4] = F[2] + F[3]
         * F[5] = F[3] + F[4]
         * 看起来没什么变化，我们可以把问题转换成从1开始的
         */
        int a, b;
        cin >> a >> b;
        b = b - a + 1;
        for(int i=3; i<=b; i++){
            F[i] = F[i-1] + F[i-2];
        }
        cout << F[b] << endl;
    }
    return 0;
}
