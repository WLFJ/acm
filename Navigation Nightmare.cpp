//
// Created by Wong Yeah Way on 2019/4/19.
//

/*
 * 导航噩梦
 * 有一个农场的导航图，知道边的信息（带方向）
 * 在建图中间还会有Bad boy BOB不断问他两点之间的距离
 * 他需要回答的距离必须沿路，还要是最优解
 * 如果信息不足，就返回-1
 * 输入：
 * N个地点，M个输入行
 * F1 F2 L D
 * 其中D指的是方向
 * NESW
 * 之后是K代表问题的数目
 * F1 F2 I
 * I是BOB会在之前建图的第几行之后提问
 *
 * 思路：
 * 还是要离散化处理，将询问按照I从小到大排序
 * 一边建图一边查询……那么这个方向是干什么的？
 * 很可能会有直线出去右直线回来的情况，也就是还需要维护一个Rank专门看方向
 * 假设N=0 E=1 S=2 W=4
 * 规定S和E是正方向 S对应N E对应W
 * 或者……分别维护两个维度计算
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
using namespace std;

#define maxn 40000+10
#define maxv 10000+10
struct node//存储输入的数据
{
    int u,v,length;
    char s;
} q[maxn];//储存边的信息
struct question//存储询问
{
    int u,v,index,pos;
    friend bool operator < (question a,question b)
    {
        return a.index<b.index;
    }
} w[maxv];
struct gather//并查集
{
    int x,y,pre;
} g[maxn];
struct result//存储答案
{
    int ans,pos;
}e[maxv];
int n,m;

bool cmp(result a,result b)
{
    return a.pos<b.pos;
}

void init()
{
    for(int i=1; i<=n; i++)
    {
        g[i].pre=i;
        g[i].x=g[i].y=0;
    }
}

int Find(int x)
{
    int temp=g[x].pre;
    if(x==g[x].pre)
        return x;
    g[x].pre=Find(temp);
    g[x].x+=g[temp].x;//直接压缩
    g[x].y+=g[temp].y;
    return g[x].pre;
}

void join(int u,int v,int length,char s)
{
    //这里有想法但是实际实现起来还是不行，这里用到的不是状态连环转移，而是简单的路径连接。
    int fx=Find(u),fy=Find(v);
    if(fx!=fy)
    {
        g[fx].pre=fy;
        //把u连接到v上面——可以看到输入的数据是u在v的位置，所以我们根据这个来连接
        if(s=='N')
            //y轴的操作，x是不变的，相当于中间没有length这条线了
            g[fx].y=g[v].y+length-g[u].y,g[fx].x=g[v].x-g[u].x;
        else if(s=='S')
            g[fx].y=g[v].y-length-g[u].y,g[fx].x=g[v].x-g[u].x;
        else if(s=='E')
            g[fx].x=g[v].x+length-g[u].x,g[fx].y=g[v].y-g[u].y;
        else
            g[fx].x=g[v].x-length-g[u].x,g[fx].y=g[v].y-g[u].y;
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    init();
    int i,k;
    for(i=0; i<m; i++)
        scanf("%d%d%d %c",&q[i].u,&q[i].v,&q[i].length,&q[i].s);
    scanf("%d",&k);
    for(i=0; i<k; i++)
        scanf("%d%d%d",&w[i].u,&w[i].v,&w[i].index),w[i].pos=i;
    sort(w,w+k);
    int ans,j=0;
    for(i=0; i<k; i++)
    {
        for(; j<w[i].index; j++)//注意j的值
            join(q[j].u,q[j].v,q[j].length,q[j].s);
        int u=w[i].u,v=w[i].v;
        int fx=Find(u),fy=Find(v);
        if(fx!=fy)
            ans=-1;
        else
            ans=abs(g[u].x-g[v].x)+abs(g[u].y-g[v].y);
        e[i].ans=ans,e[i].pos=w[i].pos;
    }
    sort(e,e+k,cmp);
    for(int i=0;i<k;++i)//按原顺序输出
        printf("%d\n",e[i].ans);
    return 0;
}