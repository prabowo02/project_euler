#include <cstdio>

int n, mod;
int dp[2][502][502];

int power(int x, int y, int m) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % m;
    x = 1LL * x * x % m;
  }
  return ret;
}

int main() {
  scanf("%d %d", &n, &mod);

  int maxseg = (n+1)/2;
  for (int i = 1; i <= maxseg; ++i) {
    dp[0][1][i] = i;
  }

  int cur = 0, nxt;
  for (int i = 2; i <= n; ++i) {
    nxt = cur ^ 1;

    int maxseg_i = (i < n-i+1 ? i : n-i+1);

    for (int seg = 1; seg <= maxseg_i; ++seg) {
      dp[nxt][seg][seg] = 
           (2LL * seg * dp[cur][seg][seg] 
          + 1LL * (seg+1) * dp[cur][seg+1][seg+1]
          + 1LL * (seg-1) * dp[cur][seg-1][seg]) % mod;
      for (int m = seg+1; m <= maxseg; ++m) {
        dp[nxt][seg][m] = 
             (2LL * seg * dp[cur][seg][m]
            + 1LL * (seg+1) * dp[cur][seg+1][m]
            + 1LL * (seg-1) * dp[cur][seg-1][m]) % mod;
      }
    }

    cur ^= 1;
  }

  int fact = 1;
  for (int i = 2; i <= n; ++i) fact = 1LL * fact * i % mod;

  printf("%lld\n", 1LL * dp[cur][1][1] * power(fact, mod-2, mod) % mod);
  return 0;
}
