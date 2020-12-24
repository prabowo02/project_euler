/******
 * Suppose P_k(x) is the k-th derivative of P(x) (i.e. P_0(x) = P(x))
 * Suppose F_k(x) is the k-th anti derivative of f(x) (i.e. F_0(x) = f(x))
 * 
 * Using integration by parts: int P_k(x) F_k(x) = [P_k(x) F_{k+1}(x)]_0^1 - int P_{k+1}(x) F_{k+1}(x)
 * Therefore int P(x) f(x) = [P_0(x) F_1(x)] - [P_1(x) F_2(x)] + [P_2(x) F_3(x)] - ...
 * P_k(0) is easy: k! * a_k
 * To compute P_k(1), first compute Q(x) = P(x+1), then compute Q_k(0)
 * (works because dP(x+1)/d(x+1) = dP(x+1)/dx * dx/d(x+1)
 *
 * Computing F_k(x) is tricky. First, d(r^n x) / s^n x = [d(r^n x)/s^n - 1/(4s^n)] + 1/(4s^n).
 * We got a sinusoidal-like wave plus a constant. Therefore F_k(1) = 1/(4^(k+1) k!) s / (s-1) + F_k(0)
 * F_k(0) is 0 when k is odd, negative when 0 (mod 4), positive otherwise.
 * I'm not sure how to properly write this, but suppose x_n = -(x_{n-2} / 2! + x_{n-4} / 4! + ... + x_0 / n! + 1/(n+1)!)
 * Then F_k(0) = x_k / 4^(k+1) * (sr^k) / (sr^k - 1)
 * x_k can be computed using generating function X = -X(cosh(x) - 1) - sinh(x)/x ==> X = -tanh(x)/x
 ***/

#pragma GCC diagnostic ignored "-Wshift-op-parentheses"

#include <bits/stdc++.h>
using namespace std;

const int M = 1 << 19;
const int MOD = 1004535809;

int r, s, m;
int a[M];

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }

  return ret;
}

namespace FFT {

const int LN = 21;
const int N = 1 << LN;

const int MOD = 1004535809;
const int PRIMITIVE_ROOT = 3;

int root[N];

void init_fft() {
  const int UNITY = power(PRIMITIVE_ROOT, MOD-1 >> LN);
  root[0] = 1;
  for (int i=1; i<N; i++) {
    root[i] = 1LL * UNITY * root[i-1] % MOD;
  }
}

// n = 2^k is the length of polynom
void fft(int n, int a[], bool invert) {
  for (int i=1, j=0; i<n; ++i) {
    int bit = n >> 1;
    for (; j>=bit; bit>>=1) j -= bit;
    j += bit;
    if (i < j) swap(a[i], a[j]);
  }

  for (int len=2; len<=n; len<<=1) {
    int wlen = (invert ? root[N - N/len] : root[N/len]);
    for (int i=0; i<n; i+=len) {
      int w = 1;
      for (int j=0; j<len>>1; j++) {
        int u = a[i+j];
        int v = 1LL * a[i+j + len/2] * w % MOD;

        a[i+j] = (u + v) % MOD;
        a[i+j + len/2] = (u - v + MOD) % MOD;

        w = 1LL * w * wlen % MOD;
      }
    }
  }

  if (invert) {
    int inv = power(n, MOD-2);
    for (int i=0; i<n; i++) a[i] = 1LL * a[i] * inv % MOD;
  }
}

int ret[N];
int a_mod[N];
int tmp_ret[N];
void inverse(int n, int a[]) {
  ret[0] = power(a[0], MOD-2);
  a_mod[0] = a[0];

  for (int len = 2; len <= n; len *= 2) {
    for (int i = len; i < len*2; ++i) ret[i] = a_mod[i] = 0;
    for (int i = 0; i < len; ++i) {
      a_mod[i] = a[i];
    }

    for (int i = 0; i < len; ++i) tmp_ret[i] = ret[i];

    fft(len*2, ret, false);
    for (int i = 0; i < len*2; ++i) ret[i] = 1LL * ret[i] * ret[i] % MOD;
    fft(len*2, ret, true);

    for (int i = len; i < len*2; ++i) ret[i] = 0;

    fft(len*2, ret, false); fft(len*2, a_mod, false);
    for (int i = 0; i < len*2; ++i) ret[i] = 1LL * ret[i] * a_mod[i] % MOD;
    fft(len*2, ret, true);

    for (int i = 0; i < len; ++i) {
      ret[i] = (2LL * tmp_ret[i] - ret[i] + MOD) % MOD;
    }
  }

  for (int i = 0; i < n; ++i) a[i] = ret[i];
}

}

int inv(int x) {
  return power(x, MOD-2);
}

int fact[M];
int ifact[M];
void init() {
  FFT::init_fft();

  fact[0] = 1;
  for (int i = 1; i < M; ++i) fact[i] = 1LL * fact[i-1] * i % MOD;
  ifact[M-1] = inv(fact[M-1]);
  for (int i = M-2; i >= 0; --i) ifact[i] = 1LL * ifact[i+1] * (i+1) % MOD;
}


// P(x) = -P(x) * (cosh(x) - 1) - sinh(x)/x
// P(x)(cosh(x)) = -sinh(x)/x
// P(x) = -tanh(x) / x

int sinhx[M], coshx[M];
int f0[M];
void precompF0(int m) {
  // The O(N^2)
  // for (int i = 0; i <= m; i += 2) {
  //   f0[i] = 1LL * ifact[i+1] % MOD;
  //   for (int j = i-2; j >= 0; j -= 2) {
  //     f0[i] = (1LL * ifact[i-j] * f0[j] % MOD + f0[i]) % MOD;
  //   }
  //   f0[i] = (MOD - f0[i]) % MOD;
  // }

  // for (int i = 0; i <= m; i += 2) {
  //   int srk = 1LL * s * power(r, i) % MOD;
  //   f0[i] = 1LL * f0[i] * inv(power(4, i+1)) % MOD * srk % MOD * inv(srk - 1) % MOD;
  // }
  // return;

  int len = 1 << 32 - __builtin_clz(m+1);

  for (int i = 0; i < len; i += 2) {
    // -sinh(x)/x
    sinhx[i] = (MOD - ifact[i+1]);

    // cosh(x)
    coshx[i] = ifact[i];
  }

  FFT::inverse(len, coshx);

  FFT::fft(len*2, sinhx, false); FFT::fft(len*2, coshx, false);
  for (int i = 0; i < len*2; ++i) {
    f0[i] = 1LL * sinhx[i] * coshx[i] % MOD;
  }
  FFT::fft(len*2, f0, true);

  for (int i = 0; i <= m; i += 2) {
    int srk = 1LL * s * power(r, i) % MOD;
    f0[i] = 1LL * f0[i] * inv(power(4, i+1)) % MOD * srk % MOD * inv(srk - 1) % MOD;
  }
}

// P(x) -> P(x+1)

int p[1 << 20];
int binom[1 << 20];
int tp[1 << 20];
void precompP0(int m) {
  int n = 1 << 32 - __builtin_clz(m+1);
  for (int i = 0; i < n; ++i) p[i] = a[i];

  for (int len = 1; len < n; len <<= 1) {
    for (int i = 0; i <= len; ++i) {
      binom[i] = 1LL * fact[len] * ifact[i] % MOD * ifact[len-i] % MOD;
    }
    for (int i = len+1; i < len<<1; ++i) binom[i] = 0;
    FFT::fft(len*2, binom, false);

    for (int i = len; i < n; i += len << 1) {
      for (int j = 0; j < len; ++j) {
        tp[j] = p[i+j];
      }
      for (int j = len; j < len<<1; ++j) {
        tp[j] = 0;
      }

      FFT::fft(len*2, tp, false);
      for (int j = 0; j < len*2; ++j) tp[j] = 1LL * tp[j] * binom[j] % MOD;
      FFT::fft(len*2, tp, true);

      for (int j = 0; j < len; ++j) {
        p[i-len+j] = (p[i-len+j] + tp[j]) % MOD;
        p[i+j] = tp[j+len];
      }
    }
  }
}

int F0(int k) {
  return f0[k];
}

int F1(int k) {
  int ret = 1LL * s * inv(4LL * (s-1) % MOD) % MOD * ifact[k] % MOD;
  return (ret + F0(k)) % MOD;
}

int P1(int k) {
  // int ret = 0;
  // for (int i = k; i <= m; ++i) {
  //   ret = (1LL * fact[i] * ifact[i-k] % MOD * a[i] % MOD + ret) % MOD;
  // }
  // return ret;

  return 1LL * fact[k] * p[k] % MOD;
}

int P0(int k) {
  return 1LL * fact[k] * a[k] % MOD;
}

void solve() {
  precompF0(m);
  precompP0(m);

  long long ans = 0;
  for (int i = 0; i <= m; ++i) {
    int term = (1LL * P1(i) * F1(i+1) - 1LL * P0(i) * F0(i+1)) % MOD;
    
    if (i & 1) ans -= term;
    else ans += term;
  }

  ans %= MOD;
  if (ans < 0) ans += MOD;
  printf("%lld\n", ans);
}

int main() {
  init();

  scanf("%d %d %d", &r, &s, &m);
  for (int i = 0; i <= m; ++i) {
    scanf("%d", &a[i]);
  }

  solve();
  return 0;
}
