#include <bits/stdc++.h>
using namespace std;

double solve(int r) {
  map<int, int> isqrt;
  for (int i = 0; i <= r; ++i) {
    isqrt[i*i] = i;
  }

  vector<tuple<int, int, int>> nodes;
  for (int i = 0; i <= r; ++i) {
    for (int j = i; i*i + j*j <= r*r; ++j) {
      int k2 = r*r - i*i - j*j;
      if (isqrt.find(k2) != isqrt.end()) {
        int k = isqrt[k2];

        nodes.emplace_back(i, j, k);
        if (k != 0) {
          nodes.emplace_back(i, j, -k);
        }
      }
    }
  }

  vector<double> dist(nodes.size(), 10);
  dist[0] = 0;
  vector<bool> flag(nodes.size());

  for (int i = 0; i < nodes.size(); ++i) {
      int u = -1;
      for (int j = 0; j < nodes.size(); ++j) {
        if (flag[j]) continue;
        if (u == -1 || dist[j] < dist[u]) {
          u = j;
        }
      }

      flag[u] = true;
      for (int v = 0; v < nodes.size(); ++v) {
        if (flag[v]) continue;

        double d = get<0>(nodes[u]) * get<0>(nodes[v]) + get<1>(nodes[u]) * get<1>(nodes[v]) + get<2>(nodes[u]) * get<2>(nodes[v]);
        d = acos(d / r / r);
        d = d * d;

        dist[v] = min(dist[v], dist[u] + d);
      }
  }

  return dist[1] / acos(-1) / acos(-1);
}

int main() {
  printf("%.10lf\n", solve(7));
  double ans = 0;
  for (int n = 1; n <= 15; ++n) {
    ans += solve((1 << n) - 1);
    // cerr << n << " " << ans << endl;
  }
  printf("%.10lf\n", ans);
  return 0;
}