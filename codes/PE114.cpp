#include <cmath>
#include <cassert>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MOD = 1000000007;

int m;

struct Matrix {
    int sz;
    vector < vector<LL> > a;
    
    Matrix(int n) {
        vector <LL> v;
        for (int i=0; i<n; i++) v.push_back(0);
        for (int i=0; i<n; i++) a.push_back(v);
        sz = n;
    }
    
    Matrix operator * (const Matrix &other) {
        Matrix ret(a.size());
        for (int i=0; i<sz; i++) {
            for (int j=0; j<sz; j++)
                for (int k=0; k<sz; k++)
                    ret.a[i][j] += a[i][k] * other.a[k][j],
                    ret.a[i][j] %= MOD;
        }
        
        return ret;
    }
    
    void print(int n) {
        for (int i=0; i<n; i++) {for (int j=0; j<n; j++) printf ("%lld ", a[i][j]); printf ("\n");}
    }
};

Matrix power (Matrix x, LL y) {
    Matrix ret(m+1);
    Matrix mul = x;
    
    for (int i=0; i<=m; i++) ret.a[i][i] = 1;
    while (y) {
        if (y & 1) ret = ret * mul;
        mul = mul * mul;
        y >>= 1;
    }
    
    return ret;
}

int main() {
    LL n;
    scanf ("%lld %d", &n, &m);
    
    assert (1 <= n && n <= 1000000000000000000LL);
    assert (1 <= m && m <= 70);
    
    Matrix mat(m+1);
    mat.a[0][0] += 2; mat.a[0][1] += MOD - 1; mat.a[0][m] += 1;
    for (int i=1; i<=m; i++) mat.a[i][i-1] = 1;
    
    // power(mat, n+1).print(m+1);
    
    mat = power(mat, n+1);
    
    printf ("%lld\n", (mat.a[0][0] - mat.a[1][0] + MOD) % MOD);
    
    return 0;
}
