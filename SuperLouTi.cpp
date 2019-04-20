//
// Created by Wong Yeah Way on 2019/4/20.
//
#include<iostream>
using namespace std;
int main(void){
    int F[45];
    F[1] = 1;
    F[2] = 1;
    int N;
    cin >> N;
    while(N--){
        int M;
        cin >> M;
        for(int i=3; i<=M; i++){
            F[i] = F[i-1] + F[i-2];
        }
        cout << F[M] << endl;
    }
    return 0;
}
