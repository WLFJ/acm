//
// Created by Wong Yeah Way on 2019/4/14.
//
#include<iostream>
#include<string>
#include<set>
#include<stack>
using namespace std;
const int MAXN = 10000 + 10;
int parents[MAXN], power[MAXN];
set<int> graph[MAXN];//使用邻接表存边
int query[50000 + 10][2], ans[50000 + 10];

int Find(int a){
    if(a == parents[a]) return a;
    else return parents[a] = Find(parents[a]);
}
void Merge(int a, int b){
    a = Find(a), b = Find(b);
    if(power[a] > power[b]) parents[b] = a;
    else if(power[a] < power[b]) parents[a] = b;
    else{
        if(a < b) parents[b] = a;
        else parents[a] = b;
    }
}
int main (void){
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(false);
    cout.tie(false);
    int N, tag = 0;
    while(cin >> N){
        if(tag ++) cout << endl;//相邻case输出空格
        for(int i=0; i<MAXN; i++){
            parents[i] = i;
            graph[i].clear();
        }
        for(int i=0; i < N; i++){
            cin >> power[i];
        }
        int M, a, b;
        cin >> M;
        for(int i=0 ;i < M; i++){
            cin >> a >> b;
            if(a > b) swap(a, b);
            graph[a].insert(b);
        }
        int Q;
        cin >> Q;
        for(int i=0; i < Q; i++){
            string cmd;
            cin >> cmd;
            if(cmd[0] == 'd'){
                cin >> a >> b;
                if(a > b)swap(a, b);
                query[i][0] = a, query[i][1] = b;
                graph[a].erase(graph[a].find(b));//新技巧！删除邻接表中的一条边
            }else{
                cin >> a;
                query[i][0] = a, query[i][1] = -1;
            }
        }
        //下面开始连边
        for(int i=0; i < N; i++){
            for(set<int>::iterator it = graph[i].begin(); it != graph[i].end(); ++it){
                Merge(i, *it);
            }
        }
        //下面倒着判断数据
        stack<int> ans;
        for(int i = Q - 1; i>=0; i--){
            if(query[i][1] == -1){//如果是询问
                int root = Find(query[i][0]);
                if(power[root] > power[query[i][0]]){
                    //保存答案
                    ans.push(root);
                }else ans.push(-1);
            }else{
                Merge(query[i][0], query[i][1]);
            }
        }
        while(!ans.empty()){
            cout << ans.top() << endl;
            ans.pop();
        }
    }
    return 0;
}
