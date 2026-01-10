#include <bits/stdc++.h>
using namespace std;

int dp[1000000][20][13];
int f(int n, int two, int three) {
  if (n == 0) return 1;
  if ((1 << two) > n || three < 0) return 0;

  int &ret = dp[n][two][three];
  if (~ret) return ret;

  ret = f(n, two + 1, three);
  for (int i = 0, term = (1 << two); i <= three; ++i) {
    if (term > n) break;
    ret += f(n - term, two + 1, i - 1);
    term *= 3;
  }
  return ret;
}

long long solve(int n) {
  vector<bool> primes(n, true);
  primes[0] = primes[1] = false;
  for (int p = 2; p < n; ++p) {
    if (!primes[p]) continue;
    for (int i = p * 2; i < n; i += p) {
      primes[i] = false;
    }
  }

  memset(dp, -1, sizeof dp);

  long long ret = 0;
  for (int i = 0; i < n; ++i) {
    if (primes[i] && f(i, 0, 12) == 1) {
      ret += i;
    }
  }

  return ret;
}

int main() {
  printf("%lld\n", solve(100));
  printf("%lld\n", solve(1000000));
  return 0;
}
