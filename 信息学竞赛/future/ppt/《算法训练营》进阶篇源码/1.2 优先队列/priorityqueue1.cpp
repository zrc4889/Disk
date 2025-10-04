#include<iostream>//优先队列实现原理，以最大堆为例实现最大值优先 
#include<algorithm>
using namespace std;
const int N=1000;
int r[N],n;

void Sink(int k){//下沉操作
    while(2*k<=n){//如果有左孩子
        int j=2*k;//j指向左孩子
        if(j<n&&r[j]<r[j+1])//如果有右孩子且左孩子比右孩子小
            j++;    //j指向右孩子
        if(r[k]>=r[j])//比较大的孩子大
            break;    //已满足堆
        else
            swap(r[k],r[j]);//与较大的孩子交换
        k=j;//k指向交换后的新位置，继续向下比较，一直下沉到叶子
    }
}

void Swim(int k){//上浮操作
    while(k>1&&r[k]>r[k/2]){//如果大于双亲
        swap(r[k],r[k/2]);//与双亲交换
        k=k/2;//k指向交换后的新位置，继续向上比较，一直上浮到根
    }
}

void CreatHeap(){//构建初始堆
    for(int i=n/2;i>0;i--)//从最后一个分支结点n/2开始下沉调整为堆，直到第一个结点
        Sink(i);
}

void push(int x){//入队
    r[++n]=x;//n加1后，将新元素放入尾部
    Swim(n);//最后一个元素上浮操作
}

void pop(){//出队
    if(n<1){
		cout<<"队列为空"<<endl; 
		return;
	}
	cout<<r[1]<<endl;//输出堆顶
    r[1]=r[n--];//最后一个元素代替堆顶，n减1
    Sink(1);//堆顶下沉操作
}

void print(){//输出队列中所有元素 
    for(int i=1;i<=n;i++)
        cout<<r[i]<<" ";
    cout<<endl;
}

int main(){
    int select,x;
    cout<<"请输入元素个数："<<endl;
    cin>>n;
    cout<<"请输入"<<n<<"个整数："<<endl;
    for(int i=1;i<=n;i++)
        cin>>r[i];
    CreatHeap();//创建初始堆
    while(true){
        cout<<"请选择数字：1.入队；2.出队；3.输出；0.退出"<<endl;
        cin>>select;
        switch(select){
            case 1:
                cout<<"输入入队元素："<<endl;
                cin>>x;
                push(x);//入队
                break;
            case 2:
                pop();//出队
                break;
            case 3:
                print();//输出队列中所有元素 
                break;
            case 0:
                return 0;
        }
    }
    return 0;
}
/*
10
30 28 20 16 18 2 16 6 10 12
*/
