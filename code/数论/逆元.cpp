//1
ll pow_mod(ll a, ll b, ll p){//a的b次方求余p
    ll ret = 1;
    while(b){
        if(b & 1) ret = (ret * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return ret;
}
ll Fermat(ll a, ll p){//费马求a关于b的逆元
    return pow_mod(a, p-2, p);
}



//2
#include<cstdio>
typedef long long ll;
void ex_gcd(ll a, ll b, ll &x, ll &y, ll &d){
    if (!b) {d = a, x = 1, y = 0;}
    else{
        ex_gcd(b, a % b, y, x, d);
        y -= x * (a / b);
    }
}
ll inv(ll t, ll p){//如果不存在，返回-1
    ll d, x, y;
    ex_gcd(t, p, x, y, d);
    return d == 1 ? (x % p + p) % p : -1;
}
int main(){
    ll a, p;
    while(~scanf("%lld%lld", &a, &p)){
        printf("%lld\n", inv(a, p));
    }
}


//3
//当p是个质数的时候有
//inv(a) = (p - p / a) * inv(p % a) % p
//o（n）
#include<cstdio>
const int N = 200000 + 5;
const int MOD = (int)1e9 + 7;
int inv[N];
int init(){
    inv[1] = 1;
    for(int i = 2; i < N; i ++){
        inv[i] = (MOD - MOD / i) * 1ll * inv[MOD % i] % MOD;
    }
}
int main(){
    init();
}

