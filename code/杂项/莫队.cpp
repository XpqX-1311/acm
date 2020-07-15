//莫队算法，可以解决一类静态，离线区间查询问题。
//BZOJ 2038: [2009 国家集训队] 小 Z 的袜子 (hose)
//Description
//作为一个生活散漫的人，小 Z 每天早上都要耗费很久从一堆五颜六色的袜子中找出一双来穿。终于有一天，小 Z 再也无法忍受这恼人的找袜子过程，于是他决定听天由命……具体来说，小 Z 把这 N 只袜子从 1 到 N 编号，然后从编号 L 到 R(L
//Input
//输入文件第一行包含两个正整数 N 和 M。N 为袜子的数量，M 为小 Z 所提的询问的数量。接下来一行包含 N 个正整数 Ci，其中 Ci 表示第 i 只袜子的颜色，相同的颜色用相同的数字表示。再接下来 M 行，每行两个正整数 L，R 表示一个询问。
//Output
//包含 M 行，对于每个询问在一行中输出分数 A/B 表示从该询问的区间 [L,R] 中随机抽出两只袜子颜色相同的概率。若该概率为 0 则输出 0/1，否则输出的 A/B 必须为最简分数。（详见样例）
//Sample Input
//6 4
//1 2 3 3 3 2
//2 6
//1 3
//3 5
//1 6
//Sample Output
//2/5
//0/1
//1/1
//4/15

//只需要统计区间内各个数出现次数的平方和
//莫队算法，两种方法，一种是直接分成 sqrt(n) 块，分块排序。
//另外一种是求得曼哈顿距离最小生成树，根据 manhattan MST 的 dfs 序求解。

//分块
//离线一般会比线段树快
const int MAXN = 50010;
const int MAXM = 50010;
struct Query {
    int L, R, id;
} node[MAXM];

long long gcd(long long a, long long b) {
    if(b==0)return a;
    return gcd(b, a%b);
}

struct Ans {
    long long a, b;//分数 a/b
    void reduce() {//分数化简
        long long d = gcd(a, b);
        a /= d;
        b /= d;
    }
} ans[MAXM];

int a[MAXN];
int num[MAXN];
int n, m, unit;

bool cmp(Query a, Query b) {
    if(a.L/unit!=b.L/unit)return a.L/unit < b.L/unit;
    else return a.R < b.R;
}

void work() {
    long long temp = 0;
    memset(num, 0, sizeof(num));
    int L = 1;
    int R = 0;
    for(int i = 0; i < m; i++) {
        while(R < node[i].R) {
            R++;
            temp -= (long long) num[a[R]]*num[a[R]];
            num[a[R]]++;
            temp += (long long) num[a[R]]*num[a[R]];
        }
        while(R > node[i].R) {
            temp -= (long long) num[a[R]]*num[a[R]];
            num[a[R]]--;
            temp += (long long) num[a[R]]*num[a[R]];
            R--;
        }
        while(L < node[i].L) {
            temp -= (long long) num[a[L]]*num[a[L]];
            num[a[L]]--;
            temp += (long long) num[a[L]]*num[a[L]];
            L++;
        }
        while(L > node[i].L) {
            L--;
            temp -= (long long) num[a[L]]*num[a[L]];
            num[a[L]]++;
            temp += (long long) num[a[L]]*num[a[L]];
        }
        ans[node[i].id].a = temp-(R-L+1);
        ans[node[i].id].b = (long long) (R-L+1)*(R-L);
        ans[node[i].id].reduce();
    }
}

int main() {
    while(scanf("%d%d", &n, &m)==2) {
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        for(int i = 0; i < m; i++) {
            node[i].id = i;
            scanf("%d%d", &node[i].L, &node[i].R);
        }
        unit = (int) sqrt(n);
        sort(node, node+m, cmp);
        work();
        for(int i = 0; i < m; i++)
            printf("%lld/%lld\n", ans[i].a, ans[i].b);
    }
    return 0;
}

//Manhattan MST 的 dfs 顺序求解
const int MAXN = 50010;
const int MAXM = 50010;
const int INF = 0x3f3f3f3f;
struct Point {
    int x, y, id;
} p[MAXN], pp[MAXN];

bool cmp(Point a, Point b) {
    if(a.x!=b.x) return a.x < b.x;
    else return a.y < b.y;
}

//树状数组，找 y-x 大于当前的，但是 y+x 最小的
struct BIT {
    int min_val, pos;

    void init() {
        min_val = INF;
        pos = -1;
    }
} bit[MAXN];

struct Edge {
    int u, v, d;
} edge[MAXN<<2];

bool cmpedge(Edge a, Edge b) {
    return a.d < b.d;
}

int tot;
int n;
int F[MAXN];

int find(int x) {
    if(F[x]==-1) return x;
    else return F[x] = find(F[x]);
}

void addedge(int u, int v, int d) {
    edge[tot].u = u;
    edge[tot].v = v;
    edge[tot++].d = d;
}

struct Graph {
    int to, next;
} e[MAXN<<1];
int total, head[MAXN];

void _addedge(int u, int v) {
    e[total].to = v;
    e[total].next = head[u];
    head[u] = total++;
}

int lowbit(int x) {
    return x&(-x);
}

void update(int i, int val, int pos) {
    while(i > 0) {
        if(val < bit[i].min_val) {
            bit[i].min_val = val;
            bit[i].pos = pos;
        }
        i -= lowbit(i);
    }
}

int ask(int i, int m) {
    int min_val = INF, pos = -1;
    while(i <= m) {
        if(bit[i].min_val < min_val) {
            min_val = bit[i].min_val;
            pos = bit[i].pos;
        }
        i += lowbit(i);
    }
    return pos;
}

int dist(Point a, Point b) {
    return abs(a.x-b.x)+abs(a.y-b.y);
}

void Manhattan_minimum_spanning_tree(int n, Point p[]) {
    int a[MAXN], b[MAXN];
    tot = 0;
    for(int dir = 0; dir < 4; dir++) {
        if(dir==1 || dir==3) {
            for(int i = 0; i < n; i++)
                swap(p[i].x, p[i].y);
        } else if(dir==2) {
            for(int i = 0; i < n; i++)
                p[i].x = -p[i].x;
        }
        sort(p, p+n, cmp);
        for(int i = 0; i < n; i++)
            a[i] = b[i] = p[i].y-p[i].x;
        sort(b, b+n);
        int m = unique(b, b+n)-b;
        for(int i = 1; i <= m; i++)
            bit[i].init();
        for(int i = n-1; i >= 0; i--) {
            int pos = lower_bound(b, b+m, a[i])-b+1;
            int ans = ask(pos, m);
            if(ans!=-1)
                addedge(p[i].id, p[ans].id, dist(p[i], p[ans]));
            update(pos, p[i].x+p[i].y, i);
        }
    }
    memset(F, -1, sizeof(F));
    sort(edge, edge+tot, cmpedge);
    total = 0;
    memset(head, -1, sizeof(head));
    for(int i = 0; i < tot; i++) {
        int u = edge[i].u, v = edge[i].v;
        int t1 = find(u), t2 = find(v);
        if(t1!=t2) {
            F[t1] = t2;
            _addedge(u, v);
            _addedge(v, u);
        }
    }
}

int m;
int a[MAXN];
struct Ans {
    long long a, b;
} ans[MAXM];
long long temp;
int num[MAXN];

void add(int l, int r) {
    for(int i = l; i <= r; i++) {
        temp -= (long long) num[a[i]]*num[a[i]];
        num[a[i]]++;
        temp += (long long) num[a[i]]*num[a[i]];
    }
}

void del(int l, int r) {
    for(int i = l; i <= r; i++) {
        temp -= (long long) num[a[i]]*num[a[i]];
        num[a[i]]--;
        temp += (long long) num[a[i]]*num[a[i]];
    }
}

void dfs(int l1, int r1, int l2, int r2, int idx, int pre) {
    if(l2 < l1) add(l2, l1-1);
    if(r2 > r1) add(r1+1, r2);
    if(l2 > l1) del(l1, l2-1);
    if(r2 < r1) del(r2+1, r1);
    ans[pp[idx].id].a = temp-(r2-l2+1);
    ans[pp[idx].id].b = (long long) (r2-l2+1)*(r2-l2);
    for(int i = head[idx]; i!=-1; i = e[i].next) {
        int v = e[i].to;
        if(v==pre) continue;
        dfs(l2, r2, pp[v].x, pp[v].y, v, idx);
    }
    if(l2 < l1)del(l2, l1-1);
    if(r2 > r1)del(r1+1, r2);
    if(l2 > l1)add(l1, l2-1);
    if(r2 < r1)add(r2+1, r1);
}

long long gcd(long long a, long long b) {
    if(b==0) return a;
    else return gcd(b, a%b);
}

int main() {
    while(scanf("%d%d", &n, &m)==2) {
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &p[i].x, &p[i].y);
            p[i].id = i;
            pp[i] = p[i];
        }
        Manhattan_minimum_spanning_tree(m, p);
        memset(num, 0, sizeof(num));
        temp = 0;
        dfs(1, 0, pp[0].x, pp[0].y, 0, -1);
        for(int i = 0; i < m; i++) {
            long long d = gcd(ans[i].a, ans[i].b);
            printf("%lld/%lld\n", ans[i].a/d, ans[i].b/d);
        }
    }
    return 0;
}