#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000123;
const int N = 10000005;

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }

  return ret;
}

int fact[N], ifact[N];
bool is_prime[N];
void init(int n=N) {
  fact[0] = 1;
  for (int i = 1; i < n; ++i) {
    fact[i] = 1LL * fact[i-1] * i % MOD;
  }

  ifact[n-1] = power(fact[n-1], MOD-2);
  for (int i = n-2; i >= 0; --i) {
    ifact[i] = 1LL * ifact[i+1] * (i+1) % MOD;
  }

  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i < n; ++i) is_prime[i] = true;
  for (int i = 2; i*i < n; ++i) {
    if (is_prime[i]) for (int j = i*2; j < n; j += i) {
      is_prime[j] = false;
    }
  }
}

int C(int n, int k) {
  return 1LL * fact[n] * ifact[k] % MOD * ifact[n-k] % MOD;
}

int count_derangement(int n, int p, int k) {
  int ret = 0;

  for (int i = 0; k+i <= p; ++i) {
    int term = 1LL * C(k+i, k) * C(p, k+i) % MOD * fact[n-k-i] % MOD;

    if (i & 1) {
      ret = (ret - term + MOD) % MOD;
    } else {
      ret = (ret + term) % MOD;
    }
  }

  return ret;
}

int solve(int n, int k) {
  int prime_count = 0;
  for (int i = 2; i <= n; ++i) if (is_prime[i]) prime_count += 1;
  
  return 1LL * count_derangement(n, prime_count, prime_count - k) * ifact[n] % MOD;
}

int main() {
  init();
  int n, k;
  scanf("%d %d", &n, &k);
  printf("%d\n", solve(n, k));
  return 0;
}
