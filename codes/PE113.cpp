#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 100020;
const int MOD = 1000000007;

LL power (LL x, int y) {
    return y ? y & 1 ? x * power (x * x % MOD, y >> 1) % MOD : power(x * x % MOD, y >> 1) : 1;
}

LL fact[N], ifact[N];

LL C(int n, int k) {
    return fact[n] * ifact[k] % MOD * ifact[n-k] % MOD;
}

int main() {
    fact[0] = ifact[0] = 1;
    for (int i=1; i<N; i++) {
        fact[i] = fact[i-1] * i % MOD;
        ifact[i] = ifact[i-1] * power(i, MOD-2) % MOD;
    }
    
    int t;
    scanf ("%d", &t);
    while (t--) {
        int k;
        scanf ("%d", &k);
        printf ("%lld\n", (C(k + 9, 9) + C(k + 10, 10) - k * 10 - 2 + MOD) % MOD);
    }
    
    return 0;
}
