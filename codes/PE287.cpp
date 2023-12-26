#include <bits/stdc++.h>
using namespace std;

vector<tuple<int, int, int, int>> split(int a, int b, int c, int d) {
  int midrow = (a + b) / 2, midcol = (c + d) / 2;
  return {
    make_tuple(a, midrow, c, midcol),
    make_tuple(a, midrow, midcol + 1, d),
    make_tuple(midrow + 1, b, midcol + 1, d),
    make_tuple(midrow + 1, b, c, midcol),
  };
}

void solve(int n) {
  int ans = 1;
  int r = 1 << (n - 1);
  queue<tuple<int, int, int, int>> q;
  for (auto [a, b, c, d] : split(0, (1 << n) - 1, 0, (1 << n) - 1)) {
    q.emplace(a, b, c, d);
  }

  auto dist = [&](pair<int, int> p) {
    return 1LL * (p.first - r) * (p.first - r) + 1LL * (p.second - r) * (p.second - r);
  };

  while (q.size()) {
    int a, b, c, d;
    tie(a, b, c, d) = q.front();
    q.pop();

    vector<pair<int, int>> v = {
      {a, c}, {a, d}, {b, c}, {b, d}
    };
    sort(v.begin(), v.end(), [&](pair<int, int> p, pair<int, int> q) {
      return dist(p) < dist(q);
    });

    if (dist(v[0]) > 1LL * r * r || dist(v.back()) <= 1LL * r * r) {
      ans += 2;
    } else {
      ans += 1;
      for (auto [na, nb, nc, nd] : split(a, b, c, d)) {
        q.emplace(na, nb, nc, nd);
      }
    }
  }

  cout << ans << endl;
}

int main() {
  double t = clock();
  solve(24);
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}
