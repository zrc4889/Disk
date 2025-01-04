#include<cstdio>//多重背包的三种解决方法，暴力拆分、二进制拆分、数组优化 
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1005;
const int maxc=100005;
int cash,n,ans;
int c[maxn],v[maxn];//c[i]、v[i]分别表示第i种钱币的数量、面值
bool dp[maxc];//dp[j]表示是否能够拼出金额j
int num[maxc];//num[j]表示金额为j时用了多少个第i种钱币

void multi_knapsack3(int n,int W){//数组优化 
	ans=0;
	dp[0]=1;
	for(int i=1;i<=n;i++){
        memset(num,0,sizeof(num));//统计数量 
        for(int j=v[i];j<=W;j++){
            if(!dp[j]&&dp[j-v[i]]&&num[j-v[i]]<c[i]){
                dp[j]=1;
                num[j]=num[j-v[i]]+1;
                ans=max(ans,j);
            }
        }
    }
}

int main(){
    while(~scanf("%d%d",&cash,&n)){
        for(int i=1;i<=n;i++)
            scanf("%d%d",&c[i],&v[i]);
        memset(dp,0,sizeof(dp));
        multi_knapsack3(n,cash);
        printf("%d\n",ans);
    }
    return 0;
}
