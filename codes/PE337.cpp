#include <bits/stdc++.h>
using namespace std;

int solve(int n, int mod) {
  vector<int> phi(n + 1);
  for (int i = 1; i <= n; ++i) {
    phi[i] = i;
  }
  for (int p = 2; p <= n; ++p) {
    if (phi[p] != p) continue;
    for (int i = p; i <= n; i += p) {
      phi[i] = phi[i] / p * (p - 1);
    }
  }

  vector<int> bit(n + 1);
  auto add = [&](int x, int val) {
    for (int i = x; i <= n; i += i & -i) {
      bit[i] = (bit[i] + val) % mod;
    }
  };
  auto query = [&](int x) {
    int ret = 0;
    for (int i = x; i > 0; i -= i & -i) {
      ret = (ret + bit[i]) % mod;
    }
    return ret;
  };

  vector<pair<int, int>> orders;
  for (int i = 7; i <= n; ++i) {
    orders.emplace_back(phi[i], -i);
  }
  sort(orders.begin(), orders.end());

  add(6, 1);

  int ans = 1;
  for (pair<int, int> p : orders) {
    int num = -p.second;

    // for i in (phi(num), num), sum dp[i] if phi(i) < phi(num)
    int count = query(num) - query(phi[num]);
    if (count < 0) count += mod;

    ans = (ans + count) % mod;
    add(num, count);
  }

  return ans;
}

int main() {
  printf("%d\n", solve(10, 100));
  printf("%d\n", solve(100, 1000000000));
  printf("%d\n", solve(10000, 100000000));
  printf("%d\n", solve(20000000, 100000000));
  return 0;
}
