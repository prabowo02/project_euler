#include <bits/stdc++.h>
using namespace std;

const int N = 50;
const int S = 20;

double q;
double dp[N + 5][S + 5];
bool vis[N + 5][S + 5];
double f(int x, int s) {
  if (s < 0) return 0;
  if (x == 0) return s == 0;
  if (vis[x][s]) return dp[x][s];
  vis[x][s] = true;
  return dp[x][s] = (1 - x/q) * f(x - 1, s - 1) + x/q * f(x - 1, s);
}

void reset() {
  for (int i = 0; i <= N; ++i) {
    for (int j = 0; j <= S; ++j) {
      vis[i][j] = false;
    }
  }
}

double p(double _q) {
  q = _q;
  reset();
  return f(N, S);
}

void solve() {
  // for (int i = 51; i <= 100; ++i) cerr << p(i) << endl;
  double l = 50, r = 100;
  for (int i = 0; i < 100; ++i) {
    double mid = (l + r) / 2;
    if (p(mid) < 0.02) {
      r = mid;
    } else {
      l = mid;
    }
  }

  printf("%.12lf\n", q);
}

int main() {
  double t = clock();
  solve();
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}