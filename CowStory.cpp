//
// Created by Wong Yeah Way on 2019/4/20.
//
#include<iostream>
using namespace std;
const int MAXN = 55;
typedef unsigned long long ull;
ull F[MAXN];
int main(void){
    int n;
    F[1] = 1;
    F[2] = 2;
    F[3] = 3;
    F[4] = 4;
    while(cin >> n && n){
        for(int i=5; i<=n; i++){
            F[i] = F[i-1] + F[i-3];
        }
        cout << F[n] << endl;
    }

    return 0;
}
