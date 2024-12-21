#include <bits/stdc++.h>

const __int128 ONE = 1;
const int N = 10000000;
const long long MOD = 1234567891011LL;

int sieve[N];
int segment[N];

const int SZ = 2;
struct Matrix {
  long long a[SZ][SZ];
  
  Matrix(int val = 0) {
    for (int i = 0; i < SZ; ++i) {
      for (int j = 0; j < SZ; ++j) {
        a[i][j] = 0;
      }
      a[i][i] = val;
    }
  }
  
  Matrix operator * (const Matrix &other) {
    Matrix ret;
    for (int i = 0; i < SZ; ++i) {
      for (int j = 0; j < SZ; ++j) {
        for (int k = 0; k < SZ; ++k) {
          ret.a[i][j] = (ONE * a[i][k] * other.a[k][j] + ret.a[i][j]) % MOD;
        }
      }
    }
    return ret;
  }
};

Matrix power(Matrix A, long long y) {
  Matrix ret(1); 
  for (; y; y >>= 1) {
    if (y & 1) ret = ret * A;
    A = A * A;
  }
  return ret;
}

long long L = 100000000000000LL;
void init() {
  for (int i = 2; i < N; ++i) {
    if (sieve[i]) {
      continue;
    }
    for (int j = i * 2; j < N; j += i) {
      sieve[j] = 1;
    }
    for (long long j = L / i * i + (L % i == 0 ? 0 : i); j < L + N; j += i) {
      segment[j - L] = 1;
    }
  }
}

int main() {
  init();

  Matrix A;
  A.a[0][0] = A.a[1][0] = A.a[0][1] = 1;
  A = power(A, L - 1);

  long long fib0 = A.a[0][0], fib1 = A.a[1][0]; // L and L-1 th fibo
  long long ans = 0;
  long long p = L;
  for (int i = 0; i < 100000; ++i) {
    while (segment[p - L]) {
      ++p;
      long long fib = (fib0 + fib1) % MOD;
      fib1 = fib0;
      fib0 = fib;
    }

    ans = (ans + fib0) % MOD;
    ++p;
    long long fib = (fib0 + fib1) % MOD;
    fib1 = fib0;
    fib0 = fib;
  }

  printf("%lld\n", ans);
  return 0;
}
