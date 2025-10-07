#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define LL long long
LL dp[2][1<<24];//记录方案数 
int state[2][1<<24];//记录状态，S=state[pre][s]，pre为前一个格子标记，s为状态编号,S为状态 
int total[2];//记录状态总数 
int pre,now;
int endx,endy;//记录最后一个非障碍格子 
bool map[15][15];
int m,n;
LL ans;
const int HASH=40013;//坑点！！哈希值太小会超时！4位素数超时，m<=12,用30013,100003等
int Hash[HASH];//记录S对应的哈希值x的状态编号
 
void HashIn(int S,LL num){//哈希表处理 
	int x=S%HASH;
	while(~Hash[x]&&state[now][Hash[x]]!=S){//线性探测 
		x++;
		x%=HASH;
	}
	if(Hash[x]==-1){//未找到，加入hash表中 
		dp[now][total[now]]=num;
		state[now][total[now]]=S;
		Hash[x]=total[now];//记录状态编号
		total[now]++;
	}
	else//找到，累加方案数 
		dp[now][Hash[x]]+=num;
}
 
void init(){//初始化地图 
	memset(map,0,sizeof(map));
	endx=-1;//最后一个非障碍格子
	for(int i=0;i<n;i++){
		char str[200];
		scanf("%s",str);
		for(int j=0;j<m;j++){
			if(str[j]=='*')
				map[i][j]=0;
			else if(str[j]=='.'){
				map[i][j]=1;
				endx=i;//最后一个非障碍格子
				endy=j;
			}
		}
	}
}
 
//位运算，取S按长度l的第p位
int getV(int S,int p,int l=2){//4进制，l=2；8进制，l=3
	return (S>>(p*l))&((1<<l)-1);
}
 
//位运算，设置S按长度l的第p位值为v
void setV(int& S,int p,int v,int l=2){
	S^=getV(S,p)<<(p*l);//第p位置0
	S|=v<<(p*l);//第p位置v 
}
 
void memsetnow(){//清空哈希表
	memset(Hash,-1,sizeof(Hash));
	total[now]=0;
}
 
void solve(){//求解答案 
	if(endx==-1){//没有非障碍格子 
		puts("0");
		return;
	}
	pre=0,now=1;
	ans=0;
	dp[pre][0]=1;
	state[pre][0]=0;//记录前一个已确定格子的状态 
	total[pre]=1;//记录前一个已确定格子的状态编号
	for(int i=0;i<n;i++){//枚举行 
		for(int j=0;j<m;j++){//枚举列 
			memsetnow();//哈希表清空
			for(int s=0;s<total[pre];s++){//枚举前一个已确定格子的所有状态编号 
				LL num=dp[pre][s];//读取前一个方案数 
				int S=state[pre][s];//读取前一个状态 
				int p=getV(S,j); //得到第j位 
				int q=getV(S,j+1);//得到第j+1位 
				if(map[i][j]==0){//有障碍，第一种情况 
					if(p==0&&q==0)
						HashIn(S,num);//插入哈希表 
					continue;
				}
				if(p==0&&q==0){//p、q均为0，第二种情况 
					if(map[i+1][j]&&map[i][j+1]){
						int nS=S;
						setV(nS,j,1);//第j位改为1 
						setV(nS,j+1,2);//第j+1位改为2
						HashIn(nS,num);
					}
					continue;
				}
				if((p>0)^(q>0)){//p、q有一个为0，第三种情况 
					if(map[i+(p>0)][j+(q>0)])//状态不变 
						HashIn(S,num);
					if(map[i+(q>0)][j+(p>0)]){//状态相反 
						int nS=S;
						setV(nS,j,q);//p、q交换 
						setV(nS,j+1,p);
						HashIn(nS,num);
					}
					continue;
				}
				if(p==1&&q==1){//第四种情况，4.1 
					int find=1;
					for(int v=j+2;v<=m;v++){//向后搜q匹配的右括号),改为左括号 
						int k=getV(S,v);//得到第v位 
						if(k==1)
							find++;
						else if(k==2)
							find--;
						if(find==0){
							int nS=S;
							setV(nS,j,0);//p、q置0 
							setV(nS,j+1,0);
							setV(nS,v,1);//改为左括号
							HashIn(nS,num);
							break;
						}
					}
					continue;
				}
				if(p==2&&q==2){//第四种情况，4.2 
					int find=1;
					for(int v=j-1;v>=0;v--){//向前搜p匹配的左括号(,改为右括号 
						int k=getV(S,v);//得到第v位
						if(k==2)
							find++;
						else if(k==1)
							find--;
						if(find==0){
							int nS=S;
							setV(nS,j,0);//p、q置0 
							setV(nS,j+1,0);
							setV(nS,v,2);//改为右括号
							HashIn(nS,num);
							break;
						}
					}
					continue;
				}
				if(p==2&&q==1){//第四种情况，4.3 
					int nS=S;
					setV(nS,j,0);//p、q置0 
					setV(nS,j+1,0);
					HashIn(nS,num);
					continue;
				}
				if(p==1&&q==2){//第四种情况，4.4 
					if(i==endx&&j==endy)//最后一个非障碍格子 
						ans+=num;
				}
			}
			swap(now,pre);
		}
		memsetnow();//哈希表清空
		for(int s=0;s<total[pre];s++){//换行处理 
			LL num=dp[pre][s];
			int S=state[pre][s]<<2;//左移一格，四进制，一格用两位表示 
			HashIn(S,num);
		}
		swap(now,pre);
	}
	printf("%I64d\n",ans);
}
 
int main(){
	while(~scanf("%d%d",&n,&m)){
		init();//初始化地图
		solve();
	}
	return 0;
}
