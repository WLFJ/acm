#include<iostream>
using namespace std;
const int MAXN = 200000 + 10;
int parents[MAXN], dis[MAXN];
int Find(int a){
    if(a == parents[a]) return a;
    else{
        int t = parents[a];
        parents[a] = Find(parents[a]);
        dis[a] += dis[t];
        return parents[a];
    }
}
bool update(int a, int b, int val){
    //转入的数据可以理解为从a指向b，边长为val的向量
    //但是我们插入后必须是有序的，所以需要根据其大小关系并入集合
    int FindA = Find(a), FindB = Find(b);
    if(FindA == FindB){
        if(dis[a] - dis[b] != val) return true;
    }else{
        //距离还是很有必要分左右的！
        //规定都是从左往右连接
        if(FindA < FindB){
            parents[FindA] = FindB;
            dis[FindA] = dis[b] + val - dis[a];
        }else{
            parents[FindB] = FindA;
            dis[FindB] = dis[a] - dis[b] - val;
        }
    }
    return false;
}
int main(void){
    int N, M;
    while(cin >> N >> M){
        for(int i=0; i<=N; i++){
            parents[i] = i;
            dis[i] = 0;
        }
        int ans = 0;
        while(M--){
            int a, b, val;
            cin >> a >> b >> val;
            b ++;
            if(update(a, b, val)) ans ++;
        }
        cout << ans << endl;
    }
    return 0;
}