//
// Created by Wong Yeah Way on 2019/4/27.
//
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
const int MAXN = 1e5 + 5;
typedef unsigned long long ULL;
ULL HashSaver[MAXN];
ULL c[MAXN][2];
const int seed = 13;
int length;
int lowbit(int x){return x&(-x);}
void update(int x, ULL y, int p, int n){
    //x是要修改的元位置 y是要新加的值 n是数组的最大位置
    //在建树的时候也使用这个办法
    for(int i=x; i<=n; i+=lowbit(i)){//注意这里加的是i的lowbit而不是x的！
        c[i][p] += y;
    }
}
ULL getsum(int x, int p){
    ULL ans = 0;
    for(int i=x; i; i-=lowbit(i)){//注意这里加的是i的lowbit而不是x的！
        ans += c[i][p];
    }
    return ans;
}
int main(void){
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    string s;
    cin >> s;
    length = s.length();
    //建立Hash表
    HashSaver[0] = 1;
    for(int i=1; i<length + 5; i++)HashSaver[i] = HashSaver[i-1] * seed;
    //建表完成!
    //建树
    for(int i=0; i<s.length(); i++){
        update(i + 1, (s[i] - 'a') * HashSaver[i], 0, length);//这里是i+1，因为数组是从1开始维护的！
        //下面反向建一棵
        update(i + 1, (s[length - 1 - i] - 'a') * HashSaver[i], 1, length);
    }
    //建树完成
    //处理输入信息
    int q;
    cin >> q;
    while(q--){
        int x, y;
        //char c[2];//这样可以顺便把当前行的回车换行给读入了
        string op;
        cin >> op >> x;
        if(op[0] == 'p'){//查询
            cin >> y;
            //查询x到y是不是回文
            //计算出区间里面的Hash后将其顶到头
            ULL l = HashSaver[length - y] * (getsum(y, 0) - getsum(x-1, 0));
            ULL r = HashSaver[x - 1] * (getsum(length - x + 1, 1) - getsum(length - y, 1));
            cout << (l == r ? "Yes" : "No") << endl;
        }else{
            //更新指定点的值
            cin >> op;//借用一下
            update(x, (op[0] - s[x-1]) * HashSaver[x - 1], 0, length);
            update(length - x + 1, (op[0] - s[x-1]) * HashSaver[length - x], 1, length);
            s[x-1] = op[0];
        }
    }
    return 0;
}