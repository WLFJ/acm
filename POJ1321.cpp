//老老实实DFS……
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 10
using namespace std;
int n,k,ans;bool a[maxn][maxn],b[maxn];
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
void DFS(int l,int stp)
{
    if (stp==k){ans++;return;}
    //这个搜索还是需要理一下思路的：
    //当前位置放一个棋子之后所在的行列都不能再放了，我们可以转换为搜索i是单向的，但是枚举列的时候如果当前列之前已经被标记了，
    //那么之后就不能再使用了！
    //也就是说搜索不再仅仅是机械的从头搜索，而是可以看看那个方向是单向的，哪个方向是可以重复走的！
    for (int i=l+1;i<=n;i++)
        for (int j=1;j<=n;j++) if (a[i][j]&&!b[j])
                b[j]=1,DFS(i,stp+1),b[j]=0;//搜完之后记得把之前的标记去掉！
}
int main()
{
    while ((n=read())!=-1&&(k=read())!=-1)//读入数字的函数！
    {
        memset(a,0,sizeof(a));memset(b,0,sizeof(b));ans=0;
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++) a[i][j]=fchar();//读入一个字符
        DFS(0,0);//开始搜索
        printf("%d\n",ans);
    }
    return 0;
}