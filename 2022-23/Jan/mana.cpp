#include <bits/stdc++.h>
using namespace std;

#define sz(v) int(std::size(v))
using i64 = long long;

const i64 INF = 1e18;

struct L {
    i64 m, b;
};
bool operator<(L u, L v) {
    if (u.m == v.m) return u.b < v.b;
    return u.m < v.m;
}
double ix(L u, L v) {
    return (double) (v.b - u.b) / (u.m - v.m);
}
i64 ev(L u, i64 x) {
    return u.m * x + u.b;
}

struct LC {
    vector<L> t;
    void insert(i64 m, i64 b) {
        t.push_back({m, b});
    }
    void build() {
        sort(begin(t), end(t));
        vector<L> tt;
        for (L u : t) {
            while (sz(tt) > 0 && tt.back().m == u.m)
                tt.pop_back();
            while (sz(tt) > 1 && ix(u,tt[sz(tt) - 2]) < ix(tt.back(), tt[sz(tt) - 2]))
                tt.pop_back();
            tt.push_back(u);
        }
        swap(t, tt);
    }
    i64 query(i64 x) {
        if (sz(t) == 1)
            return ev(t[0], x);
        int low = 0, hi = sz(t) - 1;
        while (low < hi) {
            int m = (low + hi) / 2 + 1;
            if (ix(t[m - 1], t[m]) <= x)
                low = m;
            else
                hi = m - 1;
        }
        return ev(t[low], x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<i64> sum(1 << n);
    for (int i = 0; i < n; i++) cin >> sum[1 << i];
    for (int i = 0; i < n; i++) for (int b = 0; b < 1 << n; b++) if (b >> i & 1)
        sum[b] += sum[b ^ (1 << i)];
    vector d(n, vector<i64>(n, INF));
    for (int i = 0; i < n; i++) d[i][i] = 0;
    while (m--) {
        int i, j, w;
        cin >> i >> j >> w, i--, j--;
        d[i][j] = min(d[i][j], (i64) w);
    }
    for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    vector dp(1 << n, vector<i64>(n, INF));
    for (int i = 0; i < n; i++) dp[1 << i][i] = 0;
    for (int b = 0; b < 1 << n; b++) for (int i = 0; i < n; i++) if ((b >> i & 1) && dp[b][i] != INF)
        for (int j = 0; j < n; j++) if (!(b >> j & 1) && d[i][j] != INF)
            dp[b | (1 << j)][j] = min(dp[b | (1 << j)][j], dp[b][i] + d[i][j] * sum[b]);
    vector<LC> ds(n);
    for (int i = 0; i < n; i++) for (int b = 0; b < 1 << n; b++) if (dp[b][i] != INF)
        ds[i].insert(sum[b], -dp[b][i]);
    for (int i = 0; i < n; i++) ds[i].build();
    int q;
    cin >> q;
    while (q--) {
        i64 x;
        int i;
        cin >> x >> i, i--;
        cout << ds[i].query(x) << '\n';
    }
}