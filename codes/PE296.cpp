// Because m is tangent to circumcircle, we can deduce that angle ACB equals to angle BAC
// Let F be intersection between k and AB
// Since k is angular bisector, it can be implied that ECF is isosceles triangle

#include <bits/stdc++.h>
using namespace std;

long long solve(int p) {
  long long ret = 0;
  for (int c = 2; c < p / 2; ++c) {
    for (int i = 1; i <= c / 2; ++i) {
      int g = gcd(i, c);

      // AB / AC = i / (c - i)
      // Max: AC is not longer than BC: floor(c / [(c - i) / g]) = floor(cg / (c-i))
      // Min: AB + AC is more than BC: floor(c / (c/g)) = g
      // Max: AB + AC + BC is not more than p: floor((p - c) / (c/g)) = floor(pg/c) - g
      ret += max(0LL, min(1LL * g * c / (c - i), 1LL * g * p / c - g) - g);
    }
  }
  return ret;
}

int main() {
  cout << solve(100000) << endl;
}
