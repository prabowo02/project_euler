#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;

struct Matrix {
    long long a[2][2];
    
    Matrix(int _a = 0) {
        for (int i=0; i<2; i++) for (int j=0; j<2; j++) a[i][j] = 0;
        a[0][0] = a[1][1] = _a;
    }
    
    Matrix operator * (const Matrix &other) const {
        Matrix ret;
        for (int i=0; i<2; i++)
            for(int j=0; j<2; j++) {
                for(int k=0; k<2; k++)
                    ret.a[i][j] += a[i][k] * other.a[k][j];
            ret.a[i][j] %= MOD;
        }
        return ret;
    }
};

Matrix power(Matrix x, long long y) {
    Matrix ret(1), mul = x;
    for(; y; y >>= 1) {
        if (y & 1) ret = ret * mul;
        mul = mul * mul;
    }
    return ret;
}

int main() {
    int t;
    scanf ("%d", &t);
    
    long long n;
    while (t--) {
        scanf("%lld", &n);
        Matrix a;
        a.a[0][0] = a.a[0][1] = a.a[1][0] = 1;
        
        a = power(a, n * 2);
        printf("%lld\n", a.a[0][0] * a.a[0][1] % MOD);
    }
    return 0;
}
