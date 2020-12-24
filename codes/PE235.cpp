#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int a, d, n;
long long x;

double solve() {
  double l = 0.75, r = 1.25;
  for (int i = 0; i < 150; ++i) {
    double mid = (l + r) / 2;

    double sum = 0;
    double ratio = 1;
    for (int k = 1; k <= n; ++k) {
      sum += (a - d*k) * ratio;
      ratio *= mid;
    }

    if (sum < -x) r = mid;
    else l = mid;
  }

  return l;
}

int main() {
  int q;
  scanf("%d", &q);
  while (q--) {
    scanf("%d %d %d %lld", &a, &d, &n, &x);
    printf("%.15lf\n", solve());
  }
  return 0;
}
