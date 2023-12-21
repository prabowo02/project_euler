// The transition graph is a cycle graph C6
// Split the n+m into consecutive pairs
//   If the pair is from the same ring, it doesn't change anything
//   Otherwise, we move to one direction in a C3 graph
// 
// There are several ways to count number of ways we return to the original point after traversing n times in C3
// Using dp: dp[n] = dp[n - 1] + 2dp[n - 2]; dp[0] = 1, dp[1] = 0
// From the GF 1 / (1 - 2x^2(1 / (1-x))) = (1 - x) / (1 - x - 2x^2); i.e. we group the steps by the minimal steps it returns to original points
// Or using direct formula sum of [x^3k] from (x + x^-1)^n = 1/3[(1 + 1^-1)^n + (w + w^-1)^n + (w^2 + w^-2)^n] = 1/3(2*n + 2(-1)^n)

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1234567891;

int inv(int n) {
  int ret = 1;
  for (int y = MOD - 2; y > 0; y >>= 1) {
    if (y & 1) ret = 1LL * ret * n % MOD;
    n = 1LL * n * n % MOD;
  }
  return ret;
}

int fact(int n) {
  int ret = 1;
  for (int i = 2; i <= n; ++i) {
    ret = 1LL * ret * i % MOD;
  }
  return ret;
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  if ((n + m) % 2 == 1) return 0 * printf("0\n");
  if (n > m) swap(n, m);

  int in = inv(fact(n / 2));
  int im = inv(fact(m / 2));
  int ik = 1;

  int ans = (n % 2 == 0 ? 1LL * in * im % MOD : 0);
  int a = 0, b = 1;
  for (int k = n % 2; k * 2 <= n + m; ++k) {
    if ((k & 1) == (n & 1)) {
      ans = (ans + 1LL * in * im % MOD * ik % MOD * a) % MOD;
      in = 1LL * in * ((n - k) / 2) % MOD;
      im = 1LL * im * ((m - k) / 2) % MOD;
      ik = 1LL * ik * inv(1LL * (k + 1) * (k + 2) % MOD) % MOD;
    }
    int na = (1LL * a + b + b) % MOD;
    int nb = a;
    a = na; b = nb;
  }

  ans = 1LL * ans * fact((n + m) / 2) % MOD;
  printf("%d\n", ans);
  return 0;
}
