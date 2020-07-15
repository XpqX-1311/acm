//适用于正整数
template<class T>
inline void scan_d(T &ret) {
    char c;
    ret = 0;
    while((c = getchar()) < '0' || c > '9');
    while(c >= '0' && c <= '9') {
        ret = ret*10+(c-'0'), c = getchar();
    }
}

//适用于正负整数
template<class T>
inline bool scan_d(T &ret) {
    char c;
    int sgn;
    if(c = getchar(), c==EOF) {
        return 0; //EOF
    }
    while(c!='-' && (c < '0' || c > '9')) {
        c = getchar();
    }
    sgn = (c=='-') ? -1 : 1;
    ret = (c=='-') ? 0 : (c-'0');
    while(c = getchar(), c >= '0' && c <= '9') {
        ret = ret*10+(c-'0');
    }
    ret *= sgn;
    return 1;
}

template<class T>
inline void print_d(T x) {
    if(x > 9) {
        print_d(x/10);
    }
    putchar(x%10+'0');
}

//仅适合纯数字输入输出
int Scan() {   //  输入外挂
    int res = 0, flag = 0;
    char ch;
    if((ch = getchar())=='-') {
        flag = 1;
    } else if(ch >= '0' && ch <= '9') {
        res = ch-'0';
    }
    while((ch = getchar()) >= '0' && ch <= '9') {
        res = res*10+(ch-'0');
    }
    return flag ? -res : res;
}

void Out(int a) {   //  输出外挂
    if(a < 0) {
        putchar('-');
        a = -a;
    }
    if(a >= 10) {
        Out(a/10);
    }
    putchar(a%10+'0');
}

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        n = Scan();
        Out(n);
        printf("\n");
    }
    return 0;
}

//适用于正负数(int,long long,float,double)
template<class T>
bool scan_d(T &ret) {
    char c;
    int sgn;
    T bit = 0.1;
    if(c = getchar(), c==EOF) {
        return 0;
    }
    while(c! = '-' && c!='.' && (c < '0' || c > '9')){
        c = getchar();
    }
    sgn = (c=='-') ? -1 : 1;
    ret = (c=='-') ? 0 : (c-'0');
    while(c = getchar(), c >= '0' && c <= '9') {
        ret = ret*10+(c-'0');
    }
    if(c==' ' || c=='\n') {
        ret *= sgn;
        return 1;
    }
    while(c = getchar(), c >= '0' && c <= '9') {
        ret += (c-'0')*bit, bit /= 10;
    }
    ret *= sgn;
    return 1;
}

template<class T>
inline void print_d(int x) {
    if(x > 9) {
        print_d(x/10);
    }
    putchar(x%10+'0');
}

//更加高效的输入输出外挂
struct FastIO {
    static const int S = 100<<1;

    int wpos;
    char wbuf[S];

    FastIO() : wpos(0) {}

    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;

        if(pos==len) {
            pos = 0;
            len = (int) fread(buf, 1, S, stdin);
        }
        if(pos==len) {
            return -1;
        }

        return buf[pos++];
    }

    inline int xint() {
        int s = 1, c = xchar(), x = 0;
        while(c <= 32) {
            c = xchar();
        }
        if(c=='-') {
            s = -1;
            c = xchar();
        }
        for(; '0' <= c && c <= '9'; c = xchar()) {
            x = x*10+c-'0';
        }

        return x*s;
    }

    ~FastIO() {
        if(wpos) {
            fwrite(wbuf, 1, wpos, stdout);
            wpos = 0;
        }
    }
} io;

//strtok和sscanf结合输入
/*
 *  空格作为分隔输入,读取一行的整数
 */
gets(buf);

int v;
char *p = strtok(but, " ");
while (p){
    sscanf(p,"%d", &v);
    p = strtok(NULL, " ");
}