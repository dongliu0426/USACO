#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<set<int>> g(n);
    for (int h = 0; h < m; h++) {
        int i, j;
        cin >> i >> j, i--, j--;
        if (i > j) swap(i, j);
        g[i].insert(j);
    }
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        ans += g[i].size();
        if (!g[i].empty()) {
            int j = *g[i].begin();
            g[i].erase(j);
            if (g[i].size() > g[j].size()) swap(g[i], g[j]);
            for (int k : g[i]) g[j].insert(k);
            set<int>().swap(g[i]);
        }
    }
    cout << ans - m << '\n';
}