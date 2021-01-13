#include <bits/stdc++.h>
using namespace std;

// Suppose angle at A is α
// Area of ABC = bc sin α
// Area of AEG = cb/(a+c) bc/(a+b) sin α (consequence of angle bisector theorem)
// ratio: (a+b)(a+c)/bc

// Therefore bc | (a+b)(a+c)
// In other words, (a + b)(a + c) - kbc = 0, for some integer k
// When k = 1, a(a + b + c) = 0, which is impossible since side length must be positive
// When k = 4, aa + ab + ac - 3bc = 0, and since a ≤ b ≤ c, it is only possible when a = b = c
// For k = 2 and 3, write k a^2 = ((k-1)b - a)((k-1)c - a), then factorize a^2

vector<vector<pair<int, int>>> pe;

void sieve(int n) {
  pe.resize(n + 1);
  for (int i = 2; i <= n; ++i) {
    if (pe[i].size() > 0) continue;
    for (int j = i; j < n; j += i) {
      int num = j, e = 0;
      do {
        ++e; num /= i;
      } while (num % i == 0);
      pe[j].emplace_back(i, e);
    }
  }
}

vector<long long> factors(vector<pair<int, int>> primeFactors) {
  vector<long long> ret = {1LL};
  for (pair<int, int> pe : primeFactors) {
    long long fact = 1;
    int sz = ret.size();
    for (int i = 0; i < pe.second; ++i) {
      fact *= pe.first;
      for (int j = 0; j < sz; ++j) {
        ret.push_back(ret[j] * fact);
      }
    }
  }
  return ret;
}

void factorization(int n) {
  clock_t t = clock();
  sieve(n / 3);
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;

  long long ans = n / 3;
  for (int k = 2; k <= 3; ++k) {
    for (int a = 1; a <= n / 3; ++a) {
      long long num = 1LL * k * a * a;
      vector<pair<int, int>> pfactors = pe[a];
      bool found = false;
      for (pair<int, int> &p : pfactors) {
        p.second *= 2;
        if (p.first == k) {
          ++p.second;
          found = true;
        }
      }
      if (!found) pfactors.emplace_back(k, 1);

      for (long long f : factors(pfactors)) {
        if ((f + a) % (k - 1) != 0) continue;
        if ((num/f + a) % (k - 1) != 0) continue;
        long long b = (f + a) / (k - 1);
        long long c = (num/f + a) / (k - 1);
        if (b > c) continue;
        if (a > b) continue;
        if (a + b <= c) continue;
        if (a + b + c > n) continue;

        assert(1LL * (a + b) * (a + c) == 1LL * k * b * c);
        ++ans;
      }
    }
  }

  printf("%lld\n", ans);
}

int gcd(int x, int y) {
  while (y) {
    int t = x;
    x = y;
    y = t % y;
  }
  return x;
}

void parameterization(int n) {
  clock_t t = clock();
  long long ans = n / 3;

  // From https://projecteuler.net/thread=257;page=3#184623
  // (a + b)(a + c) = 2bc
  // x = b/a, y = c/b
  // (1 + x)(1 + y) = 2xy
  // (0, -1) is solution, then use the line equation y = mx - 1
  // x = (m + 2) / m, y = m + 1
  // a = pq, b = pq + 2q^2, c = p^2 + pq; a + b > c ==> q > p/2, c + a > b ==> q < p
  // Primitive when (p, q) coprime and p odd

  // k = 2
  for (int p = 1; 3*p*p <= n; p += 2) {
    for (int q = p/2 + 1; q < p; ++q) {
      int perimeter = 3*p*q + 2*q*q + p*p;
      if (perimeter > n) break;

      // finding coprimes can still be optimized using stern-brocot
      if (gcd(p, q) == 1) ans += n / perimeter;
    }
  }

  // k = 3 can be done similarly, you will obtain
  // a = 2pq, b = pq + 3q^2, c = p^2 + pq
  // Primitive when (p, q) coprime, p not divisible by 3
  // If p and q have the same parity, solution is a/2, b/2, c/2

  // k = 3
  for (int p = 1; 4*p*p <= n*3; ++p) {
    if (p % 3 == 0) continue;
    for (int q = p/3 + 1; q < p; ++q) {
      int perimeter = 4*p*q + 3*q*q + p*p;
      if (perimeter > n * 2) break;
      if (p % 2 == q % 2) perimeter /= 2;
      if (perimeter <= n && gcd(p, q) == 1) ans += n / perimeter;
    }
  }
  printf("%lld\n", ans);
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
}

void brute(int n) {
  clock_t t = clock();
  int ans = 0;
  for (int a = 1; a <= n / 3; ++a) {
    for (int b = a; a + b + b <= n; ++b) {
      for (int c = b; a + b + c <= n; ++c) {
        if (1LL * (a + b) * (a + c) % (1LL * b * c) == 0) ++ans;
      }
    }
  }
  cout << ans << endl;
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
}

int main() {
  int n = 100000000; // perimeter
  scanf("%d", &n);

  // brute(n);
  // factorization(n);
  parameterization(n);
  return 0;
}
