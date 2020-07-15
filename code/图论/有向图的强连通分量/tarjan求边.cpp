/// hdu4738
/// http://acm.hdu.edu.cn/showproblem.php?pid=4738

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <set>
#include <list>

using namespace std;

#define N 1005

int n, m;
vector<pair<int, int>> edge[N];
int mp[N][N];
int DFN[N];
int low[N];
int cnt;
bool vis[N];
int ans;

void init() {
    for (int i = 0; i < N; ++i) {
        edge[i].clear();
        vis[i] = false;
        DFN[i] = 0;
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            mp[i][j] = 0;
        }
    }
    cnt = 1;
    ans = 0x3f3f3f3f;
}

void tarjan(int from, int u) {
    low[u] = DFN[u] = cnt++;
    vis[u] = true;
    for (int v = 0, l = edge[u].size(); v < l; ++v) {
        if (DFN[edge[u][v].first] == 0) {
            tarjan(u, edge[u][v].first);
            low[u] = min(low[u], low[edge[u][v].first]);
            if (DFN[u] < low[edge[u][v].first]) {
                if (mp[u][edge[u][v].first] == 1) {
                    ans = min(ans, edge[u][v].second);
                }
            }
        } else if (from != edge[u][v].first) {
            low[u] = min(low[u], DFN[edge[u][v].first]);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    int a, b, c;
    while (scanf("%d%d", &n, &m)) {
        if (n == 0 && m == 0) {
            break;
        }
        init();
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            edge[a].push_back(make_pair(b, c));
            edge[b].push_back(make_pair(a, c));
            mp[a][b]++;
            mp[b][a]++;
        }
        if (!edge[1].empty())
            tarjan(0, 1);
        if(ans==0)
            ans=1;
        bool type = false;
        for (int i = 1; i <= n; ++i) {
            if (!vis[i]) {
                type = true;
                break;
            }
        }
        if (type) {
            ans = 0;
        }
        if (ans == 0x3f3f3f3f) {
            ans = -1;
        }
        printf("%d\n", ans);
    }
    return 0;
}