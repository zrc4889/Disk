#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;

int main(){
	long long sum;
	int n,t,t1,t2;
	while(cin>>n){
		priority_queue<int,vector<int>,greater<int> >q;
		for(int i=0;i<n;i++){
			cin>>t;
			q.push(t);
		}
		sum=0;
		while(q.size()>1){
			t1=q.top();
			q.pop();
			t2=q.top();
			q.pop();
			t=t1+t2;
			sum+=t;
			q.push(t);
		}
		cout<<sum<<endl;
	}
	return 0;
}

