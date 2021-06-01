// x^3 = 1 (mod p^k) has 3 solutions if and only if p = 1 (mod 3) or (p = 3 and k ≥ 2).
// Other than that, it only has one solution

// This is because phi(p^k) is not divisible by 3 if p = 2 mod 3
#include <cstdio>

const int N = 7000000;

bool isPrime[N];
int primes[N], cntPrime;
void sieve() {
  cntPrime = 0;
  for (int i = 2; i < N; ++i) isPrime[i] = true;
  for (int i = 2; i < N; ++i) {
    if (!isPrime[i]) continue;
    primes[cntPrime++] = i;
    for (int j = i * 2; j < N; j += i) {
      isPrime[j] = false;
    }
  }
}

long long power(int x, int y) {
  long long ret = 1;
  while (y--) ret *= x;
  return ret;
}

const long long LIM = 1e11;
long long dfs(long long n, int x, int y) {
  if (n * power(primes[x], y) > LIM || n * primes[x] > LIM) return 0;
  long long ret = dfs(n, x + 1, y);
  if (primes[x] % 3 == 1) {
    if (y > 0) {
      for (long long p = primes[x]; n * p <= LIM; p *= primes[x]) {
        ret += dfs(n * p, x + 1, y - 1) + (y == 1 ? n * p : 0);
      }
    }
  } else if (primes[x] % 3 == 2) {
    for (long long p = primes[x]; n * p <= LIM; p *= primes[x]) {
      ret += dfs(n * p, x + 1, y) + (y == 0 ? n * p : 0);
    }
  } else {
    if (n * 3 <= LIM) ret += dfs(n * 3, x + 1, y) + (y == 0 ? n * 3 : 0);
    if (y > 0) for (long long p = 9; n * p <= LIM; p *= 3) {
      ret += dfs(n * p, x + 1, y - 1) + (y == 1 ? n * p : 0);
    }
  }
  return ret;
}

int main() {
  sieve();
  printf("%lld\n", dfs(1, 0, 5));
  return 0;
}
