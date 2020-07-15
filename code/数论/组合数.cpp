//求组合数
//1
//O(n^2)
#include<cstdio>
const int N = 2000 + 5;
const int MOD = (int)1e9 + 7;
int comb[N][N];//comb[n][m]就是C(n,m)
void init(){
    for(int i = 0; i < N; i ++){
        comb[i][0] = comb[i][i] = 1;
        for(int j = 1; j < i; j ++){
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
            comb[i][j] %= MOD;
        }
    }
}
int main(){
    init();
}

//2
//O(n)
#include<cstdio>
const int N = 200000 + 5;
const int MOD = (int)1e9 + 7;
int F[N], Finv[N], inv[N];//F是阶乘，Finv是逆元的阶乘
void init(){
    inv[1] = 1;
    for(int i = 2; i < N; i ++){
        inv[i] = (MOD - MOD / i) * 1ll * inv[MOD % i] % MOD;
    }
    F[0] = Finv[0] = 1;
    for(int i = 1; i < N; i ++){
        F[i] = F[i-1] * 1ll * i % MOD;
        Finv[i] = Finv[i-1] * 1ll * inv[i] % MOD;
    }
}
int comb(int n, int m){//comb(n, m)就是C(n, m)
    if(m < 0 || m > n) return 0;
    return F[n] * 1ll * Finv[n - m] % MOD * Finv[m] % MOD;
}
int main(){
    init();
}