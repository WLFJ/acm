//
// Created by Wong Yeah Way on 2019/4/25.
//

#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN = 200 + 10;
int a[MAXN][MAXN], b[MAXN][MAXN];
const int Next[][2] = {-1, 0, 1, 0, 0, 1, 0, -1};
char maze[MAXN][MAXN];
int mem[MAXN][MAXN];
struct node{
    int x, y;
    int times;
};
inline char fchar()
{
    //如果a == b 则 a^b == 0 否则不为0！
    //是个牛逼函数，可以用来解决读入换行空格等问题！
    char ch=getchar();
    //‘Y’表示hsj所在的位置
    //‘M’表示lsh所在的位置
    //‘.’表示可以通过的地方
    //‘#’表示教学楼即不能走的地方
    //‘@’表示稀有土拨鼠刷新的地方（地图中存在多只稀有土拨鼠）
    while (ch^'#'&&ch^'.'&&ch^'Y'&&ch^'M'&&ch^'@') ch=getchar();//如果不是我们需要的字符就一直读，直到读到为止
    return ch;//简化运算，异或运算符虽然不能返回是否相等，但是可以转换成逻辑值！
    //如果是‘#’则返回为真
}
int main(void){
    //首先从开始点搜索到每一个@所用的步数 两个人都搜索一次
    //之后计算里面对应位置最小的和 记得乘上11
    //本题最坑的就是扫过的有解地方还能走
    //5 5
    //Y@@@@
    //@@@@@
    //@@@@@
    //@@@@@
    //@@@@M
    int N, M;
    while(~scanf("%d%d", &N, &M)){
        memset(a, 0x3f, sizeof(a));
        memset(b, 0x3f, sizeof(b));
        memset(mem, 0, sizeof(mem));
        int aY, bY, aM, bM;
        for(int i=1; i<=N; i++){
            for(int j=1; j<=M; j++){
                maze[i][j] = fchar();
                if(maze[i][j] == 'Y')
                    aY = i, bY = j;
                else if(maze[i][j] == 'M')
                    aM = i, bM = j;
            }
        }
        node Start;
        Start.x = aY, Start.y = bY;
        Start.times = 0;
        queue<node> q;
        q.push(Start);
        while(!q.empty()){
            node cur = q.front();
            q.pop();
            mem[cur.x][cur.y] = 1;
            if(maze[cur.x][cur.y] == '@'){
                a[cur.x][cur.y] = min(cur.times, a[cur.x][cur.y]);
                //printf("!%d\n", cur.times);
            }
            if(maze[cur.x][cur.y] != '#'){
                for(int i=0; i<4; i++){
                    int nextX = cur.x + Next[i][0], nextY = cur.y + Next[i][1];
                    if(nextX < 0 || nextY < 0 || nextX > N || nextY > M || mem[nextX][nextY]) continue;
                    mem[nextX][nextY] = 1;
                    node nextN;
                    nextN.x = nextX, nextN.y = nextY, nextN.times = cur.times + 1;
                    q.push(nextN);
                }
            }
        }
        memset(mem, 0, sizeof(mem));
        Start.x = aM, Start.y = bM;
        Start.times = 0;
        q.push(Start);
        while(!q.empty()){
            node cur = q.front();
            q.pop();
            mem[cur.x][cur.y] = 1;
            if(maze[cur.x][cur.y] == '@'){
                b[cur.x][cur.y] = min(cur.times, b[cur.x][cur.y]);
                //printf("@%d\n", cur.times);
            }
            if(maze[cur.x][cur.y] != '#'){
                for(int i=0; i<4; i++){
                    int nextX = cur.x + Next[i][0], nextY = cur.y + Next[i][1];
                    if(nextX < 0 || nextY < 0 || nextX > N || nextY > M || mem[nextX][nextY]) continue;
                    mem[nextX][nextY] = 1;
                    node nextN;
                    nextN.x = nextX, nextN.y = nextY, nextN.times = cur.times + 1;
                    q.push(nextN);
                }
            }
        }
        int ans = 0x3f3f3f3f;
        for(int i=1; i<=N; i++){
            for(int j=1; j<=M; j++){
                if(a[i][j] != a[0][0]) ans = min(a[i][j] + b[i][j], ans);
            }
        }
        printf("%d\n", ans * 11);
    }
    return 0;
}