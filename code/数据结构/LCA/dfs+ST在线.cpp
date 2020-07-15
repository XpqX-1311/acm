/*
 * LCA (POJ 1330)
 * 在线算法 DFS + ST
 */
const int MAXN = 10010;
int rmq[2*MAXN];//rmq 数组，就是欧拉序列对应的深度序列
struct ST {
    int mm[2*MAXN];
    int dp[2*MAXN][20];//最小值对应的下标
    void init(int n) {
        mm[0] = -1;
        for(int i = 1; i <= n; i++) {
            mm[i] = ((i&(i-1))==0) ? mm[i-1]+1 : mm[i-1];
            dp[i][0] = i;
        }
        for(int j = 1; j <= mm[n]; j++)
            for(int i = 1; i+(1<<j)-1 <= n; i++)
                dp[i][j] = rmq[dp[i][j-1]] < rmq[dp[i+(1<<(j-1))][j
                ]] ? dp[i][j-1] : dp[i+(1<<(j-1))][j-1];
    }

    //查询 [a,b] 之间最小值的下标
    int query(int a, int b) {
        if(a > b)swap(a, b);
        int k = mm[b-a+1];
        return rmq[dp[a][k]] <= rmq[dp[b-(1<<k)+1][k]] ? dp[a][k] : dp[
                (1<<k)+1][k];
    }
};

//边的结构体定义
struct Edge {
    int to, next;
};
Edge edge[MAXN*2];
int tot, head[MAXN];

int F[MAXN*2];//欧拉序列，就是 dfs 遍历的顺序，长度为 2*n-1, 下标从 1 开始
int P[MAXN];//P[i] 表示点 i 在 F 中第一次出现的位置
int cnt;
ST st;

void init() {
    tot = 0;
    memset(head, -1, sizeof(head));
}

//加边，无向边需要加两次
void addedge(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void dfs(int u, int pre, int dep) {
    F[++cnt] = u;
    rmq[cnt] = dep;
    P[u] = cnt;
    for(int i = head[u]; i!=-1; i = edge[i].next) {
        int v = edge[i].to;
        if(v==pre)continue;
        dfs(v, u, dep+1);
        F[++cnt] = u;
        rmq[cnt] = dep;
    }
}

//查询 LCA 前的初始化
void LCA_init(int root, int node_num) {
    cnt = 0;
    dfs(root, root, 0);
    st.init(2*node_num-1);
}

//查询 u,v 的 lca 编号
int query_lca(int u, int v) {
    return F[st.query(P[u], P[v])];
}

bool flag[MAXN];

int main() {
    int T;
    int N;
    int u, v;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &N);
        init();
        memset(flag, false, sizeof(flag));
        for(int i = 1; i < N; i++) {
            scanf("%d%d", &u, &v);
            addedge(u, v);
            addedge(v, u);
            flag[v] = true;
        }
        int root;
        for(int i = 1; i <= N; i++)
            if(!flag[i]) {
                root = i;
                break;
            }
        LCA_init(root, N);
        scanf("%d%d", &u, &v);
        printf("%d\n", query_lca(u, v));
    }
    return 0;
}