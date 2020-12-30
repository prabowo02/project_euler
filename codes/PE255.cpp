#include <bits/stdc++.h>
using namespace std;

long long dfs(long long l, long long r, int x) {
  int xl = (x + (l + x - 1) / x) / 2, xr = (x + (r + x - 1) / x) / 2;
  long long ret = r - l + 1;
  for (int nx = xl; nx <= xr; ++nx) {
    if (nx == x) continue;

    // (nx*2 - x) * x - x + 1 .. (nx*2 + 1 - x) * x
    long long nl = max(l, 1LL * (nx*2 - x) * x - x + 1);
    long long nr = min(r, 1LL * (nx*2 + 1 - x) * x);
    ret += dfs(nl, nr, (x + (nl + x - 1) / x) / 2);
  }
  return ret;
}

int main() {
  long long sum = dfs(10000000000000LL, 99999999999999LL, 7000000);
  printf("%.10lf\n", (double) sum / 90000000000000LL);
  return 0;
}
