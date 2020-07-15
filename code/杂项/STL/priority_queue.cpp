//empty()如果队列为空返回真
//pop()删除对顶元素
//push()加入一个元素
//size()返回优先队列中拥有的元素个数
//top()返回优先队列队顶元素在默认的优先队列中，优先级高的先出队。在默认的 int 型中先出队的为较大的数。

priority_queue<int> q1;//大的先出队
priority_queue<int, vector<int>, greater<int> > q2; //小的先出队

// 自定义比较函数：
struct cmp {
    bool operator()(int x, int y) {
        return x > y; // x 小的优先级高
        //也可以写成其他方式，如：return p[x] > p[y]; 表示 p[i] 小的优先级高
    }
};
priority_queue<int, vector<int>, cmp> q;//定义方法
//其中，第二个参数为容器类型。第三个参数为比较函数。

struct node {
    int x, y;

    friend bool operator<(node a, node b) {
        return a.x > b.x; //结构体中，x 小的优先级高
    }
};
priority_queue <node> q;//定义方法
//在该结构中，y 为值, x 为优先级。
//通过自定义 operator< 操作符来比较元素中的优先级。
//在重载”<”时，最好不要重载”>”，可能会发生编译错误