/****************************
 * Name   :哭泣的阿木木
 * Time   :3-3-2019 20:51
 * Author :大哥
 * Type   :线段树
 * 版权所有_翻版不管
 ****************************
 */
#include <bits/stdc++.h>
using namespace std;
long long n,q,a,b,m,x,y;
long long ans;
char ch[10];
struct node{
	long long l,r;
	long long w,f;
}tree[1000000*4+5];
void build (long long k,long long ll,long long rr){
	tree[k].l=ll,tree[k].r=rr;
	if(tree[k].l==tree[k].r){
		scanf("%lld",&tree[k].w);
		return;
	}
	long long m=(ll+rr)/2;
	build(k*2,ll,m);
	build(k*2+1,m+1,rr);
	tree[k].w=tree[k*2].w+tree[k*2+1].w;
}
void down(long long k){
	tree[k*2].f+=tree[k].f;
	tree[k*2+1].f+=tree[k].f ;
	tree[k*2].w+=tree[k].f*(tree[k*2].r-tree[k*2].l+1);
	tree[k*2+1].w+=tree[k].f*(tree[k*2+1].r-tree[k*2+1].l+1);
	tree[k].f=0;
}
void change_point(long long k){//q3
	if(tree[k].l==tree[k].r){
		tree[k].w=y;
		return;
	}
	if(tree[k].f)down(k);
	long long m=(tree[k].l+tree[k].r)/2;
	if(x<=m)change_point(k*2);
	else change_point(k*2+1);
	tree[k].w=tree[k*2].w+tree[k*2+1].w;
}
void ask_interval(long long k){//q4
	if(tree[k].l>=a&&tree[k].r<=b){
		ans+=tree[k].w;
		return;
	}
	if(tree[k].f)down(k);
	long long m=(tree[k].l+tree[k].r)/2;
	if(a<=m)ask_interval(k*2);
	if(b>m) ask_interval(k*2+1);
}
void change_interval(long long k){//q1+q2
	if(tree[k].l>=a&&tree[k].r<=b){
		tree[k].w+=(tree[k].r-tree[k].l+1)*y;
		tree[k].f+=y;
		return;
	}
	if(tree[k].f)down(k);
	long long m=(tree[k].l+tree[k].r)/2;
	if(a<=m)change_interval(k*2);
	if(b>m) change_interval(k*2+1);
	tree[k].w=tree[k*2].w+tree[k*2+1].w;
}


int main(){
	scanf("%lld%lld",&n,&q);
	build(1,1,n);
	while(q--){
		scanf("%s",ch);
		switch(ch[1]){
			case '1':
				scanf("%lld%lld%lld",&a,&b,&y);
				change_interval(1);
				break;
			case '2':
				scanf("%lld%lld%lld",&a,&b,&y);
				y=-y;
				change_interval(1);
				break;
			case '3':
				scanf("%lld%lld",&x,&y);
				change_point(1);
				break;
			case '4':
				scanf("%lld%lld",&a,&b);
				ans=0;
				ask_interval(1);
				printf("%lld\n",ans);
				break;
		}
	}
	return 0;
}
