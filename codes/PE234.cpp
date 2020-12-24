#include <bits/stdc++.h>
using namespace std;

const int S = 100000;
const int N = 100003000;
const int MOD = 1004535809;

bool isPrime(long long n) {
  for (int i = 2; 1LL*i*i <= n; ++i) {
    if (n % i == 0) return false;
  }

  return true;
}

bool sieve[S];
bool segmented[N];
int primes[S];
void segmented_sieve(int l, int r) {
  for (int i = 0; i*i <= r; ++i) sieve[i] = true;
  for (int i = l; i <= r; ++i) segmented[i-l] = true;

  int pcount = 0;
  for (int p = 2; p*p <= r; ++p) {
    if (!sieve[p]) continue;
    primes[pcount++] = p;
    for (int j = p*2; 1LL*j*j <= r; j += p) sieve[j] = false;

    // int st = (l <= p ? p+p : (l/p + (l%p != 0)) * p);
    // for (int j = st; j <= r; j += p) segmented[j-l] = false;
  }

  const int SEG_SIZE = 10000;
  for (int i = l; i <= r; i += SEG_SIZE) {
    for (int j = 0; j < pcount; ++j) {
      int p = primes[j];
      int st = (i <= p ? p+p : (i/p + (i%p != 0)) * p);
      for (int k = st; k < i + SEG_SIZE; k += p) segmented[k-l] = false;
    }
  }
}

int lps(long long n) {
  int sn = floor(sqrt(n));
  while (1LL * sn * sn > n) --sn;

  // while (!isPrime(sn)) --sn;
  segmented_sieve(sn - 1000, sn);
  int p = sn;
  while (!segmented[p - sn + 1000]) --p;

  return p;
}

int ups(long long n) {
  int sn = ceil(sqrt(n));
  while (1LL * sn * sn < n) ++sn;

  // while (!isPrime(sn)) ++sn;
  segmented_sieve(sn, sn + 1000);
  int p = sn;
  while (!segmented[p - sn]) ++p;

  return p;
}

// pl * p(l+1) + ... + pr
int arithmetic_sum(int p, int l, int r) {
  // cerr << "as: " << p << " " << l << " " << r << endl;
  return 1LL * (r+l) * (r-l+1) / 2 % MOD * p % MOD;
}

int solve(long long L, long long R) {
  int l = lps(L), r = ups(R);
  // cerr << "ps: " << l << " " << r << endl;

  segmented_sieve(l, r);

  long long ans = 0;
  int p = -1, q = -1;
  for (int i = l; i <= r; ++i) {
    if (!segmented[i-l]) continue;

    p = q; q = i;
    if (p == -1) continue;

    ans += arithmetic_sum(p, max(1LL+p, (L-1)/p + 1), min(1LL*q*q - 1, R) / p);
    ans += arithmetic_sum(q, max(1LL*p*p, L-1) / q + 1, min(-1LL+q, R/q));
    
    long long pq = 1LL * p * q;

    if (L <= pq && pq <= R) {
        ans -= 2LL * p * q % MOD;
    }
  }

  ans %= MOD;
  if (ans < 0) ans += MOD;
  return ans;
}

int main() {
  long long L, R;
  scanf("%lld %lld", &L, &R);

  clock_t t = clock();
  printf("%d\n", solve(L, R));
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}
