//单个
bool prime(int x){//判断x是不是质数，是返回true，不是返回false
    if(x <= 1) return false;
    for(int i = 2; i < x; i ++){
        if(x % i == 0) return false;
    }
    return true;
}

//埃氏筛
const int N = 100000 + 5;
bool prime[N];
void init(){
    for(int i = 2; i < N; i ++) prime[i] = true;
    for(int i = 2; i*i < N; i ++){//判断改成i*i<N
        if(prime[i]){
            for(int j = i*i; j < N; j += i){//从i*i开始就可以了
                prime[j] = false;
            }
        }
    }
}

//线性筛
const int N = 100000 + 5;
bool prime[N];//prime[i]表示i是不是质数
int p[N], tot;//p[N]用来存质数
void init(){
    for(int i = 2; i < N; i ++) prime[i] = true;//初始化为质数
    for(int i = 2; i < N; i++){
        if(prime[i]) p[tot ++] = i;//把质数存起来
        for(int j = 0; j < tot && i * p[j] < N; j++){
            prime[i * p[j]] = false;
            if(i % p[j] == 0) break;//保证每个合数被它最小的质因数筛去
        }
    }
}

//预处理每个数的所有质因数
const int N = 100000 + 5;
vector<int > prime_factor[N];
void init(){
    for(int i = 2; i < N; i ++){
        if(prime_factor[i].size() == 0){//如果i是质数
            for(int j = i; j < N; j += i){
                prime_factor[j].push_back(i);
            }
        }
    }
}

//预处理每个数的所有因数
const int N = 100000 + 5;
vector<int > factor[N];
void init(){
    for(int i = 2; i < N; i ++){
        for(int j = i; j < N; j += i){
            factor[j].push_back(i);
        }
    }
}

//预处理每个数的质因数分解
const int N = 100000 + 5;
vector<int > prime_factor[N];
void init(){
    int temp;
    for(int i = 2; i < N; i ++){
        if(prime_factor[i].size() == 0){
            for(int j = i; j < N; j += i){
                temp = j;
                while(temp % i == 0){
                    prime_factor[j].push_back(i);
                    temp /= i;
                }
            }
        }
    }
}