#include <ctime>
#include <cassert>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

const int LN = 21;
const int N = 1 << LN;
const int MOD = 1012924417; // 2**21 * 483 + 1
const int PRIMITIVE_ROOT = 5;

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
    const int UNITY = power(PRIMITIVE_ROOT, MOD-1 >> __builtin_ctz(MOD-1));
    root[0] = 1;
    for (int i=1; i<N; i++) {
        root[i] = 1LL * UNITY * root[i-1] % MOD;
    }
}

int n; // length of polynom.
void fft(int a[], bool invert) {
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

void power(int p[], int n) {
    fft(p, false);
    for (int i=0; i<::n; i++) 
        p[i] = power(p[i], n);
    fft(p, true);
}

int p[N], q[N];

int Main() { 
    int np, sp, nc, sc;
    scanf("%d %d %d %d", &np, &sp, &nc, &sc);

    n = 1 << 32 - __builtin_clz(np * sp);
    for (int i=0; i<n; i++) p[i] = 0;
    for (int i=1; i<=sp; i++) p[i] = 1;
    power(p, np);
    // for (int i=0; i<n; i++) cerr << p[i] << " "; cerr << endl;

    n = 1 << 32 - __builtin_clz(nc * sc);
    for (int i=0; i<n; i++) q[i] = 0;
    for (int i=1; i<=sc; i++) q[i] = 1;
    power(q, nc);
    // for (int i=0; i<n; i++) cerr << q[i] << " "; cerr << endl;

    long long res = 1LL * power(sp, np) * power(sc, nc) % MOD;
    res = power(res, MOD-2);

    long long pre = 0;
    long long sum = 0;
    for (int i=1; i<=np*sp; i++) {
        if (i-1 <= nc*sc) pre = (pre + q[i-1]) % MOD;
        sum = (pre * p[i] + sum) % MOD;
    }
    
    res = res * sum % MOD;
    printf("%lld\n", res);

    return 0;
}

int main() {
    init_fft();

    int q;
    scanf("%d", &q);
    while (q--) Main();

    return 0;
}
