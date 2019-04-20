//
// Created by Wong Yeah Way on 2019/4/20.
//
#include<iostream>
using namespace std;
const int MAXN = 1000 + 10;
int dp[MAXN];
int Data[MAXN];
int main(void){
    //计算升序数组的个数
    int N;
    while(cin >> N && N){
        fill(dp, dp + N + 1, 0);
        for(int i=1; i<=N; i++)cin >> Data[i];
        //输入数据完成
        for(int i=1; i<=N; i++){
            for(int j=1;j<=i;j++){
                if(Data[j] <= Data[i]){
                    //会有充重复计算的问题
                    dp[i] = max(dp[j] + 1, dp[i]);
                }
            }
        }
        cout << dp[N] << endl;
        for(int i=0; i<=N; i++)cout << dp[i] << " ";
    }
    return 0;
}


#include <iostream>
using namespace std;

int main()
{
    int n,a[10001];
    while(cin>>n){
        int i,index;
        for(i=1;i<=n;i++)   //输入数组
            cin>>a[i];
        //找到最长非升子序列

        int count=0;

        while(true){
            for(i=1;i<=n;i++)       //检测
                if(a[i]!=0) break;  //全部为0，即将全部序列剔除之后退出循环
            if(i>n) break;

            for(i=n;i>=1;i--){
                if(a[i]!=0){
                    index=i;    //标记倒序第一个不是0的数
                    break;
                }
            }
            for(i=n-1;i>=1;i--){
                if(a[i]==0) continue;
                if(i==index) continue;
                if(a[i]>=a[index]) {a[index]=0;index=i;} //比较当前数和标记的数。如果大于等于标记的上一个数，则将上次标记的数等于0，将本次标记。
            }
            a[index]=0;         //将最后标记的不是0的数赋值0
//            for(i=1;i<=n;i++)
//                cout<<a[i]<<' ';
//            cout<<endl;
            count++;
        }
        cout<<count<<endl;

    }
    return 0;
}