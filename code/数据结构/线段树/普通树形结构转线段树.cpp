/// Apple Tree
/// http://poj.org/problem?id=3321
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
#define ld long double
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f

#define exp 1e-8
#define MOD 1000000007
#define N 100007

int f[N];
int n_sum[N];
int n_next[N];
bool type[N];
bool vis[N];
//vector<int> edge[N];
vector<vector<int> > edge(N);
int pos_numb=1;

void build(int pos_last) {
	vis[pos_last]=true;
	int n_pos=pos_numb;
	f[pos_last]=pos_numb++;
	for(int i=0, l=edge[pos_last].size(); i<l; ++i) {
		if(!vis[edge[pos_last][i]])
			build(edge[pos_last][i]);
	}
	n_next[n_pos]=pos_numb-1;
	int sum=n_pos&(-n_pos);
	n_sum[n_pos]=sum;
}

void change(int pos, int n) {
	int n_pos=f[pos];
	int val;
	if(type[pos]) {
		val=1;
	} else {
		val=-1;
	}
	type[pos]=!type[pos];
	while(n_pos<=n) {
		n_sum[n_pos]+=val;
		n_pos=n_pos+(n_pos&(-n_pos));
	}
}

int getsum(int x) {
	int ans=0;
	for(int i=x; i; i-=i&(-i))
		ans+=n_sum[i];
	return ans;
}

int count(int pos) {
	int n_pos=f[pos];
	return getsum(n_next[n_pos])-getsum(n_pos-1);
}

int main() {
	std::ios::sync_with_stdio(false);
#ifdef Wang_Zhifeng
	freopen("in.txt", "r", stdin);
#endif
	int n, m, a, b;
	char s[5];
	scanf("%d", &n);
	for(int i=1; i<n; ++i) {
		scanf("%d%d", &a, &b);
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	build(1);
	scanf("%d", &m);
	while(m--) {
		scanf("%s%d", s, &a);
		if(s[0]=='Q') {
			printf("%d\n", count(a));
		} else {
			change(a, n);
		}
	}
	return 0;
}