///Gorgeous Sequence
///http://acm.hdu.edu.cn/showproblem.php?pid=5306
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <ctime>

using namespace std;
#define ll long long
#define N 1000000

struct node {
	int l, r;
	ll max;
	ll max2;
	ll numb;
	ll add;
	ll f;
} tree[N<<2|7];

void update(int k) {
	if(tree[k<<1].max==tree[k<<1|1].max) {
		tree[k].max=tree[k<<1].max;
		tree[k].numb=tree[k<<1].numb+tree[k<<1|1].numb;
		tree[k].max2=max(tree[k<<1].max2, tree[k<<1|1].max2);
	} else if(tree[k<<1].max>tree[k<<1|1].max) {
		tree[k].max=tree[k<<1].max;
		tree[k].numb=tree[k<<1].numb;
		tree[k].max2=max(tree[k<<1].max2, tree[k<<1|1].max);
	} else {
		tree[k].max=tree[k<<1|1].max;
		tree[k].numb=tree[k<<1|1].numb;
		tree[k].max2=max(tree[k<<1|1].max2, tree[k<<1].max);
	}
	tree[k].add=tree[k<<1].add+tree[k<<1|1].add;
}

void pushdown(int k) {
	if(tree[k].max<=tree[k].f) {
		tree[k].f=0;
		return;
	}
	if(tree[k].l==tree[k].r) {
		tree[k].max=tree[k].f;
		tree[k].add=tree[k].f;
		tree[k].f=0;
		return;
	}
	if(tree[k].max2<tree[k].f) {
		tree[k].add-=(tree[k].max-tree[k].f)*tree[k].numb;
		tree[k].max=tree[k].f;
		if(tree[k<<1].f) {
			tree[k<<1].f=min(tree[k<<1].f, tree[k].f);
		} else {
			tree[k<<1].f=tree[k].f;
		}
		if(tree[k<<1|1].f) {
			tree[k<<1|1].f=min(tree[k<<1|1].f, tree[k].f);
		} else {
			tree[k<<1|1].f=tree[k].f;
		}
		tree[k].f=0;
		return;
	}
	if(tree[k<<1].f)
		pushdown(k<<1);
	if(tree[k<<1|1].f)
		pushdown(k<<1|1);
	tree[k<<1].f=tree[k].f;
	tree[k<<1|1].f=tree[k].f;
	tree[k].f=0;
	pushdown(k<<1);
	pushdown(k<<1|1);
	update(k);
	return;
}

void build(int k, int l, int r) {
	tree[k].l=l;
	tree[k].r=r;
	tree[k].f=0;
	if(l==r) {
		scanf("%d", &tree[k].max);
		tree[k].numb=1;
		tree[k].max2=0;
		tree[k].add=tree[k].max;
		tree[k].f=0;
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1, l, mid);
	build(k<<1|1, mid+1, r);
	update(k);
}

void change_interval(int k, int l, int r, int t) {
	if(tree[k].f)
		pushdown(k);
	if(tree[k].l>=l&&tree[k].r<=r) {
		tree[k].f=t;
		pushdown(k);
		return;
	}
	int mid=(tree[k].l+tree[k].r)>>1;
	if(tree[k<<1].f)
		pushdown(k<<1);
	if(tree[k<<1|1].f)
		pushdown(k<<1|1);
	if(l<=mid) {
		change_interval(k<<1, l, r, t);
	}
	if(r>mid) {
		change_interval(k<<1|1, l, r, t);
	}
	update(k);
}

ll ask_interval_add(int k, int l, int r) {
	if(tree[k].f)
		pushdown(k);
	if(tree[k].l>=l&&tree[k].r<=r) {
		return tree[k].add;
	}
	int mid=(tree[k].l+tree[k].r)>>1;
	ll ans=0;
	if(l<=mid) {
		ans+=ask_interval_add(k<<1, l, r);
	}
	if(r>mid) {
		ans+=ask_interval_add(k<<1|1, l, r);
	}
	return ans;
}

int ask_interval_max(int k, int l, int r) {
	if(tree[k].f)
		pushdown(k);
	if(tree[k].l>=l&&tree[k].r<=r) {
		return tree[k].max;
	}
	int mid=(tree[k].l+tree[k].r)>>1;
	int ans=-1;
	if(l<=mid) {
		ans=ask_interval_max(k<<1, l, r);
	}
	if(r>mid) {
		if(ans==-1)
			ans=ask_interval_max(k<<1|1, l, r);
		else
			ans=max(ans, ask_interval_max(k<<1|1, l, r));
	}
	return ans;
}


int main() {
#ifdef Wang_Zhifeng
	freopen("in.txt", "r", stdin);
#endif
	int t, n, m, a, b, c, d;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		build(1, 1, n);
		while(m--) {
			scanf("%d", &a);
			switch(a) {
				case 0:
					scanf("%d%d%d", &b, &c, &d);
					change_interval(1, b, c, d);
					break;
				case 1:
					scanf("%d%d", &b, &c);
					printf("%d\n", ask_interval_max(1, b, c));
					break;
				case 2:
					scanf("%d%d", &b, &c);
					printf("%lld\n", ask_interval_add(1, b, c));
					break;
			}
		}
	}
	return 0;
}