#include<bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int FIVE = 400000003;

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

Matrix a;

long long getPrefix(long long n) {
    Matrix A = power(a, n + 1 & ~1);
    Matrix B = power(a, n & ~1);
    
    long long one = ((A.a[0][0]*7 + A.a[0][1]*8)*2 - (A.a[1][0]*7 + A.a[1][1]*8)*3 - 7*2 + 8*3) % MOD * FIVE;
    long long two = ((B.a[0][0]*17+ B.a[0][1]*8)*2 - (B.a[1][0]*17+ B.a[1][1]*8)*3 - 17*2 + 8*3) % MOD * FIVE;
    
    one -= (n + 1 >> 1) * 7; one %= MOD; one *= FIVE;
    two -= (n >> 1) * 7; two %= MOD; two *= FIVE;
    
    return ((one + two) % MOD + MOD) % MOD;
}

int main() {
    a.a[0][0] = 3; a.a[0][1] = -1;
    a.a[1][0] = 1; a.a[1][1] = 0;
    
    int t;
    scanf("%d", &t);
    long long L, R;
    while (t--) {
        scanf("%lld %lld", &L, &R);
        printf("%lld\n", (getPrefix(R+1) - getPrefix(L) + MOD) % MOD);
    }
    
    return 0;
}
