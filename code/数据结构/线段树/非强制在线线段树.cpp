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
#define N 30005
#define M 100005

struct node {
	int l, r;
	ll val;
} tree[N<<2+10];
int f[N];//the pos which last numb's val equal the numb's val
map<int, int> mp;//hash from val to f
int val[N];// the val in array

void build(int k, int l, int r) {
	tree[k].l=l;
	tree[k].r=r;
	if(l==r) {
		if(f[l]==0)
			tree[k].val=val[l];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1, l, mid);
	build(k<<1|1, mid+1, r);
	tree[k].val=tree[k<<1].val+tree[k<<1|1].val;
}

void change_point(int k, int pos, int val) {
	if(tree[k].l==tree[k].r) {
		tree[k].val=val;
		return;
	}
	int mid=(tree[k].l+tree[k].r)>>1;
	if(pos<=mid)
		change_point(k<<1, pos, val);
	else
		change_point(k<<1|1, pos, val);
	tree[k].val=tree[k<<1].val+tree[k<<1|1].val;
}

ll find_interval(int k, int l, int r) {
	if(tree[k].l>=l&&tree[k].r<=r) {
		return tree[k].val;
	}
	int mid=(tree[k].l+tree[k].r)>>1;
	ll ans=0;
	if(l<=mid) {
		ans+=find_interval(k<<1, l, r);
	}
	if(r>mid) {
		ans+=find_interval(k<<1|1, l, r);
	}
	return ans;
}

struct interval {
	int l;
	int r;
	int pos=0;
};
interval query[M];
ll ans[M];

bool cmp(interval a, interval b) {
	return a.r<b.r;
}


int main() {
	std::ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
#endif
	int t, n, m,pos;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);

		pos=1;
		mp.clear();
		for(int i=1; i<=n; ++i) {
			scanf("%d", &val[i]);
			f[i]=mp[val[i]];
			mp[val[i]]=i;
		}
		build(1, 1, n);

		scanf("%d", &m);
		for(int i=1; i<=m; ++i) {
			scanf("%d%d", &query[i].l, &query[i].r);
			query[i].pos=i;
		}
		sort(query+1, query+1+m, cmp);

		for(int i=1; i<=m; ++i) {
			while(query[i].r>=pos) {
				if(f[pos]!=0){
					change_point(1, f[pos], 0);
					change_point(1, pos, val[pos]);
				}
				pos++;
			}
			ans[query[i].pos]=find_interval(1, query[i].l, query[i].r);
		}
		for(int i=1; i<=m; ++i) {
			printf("%lld\n", ans[i]);
		}
	}
	return 0;
}