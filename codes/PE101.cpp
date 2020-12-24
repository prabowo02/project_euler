#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 3003;
const int MOD = 1000000007;

int power (int x, int y) {
    return y ? y & 1 ? 1LL * x * power(1LL * x * x % MOD, y >> 1) % MOD : power(1LL * x * x % MOD, y >> 1) : 1;
}

vector <int> X, Y;
int fact[N], ifact[N];

int l (int j, int x) {    
    return 1LL * fact[x] * ifact[j] % MOD * ifact[X.size() - 1 - j] % MOD * power(x - j, MOD - 2) % MOD * (X.size() - 1 - j & 1 ? -1 : 1);    
}

int L(int x) {
    int ret = 0;
    for (int i=0; i<X.size(); i++) {
        ret = (1LL * Y[i] * l(i, x) + ret) % MOD;
    }
    
    return ret < 0 ? ret + MOD : ret;
}

int main() {
    int n;
    scanf ("%d", &n);
    
    int a[N];
    for (int i=0; i<=n; i++) scanf ("%d", a + i);
    
    fact[0] = ifact[0] = 1;
    for (int i=1; i<N; i++) {
        fact[i] = 1LL * fact[i-1] * i % MOD;
        ifact[i] = 1LL * ifact[i-1] * power(i, MOD-2) % MOD;
    }
    
    for (int i=0; i<n; i++) {
        int sum = 0;
        for (int j=0; j<=n; j++) {
            sum = (1LL * a[j] * power(i+1, j) + sum) % MOD;
        }
        Y.push_back(sum);
    }
    
    for (int i=0; i<n; i++) {
        X.push_back(i);
        printf ("%d ", L(i+1));
    }
    return 0;
}
