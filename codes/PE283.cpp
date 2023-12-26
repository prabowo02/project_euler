// https://oeis.org/A007237

// A(n) is the number of pairs r, s of positive integers such that
// r <= s
// 4n^2 < rs <= 12n^2
// 4n^2 (r + s) / (rs - 4n^2) >= s
// t = 4n^2 (r + s) / (rs - 4n^2) is an integer

// The triangle itself is (r + s, r + t, s + t)

#include <bits/stdc++.h>
using namespace std;

void solve(int N) {
  long long ans = 0;
  for (int n = 1; n <= N; ++n) {
    int cnt = 0;
    for (int s = 2*n; s <= 12*n*n; ++s) {
      for (int r = 4*n*n / s + 1; r <= s; ++r) {
        if (r * s > 12*n*n) break;
        if (4LL*n*n * (r + s) % (r*s - 4*n*n) != 0) continue;
        long long t = 4LL*n*n * (r + s) / (r*s - 4*n*n);
        if (t >= s) {
          ++cnt;
          ans += 2LL * (r + s + t);
        }
      }
    }
    // cerr << n << " " << cnt << endl;
  }
  cout << ans << endl;
}

int main() {
  clock_t t = clock();
  solve(1000);
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}
