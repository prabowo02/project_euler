#include <bits/stdc++.h>
using namespace std;

const int M = 155;
const int N = 10005;
const int D = 55;
const int MOD = 1000000007;

int n, d, m, s;

int min_dig;
int dp[M][M*D];
int f(int m, int s) {
  if (s < 0) return 0;
  if (m == 0) return 1;
  if (~dp[m][s]) return dp[m][s];

  return dp[m][s] = (1LL * f(m-1, s-min_dig) - f(m-1, s-d-1) + f(m, s-1) + MOD) % MOD;
}

void init_dp(int mini_dig) {
  min_dig = mini_dig;
  for (int m = ::m; m >= 0; --m) {
    for (int s = ::s; s >= 0; --s) {
      dp[m][s] = -1;
    }
  }

  for (int m = ::m; m >= 0; --m) {
    for (int s = ::s; s >= 0; --s) {
      dp[m][s] = (f(m, s) - f(m, s-1) + MOD) % MOD;
    }
  }
}

int power[D][N];
void init_power() {
  for (int i = 0; i <= d; ++i) {
    power[i][0] = 1;
    for (int j = 1; j <= n; ++j) {
      power[i][j] = 1LL * power[i][j-1] * i % MOD;
    }
  }
}

int fact[N], ifact[N];
void init_combin() {
  fact[0] = 1;
  for (int i = 1; i < N; ++i) fact[i] = 1LL * fact[i-1] * i % MOD;

  ifact[N-1] = 888832204;
  for (int i = N-2; i >= 0; --i) ifact[i] = 1LL * ifact[i+1] * (i+1) % MOD;
}

int C(int n, int k) {
  if (k < 0 || k > n) return 0;
  assert(0 <= n && n < N);
  return 1LL * fact[n] * ifact[k] % MOD * ifact[n-k] % MOD;
}

int main() {
  scanf("%d %d %d %d", &n, &d, &m, &s);

  init_power();
  init_combin();

  int ans = 0;
  for (int mini = 1; mini <= d; ++mini) {
    init_dp(mini + 1);
    for (int mini_cnt = 1; mini_cnt * mini <= s; ++mini_cnt) {
      if (mini_cnt > m) break;

      int tmp = 1LL * C(n, m - mini_cnt) * dp[m - mini_cnt][s - mini_cnt * mini] % MOD;
      for (int i = mini_cnt; i <= n - m + mini_cnt; ++i) {
        assert(n - m + mini_cnt - i >= 0);
        assert(mini >= 1);
        assert(mini < D);
        ans = (1LL * tmp * C(i-1, mini_cnt-1) % MOD * power[mini-1][i-mini_cnt] % MOD * power[mini][n - m + mini_cnt - i] % MOD + ans) % MOD;
      }
    }
  }

  printf("%d\n", ans);
  return 0;
}
