#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN = 200000 + 10;
struct node{
    int w, id;
    int l, r;
}tree[MAXN << 2];
struct {
    int p, id;
}pss[MAXN];
void up(int root){
    tree[root].w = tree[root << 1].w + tree[root << 1 | 1].w;
}
void build(int l, int r, int root){
    tree[root].l = l, tree[root].r = r;
    if(l == r){
        tree[root].w = 1;
        tree[root].id = -1;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, root << 1);
    build(mid + 1, r, root << 1 | 1);
    up(root);//别忘了维护性质！
}
void update(int position, int id, int l, int r, int root){
    if(l == r && tree[root].w == 1){
        tree[root].id = id;
        tree[root].w = 0;
        return;
    }
    int mid = (l + r) >> 1;
    if(position <= tree[root << 1].w) update(position, id, l, mid, root << 1);
    else update(position - tree[root << 1].w, id, mid+1, r, root << 1 | 1);
    up(root);
}
void preOrder(int root){
    if(tree[root].l == tree[root].r){
        printf("%d ", tree[root].id);
        return;
    }
    preOrder(root << 1);
    preOrder(root << 1 | 1);
}
int main(void){
    int N;
    while(~scanf("%d", &N)){
        build(1, N, 1);
        for(int i=0; i<N; i++){
            scanf("%d %d", &pss[i].p, &pss[i].id);
        }
        for(int i=N-1; i>=0; i--){
            update(pss[i].p +1, pss[i].id, 1, N, 1);
        }
        preOrder(1);
        puts("");
    }
    return 0;
}