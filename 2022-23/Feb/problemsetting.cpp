#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MOD = 1e9 + 7;

int expo(int a, int k) {
    int p = 1;
    while (k > 0) {
        if (k & 1) p = (i64) p * a % MOD;
        a = (i64) a * a % MOD, k >>= 1;
    }
    return p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> x(n);
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) if (s[j] == 'H')
            x[j] |= 1 << i;
    }
    vector<int> cnt(1 << m);
    for (int b : x) cnt[b]++;
    vector<int> fac(n + 1), ifac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = (i64) fac[i - 1] * i % MOD;
    ifac[n] = expo(fac[n], MOD - 2);
    for (int i = n; i >= 1; i--) ifac[i - 1] = (i64) ifac[i] * i % MOD;
    vector f(1 << m, vector<int>(m));
    int ans = 0;
    for (int b = 0; b < 1 << m; b++) {
        int dp = 1;
        for (int i = m - 1; i >= 0; i--) if (b >> i & 1)
            dp = (dp + f[b ^ (1 << i)][i]) % MOD;
        int coef = 0;
        for (int i = 0; i < cnt[b]; i++) coef = (coef + ifac[i]) % MOD;
        coef = (i64) coef * fac[cnt[b]] % MOD;
        dp = (i64) dp * coef % MOD;
        ans = (ans + dp) % MOD;
        f[b][0] = dp;
        for (int i = 0; i < m - 1; i++) {
            f[b][i + 1] = f[b][i];
            if (b >> i & 1) f[b][i + 1] = (f[b][i + 1] + f[b ^ (1 << i)][i]) % MOD;
        }
    }
    cout << ans << '\n';
}