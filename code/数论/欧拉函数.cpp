//欧拉函数
//1
//O（√n）
int phi(int x){
    int ans = x;
    for(int i = 2; i*i <= x; i++){
        if(x % i == 0){
            ans = ans / i * (i-1);
            while(x % i == 0) x /= i;
        }
    }
    if(x > 1) ans = ans / x * (x-1);
    return ans;
}


//2
//O(n)
#include<cstdio>
const int N = 100000 + 5;
int phi[N];
void Euler(){
    phi[1] = 1;
    for(int i = 2; i < N; i ++){
        if(!phi[i]){
            for(int j = i; j < N; j += i){
                if(!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i-1);
            }
        }
    }
}
int main(){
    Euler();
}

//3 比2快
//O(n)
#include<cstdio>
using namespace std;
const int N = 1e6+10 ;
int phi[N], prime[N];
int tot;//tot计数，表示prime[N]中有多少质数
void Euler(){
    phi[1] = 1;
    for(int i = 2; i < N; i ++){
        if(!phi[i]){
            phi[i] = i-1;
            prime[tot ++] = i;
        }
        for(int j = 0; j < tot && 1ll*i*prime[j] < N; j ++){
            if(i % prime[j]) phi[i * prime[j]] = phi[i] * (prime[j]-1);
            else{
                phi[i * prime[j] ] = phi[i] * prime[j];
                break;
            }
        }
    }
}

int main(){
    Euler();
}


//性质
//p为质数
//1. phi(p)=p-1   因为质数p除了1以外的因数只有p，故1至p的整数只有p与p不互质
//2. 如果i mod p = 0, 那么 phi(i * p)=phi(i) * p
//3.若i mod p ≠0,  那么 phi( i * p )=phi(i) * ( p-1 )



//a^b % p  =  (a%p)^(b%φ(p)) % p=(a%p)^(φ(p)+b%φ(p)) % p
