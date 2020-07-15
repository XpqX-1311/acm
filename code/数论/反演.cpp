//二项式反演
//f(n)=i从零到n C(n,i)g(i) 求和
//g(n)=i从零到n (-1)^(n-i)C(n,i)f(i) 求和

//莫比乌斯反演
//f(n)= d是n的因子 g(d) 求和
//g(n)= d是n的因子 μ(d)f(n/d) 求和

//μ(x)是莫比乌斯函数，它是这样计算的
//μ(1) = 1
//x = p1 * p2 * p3 ……*pk（x由k个不同的质数组成）则μ(x) = (-1)^k
//其他情况，μ (x) = 0
//   （1）对任意正整数n有
//https://images.cnblogs.com/cnblogs_com/linyujun/787954/o_20140416161656796.png
//   （2）对任意正整数n有
//https://images.cnblogs.com/cnblogs_com/linyujun/787954/o_20140416161656796.png


//求μ函数
#include<cstdio>
const int N = 1e6 + 5;
int mu[N], vis[N], prime[N];
int tot;//用来记录prime的个数
void init(){
    mu[1] = 1;
    for(int i = 2; i < N; i ++){
        if(!vis[i]){
            prime[tot ++] = i;
            mu[i] = -1;
        }
        for(int j = 0; j < tot && i * prime[j] < N; j ++){
            vis[i * prime[j]] = 1;
            if(i % prime[j]) mu[i * prime[j]] = -mu[i];
            else{
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
}
int main(){
    init();
}


//莫比乌斯的两种表述
//https://images.cnblogs.com/cnblogs_com/linyujun/787954/o_20140417200055140.png
//莫比乌斯第一种描述，一般是这种
//https://images.cnblogs.com/cnblogs_com/linyujun/787954/o_20140417200609375.png
//莫比乌斯第二种描述，这种也可以而且有些题这种更好