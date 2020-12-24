#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

const int N = 1000005;
const int MOD = 1000000007;

LL power (LL x, int y) {
    LL ret = 1;
    LL mul = x;
    while (y) {
        if (y & 1) ret = (ret * mul) % MOD;
        
        mul = (mul * mul) % MOD;
        y >>= 1;
    }
    
    return ret;
}

LL fact[N];
LL ifact[N];
LL inv[N];

LL C(int n, int k) {
    return fact[n] * ifact[k] % MOD * ifact[n-k] % MOD;
}

int main() {
    
    fact[0] = ifact[0] = 1;
    for (int i=1; i<N; i++) {
        fact[i] = i * fact[i-1] % MOD;
        inv[i] = power(i, MOD-2);
        ifact[i] = inv[i] * ifact[i-1] % MOD;        
    }
    
    int t;
    scanf ("%d", &t);
    while (t--) {
        int n;
        scanf ("%d", &n);
        
        LL sum = 0;
        for (int r = 2; 2 * r <= n; r++) {
            sum += C(n, 2*r) * C(2*r, r) % MOD * (r-1) % MOD * inv[2*(r+1)];
            sum %= MOD;
        }
        
        printf ("%lld\n", sum);
    }
    return 0;
}
