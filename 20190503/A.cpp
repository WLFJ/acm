//
// Created by Wong Yeah Way on 2019/5/3.
//
//
// Created by Wong Yeah Way on 2019/5/3.
//
#include <cstdio>
#include <cstring>
#include <queue>
#include <cmath>
#include <algorithm>
#include <set>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>
#define pi acos(-1.0)
#define eps 1e-6
#define fi first
#define se second
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define bug         printf("******\n")
#define mem(a,b)    memset(a,b,sizeof(a))
#define fuck(x)     cout<<"["<<x<<"]"<<endl
#define f(a)        a*a
#define sf(n)       scanf("%d", &n)
#define sff(a,b)    scanf("%d %d", &a, &b)
#define sfff(a,b,c) scanf("%d %d %d", &a, &b, &c)
#define pf          printf
#define FRE(i,a,b)  for(i = a; i <= b; i++)
#define FREE(i,a,b) for(i = a; i >= b; i--)
#define FRL(i,a,b)  for(i = a; i < b; i++)
#define FRLL(i,a,b) for(i = a; i > b; i--)
#define FIN freopen("DATA.txt","r",stdin)
#define lowbit(x)   x&-x
//#pragma comment (linker,"/STACK:102400000,102400000")
typedef unsigned long long ull;
typedef long long ll;
using namespace std;
const int maxn = 100000 + 10;
typedef long long LL;
const int MX = 505;
const ll inf = 1000000000 + 10;
const int MXE = MX * MX * 4;
int main(void){
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    ll n, w, num, Min=inf, Max = -inf, cnt = 0;
    cin >> n >> w;
    while(n--){
        cin >> num;
        cnt += num;
        Min = min(Min, cnt);
        Max = max(Max, cnt);
    }
    zh
    if(Max <= w){
        int l = 0, r;
        if(Min < 0) l = -Min;
        if(Max <= 0){
            r = w;
        }else r = w - Max;
        if(l <= r){
            cout << r - l + 1 << endl;
        }else cout << 0 << endl;
    }else cout << 0 << endl;
    return 0;
}