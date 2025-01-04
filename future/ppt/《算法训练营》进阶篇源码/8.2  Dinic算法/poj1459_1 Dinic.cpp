#include<iostream>//当前弧优化，下次直接从cur[u]开始增广，节省时间，优化后485ms 
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=110;
const int M=10100;
int n,m,cnt;
int head[N],d[N],cur[N];
struct Edge{
   int v,next;
   int cap,flow;
}E[M<<1];//双边

void init(){//初始化 
    memset(head,-1,sizeof(head));
    cnt=0;
}

void add(int u,int v,int c){
    E[cnt].v=v;
    E[cnt].cap=c;
    E[cnt].flow=0;
    E[cnt].next=head[u];
    head[u]=cnt++;
}

void adde(int u,int v,int c){
    add(u,v,c);
    add(v,u,0);
}

bool bfs(int s,int t){//分层
    memset(d,0,sizeof(d));
    queue<int>q;
    d[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];~i;i=E[i].next){
        	int v=E[i].v;
        	if(!d[v]&&E[i].cap>E[i].flow){
                d[v]=d[u]+1;
				q.push(v);
				if(v==t)  return 1;
			}	
		}
    }
    return 0;
}

int dfs(int u,int flow,int t){//在分层的基础上dfs 
    if(u==t) return flow;
	int rest=flow;//最小残量 
    for(int &i=cur[u];~i;i=E[i].next){//引用&，cur和i一起更新，或在内部写cur[u]=E[i].next 
    	int v=E[i].v;
    	if(d[v]==d[u]+1&&E[i].cap>E[i].flow){
            int k=dfs(v,min(rest,E[i].cap-E[i].flow),t);
			if(!k) d[v]=0;//优化
			E[i].flow+=k;
			E[i^1].flow-=k;
			rest-=k;
			if(!rest) break;//此处很重要，避免更新cur
		}	
	}
	return flow-rest;
}

int Dinic(int s,int t){
	int maxflow=0;
	while(bfs(s,t)){
		for(int i=0;i<=n+2;i++)
			cur[i]=head[i];
		maxflow+=dfs(s,inf,t);
	}
	return maxflow;
}

int main(){
    int np,nc,u,v,w;
	char ch;
    while(cin>>n>>np>>nc>>m){
        init();
        for(int i=1;i<=m;i++){
			cin>>ch>>u>>ch>>v>>ch>>w;
            adde(u,v,w);
        }
        for(int i=1;i<=np;i++){
			cin>>ch>>v>>ch>>w;
            adde(n+1,v,w);
        }
        for(int i=1;i<=nc;i++){
            cin>>ch>>u>>ch>>w;
            adde(u,n+2,w);
        }
        cout<<Dinic(n+1,n+2)<<endl;
    }
    return 0;
}
