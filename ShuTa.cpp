//
// Created by Wong Yeah Way on 2019/4/20.
//
#include<iostream>
using namespace std;
int tower[100][100];
int main(void){
    int n;
    while(cin >> n){
        while(n--){
            int h,num;
            cin >> h;
            for(int i=0;i<h;i++){
                for(int j=0;j<=i;j++){
                    cin >> num;
                    tower[i][j] = num;
                }
            }
            //读入数据完毕
            for(int i=h-2;i>=0;i--){
                for(int j=0;j<=i;j++){
                    //判断一下左右儿子哪个比较大 加和更新.
                    tower[i][j] += tower[i+1][j]>tower[i+1][j+1]?tower[i+1][j]:tower[i+1][j+1];
                }
            }
            cout << tower[0][0] << "\n";
        }
    }
    return 0;
}