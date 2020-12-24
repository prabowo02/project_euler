/*************
 * Use lagrangian multiplier to find x_i
 * x_i = (X/A * a_i)^a_i
 * Let P(x) = (X/A * i)^i for i from 1 to inf
 * Ans: [x^A] P(x)^m
 *************/

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define double long double

const int LN = 16;
const int N = 1 << LN;
const double PI = 3.1415926535897932384626433;
const int MOD = 1000000007;

struct complex {
  double re, im;
  complex(){}
  complex(double _re, double _im) : re(_re), im(_im){}
  complex operator + (const complex &a) const{ return complex(re + a.re, im + a.im); }
  complex operator - (const complex &a) const{ return complex(re - a.re, im - a.im); }
  complex operator * (const complex &a) const{ return complex(re * a.re - im * a.im, re * a.im + im * a.re); }
  complex operator / (const double &a) const{ return complex(re / a, im / a); }
  complex operator * (const double &a) const{ return complex(re * a, im * a); }
  complex conjugate() const{ return complex(re, -im); }
};

complex w[2][20][N << 1];

int bitrev[N << 1];
void prepare_fft() {
    for (int len = 2; len <= N << 1; len <<= 1) {
        double ang = 2.0 * PI / len;
        
        complex W(1, 0); complex V(1, 0);
        complex wlen(cos(ang), sin(ang));
        complex vlen(cos(-ang), sin(-ang));
        
        for (int j=0; j<len/2; j++) {
            w[0][__builtin_ctz(len)][j] = W;
            W = W * wlen;
            
            w[1][__builtin_ctz(len)][j] = V;
            V = V * vlen;
        }
    }
    
    for (int i=0; i<N<<1; i++) bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << LN);
}

void fft(complex a[], bool invert){
    int n = N << 1;
  for(int i = 0; i < n; i++) if (i < bitrev[i]) swap(a[i], a[bitrev[i]]);
    
  for(int len = 2; len <= n; len <<= 1){
    for(int i = 0; i < n; i += len){
      for(int j = 0; j < len >> 1; j++){
        complex u = a[i + j], v = a[i + j + len / 2] * w[invert][__builtin_ctz(len)][j];
        a[i + j] = u + v;
        a[i + j + len / 2] = u - v;
      }
    }
  }
  if(invert) for(int i = 0; i < n; i++) a[i] = a[i] / n;
}

double error = 0;
complex fa1[N << 1], fb1[N << 1], fa2[N << 1], fb2[N << 1];
void multiply(long long a[], long long b[], long long res[]){
  int n = N << 1;
    
    for (int i=0; i<N; i++) {
        fa1[i].re = a[i] & 65535; fa1[i].im = a[i] >> 16;
        fb1[i].re = b[i] & 65535; fb1[i].im = b[i] >> 16;
    }
    for (int i=N; i<n; i++) {
        fa1[i].re = 0; fa1[i].im = 0;
        fb1[i].re = 0; fb1[i].im = 0;
    }
    fft(fa1, false); fft(fb1, false);
    
    for (int i=0; i<n; i++) {
        complex a1 = (fa1[i] + fa1[(n-i) % n].conjugate()) / 2.0;
        complex a2 = (fa1[i] - fa1[(n-i) % n].conjugate()) * complex(0, -0.5);
        complex b1 = (fb1[i] + fb1[(n-i) % n].conjugate()) / 2.0;
        complex b2 = (fb1[i] - fb1[(n-i) % n].conjugate()) * complex(0, -0.5);
        
        fa2[i] = a1*b1 + complex(0, 1)*a2*b2;
        fb2[i] = a1*b2 + a2*b1;
    }
    fft(fa2, true); fft(fb2, true);
    
    for (int i=0; i<n; i++) {
        long long a = (long long) (fa2[i].re + 0.5) % MOD;
        long long b = (long long) (fb2[i].re + 0.5) % MOD;
        long long c = (long long) (fa2[i].im + 0.5) % MOD;
        
        res[i] = (a + (b << 16) + (c << 32)) % MOD;        
    }
}

// x and res must be different pointers
void power(long long x[], int y, long long res[]) {
    res[0] = 1; for (int i=1; i<N<<1; i++) res[i] = 0;
    for (; y; y >>= 1) {
        if (y & 1) multiply(res, x, res);
        multiply(x, x, x);
    }
}

int power(int x, int y) {
    int ret = 1;
    int mul = x;
    for (; y; y >>= 1) {
        if (y & 1) ret = 1LL * ret * mul % MOD;
        mul = 1LL * mul * mul % MOD;
    }
    
    return ret;
}

long long p[N << 1];
long long res[N << 1];

int main() { 
    prepare_fft();
    
    int x, a, m;
    scanf("%d %d %d", &x, &a, &m);
    
    int frac = 1LL * x * power(a, MOD - 2) % MOD;
    p[0] = 0;
    for (int i=1; i<=a; i++) {
        p[i] = power((int) (1LL * frac * i % MOD), i);
    }
    
    power(p, m, res);
    printf("%lld\n", res[a]);
    return 0;
}
