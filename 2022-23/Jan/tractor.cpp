#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using pii = pair<int, int>;

const int N = 2e5, L = 18;

int n, q;
string s;
pii seg[N];
int jr[N], jl[N];
int br[L][N], bl[L][N]; i64 sr[L][N], sl[L][N];
int pf[N + 1];

int qry_dis(int i, int j) {
    int d = 0;
    for (int l = L - 1; l >= 0; l--) if (br[l][i] < j) {
        d += 1 << l;
        i = br[l][i];
    }
    return d + 1;
}

i64 qry_r(int i, int j) {
    i64 s = 0;
    for (int l = L - 1; l >= 0; l--) if (br[l][i] < j) {
        s += sr[l][i];
        i = br[l][i];
    }
    return s;
}
i64 qry_l(int i, int j) {
    i64 s = 0;
    for (int l = L - 1; l >= 0; l--) if (bl[l][j] > i) {
        s += sl[l][j];
        j = bl[l][j];
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    cin >> s;
    for (int i = 0, iL = 0, iR = 0; i < n * 2; i++) {
        if (s[i] == 'L') {
            seg[iL++] = {i, -1};
        } else {
            seg[iR++].second = i;
        }
    }
    cin >> s;
    for (int i = 0; i < n; i++) pf[i + 1] = pf[i] + s[i] - '0';
    {
        int p = -1;
        for (int i = 0; i < n; i++) {
            while (p + 1 < n && seg[p + 1].first < seg[i].second) p++;
            jr[i] = p;
        }
    }
    {
        int p = n;
        for (int i = n - 1; i >= 0; i--) {
            while (p > 0 && seg[p - 1].second > seg[i].first) p--;
            jl[i] = p;
        }
    }
    for (int i = 0; i < n; i++) {
        br[0][i] = jr[i];
        sr[0][i] = pf[jr[i] + 1];
        bl[0][i] = jl[i];
        sl[0][i] = pf[jl[i]];
    }
    for (int l = 1; l < L; l++) for (int i = 0; i < n; i++) {
        br[l][i] = br[l - 1][br[l - 1][i]];
        sr[l][i] = sr[l - 1][i] + sr[l - 1][br[l - 1][i]];
        bl[l][i] = bl[l - 1][bl[l - 1][i]];
        sl[l][i] = sl[l - 1][i] + sl[l - 1][bl[l - 1][i]];
    }
    while (q--) {
        int i, j;
        cin >> i >> j, i--, j--;
        cout << qry_dis(i, j) << ' ' << (s[i] == '1') + (s[j] == '1') + qry_r(i, j) - qry_l(i, j) << '\n';
    }
}