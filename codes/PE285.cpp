// (ak + 1)^2 + (bk + 1)^2 = y^2

// 0 <= b <= 1
// ==> 1 <= (bk + 1)^2 <= (k + 1)^2

// (bk + 1)^2 = y^2 - (ak + 1)^2

// y <= k + 0.5
// ==> (bk + 1)^2 <= (k + 0.5)^2 - (ak + 1)^2 = k^2 (1 - a^2) + k (1 - 2a) - 0.75 <= k^2 + k <= (k + 1)^2
// ==> b always upper bounded by 1/k [sqrt((k + 0.5)^2 - (ak + 1)^2) - 1]

// k - 0.5 <= y
// ==> (bk + 1)^2 >= (k - 0.5)^2 - (ak + 1)^2 = k^2 (1 - a^2) + k (-1 - 2a) - 0.75
// ==> When a = 0, k^2 - k - 0.75 >= 1 (if k >= 2), when a = 1, -3k - 0.75 <= 1
// ==> Lower bound passes through 1

// (k - 0.5)^2 - (ak + 1)^2 = 1
// ==> a = (sqrt((k - 0.5)^2 - 1) - 1) / k

// When k > 1,
// integral_{0}^{(sqrt((k + 0.5)^2 - 1) - 1) / k} 1/k [sqrt((k + 0.5)^2 - (xk + 1)^2) - 1] dx
// - 
// integral_{0}^{(sqrt((k - 0.5)^2 - 1) - 1) / k} 1/k [sqrt((k - 0.5)^2 - (xk + 1)^2) - 1] dx

// Then use the fact that integral sqrt(c^2 - (ax + b)^2) dx = c^2 / 2a * (arcsin((ax + b) / c) + (ax + b) / c * sqrt(1 - (ax + b)^2 / c^2)) + C


#include <bits/stdc++.h>
using namespace std;

// integral_0^x 1/k (sqrt(c^2 - (xk + 1)^2) - 1)
double integral(int k, double x, double c) {
  double t = (k*x + 1) / c;
  double s = 1.0 / c;
  return c*c / (2*k) * (asin(t) + t * sqrt(1 - t*t) - asin(s) - s * sqrt(1 - s*s)) / k - x / k;
}

double area(int k) {
  double lo = (sqrt((k - 0.5) * (k - 0.5) - 1) - 1) / k;
  double hi = (sqrt((k + 0.5) * (k + 0.5) - 1) - 1) / k;
  if (k == 1) {
    return integral(k, hi, k + 0.5);
  }
  return integral(k, hi, k + 0.5) - integral(k, lo, k - 0.5);
}

void solve(int n) {
  double ans = 0;
  for (int k = 1; k <= n; ++k) {
    ans += area(k) * k;
  }
  printf("%.12lf\n", ans);
}

int main() {
  double t = clock();
  solve(100000);
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}

