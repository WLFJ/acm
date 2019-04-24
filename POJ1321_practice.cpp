//
// Created by Wong Yeah Way on 2019/4/24.
//
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 10
using namespace std;
int n,k,ans;bool a[maxn][maxn],b[maxn];
//先把板子粘过来
inline int read()
{
    //读入一个数字
    bool f=0;char ch=getchar();
    while (ch<'0'||ch>'8') f^=!(ch^45),ch=getchar();//判断我们的接受范围
    //看一下是不是我们第一遍读入的内容……？如果是‘-’，那么f就是1，其他的都是0
    //！相当于负数的判断也有了！
    return f? (~(ch^48))+1:ch^48;//根据补码的性质，将这个数字按位取反之后+1便能得到其负值
    //读入一个字符后转换为数字的办法：c^48就可以了！同理，如果想算字母的偏移，也可以用这个办法
}
inline bool fchar()
{
    //如果a == b 则 a^b == 0 否则不为0！
    //是个牛逼函数，可以用来解决读入换行空格等问题！
    char ch=getchar();
    while (ch^'#'&&ch^'.') ch=getchar();//如果不是我们需要的字符就一直读，直到读到为止
    return ch^'.';//简化运算，异或运算符虽然不能返回是否相等，但是可以转换成逻辑值！
    //如果是‘#’则返回为真
}
int DFS(int l, int stp){
    if(stp == k){
        ans ++;return 0;
    }else{
        for(int i=l+1; i<=n; i++){
            for(int j=1; j<=n; j++) if(a[i][j] && !b[j])
                b[j] = 1, DFS(i, stp+1), b[j] = 0;
        }
    }
    return 0;
}
int main(void){
    while((n = read()) != -1 && (k = read()) != -1){
        memset(a, 0, sizeof(a)), memset(b, 0, sizeof(b)), ans = 0;
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                a[i][j] = fchar();
            }
        }
        DFS(0, 0);
        printf("%d\n", ans);
    }

    return 0;
}