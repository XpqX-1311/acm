//前置函数
//void ex_gcd(ll a, ll b, ll &x, ll &y, ll &d) {
//    if (!b) { d=a, x=1, y=0; }
//    else {
//        ex_gcd(b, a%b, y, x, d);
//        y-=x*(a/b);
//    }
//}
//
//ll inv(ll t, ll p) {//如果不存在，返回-1
//    ll d, x, y;
//    ex_gcd(t, p, x, y, d);
//    return d==1 ? (x%p+p)%p : -1;
//}


//m1,m2,...,mn互质
//n个方程：x=a[i](mod m[i]) (0<=i<n)
ll china(int n, ll *a, ll *m){
    ll M = 1, ret = 0;
    for(int i = 0; i < n; i ++) M *= m[i];
    for(int i = 0; i < n; i ++){
        ll w = M / m[i];
        ret = (ret + w * inv(w, m[i]) * a[i]) % M;
    }
    return (ret + M) % M;
}


//m1,m2,...,mn不互质
typedef pair<ll, ll> Pll;
Pll linear(ll A[], ll B[], ll M[], int n) {//求解A[i]x = B[i] (mod M[i]),总共n个线性方程组 
    ll x = 0, m = 1;
    for(int i = 0; i < n; i ++) {
        ll a = A[i] * m, b = B[i] - A[i]*x, d = gcd(M[i], a);
        if(b % d != 0)  return Pll(0, -1);//答案不存在，返回-1 
        ll t = b/d * inv(a/d, M[i]/d)%(M[i]/d);
        x = x + m*t;
        m *= M[i]/d;
    }
    x = (x % m + m ) % m;
    return Pll(x, m);//返回的x就是答案，m是最后的lcm值 
}