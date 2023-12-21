// Parametric for primitive
// 60 degree: (a, b, c) = (m^2 - n^2, 2mn - n^2, m^2 - mn + n^2), m n coprime, n < m/2, if m + n is divisible by 3, divide them by 3
// 90 degree: (a, b, c) = (m^2 - n^2, 2mn, m^2 + n^2), m n coprime and not both odd
// 120 degree: (a, b, c) = (m^2 - n^2, 2mn + n^2, m^2 + mn + n^2), m n coprime and m - n not divisible by 3

// Their perimeters:
// 2m^2 + mn - n^2
// 2m^2 + 2mn
// 2m^2 + 3mn + n^2

#include <bits/stdc++.h>
using namespace std;

void solve(int N) {
  queue<pair<int, int>> q;
  q.emplace(1, 2);

  long long ans = 0;  // Equilateral triangle count

  while (q.size()) {
    int m, n;
    tie(m, n) = q.front();
    q.pop();

    if (m < n) swap(n, m);

    long long p = 2LL * m * m + 1LL * m * n - 1LL * n * n;

    // 60
    if (p > N * 3) continue;
    if (n <= m / 2) {
      if ((m + n) % 3 != 0) ans += N / p;
      else ans += N / (p / 3);
    }

    // 90
    p += 1LL * m * n + 1LL * n * n;
    if (m % 2 == 0 || n % 2 == 0) ans += N / p;

    // 120
    p += 1LL * m * n + 1LL * n * n;
    if ((m - n) % 3 != 0) ans += N / p;

    q.emplace(m + n, n);
    q.emplace(m, m + n);
  }

  cout << ans << endl;
}

int main() {
  int n = 100000000;
  cin >> n;
  clock_t t = clock();
  solve(n);
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
}
