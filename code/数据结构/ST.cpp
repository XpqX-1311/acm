//基本思想:f[i][j]代表i起点,2^j长度的区间最值
//查询时[f,t]区间存在一个数k保证2^k<=len且2^(k+1)>len
//则区间最值就是 max(f[l][k],f[r-(1<<k)+1][k]) 了
// 这种叠加区间的思维很有用处

void preST(int len) {
    for(int i = 1; i <= len; i++) f[i][0] = i;
    int m = log(len)/log(2)+1;
    for(int j = 1; j < m; j++)
        for(int i = 1; i <= (len-(1<<j)+1); i++)
            f[i][j] = max(f[i][j-1], f[i+(1<<(j-1))][j-1]);
//[i,i+2^j-1]最大值即是 i~i+2^(j-1)和 i+2^(j-1)~i+2^(j-1)+2^(j-1) 这两半区间的较大值
}

int queryST(int l, int r) {
    int k = log(r-l+1)/log(2); //保证k满足 2^k<r+l-1<=2^(k+1)
    return max(f[l][k], f[r-(1<<k)+1][k]);
}