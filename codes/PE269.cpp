// Polynomial written as: P = a0 + x * (a1 + x * (...))
// zero if and only if P(i) = 0, for some i in [-9, 0]

#include <bits/stdc++.h>
using namespace std;

int N, B;

bool canReachZero(int x, int b) {
  if (x == 0) return true;
  if (x < 0) {
    return x * -b * -b + (B - 1) > x;
  }
  return min(0, x * -b + (B - 1)) * -b < x;
}

map<pair<int, vector<int>>, long long> dp;
long long dfs(int x, vector<int> bases, vector<int> vals) {
  if (x == N) {
    for (int v : vals) if (v != 0) return 0;
    return 1;
  }
  auto it = dp.find(make_pair(x, vals));
  if (it != dp.end()) return it->second;

  long long ret = 0;
  for (int d = 0; d < B; ++d) {
    vector<int> nvals;
    for (int i = 0; i < bases.size(); ++i) {
      nvals.push_back(vals[i] * -bases[i] + d);
      if (!canReachZero(nvals.back(), bases[i])) {
        nvals.pop_back();
        break;
      }
    }

    if (nvals.size() == bases.size()) ret += dfs(x + 1, bases, nvals);
  }

  return dp[make_pair(x, vals)] = ret;
}

int main() {
  N = 16; B = 10;
  // scanf("%d %d", &n, &B);
  long long ans = 0;
  for (int mask = 1; mask < 1 << B; ++mask) {
    dp.clear();
    vector<int> bases;
    for (int j = 0; j < B; ++j) {
      if (mask >> j & 1) bases.push_back(j);
    }
    long long res = dfs(0, bases, vector<int>(bases.size()));
    if (bases.size() & 1) ans += res;
    else ans -= res;
  }

  printf("%lld\n", ans);
  return 0;
}
