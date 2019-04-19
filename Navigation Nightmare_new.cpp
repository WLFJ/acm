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
 *
 * 错误的地方：
 * 没有考虑到问同一行！（其实在写到IF的时候就应该想到这个问题
 * 输出要按照输入顺序！（这个算是离线化技术的经验积累吧，如果处理了输入数据的顺序，就应该相应改变输出数据的顺序
 */
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN = 40000 + 10, MAXM = 40000 + 10, MAXK = 10000 + 10;
//我们需要记录建图的明细
struct makemap_node{
    int front, tail, length;
    char direction;
}makeLines[MAXN];
//询问的明细
struct query_node{
    int front, tail, index, inputID;
    friend bool operator<  (const query_node n1, const query_node n2){
        return n1.index < n2.index;
    }
}qLines[MAXM];
//图的继承信息 包括父亲，x轴 y轴分开
struct node{
    int parent, x, y;
}map[MAXN];
struct ans_node{
    int ans, inputID;
    friend bool operator<(const ans_node n1, const ans_node n2){
        return n1.inputID < n2.inputID;
    }
}ans[MAXK];
void Init(int n){
    for(int i=0; i<=n; i++){
        map[i].parent = i;
    }
}
int Find(int a){
    if(map[a].parent == a) return a;
    else{
        int t = map[a].parent;
        map[a].parent = Find(t);
        map[a].x += map[t].x;
        map[a].y += map[t].y;//这里居然没有写出来！其实想一下就明白，松弛节点的时候只需要在已有的基础上连接父节点的边！
        return map[a].parent;
    }
}
void Union(int front, int tail, int length, char direction){
    int FindFront = Find(front), FindTail = Find(tail);
    if(front != tail){//根本不可能出现已经连上的情况！
        map[FindFront].parent = FindTail;//根据传入时候的定义连接
        switch(direction){
            case 'E':
                //front tail的方式放置
                //Right x Change y NOT Change
                map[FindFront].x = -map[front].x + length + map[tail].x;
                map[FindFront].y = -map[front].y + map[tail].y;
                break;
            case 'W':
                //West x Change y NOT Change
                map[FindFront].x = -map[front].x - length + map[tail].x;
                map[FindFront].y = -map[front].y + map[tail].y;
                break;
            case 'S':
                //Down y Change x NOT Change
                //这个要看建立的坐标系了，根据日暮所示，现在的位置应该为+
                map[FindFront].y = -map[front].y - length + map[tail].y;
                map[FindFront].x = -map[front].x + map[tail].x;
                break;
            case 'N':
                map[FindFront].y = -map[front].y + length + map[tail].y;
                map[FindFront].x = -map[front].x + map[tail].x;
                break;
        }

    }
}
//到此为止相关函数就设计完成了，下面是离线化过程
int main(void){
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    int N, M, K;
    cin >> N >> M;
    Init(N);
    for(int i=0; i<M; i++){
        cin >> makeLines[i].front >> makeLines[i].tail >> makeLines[i].length >> makeLines[i].direction;
    }
    cin >> K;
    for(int i=0; i<K; i++){
        cin >> qLines[i].front >> qLines[i].tail >> qLines[i].index;
        qLines[i].inputID = i;
    }
    //离线化完成
    int q = 0;
    sort(qLines, qLines + K);
    for(int i=0; i<M; i++){
        //先建表
        Union(makeLines[i].front, makeLines[i].tail, makeLines[i].length, makeLines[i].direction);
        //判断
        while(q < K && i+1 == qLines[q].index){//如果到了当前行……
            //注意！这里需要按照输出顺序，之前的询问已经排过序了！
            int Front = qLines[q].front, Tail = qLines[q].tail;
            int FindFront = Find(Front), FindTail = Find(Tail);
            if(FindFront == FindTail){
                ans[q].ans = abs(map[Front].x - map[Tail].x) + abs(map[Front].y - map[Tail].y);
            }else ans[q].ans = -1;
            ans[q].inputID = qLines[q].inputID;
            q++;
        }
    }
    //按照输入顺序输出
    sort(ans, ans + K);
    for(int i=0; i<K; i++){
        cout << ans[i].ans << endl;
    }
    return 0;
}
