// Primes of the form n^2 + (n + 1)^2
// https://oeis.org/A027862

#include <bits/stdc++.h>

long long multiply(long long a, long long b, long long m) {
  return (__int128) a * b % m;
}

long long power(long long x, long long y, long long mod) {
  long long result = 1;
  long long multiplicator = x % mod;
  for (; y; y >>= 1) {
    if (y & 1) result = multiply(result, multiplicator, mod);
    multiplicator = multiply(multiplicator, multiplicator, mod);
  }
  
  return result;
}

std::vector<long long> A_Miller_Rabin = {2, 3, 5, 7, 11, 13, 17, 19, 23}; // N < 2^64
bool isPrime_deterministic(long long n) {
  if (!(n & 1)) return false;

  long long s = __builtin_ctzll(n-1), d = (n-1) >> s;

  for (long long a : A_Miller_Rabin) {
    long long x = power(a, d, n);
    if (x == 1 || x == n - 1) continue;
    for (long long j = 1; j < s; j++) {
      x = multiply(x, x, n);
      if (x == 1) return false;
      if (x == n - 1) break;
    }
    if (x != n - 1) return false;
  }
  return true;
}

const int SIEVE_N = 10000000;
bool is_prime[SIEVE_N];
void sieve() {
  for (int i = 3; i < SIEVE_N; i += 2) is_prime[i] = true;
  is_prime[2] = true;
  for (int p = 3; p < SIEVE_N; p += 2) {
    if (!is_prime[p]) continue;
    for (int i = p * 2; i < SIEVE_N; i += p) {
      is_prime[i] = false;
    }
  }
}

void solve(long long N) {
  sieve();
  int cnt = 0;
  for (long long n = 1; ; ++n) {
    long long p = n * n + (n + 1) * (n + 1);
    if (p >= N) break;

    if (p < SIEVE_N) {
      if (is_prime[p]) ++cnt;
    } else {
      if (isPrime_deterministic(p)) ++cnt;
    }
  }
  printf("%d\n", cnt);
}

const int SIEVE_P = 50000000;
long long s[SIEVE_P + 1];
void solve2(long long N) {
  for (int i = 1; i <= SIEVE_P; ++i) {
    s[i] = 1LL * i * i + 1LL * (i + 1) * (i + 1);
    if (s[i] > N) break;
  }
  int cnt = 0;
  for (int i = 1; i <= SIEVE_P; ++i) {
    if (s[i] == 1LL * i * i + 1LL * (i + 1) * (i + 1)) {
      ++cnt;
    }
    if (s[i] > 1) {
      long long p = s[i];
      for (long long j = i; j <= SIEVE_P; j += p) {
        while (s[j] % p == 0) s[j] /= p;
      }
      for (long long j = p - i - 1; j <= SIEVE_P; j += p) {
        while (s[j] % p == 0) s[j] /= p;
      }
    }
  }
  printf("%d\n", cnt);
}

int main() {
  long long N = 5000000000000000LL;
  // solve(N);
  solve2(N);
  return 0;
}
