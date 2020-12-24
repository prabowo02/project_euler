#include <bits/stdc++.h>
using namespace std;

/*
Usage Example:
```
int a[n], b[n], c[n];
fft(n, a, false); fft(n, b, false);
for (int i=0; i<n; i++) c[i] = a[i]*b[i];
fft(n, c, true);
```
*/
namespace FFT {

/* ----- Adjust the constants here ----- */
const int LN = 21;
const int N = 1 << LN;

// `MOD` must be of the form 2**`LN` * k + 1, where k odd.
const int MOD = 1004535809; // 2**21 * 479 + 1.
const int PRIMITIVE_ROOT = 3; // Primitive root modulo `MOD`.
/* ----- End of constants ----- */

int root[N];

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  return ret;
}

void init_fft() {
  const int UNITY = power(PRIMITIVE_ROOT, MOD-1 >> LN);
  root[0] = 1;
  for (int i=1; i<N; i++) {
    root[i] = 1LL * UNITY * root[i-1] % MOD;
  }
}

// n is the length of polynom
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

}

const int N = 1299710;
int phi[N]; int chain[N];
vector<int> primes;

const int len = 1 << 17;
const int MAXK = 50000;
int poly[len], mul[len], mul2[len];

// A(x) ^= k.
void power(int a[], int k, int max_degree) {
  int len = 1 << 32 - __builtin_clz(max_degree * 2);
  
  for (int i=len>>1; i<len; i++) a[i] = 0;
  FFT::fft(len, a, false);
  
  int res[len];
  for (int i=0; i<len; i++) res[i] = 0; res[0] = 1;
  FFT::fft(len, res, false);
  
  for (; k; k >>= 1) {
    if (k & 1) {
      for (int i=0; i<len; i++) res[i] = 1LL * res[i] * a[i] % FFT::MOD;
      FFT::fft(len, res, true);
      for (int i=len>>1; i<len; i++) res[i] = 0;
      if (k != 1) FFT::fft(len, res, false);
    }
    
    if (k != 1) {
      for (int i=0; i<len; i++) a[i] = 1LL * a[i] * a[i] % FFT::MOD;
      FFT::fft(len, a, true);
      for (int i=len>>1; i<len; i++) a[i] = 0;
      FFT::fft(len, a, false);
    }
  }
  
  for (int i=0; i<len; i++) a[i] = res[i];
}

void init() {
  FFT::init_fft();
  
  for (int i=1; i<N; i++) phi[i] = i;
  for (int i=2; i<N; i++) {
    if (phi[i] != i) continue;
    primes.push_back(i);
    for (int j=i; j<N; j+=i) phi[j] = phi[j] / i * (i-1);
  }
  
  chain[1] = 1;
  for (int i=2; i<N; i++) chain[i] = 1 + chain[phi[i]];
}

int solve() {
  init();

  int n, a, q;
  scanf("%d %d %d", &n, &a, &q);
  
  vector<int> cnt(21, 0);
  for (int i=1; i<n; i++) {
    ++cnt[chain[primes[i]] - 2];
  }
  
  
  for (int i=1; i<len; i++) poly[i] = 0;
  poly[0] = 1;
  
  FFT::fft(len, poly, false);
  
  for (int i=1; i<cnt.size(); i++) {
    if (cnt[i] == 0) continue;
    
    for (int j=0; j<len; j++) mul[j] = 0;
    for (int j=0; j<=a; j++) mul[j] = 1;
    
    power(mul, cnt[i], MAXK / i);
    
    for (int j=0; j<len; j++) mul2[j] = 0;
    for (int j=0; j*i <= MAXK; j++) mul2[j*i] = mul[j];
  
    // cerr << i << " " << cnt[i] << endl;
    // for (int i=0; i<10; i++) cerr << mul2[i] << " "; cerr << endl;
    
    FFT::fft(len, mul2, false);
    for (int i=0; i<len; i++) poly[i] = 1LL * poly[i] * mul2[i] % FFT::MOD;
    FFT::fft(len, poly, true);
    for (int i=len>>1; i<len; i++) poly[i] = 0;
    FFT::fft(len, poly, false);
  }
  
  {
    for (int j=0; j<len; j++) mul[j] = 0;
    ++mul[0];
    for (int j=0; j<a; j++) ++mul[j];
    
    FFT::fft(len, mul, false);
    for (int i=0; i<len; i++) poly[i] = 1LL * poly[i] * mul[i] % FFT::MOD;
    FFT::fft(len, poly, true);
  }
  
  // for (int i=0; i<10; i++) cerr << poly[i] << " "; cerr << endl;
  
  while (q--) {
    int k;
    scanf("%d", &k);
    
    if (k == 1 || k == 2) printf("1\n");
    else printf("%d\n", poly[k-2]);
  }

  return 0;
}

int main() {
  clock_t t = clock();
  solve();
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}
