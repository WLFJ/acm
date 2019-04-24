#include<stdio.h>
#include<string.h>
#include<cmath>
#include<algorithm>
using namespace std;
int dp[100005][12];
int main()
{
    int n,i,j,maxt;
    int x,t;
    while(scanf("%d",&n) , n)
    {
        maxt=0;
        memset(dp,0,sizeof(dp));
        for(i=0;i<n;i++)
        {
            scanf("%d%d",&x,&t);
            dp[t][x]++;
            if(maxt<t)  maxt=t;
        }
        for(i=maxt-1;i>=0;i--)
        {
            dp[i][0]+=max(dp[i+1][1],dp[i+1][0]);
            for(j=1;j<11;j++)
            {
                dp[i][j]+=max(max(dp[i+1][j-1],dp[i+1][j]),dp[i+1][j+1]);
            }
        }
        printf("%d\n",dp[0][5]);
    }
    return 0;
}