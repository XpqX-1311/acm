#include <set>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <cmath>
#include <cstdio>
#include <bitset>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define mid ((l + r) >> 1)
#define pii pair<int, int>
#define piii pair<pii, pii>
#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r
#define debug cout << "DEBUG" << endl;
#define isdigit(x) ((x) >= '0' && (x) <= '9')
#define rep(i, n) for(int i = 0; i < (n); ++i)
#define fast ios::sync_with_stdio(false);cin.tie(NULL);


//
typedef long long LL;
typedef unsigned long long ULL;
const ULL seed = 131;
const LL MOD = 23333;
const double eps = 1e-8;
const int maxn = 1e5 + 7;
const int maxm = 3e6 + 7;
const int inf = 0x3f3f3f3f;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const double pi = 3.1415926535898;

char str[maxn];
int cnt1 = 0, cnt2 = 0;

int main() {
    scanf("%s", str);
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == '(') cnt1++;
        if (str[i] == ')') cnt2++;
        if (cnt2 > cnt1) break;
    }
    if (cnt2 > cnt1) return printf("%d\n", cnt2), 0;
    cnt1 = cnt2 = 0;
    for (int i = strlen(str) - 1; i >= 0; --i) {
        if (str[i] == '(') cnt1++;
        if (str[i] == ')') cnt2++;
        if (cnt1 > cnt2) break;
    }
    if (cnt1 > cnt2) return printf("%d\n", cnt1), 0;
}



















