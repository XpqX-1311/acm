//快速幂
ll pow_mod(ll a, ll b, ll p){//a的b次方求余p
    ll ret = 1;
    while(b){
        if(b & 1) ret = (ret * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return ret;
}


//快速乘
ll mul(ll a, ll b, ll p){//快速乘，计算a*b%p
    ll ret = 0;
    while(b){
        if(b & 1) ret = (ret + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return ret;
}