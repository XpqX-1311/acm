//基于边权，修改单条边权，查询路径边权最大值（SPOJ QTREE 树链剖分 + 线段树）

const int MAXN = 10010;
struct Edge {
    int to, next;
} edge[MAXN*2];
int head[MAXN], tot;
int top[MAXN];//top[v] 表示 v 所在的重链的顶端节点
int fa[MAXN]; //父亲节点
int deep[MAXN];//深度
int num[MAXN];//num[v] 表示以 v 为根的子树的节点数
int p[MAXN];//p[v] 表示 v 与其父亲节点的连边在线段树中的位置
int fp[MAXN];//和 p 数组相反
int son[MAXN];//重儿子
int pos;

void init() {
    tot = 0;
    memset(head, -1, sizeof(head));
    pos = 0;
    memset(son, -1, sizeof(son));
}

void addedge(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

//第一遍 dfs 求出 fa,deep,num,son
void dfs1(int u, int pre, int d) {
    deep[u] = d;
    fa[u] = pre;
    num[u] = 1;
    for(int i = head[u]; i!=-1; i = edge[i].next) {
        int v = edge[i].to;
        if(v!=pre) {
            dfs1(v, u, d+1);
            num[u] += num[v];
            if(son[u]==-1 || num[v] > num[son[u]])
                son[u] = v;
        }
    }
}

//第二遍 dfs 求出 top 和 p
void getpos(int u, int sp) {
    top[u] = sp;
    p[u] = pos++;
    fp[p[u]] = u;
    if(son[u]==-1) return;
    getpos(son[u], sp);
    for(int i = head[u]; i!=-1; i = edge[i].next) {
        int v = edge[i].to;
        if(v!=son[u] && v!=fa[u])
            getpos(v, v);
    }
}

//线段树
struct Node {
    int l, r;
    int Max;
} segTree[MAXN*3];

void build(int i, int l, int r) {
    segTree[i].l = l;
    segTree[i].r = r;
    segTree[i].Max = 0;
    if(l==r)return;
    int mid = (l+r)/2;
    build(i<<1, l, mid);
    build((i<<1)|1, mid+1, r);
}

void push_up(int i) {
    segTree[i].Max = max(segTree[i<<1].Max, segTree[(i<<1)|1].Max);
}

// 更新线段树的第 k 个值为 val
void update(int i, int k, int val) {
    if(segTree[i].l==k && segTree[i].r==k) {
        segTree[i].Max = val;
        return;
    }
    int mid = (segTree[i].l+segTree[i].r)/2;
    if(k <= mid)update(i<<1, k, val);
    else update((i<<1)|1, k, val);
    push_up(i);
}

//查询线段树中 [l,r] 的最大值
int query(int i, int l, int r) {
    if(segTree[i].l==l && segTree[i].r==r)
        return segTree[i].Max;
    int mid = (segTree[i].l+segTree[i].r)/2;
    if(r <= mid)return query(i<<1, l, r);
    else if(l > mid)return query((i<<1)|1, l, r);
    else return max(query(i<<1, l, mid), query((i<<1)|1, mid+1, r));
}

//查询 u->v 边的最大值
int find(int u, int v) {
    int f1 = top[u], f2 = top[v];
    int tmp = 0;
    while(f1!=f2) {
        if(deep[f1] < deep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        tmp = max(tmp, query(1, p[f1], p[u]));
        u = fa[f1];
        f1 = top[u];
    }
    if(u==v)return tmp;
    if(deep[u] > deep[v]) swap(u, v);
    return max(tmp, query(1, p[son[u]], p[v]));
}

int e[MAXN][3];

int main() {
    int T;
    int n;
    scanf("%d", &T);
    while(T--) {
        init();
        scanf("%d", &n);
        for(int i = 0; i < n-1; i++) {
            scanf("%d%d%d", &e[i][0], &e[i][1], &e[i][2]);
            addedge(e[i][0], e[i][1]);
            addedge(e[i][1], e[i][0]);
        }
        dfs1(1, 0, 0);
        getpos(1, 1);
        build(1, 0, pos-1);
        for(int i = 0; i < n-1; i++) {
            if(deep[e[i][0]] > deep[e[i][1]])
                swap(e[i][0], e[i][1]);
            update(1, p[e[i][1]], e[i][2]);
        }
        char op[10];
        int u, v;
        while(scanf("%s", op)==1) {
            if(op[0]=='D')break;
            scanf("%d%d", &u, &v);
            if(op[0]=='Q')
                printf("%d\n", find(u, v));//查询 u->v 路径上边权的最大值
            else update(1, p[e[u-1][1]], v);//修改第 u 条边的长度为 v
        }
    }
    return 0;
}