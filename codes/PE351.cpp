#include <bits/stdc++.h>
using namespace std;

long long H(int n) {
  vector<int> mu(n);
  vector<int> coprimes(n);

  long long ans = 0;
  mu[1] = 1;
  for (int d = 1; d < n; ++d) {
    for (int i = d; i < n; i += d) {
      coprimes[i] += (n - i) / d * mu[d];
    }
    for (int i = d*2; i < n; i += d) {
      mu[i] -= mu[d];
    }
    ans += coprimes[d];
  }

  ans = (ans + 1) * 6; // Number of points that are not hidden
  return 3LL * n * (n + 1) - ans;
}

int main() {
  printf("%lld\n", H(5));
  printf("%lld\n", H(10));
  printf("%lld\n", H(1000));
  printf("%lld\n", H(100000000));
  return 0;
}
