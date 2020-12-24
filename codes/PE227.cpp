#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
const int MOD = 1000000009;

int n, m;

int power(int x, int y) {
    int ret = 1;
    for (; y; y >>= 1) {
        if (y & 1) ret = 1LL * ret * x % MOD;
        x = 1LL * x * x % MOD;
    }
    
    return ret;
}

int coeff[N][3];
int ans[N];

int main() {
    scanf("%d %d", &n, &m);
    
    n >>= 1;
    
    int det = 1LL * power(m, MOD-2) * power(m, MOD-2) % MOD;
    
    int two = det;
    int one = 2LL * (m-2) * det % MOD;
    int zero = (1LL * (m-2) * (m-2) + 2) * det % MOD;
    
    if (n == 1) {
        // f(1) = (1 + zero*f(1) + 2*one*f(0) +2*two*f(1))
        // f(1) (1 - zero - 2*two) = 1 + 2*one*f(0)
        
        det = power(((1LL - zero - 2LL * two) % MOD + MOD) % MOD, MOD-2);
        
        printf("%d\n", det);
        return 0;
    }
    
    det = power((1-zero + MOD) % MOD, MOD-2);
    coeff[n][0] = 2LL * one * det % MOD;
    coeff[n][1] = 2LL * two * det % MOD;
    coeff[n][2] = det;
    
    det = power((1 - (
        1LL * zero + 
        1LL * one * coeff[n][0] + 
        (n > 2 ? 1LL * two : 2LL * two)
    ) % MOD + MOD) % MOD, MOD - 2);
    coeff[n-1][0] = (1LL * one + 1LL * one * coeff[n][1]) % MOD * det % MOD;
    coeff[n-1][1] = (1LL * two * det) % MOD;
    coeff[n-1][2] = (1LL + 1LL * one * coeff[n][2] % MOD) * det % MOD;
    
    for (int i=n-2; i>0; --i) {
        int x0 = (
            1LL * zero + 
            1LL * one * coeff[i+1][0] % MOD + 
            1LL * two * coeff[i+2][1] % MOD +
            1LL * two * coeff[i+2][0] % MOD * coeff[i+1][0] % MOD
        ) % MOD;
        
        int x1 = (
            1LL * one + 
            1LL * one * coeff[i+1][1] % MOD + 
            1LL * two * coeff[i+2][0] % MOD * coeff[i+1][1] % MOD
        ) % MOD;
        
        int x2 = (
            1LL * two
        ) % MOD;
        
        int c = (
            1LL + 
            1LL * one * coeff[i+1][2] % MOD +
            1LL * two * coeff[i+2][2] % MOD +
            1LL * two * coeff[i+2][0] % MOD * coeff[i+1][2] % MOD
        ) % MOD;
        
        if (i == 1) {
            x0 = (x0 + x2) % MOD;
            x2 = 0;
        }
        
        int det = power((1 -x0 + MOD) % MOD, MOD-2);
        
        coeff[i][0] = 1LL * x1 * det % MOD;
        coeff[i][1] = 1LL * x2 * det % MOD;
        coeff[i][2] = 1LL * c * det % MOD;
    }
    
    ans[0] = 0;
    ans[1] = coeff[1][2];
    
    for (int i=2; i<=n; i++) {
        ans[i] = (
            1LL * coeff[i][0] * ans[i-1] +
            1LL * coeff[i][1] * ans[i-2] +
            coeff[i][2]
        ) % MOD;
    }
    
    printf("%d\n", ans[n]);
    
    return 0;
}
