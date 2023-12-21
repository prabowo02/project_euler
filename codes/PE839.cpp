#include <bits/stdc++.h>
using namespace std;

long long ceil(long long x, long long y) {
  return (x + y - 1) / y;
}

int main() {
  int n;
  scanf("%d", &n);

  long long ans = 0;
  vector<pair<int, int>> v;
  v.emplace_back(0, 0);

  int s = 290797;
  for (int i = 0; i < n; ++i, s = 1LL * s * s % 50515093) {
    // cerr << s << endl;
    if (s > v.back().first) {
      v.emplace_back(s, 1);
      continue;
    }

    int t = s;
    while (true) {
      // for (pair<int, int> p : v) cerr << p.first << " " << p.second << endl; cerr << t << endl;
      int l = v.end()[-1].first - v.end()[-2].first;
      int r = (v.back().first - t) / (v.back().second + 1);

      if (r == 0) {
        int step = v.back().first - t, w = v.end()[-1].second;
        if (v.end()[-2].first + 1 == v.end()[-1].first) {
          t += step;
          v.end()[-2].second += step;
          v.end()[-1].second -= step;
        } else if (step > 0) {
          v.back().second -= step;
          t += step;
          v.emplace_back(v.back().first - 1, step);
          swap(v.end()[-1], v.end()[-2]);
        }

        ++v.back().second;
        ans += 1LL * w * step - 1LL * step * (step - 1) / 2;
        break;
      }

      ans += 1LL * v.back().second * (v.back().second + 1) / 2 * min(l, r);
      if (l <= r) {
        t += l * v.back().second;
        v.end()[-2].second += v.end()[-1].second;
        v.pop_back();
      } else {
        // cerr << "R: " << r << endl;
        t += r * v.back().second;
        v.back().first -= r;
      }
    }
      // for (pair<int, int> p : v) cerr << p.first << " " << p.second << endl;
  }

  printf("%lld\n", ans);
  return 0;
}
