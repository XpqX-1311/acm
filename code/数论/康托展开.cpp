void cantor(int s[], LL num, int k){//康托展开，把一个数字num展开成一个数组s，k是数组长度
    int t;
    bool h[k];//0到k-1，表示是否出现过 
    memset(h, 0, sizeof(h));
    for(int i = 0; i < k; i ++){
        t = num / fac[k-i-1];
        num = num % fac[k-i-1];
        for(int j = 0, pos = 0; ; j ++, pos ++){
            if(h[pos]) j --;
            if(j == t){
                h[pos] = true;
                s[i] = pos + 1;
                break;
            }
        }
    }
}
void inv_cantor(int s[], LL &num, int k){//康托逆展开，把一个数组s换算成一个数字num 
    int cnt;
    num = 0;
    for(int i = 0; i < k; i ++){
        cnt = 0;
        for(int j = i + 1; j < k; j ++){
            if(s[i] > s[j]) cnt ++;//判断几个数小于它
        }
        num += fac[k-i-1] * cnt;
    }
}