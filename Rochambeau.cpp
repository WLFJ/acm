//
// Created by Wong Yeah Way on 2019/4/16.
//
/*
 * N个小孩在和你玩Rochambeau（石头剪刀布）
 * 其中一个是裁判
 * 剩下的小孩分成三组（可以有没有人的组）
 * 你不知道谁是裁判，也不知道小孩们是怎样分组的
 * 就这样小孩们开始了M回合的游戏
 * 每一轮随机选择两个小孩玩游戏
 * 你会知道结果，但是不知道他们出了什么手势
 * 现在已知相同组的小朋友出相同的手势，
 * 不同的组是不同的手势
 * 裁判每次随机出手势
 * 现在问你至少需要多少轮比赛，才能知道谁是猜裁判？
 *
 * 输入：
 * 输入包含多组数据
 * N M
 * 下面M行包含两个数字，是小朋友的ID
 * 用=><分别表示平局，第一个小朋友赢、第二个小朋友赢
 *
 * 输出：下面几种情况
 * Can not determine
 * Player 1 can be determined to be the judge after 4 lines
 * Impossible
 * Player 0 can be determined to be the judge after 0 lines
 */
//下面是嫖来的代码……
/*
POJ 2912
枚举+并查集
枚举每一个裁判，看有没有不出错的
如果没有，说明是Impossible
如果有超过一个，那么就是Can not determine
如果只有一个，那么输出其他出错的位置的最大值
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;
const int MAXN=510;
const int MAXM=2010;
struct Node
{
    int u,v;
    int re;
}node[MAXM];//记录输入的情况
int F[MAXN];//记录根节点
int val[MAXN];//记录每一次比赛之后相邻节点的关系 只能是< = > 三种关系
int find(int x)
{
    if(F[x]==-1)return x;
    int tmp=find(F[x]);
    val[x]+=val[F[x]];
    val[x]%=3;//三种关系的传递
    return F[x]=tmp;
}
char str[30];
int main()
{
    int n,m;
    int u,v;
    while(scanf("%d%d",&n,&m)==2)
    {
        gets(str);
        for(int i=0;i<m;i++)
        {
            //scanf("%s",&str);
            gets(str);
            int t=0;
            int len=strlen(str);
            for(t=0;t<len;t++)
                if(str[t]=='>'||str[t]=='='||str[t]=='<')
                    break;
            u=0;
            for(int j=0;j<t;j++)
            {
                u*=10;
                u+=str[j]-'0';
            }
            v=0;
            for(int j=t+1;j<len;j++)
            {
                v*=10;
                v+=str[j]-'0';
            }
            node[i].u=u;
            node[i].v=v;
            //将三种关系定义为 = <  >我们需要看一下是不是这样
            //当然是这样，连等传递没有问题，其他两个也是这样，说明这类题目的关系一定要具有传递性
            if(str[t]=='=')node[i].re=0;
            else if(str[t]=='<')node[i].re=1;
            else node[i].re=2;
        }
        //从这里开始枚举枚举假设每一个是裁判
        //注意我们寻找裁判判断的依据：因为裁判是随机出拳的，所以必定在某一行出现矛盾
        //最多多少行判断矛盾则是看一下当前循环检查时发生矛盾的最低位置
        int ansi;
        int anst=0;
        int t0=0;//不矛盾的个数
        for(int i=0;i<n;i++)
        {
            memset(F,-1,sizeof(F));
            memset(val,0,sizeof(val));
            int ff=-1;
            for(int j=0;j<m;j++)
            {
                if(node[j].u==i || node[j].v==i)continue;//这一句是关键，忽略所有裁判比赛的结果
                u=node[j].u;
                v=node[j].v;
                int t1=find(u);
                int t2=find(v);
                if(t1==t2)//如果两个之间存在某种关系
                {
                    if(val[v]!=(val[u]+node[j].re)%3)//矛盾了
                    {
                        ff=j+1;//记录发生矛盾的位置
                        break;
                    }
                }
                else//之前没有遇到这个关系，需要创建关系
                {
                    F[t2]=t1;
                    val[t2]=val[u]-val[v]+node[j].re;//满足分析
                    val[t2]=(val[t2]+3)%3;//保证其是在0 1 2中间
                }
            }
            if(ff==-1)//没有发生矛盾
            {
                ansi=i;//猜测裁判的ID
                t0++;//记录出现了多少个裁判
            }
            else anst=max(anst,ff);//
        }
        if(t0==0)printf("Impossible\n");
        else if(t0>=2)printf("Can not determine\n");
        else
            printf("Player %d can be determined to be the judge after %d lines\n",ansi,anst);
    }
    return 0;
}