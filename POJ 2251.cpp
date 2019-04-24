//
// Created by Wong Yeah Way on 2019/4/24.
//
//三维搜索题，最暴力的搜索
// 每一个点有6个位置可以走：上下左右前后
//那么我们就最简单的构造三维bool数组（正好可以用板子）
//模拟每一步的操作
//记录走过的位置，这里我们枚举的是方案而不是坐标，所以需要再开一个数组记录走过没有
//因为需要找到最短路径，我们应该使用BFS，如果最后队列为空还没有找到答案，那么就是无解的。
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXL = 30 + 5, MAXR = 30 + 5, MAXC = 30 + 5;
const int Next[][3] = {-1, 0, 0, 1, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 1, 0, 0, -1};
int L, R, C;
char maze[MAXL][MAXR][MAXC];
bool mem[MAXL][MAXR][MAXC];
struct pos{
    int x, y, z, t;
};
inline char fchar()
{
    //如果a == b 则 a^b == 0 否则不为0！
    //是个牛逼函数，可以用来解决读入换行空格等问题！
    char ch=getchar();
    while (ch^'#'&&ch^'.'&&ch^'S'&&ch^'E') ch=getchar();//如果不是我们需要的字符就一直读，直到读到为止
    return ch;//简化运算，异或运算符虽然不能返回是否相等，但是可以转换成逻辑值！
    //如果是‘*’则返回为真
}
int main(void){
    while(scanf("%d %d %d", &L, &R, &C), L+R+C){
        memset(mem, 0, sizeof(mem));
        pos p;p.t = 0;
        for(int i=1; i<=L; i++){
            for(int j=1; j<=R; j++){
                for(int k=1; k<=C; k++){
                    maze[i][j][k] = fchar();
                    if(maze[i][j][k] == 'S')p.z = i, p.x = j, p.y = k;
                }
            }
        }
        queue<pos> q;
        q.push(p);
        bool haveSolution = false;
        while(!q.empty()){
            p = q.front();q.pop();
            //这里我们主要判断逻辑状态，下面的生成中我们判断数据输入是否越界之类的合法性
            char c = maze[p.z][p.x][p.y];
            if(c == '#')continue;
            else if(c == 'E'){
                haveSolution = true;
                break;
            }
            pos nextp;
            nextp.t = p.t + 1;//别忘了统计时间！
            for(int i=0; i<6; i++){
                nextp.x = p.x + Next[i][0];
                nextp.y = p.y + Next[i][1];
                nextp.z = p.z + Next[i][2];
                if(nextp.x < 1 || nextp.y < 1 || nextp.z < 1 || nextp.x > R || nextp.y > C || nextp.z > L || mem[nextp.z][nextp.x][nextp.y]) continue;
                mem[nextp.z][nextp.x][nextp.y] = true;
                q.push(nextp);
            }
        }
        if(haveSolution){
            printf("Escaped in %d minute(s).\n", p.t);
        }else{
            puts("Trapped!");
        }
    }

    return 0;
}