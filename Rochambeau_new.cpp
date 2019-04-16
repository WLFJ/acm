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
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
const int MAXN = 500 + 10;
const int MAXM = 2000 + 10;
int Parent[MAXN], Rank[MAXN];
struct q{
    int u, v, opr;
}qs[MAXM];
void Init(int n){
    //我们可以直接把数组填充！
    /*
    for(int i=0; i<=n; i++){
        Parent[i] = i;
        Rank[i] = 0;
    }
     */
    fill(Parent, Parent + n + 1, -1);
    fill(Rank, Rank + n + 1, 0);
    //POJ快了30ms！
}
int Find(int a){
    if(Parent[a] == -1) return a;//这样就间接实现了初始化
    else{
        //在下面这个模式下我们保证了祖父节点是根节点
        //现在我们要压缩路径，同时更新Rank
        int t = Find(Parent[a]);
        //经过上面的操作我们就能通过Parent[a]拿到当前节点的真正祖父节点！
        Rank[a] += Rank[ Parent[a] ];
        Rank[a] %= 3;
        return Parent[a] = t;
    }
}
bool Union(int a, int b, int opr){
    //注意我们定义的节点关系是从b指向a的！
    int FindA = Find(a), FindB = Find(b);
    if(FindA == FindB){//判断是否出现了矛盾
        //不需要大动干戈涉及到父亲节点……因为u和v之间的关系已经有了啊！
        if((Rank[b] != (Rank[a] + opr) % 3)) return true;//注意相加顺序
    }else{//建立关系
        Parent[FindB] = FindA;//要满足b指向a！
        //在这里才回忆那一圈！
        Rank[FindB] = -Rank[b] + opr + Rank[a];
        Rank[FindB] = (Rank[FindB] + 3) % 3;
    }
    return false;
}
int main(void){
    //快30ms!
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    int N, M;
    string line;
    while(cin >> N >> M){
        for(int i=0; i<M; i++){
            cin >> line;
            int num, j;
            for(num = 0, j=0; line.at(j) >= '0' && line.at(j)<='9'; j++){
                num *= 10;
                num += line.at(j) - '0';
            }
            qs[i].u = num;
            switch(line.at(j)){
                case '=':qs[i].opr = 0;break;
                case '<':qs[i].opr = 1;break;
                case '>':qs[i].opr = 2;break;
            }
            for(num = 0, j++; j < line.length(); j++){
                num *= 10;
                num += line.at(j) - '0';
            }
            qs[i].v = num;
        }
        int ans_i, ans_f = 0, cnt_i = 0;
        //数据处理完成
        for(int i=0; i<N;i++){//假设i是裁判
            //初始化条件
            Init(N);
            int lastLine = -1;
            //看每一条命令
            for(int j=0; j<M; j++){
                if(qs[j].u == i || qs[j].v == i) continue;
                if(Union(qs[j].u, qs[j].v, qs[j].opr)){//根本没有出现矛盾
                    //出现矛盾
                    lastLine = j + 1;
                    break;
                }
            }
            if(lastLine == -1){//没有出现矛盾
                ans_i = i;
                cnt_i ++;//记录有多少个裁判
            }else ans_f = max(lastLine, ans_f);
        }
        if(cnt_i == 0)puts("Impossible");
        else if(cnt_i >= 2) puts("Can not determine");
        else printf("Player %d can be determined to be the judge after %d lines\n",ans_i,ans_f);
    }
    return 0;
}
