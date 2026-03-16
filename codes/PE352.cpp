#include <bits/stdc++.h>
using namespace std;

int n;
double p;
double allneg[10005];

double dp[10005][2];
double f(int n, int pos) {
  if (n == 1) {
    return 1 - pos;
  }
  double &ret = dp[n][pos];
  if (ret > -0.5) return ret;

  ret = n;
  if (pos == 0) {
    for (int i = 1; i < n; ++i) {
      // Test on i sheep, and is positive
      double t = (1 - allneg[i]) * (f(i, 1) + f(n - i, 0));
      // Test on i sheep, and is negative
      t += allneg[i] * f(n - i, 0);
      ret = min(ret, 1 + t);
    }

    ret = min(ret, 1 + (1 - allneg[n]) * f(n, 1));
  } else {
    double d = 1 - allneg[n];
    for (int i = 1; i < n; ++i) {
      // Test on i sheep, and is positive
      double t = (1 - allneg[i]) / d * (f(i, 1) + f(n - i, 0));
      // Test on i sheep, and is negative
      t += allneg[i] * (1 - allneg[n - i]) / d * f(n - i, 1);

      ret = min(ret, 1 + t);
    }
  }

  return ret;
}

void initDP(int n, double p) {
  ::n = n;
  ::p = p;
  allneg[0] = 1;
  for (int i = 1; i <= n; ++i) {
    dp[i][0] = dp[i][1] = -1;
    allneg[i] = allneg[i - 1] * (1 - p);
  }
}

double T(int n, double p) {
  initDP(n, p);
  return f(n, 0);
}

int main() {
  printf("%.6lf\n", T(25, 0.02));
  printf("%.6lf\n", T(25, 0.10));
  double ans = 0;
  for (int i = 1; i <= 50; ++i) {
    cerr << i << endl;
    ans += T(10000, i * 0.01);
  }
  printf("%.6lf\n", ans);
  return 0;
}
