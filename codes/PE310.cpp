#include <bits/stdc++.h>
using namespace std;

int dpNim[100005];
int nimber(int n) {
  if (~dpNim[n]) return dpNim[n];

  vector<int> x;
  for (int i = 1; i*i <= n; ++i) {
    x.push_back(nimber(n - i*i));
  }
  sort(x.begin(), x.end());
  x.resize(unique(x.begin(), x.end()) - x.begin());

  for (int i = 0; ; ++i) {
    if (i >= x.size() || x[i] != i) return dpNim[n] = i;
  }
  assert(0);
}

long long dp[100005][4][512];
long long f(int n, int k, int x) {
  if (n < 0) {
    return 0;
  }
  if (k == 0) {
    return x == 0;
  }
  if (~dp[n][k][x]) return dp[n][k][x];
  return dp[n][k][x] = f(n - 1, k, x) + f(n, k - 1, x ^ nimber(n));
}

int main() {
  memset(dpNim, -1, sizeof dpNim);
  memset(dp, -1, sizeof dp);
  printf("%lld\n", f(29, 3, 0));
  printf("%lld\n", f(100000, 3, 0));
  return 0;
}
