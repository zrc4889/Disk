#include<cstdio>
#include<cstring>
using namespace std;
#define N 50010
int n,fa[N],d[N];

void Init(){
	for(int i=1;i<=n;i++){
		fa[i]=i;
		d[i]=0;
	}	
}

int Find(int x){
	int fx=fa[x];
	if(x!=fa[x]){
		fa[x]=Find(fa[x]);
		d[x]=(d[x]+d[fx])%3;
	} 	
    return fa[x];
}

void print(){
	for(int i=1;i<=n;i++){
		printf("fa[%d",i);
		printf("]=%d\t",fa[i]);
		printf("d[%d",i);
		printf("]=%d\n",d[i]);
	}
} 

int main(){
	int k,c,x,y,total=0,a,b;
	scanf("%d%d",&n,&k);
	Init();
	while(k--){
		scanf("%d%d%d",&c,&x,&y);
		if(x>n||y>n||(c==2&&x==y))
			total++;
		else{
			a=Find(x),b=Find(y);
			if(a==b){
				if((d[x]-d[y]+3)%3!=c-1)
					total++;
			}
			else{
				fa[a]=b;
				d[a]=(d[y]-d[x]+3+c-1)%3;
			}
		}
		print();
	}
	printf("%d\n",total);
	return 0;
}
/*
7 9
2 1 2
2 2 3
1 1 3
2 3 1
1 5 5
2 5 2
2 6 1
2 3 7
1 6 6
*/
