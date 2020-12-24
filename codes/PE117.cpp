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
    Matrix ret(x.sz);
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
    int t;
    scanf ("%d", &t);
    while (t--) {
        LL n;
        scanf ("%lld", &n);
        
        Matrix c(4);
        c.a[0][0] = c.a[0][1] = c.a[0][2] = c.a[0][3] = 1;
        c.a[1][0] = c.a[2][1] = c.a[3][2] = 1;
        
        LL sum = power(c, n).a[0][0];  
        
        printf ("%lld\n", sum % MOD);
    }
    return 0;
}
