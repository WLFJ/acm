//
// Created by Wong Yeah Way on 2019/4/17.
//
#include<stdio.h>
#include<string.h>
const int MAXN = 100 + 10;
int Next[MAXN];
void KMP(char* a){
    Next[0] = -1;
    int len = strlen(a);
    for(int i=1; i<len; ++i){
        int j = Next[i - 1];
        while(a[j+1] != a[i] && j >= 0) j = Next[j];
        if(a[j+1] == a[i]) Next[i] = j + 1;
        else Next[i] = -1;
    }
}
int Find(char* a, char* b){
    //在a中寻找b第一次出现的位置
    int i = 0, j = 0;
    while(j<strlen(b)){
        if(a[i] == b[j]) i++,j++;
        else j = Next[j]+1;
        if(j == 0)i++;
    }
    return i - j + 1;//从这个位置开始嘛
}
int main(void){
    char a[MAXN], b[MAXN];
    puts("请分别输入两个串，将在第一个串中寻找第二个串第一次出现的位置:");
    gets(a);gets(b);
    KMP(b);
    int ans = Find(a, b);
    printf("第一个出现子串的位置：%d\n", ans);
    return 0;
}
