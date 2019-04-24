//
// Created by Wong Yeah Way on 2019/4/21.
//

#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>
#define INF 0x3f3f3f3f
#define N 110
using namespace std;
int Next[4][2]= {{0,1},{1,0},{0,-1},{-1,0}};
int len[N][N],a[N][N];
int m,n;
int dp(int x,int y)
{
    int tx,ty,k,s,ms;
    ms=0;
    if(len[x][y]!=0)//递归出口；
        return len[x][y];
    for(k=0; k<=3; k++)
    {
        tx=Next[k][0]+x;
        ty=Next[k][1]+y;
        if(tx<0||ty<0||tx>m-1||ty>n-1)
            continue;
        if(a[tx][ty]<a[x][y])//这个位置必须是下降的
        {
            s=dp(tx,ty);//计算下一个地点的值
            ms=max(ms,s);//从当前起点计算一个最大值
        }
    }
    len[x][y]=ms+1;//在所有情况都走完之后把这个地点标记
    return len[x][y];
}
int main()
{
    int i,j,Max;
    while(~scanf("%d%d",&m,&n))
    {
        memset(a,0,sizeof(a));
        memset(len,0,sizeof(len));
        for(i=0; i<m; i++)
            for(j=0; j<n; j++)
                scanf("%d",&a[i][j]);
            //读入数据完成！
        Max=-1;
        for(i=0; i<m; i++)
            for(j=0; j<n; j++)
                Max=max(Max,dp(i,j));//寻找从当前位置下降的最大值！
        printf("%d\n",Max);
    }
    return 0;
}
