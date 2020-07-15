//C(n, m) % p  =  C(n / p, m / p) * C(n%p, m%p) % p
//对于C(n / p, m / p)，如果n / p 还是很大，可以递归下去

ll Lucas(ll n, ll m, int p) {
    return m ? Lucas(n/p, m/p, p)*comb(n%p, m%p, p)%p : 1;
}