#include <bits/stdc++.h>
using namespace std;

#define sz(v) int(std::size(v))
using i64 = long long;

const int N = 7500;

string s;
int n;
i64 ans;
vector<int> g;

struct DS {
    int ch[N * 2 + 1];
    int cur_x; i64 cur_s;
    int num_leq, tot;

    void reset() {
        memset(ch, 0, sizeof ch);
        cur_x = 0, cur_s = 0;
        num_leq = 0;
        tot = 0;
    }
    void add_func(int c) {
        cur_s += abs(cur_x - c);
        num_leq += c <= cur_x;
        ch[c] += 1;
        tot++;
    }
    void shift_left() {
        num_leq -= ch[cur_x];
        cur_s -= num_leq;
        cur_s += tot - num_leq;
        cur_x--;
    }
    void shift_right() {
        cur_s += num_leq;
        cur_s -= tot - num_leq;
        num_leq += ch[cur_x + 1];
        cur_x++;
    }
    int qry_sum(int x) {
        while (cur_x > x) shift_left();
        while (cur_x < x) shift_right();
        return cur_s;
    }
} T;

i64 solve_center(int p, int q)  {
    int mid = p == q ? g[p] : -1;
    i64 val = 0;
    T.reset();
    while (p >= 0 && q < sz(g)) {
        int L = p == 0 ? -1 : g[p - 1];
        int R = q == sz(g) - 1 ? n : g[q + 1];
        if (p < q) T.add_func(g[p] + g[q]);
        for (int l = L + 1; l <= g[p]; l++) for (int r = g[q]; r < R; r++) {
            if (~mid) {
                if ((r - l + 1) % 2 == 0) val += -1;
                else val += T.qry_sum(l + r) + abs(mid - (l + r) / 2);
            } else val += T.qry_sum(l + r);
        }
        p--, q++;
    }
    return val;
}

int main() {
    cin >> s;
    n = sz(s);
    for (int i = 0; i < n; i++) if (s[i] == 'G') g.push_back(i);
    for (int i = 0; i < sz(g); i++) ans += solve_center(i, i);
    for (int i = 0; i < sz(g) - 1; i++) ans += solve_center(i, i + 1);
    cout << ans << '\n';
}