#include <cmath>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;

const long long MOD = 1000000007;
const double PI = 3.1415926535897932384626433;
const int N = 100005;
const long long K = 32768;

// (sum_{i=0} 1/i! * x^i)^10

#define double long double

struct complex {
  double re, im;
  complex(){}
  complex(double _re, double _im) : re(_re), im(_im){}
  complex operator + (const complex &a) const{ return complex(re + a.re, im + a.im); }
  complex operator - (const complex &a) const{ return complex(re - a.re, im - a.im); }
  complex operator * (const complex &a) const{ return complex(re * a.re - im * a.im, re * a.im + im * a.re); }
  complex operator / (const double &a) const{ return complex(re / a, im / a); }
  complex operator * (const double &a) const{ return complex(re * a, im * a); }
};

complex w[2][20][262144];

int bitrev[262144];
void prepare_fft() {
    for (int len = 2; len <= 262144; len <<= 1) {
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
    
    for (int i=0; i<262144; i++) bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << 17);
}

void fft(complex a[], bool invert){
    int n = 262144;
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

complex fa1[262144], fb1[262144], fa2[262144], fb2[262144];
complex tr1[262144], tr2[262144], tr3[262144], tr4[262144];
long long a1[262144], a2[262144], b1[262144], b2[262144], r2[262144], r3[262144], r4[262144];
void multiply_fft(long long res[]){ 
    int n = 262144;
    
  for(int i = 0; i < n; i++) {
        fa1[i].re = a1[i], fa1[i].im = 0;
        fa2[i].re = a2[i], fa2[i].im = 0;
        fb1[i].re = b1[i], fb1[i].im = 0;
        fb2[i].re = b2[i], fb2[i].im = 0;
    }
    
  fft(fa1, false); fft(fb1, false); fft(fa2, false); fft(fb2, false);
  for (int i=0; i<n; i++) {
        tr1[i] = fa1[i] * fb1[i];
        tr2[i] = fa1[i] * fb2[i];
        tr3[i] = fa2[i] * fb1[i];
        tr4[i] = fa2[i] * fb2[i];
    }
  fft(tr1, true); fft(tr2, true); fft(tr3, true); fft(tr4, true);
    
    for(int i = 0; i < n; i++) {
        res[i] = (long long) (tr1[i].re + 0.5) % MOD;
        r2[i] = (long long) (tr2[i].re + 0.5) % MOD;
        r3[i] = (long long) (tr3[i].re + 0.5) % MOD;
        r4[i] = (long long) (tr4[i].re + 0.5) % MOD;
        
        res[i] += (r2[i] + r3[i] << 15) % MOD;
        res[i] += r4[i] * 73741817 % MOD;
        res[i] %= MOD;
    }
}

void multiply(long long a[], long long b[], long long res[]){
  int n = 131072;

  for(int i = 0; i < n; i++){
    a1[i] = a[i] & 32767;
    a2[i] = a[i] >> 15;
    }
    
    for (int i=0; i<n; i++) {
    b1[i] = b[i] & 32767;
    b2[i] = b[i] >> 15;
  }
    
  multiply_fft(res);
}

int power(int x, int y) {
    long long ret = 1, mul = x;
    for (; y; y >>= 1) {
        if (y & 1) ret = ret * mul % MOD;
        mul = mul * mul % MOD;
    }
    return ret;
}

int fact[N];


int input() {
    char c = getchar();
    int res = 0;
    do {
        res = (res << 3) + (res << 1) + c - '0';
        c = getchar();
    } while (c >= '0' && c <= '9');
    
    return res;
}

long long gf[262144], a[262144], b[262144];

int main() {
    clock_t start = clock();

    int m, t;
    m = input(); t = input();
        
    fact[0] = 1;
    for (int i=1; i<N; i++) fact[i] = 1LL * fact[i-1] * i % MOD;
    
    gf[m] = power(fact[m], MOD-2);
    for (int i=m-1; i>=0; i--) gf[i] = 1LL * gf[i+1] * (i+1) % MOD;   
    
    prepare_fft();
    
    multiply(gf, gf, a);
    multiply(a, a, a);
    multiply(a, a, a);
    multiply(a, gf, b);
    multiply(b, gf, a);
    
    gf[m] = 0; multiply(b, gf, b);

    // print(a);
    
    int k;
    while (t--) {
        k = input();
        
        long long res = 1LL * a[k] * fact[k] % MOD;
        res -= 1LL * b[k-1] * fact[k-1] % MOD;
        
        printf("%lld\n", (res + MOD) % MOD);
    }
    
    cerr << (double) (clock() - start) / CLOCKS_PER_SEC << endl;
    
    return 0;
}
