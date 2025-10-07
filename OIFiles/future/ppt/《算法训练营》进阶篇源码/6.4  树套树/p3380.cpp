#include<cstdio>//线段树+Treap,注意开O2优化 
#include<cstdlib>
#include<ctime>
#include<algorithm>
#define ls t[x].ch[0]
#define rs t[x].ch[1]
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=20e5+10;//平衡树节点数nlogn，尽量开大一点 
int n,m,mn,mx;
int p[maxn];

struct node{//平衡树节点 
	int val,key,cnt,size;
	int ch[2];
}t[maxn];
int tot;//平衡树节点总数 

struct Treap{//平衡树 
	int root;
	void update(int x){//更新 
		t[x].size=t[ls].size+t[rs].size+t[x].cnt;
	}
	
	void rotate(int &x,bool c){//旋转 
		int y=t[x].ch[c];
		t[x].ch[c]=t[y].ch[c^1];
		t[y].ch[c^1]=x;
		update(x),update(x=y);
	}
	
	void insert(int &x,int val){//插入 
		if(!x){
			x=++tot;
			t[x].cnt=t[x].size=1;
			t[x].key=rand(),t[x].val=val;
			t[x].ch[0]=t[x].ch[1]=0;
			return ;
		}
		if(t[x].val==val){t[x].cnt++;}
		else{
			bool c=val>t[x].val;
			insert(t[x].ch[c],val);
			if(t[x].key<t[t[x].ch[c]].key) rotate(x,c);
		}
		update(x);
	}
	
	void delet(int &x,int val){//删除 
		if(!x) return ;
		if(t[x].val==val){
			if(t[x].cnt>1){t[x].cnt--;t[x].size--;return;}
			if(ls==0||rs==0){x=ls+rs;return;}
			bool c=t[ls].key>t[rs].key;
			rotate(x,c),delet(t[x].ch[c^1],val);
		}
		else delet(t[x].ch[t[x].val<val],val);
		update(x);
	}
	
	int rank(int x,int val){//返回比val小的数 
		if(!x) return 0;
		if(t[x].val==val) return t[ls].size;
		if(t[x].val>val) return rank(ls,val);
		else return t[ls].size+t[x].cnt+rank(rs,val);
	}
	
	int pre(int x,int val){//找前驱 
		if(!x) return -inf;
		if(t[x].val>=val) return pre(ls,val);
		else return max(t[x].val,pre(rs,val));
	}
	
	int nxt(int x,int val){//找后继 
		if(!x) return inf;
		if(t[x].val<=val) return nxt(rs,val);
		else return min(t[x].val,nxt(ls,val));
	}
}a[maxn];//线段树每一个节点对应一棵平衡树 

void build(int x,int l,int r){//创建线段树(非存储型) 
	a[x].root=0;
	for(int i=l;i<=r;i++)
		a[x].insert(a[x].root,p[i]);//将区间[l,r]数据插入到平衡树中 
	if(l==r) return ;
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}

int queryrank(int x,int l,int r,int ql,int qr,int k){//查询[ql,qr]值为k的排名 
	if(ql<=l&&r<=qr)
		return a[x].rank(a[x].root,k);//在平衡树中查询比k小的元素个数 
	int ans=0,mid=(l+r)>>1;
	if(ql<=mid)	ans+=queryrank(x<<1,l,mid,ql,qr,k);
	if(qr>mid) ans+=queryrank(x<<1|1,mid+1,r,ql,qr,k);
	return ans;
}

int queryval(int ql,int qr,int k){//查询[ql,qr]排名为k的值
	int l=mn,r=mx,mid,ans=0;//二分 
	while(l<=r){
		mid=(l+r)>>1;
		if(queryrank(1,1,n,ql,qr,mid)+1<=k) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}

void modify(int x,int l,int r,int pos,int k){//点更新，将第pos个元素改为k 
	a[x].delet(a[x].root,p[pos]);//先从平衡树中删除 
	a[x].insert(a[x].root,k);//再将新值插入平衡树
	if(l==r) return ;
	int mid=(l+r)>>1;
	if(pos<=mid) modify(x<<1,l,mid,pos,k);
	else modify(x<<1|1,mid+1,r,pos,k);
}

int querypre(int x,int l,int r,int ql,int qr,int k){//查询[ql,qr]中k的前驱 
	if(ql<=l&&r<=qr) return a[x].pre(a[x].root,k);//在平衡树中查询前驱
	int mid=(l+r)>>1,ans=-inf;
	if(ql<=mid) ans=max(ans,querypre(x<<1,l,mid,ql,qr,k));
	if(qr>mid) ans=max(ans,querypre(x<<1|1,mid+1,r,ql,qr,k));
	return ans;
}

int querynxt(int x,int l,int r,int ql,int qr,int k){//查询[ql,qr]中k的后继 
	if(ql<=l&&r<=qr) return a[x].nxt(a[x].root,k);//在平衡树中查询后继 
	int mid=(l+r)>>1,ans=inf;
	if(ql<=mid) ans=min(ans,querynxt(x<<1,l,mid,ql,qr,k));
	if(qr>mid) ans=min(ans,querynxt(x<<1|1,mid+1,r,ql,qr,k));
	return ans;
}

int main(){
	srand(time(0));
	scanf("%d%d",&n,&m);
	mn=inf,mx=-inf;//初始化最小值、最大值 
	for(int i=1;i<=n;i++){
		scanf("%d",&p[i]);
		mn=min(mn,p[i]),mx=max(mx,p[i]);
	}
	tot=0;
	build(1,1,n);
	while(m--){
		int opt,l,r,k,pos;
		scanf("%d",&opt);
		if(opt==1){//查询值为k的排名
			scanf("%d%d%d",&l,&r,&k);
			printf("%d\n",queryrank(1,1,n,l,r,k)+1);
		}
		else if(opt==2){//查询排名为k的值
			scanf("%d%d%d",&l,&r,&k);
			printf("%d\n",queryval(l,r,k));
		}
		else if(opt==3){//点更新 
			scanf("%d%d",&pos,&k);
			modify(1,1,n,pos,k);p[pos]=k;
			mn=min(mn,k),mx=max(mx,k);
		}
		else if(opt==4){//找k的前驱 
			scanf("%d%d%d",&l,&r,&k);
			int ans=querypre(1,1,n,l,r,k);
			printf("%d\n",ans==-inf?-2147483647:ans);
		}
		else{//找k的后继
			scanf("%d%d%d",&l,&r,&k);
			int ans=querynxt(1,1,n,l,r,k);
			printf("%d\n",ans==inf?2147483647:ans);
		}
	}
	return 0;
}
