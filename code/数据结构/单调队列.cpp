//优先队列一般要结合题的意思来做限制

//deque版本
deque<int> maxdq;
while(!maxdq.empty()&&arr[maxdq.back()]<arr[i])
	maxdq.pop_back();
maxdq.push_back(i);

deque<int> mindq;
while(!mindq.empty()&&arr[mindq.back()]>arr[i])
	mindq.pop_back();
mindq.push_back(i);

//数组模拟 除了empty以外不会检测操作是否合法
//数组上限,超了会wa 但本地不一定会报错
#define deq_N 10000
class deq{
public:
	//模拟数组
	int arr[deq_N]
	//伪地址
	int front,end;

	void init(){
		front=0;
		end=0;
	}
	bool empty(){
		//front不可能大于end
		return front==end;
	}
	int push_back(int val){
		end++=val;
	}
	pop_back(){
		end--;
	}
	pop_front(){
		front++;
	}
};
//使用
deq dq;

while(head!=end&&dq[end-1]>=arr[i])
	end--;
while(head!=end&&dqpos[head]<i-a)
	head++;
dq[end++]=arr[i];
