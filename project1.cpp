#include <bits/stdc++.h>
#include <unistd.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define rep(i,j,n) for(i=j;i<n;i++)
#define repi(i,j,n) for(i=j;i>n;i--)
#define inf 1e18
#define M 1000000007
#define pie 3.141592653589793238
#define ll long long
#define ld long double
#define vll vector<ll>
#define pll pair<ll,ll>
#define vpll vector<pll>
#define pb push_back
#define F first
#define S second
#define UQ(x) (x).resize(distance((x).begin(),unique(x.begin(),x.end())))

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set=tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
mt19937_64 rnd64(chrono::high_resolution_clock::now().time_since_epoch().count());

ll power(ll a,ll m,ll mod){
    ll ans=1;
    while(m){
        if(m%2){
            ans*=a;
            ans%=(mod);
        }
        a=(a*a)%(mod);
        m>>=1;
    }
    return ans;
}


void init(ll* a,ll n,ll val){
    for(ll i=0;i<n;i++)
        a[i]=val;
}

const ll N  = 500100;
ll n;

ll a[N],st[4*N][2],lf[4*N][2],ri[4*N][2],lazy[4*N],e[4*N],b[4*N];

void lazyp(ll node){
    if(lazy[node]) {
        lazy[2*node]^=lazy[node];
        lazy[2*node+1]^=lazy[node];
        swap(st[2*node][0],st[2*node][1]);
        swap(lf[2*node][0],lf[2*node][1]);
        swap(ri[2*node][0],ri[2*node][1]);
        swap(st[2*node+1][0],st[2*node+1][1]);
        swap(lf[2*node+1][0],lf[2*node+1][1]);
        swap(ri[2*node+1][0],ri[2*node+1][1]);
        b[2*node]^=1;
        b[2*node+1]^=1;
        e[2*node]^=1;
        e[2*node+1]^=1;
        lazy[node]=0;
    }
}

void upd(ll node,ll mid,ll l,ll r){
    b[node]=b[2*node];
    e[node]=e[2*node+1];
    ll a1=e[2*node],a2=b[2*node+1];
    st[node][0]=max({st[2*node][0],st[2*node+1][0],ri[2*node][0],lf[2*node+1][0]});
    if(a1<=a2) st[node][0]=max(st[node][0],ri[2*node][0]+lf[2*node+1][0]);
    st[node][1]=max({st[2*node][1],st[2*node+1][1],ri[2*node][1],lf[2*node+1][1]});
    if(a1>=a2) st[node][1]=max(st[node][1],ri[2*node][1]+lf[2*node+1][1]);

    lf[node][0]=lf[2*node][0];
    if(lf[2*node][0]==mid-l+1&&a1<=a2) lf[node][0]+=lf[2*node+1][0];
    lf[node][1]=lf[2*node][1];
    if(lf[2*node][1]==mid-l+1&&a1>=a2) lf[node][1]+=lf[2*node+1][1];

    ri[node][0]=ri[2*node+1][0];
    if(ri[2*node+1][0]==r-mid&&a1<=a2) ri[node][0]+=ri[2*node][0];
    ri[node][1]=ri[2*node+1][1];
    if(ri[2*node+1][1]==r-mid&&a1>=a2) ri[node][1]+=ri[2*node][1];
}

void build(ll node,ll l,ll r){
    ll i;
    if(l==r){
        rep(i,0,2)st[node][i]=1,lf[node][i]=1,ri[node][i]=1;
        b[node]=a[l],e[node]=a[l];
        return;
    }
    ll mid=(l+r)/2;
    build(2*node,l,mid);
    build(2*node+1,mid+1,r);
    upd(node,mid,l,r);
}

pair<ll,pll > query(ll node,ll l,ll r,ll sb,ll se){
    if(sb>r||se<l) return {0,{0,0}};
    if(sb>=l&&se<=r){
        swap(st[node][0],st[node][1]);
        swap(lf[node][0],lf[node][1]);
        swap(ri[node][0],ri[node][1]);
        lazy[node]^=1;
        b[node]^=1;
        e[node]^=1;
        pair<ll,pll > p;
        p.F=st[node][0];
        p.S.F=lf[node][0];
        p.S.S=ri[node][0];
        return p;
    }
    lazyp(node);
    ll mid=(sb+se)/2;

    pair<ll,pll> left=query(2*node,l,r,sb,mid), right=query(2*node+1,l,r,mid+1,se);
    upd(node,mid,sb,se);
    if(r<=mid)left;
    if(l>mid)right;
    pair<ll,pll> p;

    ll a1=e[2*node],a2=b[2*node+1];

    p.F=max({left.F,right.F,left.S.S,right.S.F});
    if(a1<=a2) p.F = max(p.F,left.S.S+right.S.F);

    p.S.F=left.S.F;
    if(left.S.F==mid-sb+1&&a1<=a2) p.S.F += right.S.F;

    p.S.S=right.S.S;
    if(right.S.S==se-mid&&a1<=a2) p.S.S += left.S.S;

    return p;
}


void solve(){
    ll i,j,_;
    ll l,r;
    cin>>l>>r;
    --l,--r;
    pair<ll,pll> p = query(1,l,r,0,n-1);
    cout<<max({p.F,p.S.F,p.S.S})<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T=1,i;
    cin>>n>>T;
    char ch;
    rep(i,0,n){
        cin>>ch;
        a[i]=(ch=='<');
    }
    build(1,0,n-1);
    while(T--){
        solve();
    }
    return 0;
}

?