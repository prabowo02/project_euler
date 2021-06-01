#include <bits/stdc++.h>
using namespace std;

vector<int> primes;

bool isPrime(int p) {
  for (int i = 2; i*i <= p; ++i) {
    if (p % i == 0) return false;
  }
  return true;
}

int C(int n, int k) {
  int ret = 1;
  for (int i = 0; i < k; ++i) {
    ret *= (n - i);
    ret /= (i + 1);
  }
  return ret;
}

int main() {
  long long maxn = 1e16;
  vector<int> primes;
  for (int i = 2; i < 100; ++i) if (isPrime(i)) {
    primes.push_back(i);
  }

  long long ans = 0;
  for (int mask = 15; mask < 1 << primes.size(); ++mask) {
    int popcount = __builtin_popcount(mask);
    if (popcount < 4) continue;
    long long num = 1;
    for (int j = 0; j < primes.size(); ++j) {
      if (mask >> j & 1) {
        num *= primes[j];
        if (num > maxn) break;
      }
    }

    if (popcount - 4 & 1) ans -= maxn / num * C(popcount - 1, 4 - 1);
    else ans += maxn / num * C(popcount - 1, 4 - 1);
  }

  printf("%lld\n", ans);
  return 0;
}
