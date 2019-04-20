//
// Created by Wong Yeah Way on 2019/4/20.
//
#include<iostream>
using namespace std;
int main(void){
    int N;
    while(cin >> N && N){
        int sum = 0, num1, num2;
        cin >> num1;
        sum += num1;
        for(int i=1; i<N; i++){
            cin >> num2;
            if(num2 > num1) sum += num2;
            else sum = max(num2, sum);
            num1 = num2;
        }
        cout << sum << endl;
    }
    return 0;
}
