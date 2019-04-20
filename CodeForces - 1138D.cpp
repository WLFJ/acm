//
// Created by Wong Yeah Way on 2019/4/20.
//
#include<bits/stdc++.h>
using namespace std;
int nex[500004];
char s[500004],t[500004];
void getnext(char ptr[])
{
    int i=0,j=-1,len=strlen(ptr);
    nex[0]=-1;
    while(i<len)
    {
        if(j==-1||ptr[i]==ptr[j])nex[++i]=++j;
        else j=nex[j];
    }
}
int main()
{
    scanf("%s%s",s,t);
    getnext(t);
    int zero=0,one=0;
    int len=strlen(s);
    for (int i = 0; i < len; ++i) {
        if(s[i]=='0')zero++;
        else one++;
    }
    //先统计母串中0 1的数目
    string ans="";
    int cnt=0;
    len=strlen(t);//要生成的子串序列
    while(zero>0&&one>0)
    {
        if(t[cnt]=='0')
        {
            if(zero>0)
            {
                zero--;
                ans+='0';
            }
            else break;
        }
        else
        {
            if(one>0)
            {
                one--;
                ans+='1';
            }
            else break;
        }
        cnt++;
        //上面都是一般的操作，如果有0 or 1就将其放入
        if(cnt==len)
        {
            cnt=nex[cnt];
        }
    }
    while(zero--)ans+='0';
    while(one--)ans+='1';
    cout<<ans<<endl;
}

