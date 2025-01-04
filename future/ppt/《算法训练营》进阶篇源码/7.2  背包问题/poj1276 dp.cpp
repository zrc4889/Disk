#include<cstdio>//包括多重背包的三种解决方法，暴力拆分、二进制拆分、数组优化 
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1005;
const int maxc=100005;
int cash,n;
int c[maxn],v[maxn];//c[i]、v[i]分别表示第i种钱币的数量、面值
int dp[maxc];//dp[j]表示不超过j时能够拼出的最大金额

void multi_knapsack1(int n,int W){//暴力拆分 超时！！！ 
    for(int i=1;i<=n;i++)
    	for(int k=1;k<=c[i];k++)//多一层循环 
			for(int j=W;j>=v[i];j--)
				dp[j]=max(dp[j],dp[j-v[i]]+v[i]);
}

void multi_knapsack2(int n,int W){//二进制拆分 
    for(int i=1;i<=n;i++){
		if(c[i]*v[i]>=W){//转化完全背包 
            for(int j=v[i];j<=W;j++)
                dp[j]=max(dp[j],dp[j-v[i]]+v[i]);
        }
        else{
            for(int k=1;c[i]>0;k<<=1){//二进制拆分
	            int x=min(k,c[i]);
	            for(int j=W;j>=v[i]*x;j--)//转化01背包 
	                dp[j]=max(dp[j],dp[j-v[i]*x]+x*v[i]);
	            c[i]-=x;
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
        printf("%d\n",dp[cash]);
    }
    return 0;
}
