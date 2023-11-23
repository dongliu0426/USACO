#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using matrix = array<array<i64, 8>, 8>;

const int N = 2e5;

void mult(const matrix& a, const matrix& b, matrix& c) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j] + a[i][3] * b[3][j] + a[i][4] * b[4][j] + a[i][5] * b[5][j] + a[i][6] * b[6][j] + a[i][7] * b[7][j];
}

void mat(matrix& a, int p, char c) {
    for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++)
        a[i][j] = 0;
    for (int i = 1; i <= 6; i++)
        a[i][i] = 1;
    a[0][0] = 1;
    a[6][7] = 1;
    if (c == 'b')
        a[1][1] = 0, a[0][1] = p + 1, a[6][1] = 1;
    else if (c == 'e')
        a[2][2] = 0, a[6][6] = 0, a[1][2] = 1, a[5][6] = 1, a[5][7] = 1, a[6][7] = 0;
    else if (c == 's')
        a[3][3] = 0, a[4][4] = 0, a[2][3] = 1, a[3][4] = 1;
    else if (c == 'i')
        a[5][5] = 0, a[4][5] = 1;
    a[7][7] = 1;
}

string s;
matrix t[N * 4];

void bld(int k, int l, int r) {
    if (l == r)
        mat(t[k], l, s[l]);
    else {
        int m = (l + r) / 2;
        bld(k << 1 | 0, l, m), bld(k << 1 | 1, m + 1, r);
        mult(t[k << 1 | 0], t[k << 1 | 1], t[k]);
    }
}
void upd(int k, int l, int r, int p) {
    if (l == r)
        mat(t[k], l, s[l]);
    else {
        int m = (l + r) / 2;
        if (p <= m) upd(k << 1 | 0, l, m, p);
        else upd(k << 1 | 1, m + 1, r, p);
        mult(t[k << 1 | 0], t[k << 1 | 1], t[k]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    int n = s.size();
    bld(1, 0, n - 1);
    cout << t[1][0][7] << '\n';
    int q;
    cin >> q;
    while (q--) {
        int p;
        cin >> p, p--;
        cin >> s[p];
        upd(1, 0, n - 1, p);
        cout << t[1][0][7] << '\n';
    }
}