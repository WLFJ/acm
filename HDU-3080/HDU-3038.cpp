//
// Created by Wong Yeah Way on 2019/4/14.
//

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
    int FindA = Find(a), FindB = Find(b);
    if(FindA == FindB){
        if(dis[b] - dis[a] != val) return true;
    }else{
        if(FindA < FindB){
            parents[FindA] = FindB;
            dis[FindA] = dis[b] + val - dis[a];
        }else{
            parents[FindB] = FindA;
            dis[FindB] = dis[a] - val + dis[b];
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
            if(update(a, b, val)){
                ans ++;
            }
        }
        cout << ans << endl;
    }

    return 0;
}