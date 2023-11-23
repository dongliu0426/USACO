#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector w(n, vector<int>(n));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> w[i][j];
    vector<pii> ord(n * n);
    for (auto &[i, j] : ord) cin >> i >> j, i--, j--;
    vector one(n, vector<int>(n, INF)), two(n, vector<int>(n, INF));
    vector<int> three(n, INF), four_s(n, INF), four_t(n, INF);
    vector<int> ans(n * n, INF);
    for (int h = n * n - 2; h >= 0; h--) {
        auto [i, j] = ord[h + 1];
        one[i][j] = w[i][j];
        for (int k = 0; k < n; k++) {
            two[i][k] = min(two[i][k], one[i][j] + one[j][k]);
            two[k][j] = min(two[k][j], one[k][i] + one[i][j]);
        }
        for (int k = 0; k < n; k++) {
            three[k] = min(three[k], one[0][i] + two[i][k]);
            three[k] = min(three[k], one[0][j] + two[j][k]);
            three[k] = min(three[k], two[0][i] + one[i][k]);
        }
        for (int k = 0; k < n; k++) {
            four_s[j] = min(four_s[j], two[0][k] + two[k][j]);
            four_s[k] = min(four_s[k], two[0][i] + two[i][k]);
            four_s[k] = min(four_s[k], two[0][j] + two[j][k]);
            four_t[i] = min(four_t[i], two[i][k] + two[k][n - 1]);
            four_t[k] = min(four_t[k], two[k][i] + two[i][n - 1]);
            four_t[k] = min(four_t[k], two[k][j] + two[j][n - 1]);
        }
        if (i == 0) {
            for (int u = 0; u < n; u++) for (int v = 0; v < n; v++)
                four_s[v] = min(four_s[v], two[0][u] + two[u][v]);
        }
        if (j == n - 1) {
            for (int u = 0; u < n; u++) for (int v = 0; v < n; v++)
                four_t[v] = min(four_t[v], two[v][u] + two[u][n - 1]);
        }
        if (k == 1) ans[h] = one[0][n - 1];
        else if (k == 2) ans[h] = two[0][n - 1];
        else if (k == 3) ans[h] = three[n - 1];
        else if (k == 4) ans[h] = four_s[n - 1];
        else if (k == 5) for (int i = 0; i < n; i++) ans[h] = min(ans[h], four_s[i] + one[i][n - 1]);
        else if (k == 6) for (int i = 0; i < n; i++) ans[h] = min(ans[h], four_s[i] + two[i][n - 1]);
        else if (k == 7) for (int i = 0; i < n; i++) ans[h] = min(ans[h], three[i] + four_t[i]);
        else for (int i = 0; i < n; i++) ans[h] = min(ans[h], four_s[i] + four_t[i]);
    }
    for (int x : ans) cout << (x == INF ? -1 : x) << '\n';
}