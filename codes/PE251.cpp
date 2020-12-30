// cbrt(a - b sqrt(c)) = 1 - cbrt(a + b sqrt(c))
// a - b sqrt(c) = 1 - 3cbrt(a + b sqrt(c)) + 3cbrt((a + b sqrt(c))^2) - (a + b sqrt(c))
// (2a - 1) = -3cbrt(a + b sqrt(c)) + 3cbrt((a + b sqrt(c))^2)
// (2a - 1)^3 = -27(a + b sqrt(c)) + 81(a + b sqrt(c))(cbrt(a + b sqrt(c)) - cbrt(a + b sqrt(c))^2) + 27(a + b sqrt(c))^2
// (2a - 1)^3 = -27(a + b sqrt(c)) -27(a + b sqrt(c))(2a - 1) + 27(a + b sqrt(c))^2
// (2a - 1)^3 = -27a - 27b sqrt(c) - 54a^2 + 27a - 54ab sqrt(c) + 27b sqrt(c) + 27a^2 + 54ab sqrt(c) + 27b^2c
// (2a - 1)^3 = -27a^2 + 27b^2c
// 8a^3 + 15a^2 + 6a - 1 = 27 b^2c
// (a + 1)^2 (8a - 1) = 27 b^2 c

// consider mod 3
// 8a^3 - 1 = 0 (mod 3)
// a = 2 (mod 3)

// (3k)^2 (8(3k - 1) - 1) = 27 b^2c
// k^2(8k - 3) = b^2 c

// iterate for b = 1 ...

// (3k - 1) + b + k^2(8k - 3) / b^2 <= n

// k^2(8k - 3) = 0 (mod b^2)
// if b prime power
//   k = 0 (mod b) or [k = (7b^2 + 1) / 8 * 3 (mod b^2) if b is odd]
// if b is power of 3, then (8k - 3) = 0 (mod b^2 / 9) also satisfies

#include <bits/stdc++.h>
using namespace std;

const __int128 ONE = 1;

int n;
const int N = 110000005;

int primeFactors[N];

void sieve() {
  for (int p = 2; p < N; ++p) {
    if (primeFactors[p] > 0) continue;
    for (int j = p; j < N; j += p) primeFactors[j] = p;
  }
}

int maxK(int b) {
  // 3k-1 + b + k^2(8k - 3) / b^2 <= n
  int l = 1, r = n;
  int ret = 0;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (mid*3 - 1 + b + ONE*mid*mid*(mid*8 - 3) / b / b <= n) {
      l = mid + 1;
      ret = mid;
    } else {
      r = mid - 1;
    }
  }
  return ret;
}

long long brute() {
  long long ans = 0;
  for (int b = 1; b < n; ++b) {
    int k = maxK(b);
    if (k == 0) break;

    for (int i = 0; i < b*b; ++i) {
      if (1LL*i*i*(i*8 - 3) % (b*b) == 0) {
        ans += (k + b*b - i) / (b*b);
        // if (i <= k) cerr << i << " " << b*b << endl;
        if (i == 0) --ans;
      }
    }
  }
  return ans;
}

long long power(long long x, long long y, long long mod) {
  long long ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = ONE * ret * x % mod;
    x = ONE * x * x % mod;
  }
  return ret;
}

pair<long long, long long> crt(vector<tuple<int, int, long long>> residue) {
  long long mod = 1;
  for (int i = 0; i < residue.size(); ++i) {
    int r, p; long long pe;
    tie(r, p, pe) = residue[i];
    mod *= pe;
  }

  long long res = 0;
  for (int i = 0; i < residue.size(); ++i) {
    int r, p; long long pe;
    tie(r, p, pe) = residue[i];
    res = (ONE * mod/pe * power(mod/pe, pe/p*(p-1) - 1, pe) % mod * r + res) % mod;
  }
  return {res, mod};
}

long long dfs(int k, vector<tuple<int, int, long long>> &residue, const vector<pair<int, int>> &moduli) {
  if (residue.size() == moduli.size()) {
    pair<long long, long long> res = crt(residue);
    // cerr << res.first << " " << res.second << endl;
    return (k + res.second - res.first) / res.second - (res.first == 0);
  }

  int p, pe, ret = 0;
  tie(p, pe) = moduli[residue.size()];

  residue.emplace_back(0, p, pe);
  ret += dfs(k, residue, moduli);
  residue.pop_back();

  if (p > 3) {
    long long m = (7LL*pe*pe + 1) / 8 * 3 % (1LL*pe*pe);
    if (m <= k) {
      residue.emplace_back(m, p, 1LL*pe*pe);
      ret += dfs(k, residue, moduli);
      residue.pop_back();
    }
  } else if (p == 3 && pe > 3) {
    long long m = (7LL*pe*pe/9 + 1) / 8 * 3 % (1LL*pe*pe/9);
    if (m <= k) {
      residue.emplace_back(m, p, 1LL*pe*pe/9);
      ret += dfs(k, residue, moduli);
      residue.pop_back();
    }
  }

  return ret;
}

int main() {
  sieve();
  cerr << "DONE SIEVE" << endl;
  scanf("%d", &n);

  long long ans = 0;
  for (int b = 1; b < n; ++b) {
    int k = maxK(b);
    if (k == 0) break;

    vector<pair<int, int>> moduli;
    int num = b;
    while (num > 1) {
      int p = primeFactors[num];
      int e = 0, pe = 1;
      do {
        num /= p;
        ++e;
        pe *= p;
      } while (num % p == 0);
      moduli.emplace_back(p, pe);
    }

    // cerr << moduli.size() << endl;
    vector<tuple<int, int, long long>> residue;
    ans += dfs(k, residue, moduli);
  }

  printf("%lld\n", ans);
  return 0;
}
