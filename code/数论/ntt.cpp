//ntt
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const int N=(1<<18)+5, INF=1e9;
const double PI=acos(-1);
inline int read(){
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}

ll P=1004535809;
ll Pow(ll a, ll b,ll P) {
    ll ans=1;
    for(; b; b>>=1, a=a*a%P)
        if(b&1) ans=ans*a%P;
    return ans;
}
struct NumberTheoreticTransform {
    int n, rev[N];
    ll g;
    void ini(int lim) {
        g=3;
        n=1; int k=0;
        while(n<lim) n<<=1, k++;
        for(int i=0; i<n; i++) rev[i] = (rev[i>>1]>>1) | ((i&1)<<(k-1));
    }
    void dft(ll *a, int flag) {
        for(int i=0; i<n; i++) if(i<rev[i]) swap(a[i], a[rev[i]]);
        for(int l=2; l<=n; l<<=1) {
            int m=l>>1;
            ll wn = Pow(g, flag==1 ? (P-1)/l : P-1-(P-1)/l, P);
            for(ll *p=a; p!=a+n; p+=l) {
                ll w=1;
                for(int k=0; k<m; k++) {
                    ll t = w * p[k+m]%P;
                    p[k+m]=(p[k]-t+P)%P;
                    p[k]=(p[k]+t)%P;
                    w=w*wn%P;
                }
            }
        }
        if(flag==-1) {
            ll inv=Pow(n, P-2, P);
            for(int i=0; i<n; i++) a[i]=a[i]*inv%P;
        }
    }
    void mul(ll *a, ll *b, int m) {
        ini(m);
        dft(a, 1); dft(b, 1);
        for(int i=0; i<n; i++) a[i]=a[i]*b[i];
        dft(a, -1);
    }
}f;

int n1, n2, m, c[N];
ll a[N], b[N];
char s1[N], s2[N];
int main() {
    //freopen("in","r",stdin);
    scanf("%s%s",s1,s2);
    n1=strlen(s1); n2=strlen(s2);
    for(int i=0; i<n1; i++) a[i] = s1[n1-i-1]-'0';
    for(int i=0; i<n2; i++) b[i] = s2[n2-i-1]-'0';
    m=n1+n2-1;
    f.mul(a, b, m);
    for(int i=0; i<m; i++) c[i]=a[i];
    for(int i=0; i<m; i++) c[i+1]+=c[i]/10, c[i]%=10;
    if(c[m]) m++;
    for(int i=m-1; i>=0; i--) printf("%d",c[i]);
}