//区间求和类问题（前缀和）
//求序列中第 K 大数
//“楼兰^V图腾”类问题的统计
//最大值/最小值

const int maxn = 200010;
int n, m;
int a[maxn], rs[maxn];

int lowbit(int x) {
    return x&-x;
}

void update(int x, int val) {
    while(x <= n) {
        rs[x] += val;
        x += lowbit(x);
    }
}

int query_sum(int x) {
    int res = 0;
    while(x > 0) {
        res += rs[x];
        x -= lowbit(x);
    }
    return res;
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        memset(rs, 0, sizeof(rs));
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            update(i, a[i]);
        }
        char ch[5];
        int l, r;
        while(m--) {
            scanf("%s%d%d", ch, &l, &r);
            if(ch[0]=='Q') printf("%d\n", query_sum(r)-query_sum(l));
            else update(l, r);
        }
    }
    return 0;
}