//
// Created by Wong Yeah Way on 2019/4/14.
//

/*
 * 先翻译题目
 * 为了增强防御能力，许多银河中的星星联合在一起构建了许多双向通道进行交流
 * 但是当星际战争开始的时候，一些管道会被其他维度的怪兽摧毁
 * 于是当一些星球想要寻求支援的时候就会出现问题
 * 宇宙中的星期编号0~N-1，并且他们所带的能量为非负整数pi
 * 当星球A需要支援时，他将会给离他最近并且能量最高的星球发消息
 * 并且这个星球必须比求助星球能量更高
 * 如果有多个能量相当的星球，选择标号最小的
 * 于是A有可能找不到支援的星球
 *
 * 给出战争的一些信息和对星球的一些询问，对于每个询问，找到知否满足上面的条件
 *
 * 输入：
 * 多组输入 不超过20 Cases 处理到EOF
 * 第一行N 星球的数量
 * 下面是N个数 代表每个星球的能量
 * 下一行M代表战争前修建的管道数目
 * 下面M行a b代表二者有管道（无重边）
 * 下一行Q
 * 会给出两种命令
 * destroy a b
 * query a
 *
 * 输出：
 * 无解 -1
 * 有解输出 编号
 * 相邻Case之间有空行
 */
/*
 * 分析
 * 涉及两种操作：删除边、找到最大的节点
 * 正着删除是不可能的，所以“正难反易”，先记录所有的操作，遇到Destory在建立并查集的时候
 * 就不连接这条边，等到这条命令来的时候再连接，查询最大节点，可以通过rank比较把最大的节点放在root上
 */
#include<iostream>
#include<cstdio>
#include<set>
using  namespace std;

const int MAX=10000+100;
int par[MAX];
int power[MAX];
set<int>g[MAX];//看一下set是怎么用的
int query[50000+100][2];
int ans[50000+100];

int Get_par(int x)
//查找a的父亲节点并压缩路径
{

    int r=x;
    while(r!=par[r])
        r=par[r];
    int i=x,j;
    while(i!=r)
    {
        j=par[i];
        par[i]=r;
        i=j;
    }
    return r;
}

void Merge(int a,int b)
//合并a,b
{
    int pa,pb;
    pa=Get_par(a);
    pb=Get_par(b);
    if(power[pa]<power[pb])//力量大的作为根节点
    {
        par[pa]=pb;
    }
    else if(power[pa]>power[pb])
    {
        par[pb]=pa;
    }
    else
    {
        if(pa<pb)//如果力量  则编号小的作为根节点
            par[pb]=pa;
        else par[pa]=pb;
    }
}
int main()
{
    int n,m,i,a,b,qnum,tag=0;
    char cmd[10];
    while(~scanf("%d",&n))
    {
        if(tag++)			//连续的例子之间输出一个空行
            printf("\n");
        for(i=0;i<MAX;i++)//初始化  对每个集合清空
        {
            par[i]=i;
            g[i].clear();
        }
        for(i=0;i<n;i++)
        {
            scanf("%d",&power[i]);
        }
        scanf("%d",&m);
        for(i=0;i<m;i++)//防止重复
        {
            scanf("%d%d",&a,&b);
            if(a>b)
                swap(a,b);
            g[a].insert(b);//类似于邻接表
        }

        scanf("%d",&qnum);
        for(i=0;i<qnum;i++)
        {
            scanf("%s",cmd);
            if(cmd[0]=='d')
            {
                scanf("%d%d",&a,&b);
                if(a>b)
                    swap(a,b);
                query[i][0]=a,query[i][1]=b;
                g[a].erase(g[a].find(b));//查找b在a集合的位置  然后删除b//删除边的操作
            }
            else
            {
                scanf("%d",&a);
                query[i][0]=a,query[i][1]=-1;
            }
        }

        for(i=0;i<n;i++)
        {
            for(set<int>::iterator it=g[i].begin();it!=g[i].end();it++)//建立并查集
                Merge(i,*it);
        }

        int id=0;
        for(i=qnum-1;i>=0;i--)//从最后一个开始判断
        {
            if(query[i][1]==-1)		//进行查询操作
            {
                int tmp=Get_par(query[i][0]);//返回根节点
                if(power[tmp]>power[query[i][0]])//如果力量更大的话 则满足题意
                    ans[id++]=tmp;
                else ans[id++]=-1;//否则不成立
            }
            else						//摧毁操作  逆向返回 则变为使其合并
            {
                Merge(query[i][0],query[i][1]);
            }
        }

        for(i=id-1;i>=0;i--)
            printf("%d\n",ans[i]);
    }
    return 0;
}