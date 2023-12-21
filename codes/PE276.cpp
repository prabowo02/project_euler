#include <bits/stdc++.h>
using namespace std;

ostream& operator << (ostream &os, __int128 value) {
  vector<int> v;
  while (value > 0) {
    v.push_back(value % 10);
    value /= 10;
  }
  while (v.size()) os << v.back(), v.pop_back();
  return os;
}

long long solve(int n) {
  vector<__int128> triples(n + 1);  // Number of triples s.t. 1 <= a <= b <= c, a + b + c <= n
  triples[3] = 1;
  triples[4] = 1;
  triples[5] = 2;
  for (int i = 6; i <= n; ++i) {
    triples[i] = triples[i - 1] + triples[i - 2] - triples[i - 4] - triples[i - 5] + triples[i - 6];
    // if (i % 2 == 0) assert(triples[i] == (i*i % 48 < 24 ? i*i / 48 : i*i / 48 + 1));
  }
  for (int i = 1; i <= n; ++i) {
    triples[i] += triples[i - 1];
  }

  // There exists this G.F. too apparently: https://mathworld.wolfram.com/IntegerTriangle.html
  // x^3 / (1 - x)(1 - x^2)(1 - x^3)(1 - x^4) number of integer triangles with perimeter <= n
  // i.e. a triple (a, b, c) is written as a(0, 1, 1) + b(1, 1, 1) + c(1, 1, 2)
  auto triangles = [&](int n) {
    __int128 ret = triples[n];
    for (int i = 2; i <= n / 2; ++i) {
      // a + b = i; c >= i
      ret -= 1LL * (n - i - i + 1) * (i / 2);
    }
    return ret;
  };

  vector<int> mu(n + 1, 1);
  vector<bool> isPrime(n + 1, true);
  for (int p = 2; p <= n; ++p) {
    if (!isPrime[p]) continue;
    for (int i = p * 2; i <= n; i += p) isPrime[i] = false;
    for (int i = p; i <= n; i += p) {
      mu[i] = -mu[i];
      if (i / p % p == 0) mu[i] = 0;
    }
  }

  // for (int i = 3; i <= n; ++i) cerr << triples[i] << " " << triangles(i) << endl;

  __int128 ans = 0;
  for (int i = 1; i <= n; ++i) ans += triangles(n / i) * mu[i];

  return ans;
}

int main() {
  int n;
  cin >> n;
  clock_t t = clock();
  cout << solve(n) << endl;
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}
