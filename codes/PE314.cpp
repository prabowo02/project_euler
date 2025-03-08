#include <bits/stdc++.h>
using namespace std;

const int N = 255;

int n;

inline double area(int x, int y, int i, int j) {
  return (x * j - y * i) / 2.0;
}

double dp[N][N];
pair<int, int> track[N][N];
double _solve(double lambda) {
  dp[0][n] = 0;
  for (int x = 0; x <= n; ++x) {
    for (int y = n; y >= 0; --y) {
      if (x == 0 && y == n) continue;
      for (int i = x; i >= 0; --i) {
        for (int j = y; j <= n; ++j) {
          if (x == i && y == j) {
            dp[x][y] = -1e9;
            continue;
          }
          double val = area(x, y, i, j) - lambda * hypot(x - i, y - j) + dp[i][j];
          if (val > dp[x][y]) {
            dp[x][y] = val;
            track[x][y] = make_pair(i, j);
          }
        }
      }
    }
  }

  double Area = 0, Peri = 0;
  int x = n, y = 0;
  while (x != 0 || y != n) {
    int i = track[x][y].first, j = track[x][y].second;
    Area += area(x, y, i, j);
    Peri += hypot(x - i, y - j);
    x = i, y = j;
  }
  return Area / Peri;
}

double solve(int n) {
  ::n = n;
  double lambda = n / 2.0;
  for (int i = 0; i < 5; ++i) {
    printf("%.12lf\n", lambda);
    lambda = _solve(lambda);
  }
  return lambda;
}

int main() {
  printf("%.12lf\n", solve(250));
  return 0;
}
