//在一个DAG（有向无环图）上表示出一个字符串的所有子串

const int CHAR = 26;
const int MAXN = 250010;

struct SAM_Node {
    SAM_Node *fa, *next[CHAR];
    int len;
    long long cnt;

    void clear() {
        fa = 0;
        memset(next, 0, sizeof(next));
        cnt = 0;
    }
} pool[MAXN*2];

SAM_Node *root, *tail;

SAM_Node *newnode(int len) {
    SAM_Node *cur = tail++;
    cur->clear();
    cur->len = len;
    return cur;
}

void SAM_init() {
    tail = pool;
    root = newnode(0);
}

SAM_Node *extend(SAM_Node *last, int x) {
    SAM_Node *p = last, *np = newnode(p->len+1);
    while(p && !p->next[x])
        p->next[x] = np, p = p->fa;
    if(!p)np->fa = root;
    else {
        SAM_Node *q = p->next[x];
        if(q->len==p->len+1)np->fa = q;
        else {
            SAM_Node *nq = newnode(p->len+1);
            memcpy(nq->next, q->next, sizeof(q->next));
            nq->fa = q->fa;
            q->fa = np->fa = nq;
            while(p && p->next[x]==q)
                p->next[x] = nq, p = p->fa;
        }
    }
    return np;
}
