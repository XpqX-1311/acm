ll gcd(ll a, ll b) {
    return b ? gcd(b, a%b) : a;
}

ll lcm(ll a, ll b) {
    return a*b/gcd(a, b);
}


void ex_gcd(ll a, ll b, ll &x, ll &y, ll &d){
    if (!b) {d = a, x = 1, y = 0;}
    else{
        ex_gcd(b, a % b, y, x, d);
        y -= x * (a / b);
    }
}
//int main(){
//    ll a, b, d, x, y;
//    while(~scanf("%lld%lld", &a, &b)){
//        ex_gcd(a, b, x, y, d);
//        printf("%lld*a + %lld*b = %lld\n", x, y, d);
//    }
//}