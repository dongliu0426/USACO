#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

const int N = 1e5, N_ = 1 << 17, MOD = 1e9 + 7, v2 = (MOD + 1) / 2;

int n, k;
i64 qd[N], qb[N], x[N + 1], num[N_ * 2], ext[N_ * 2], ans[N_ * 2];

i64 sum(i64 l, i64 r) {
    return (r - l + 1) % MOD * ((l + r) % MOD) % MOD * v2 % MOD;
}
i64 shoot(int k, int l, int r, i64 v) {
    if (l + 1 == r) return sum(x[l], x[l] + num[k] + v - 1);
    int m = (l + r) / 2;
    return num[k * 2] + v < x[m] - x[l]
        ? shoot(k * 2, l, m, v) + ans[k] - ans[k * 2]
        : shoot(k * 2 + 1, m, r, v + ext[k * 2] + num[k * 2] - (x[m] - x[l])) + sum(x[l], x[m] - 1);
}
void pull(int k, int l, int r) {
    int m = (l + r) / 2;
    if (ext[k * 2] + num[k * 2 + 1] >= x[r] - x[m]) {
        num[k] = num[k * 2] + x[r] - x[m];
        ext[k] = ext[k * 2] + num[k * 2 + 1] + ext[k * 2 + 1] - (x[r] - x[m]);
        ans[k] = ans[k * 2] + sum(x[m], x[r] - 1);
    } else {
        num[k] = num[k * 2] + num[k * 2 + 1] + ext[k * 2];
        ext[k] = ext[k * 2 + 1];
        ans[k] = ans[k * 2] + shoot(k * 2 + 1, m, r, ext[k * 2]);
    }
    ans[k] = (ans[k] % MOD + MOD) % MOD;
}
void upd(int k, int l, int r, int i, i64 v) {
    if (l + 1 == r) {
        num[k] = min(v, x[r] - x[l]);
        ext[k] = v - num[k];
        ans[k] = sum(x[l], x[l] + num[k] - 1);
    } else {
        int m = (l + r) / 2;
        i < m ? upd(k * 2, l, m, i, v) : upd(k * 2 + 1, m, r, i, v);
        pull(k, l, r);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> qd[i] >> qb[i], x[i] = qd[i];
    sort(x, x + n);
    k = unique(x, x + n) - x;
    x[k] = 1e18;
    for (int i = 0; i < n; i++) {
        upd(1, 0, k, lower_bound(x, x + k, qd[i]) - x, qb[i]);
        cout << ans[1] << '\n';
    }
}