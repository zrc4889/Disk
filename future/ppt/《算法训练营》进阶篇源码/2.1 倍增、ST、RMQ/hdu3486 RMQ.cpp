/*本题穷举超时,但数据有问题，二分可通过。实际上不满足单调性，不可二分。 
  例如6 199   1 1 100 100 1 1,二分首先分3段,不行分4段,实际上分2段即可。 
  本题可以采用RMQ+优化，当区间长度和上次一样时，不再重新计算，直接累加下一个区间最值即可。 
*/ 
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200010;
int a[N];
int n,k;
int F[N][20],lb[N];

void Initlog(){
	lb[0]=-1;
    for(int i=1;i<=N;i++)
        lb[i]=lb[i-1]+(i&(i-1)?0:1);
}

void ST(int n){
    for(int i=1;i<=n;i++)
		F[i][0]=a[i];
    for(int j=1;j<=lb[n];j++)
        for(int i=1;i<=n-(1<<j)+1;i++)
            F[i][j]=max(F[i][j-1],F[i+(1<<(j-1))][j-1]);
}

int RMQ(int l,int r){
    int k=lb[r-l+1];
    return max(F[l][k],F[r-(1<<k)+1][k]);
}

void solve(){
	ST(n);
    int i,j=0,t,ans=0,pre=0;
    for(i=1;i<=n;i++){
        t=n/i;
        if(pre!=t){//如果区间长度和上次一样，不用初始化，直接累加下一个区间最值即可 
            j=0;
            ans=0;
        }
        for(;j<i;j++)
            ans+=RMQ(t*j+1,j*t+t);
        pre=t;
        if(ans>k) break;
    }
    if(i>n)
		printf("-1\n");
    else
    	printf("%d\n",i);
}

int main(){
    Initlog();
	while(scanf("%d%d",&n,&k)){
        if(n==-1&&k==-1)
        	break;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
		solve();
    }
    return 0;
}
