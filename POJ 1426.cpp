//
// Created by Wong Yeah Way on 2019/4/24.
//
#include<cstdio>
#include<iostream>
using namespace std;
typedef unsigned long long ull;
int n;
ull m;
bool DFS(ull a, int deepth){
    if(deepth >= 20) return false;
    if(!(a % n)){
        m = a;
        return true;
    }
    if(DFS(a * 10 + 1, deepth + 1))return true;
    return DFS(a * 10, deepth + 1);
}
int main(void){
    while(scanf("%d", &n), n){
        m = 1;
        DFS(1, 0);
        cout << m << endl;
    }
    return 0;
}
