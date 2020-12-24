#include <cassert>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MOD = 1000000009;

const int sz = 61;
struct Matrix {
    LL a[sz][sz];
    
    Matrix (int x = 0) {
        for (int i=0; i<sz; i++)
            for (int j=0; j<sz; j++)
                a[i][j] = x * (i == j);
    }
    
    Matrix operator * (const Matrix &other) const {
        Matrix ret;
        for (int i=0; i<sz; i++)
            for (int j=0; j<sz; j++)
                for (int k=0; k<sz; k++)
                    ret.a[i][j] += a[i][k] * other.a[k][j],
                    ret.a[i][j] %= MOD;
            
        return ret;
    }
};

Matrix power(Matrix x, LL y) {
    return y ? y & 1 ? x * power(x * x, y >> 1) : power(x * x, y >> 1) : Matrix(1);
}

int main() {       
    
    LL n;
    scanf ("%lld", &n);
    
    Matrix mat;
    for (int i=1; i<=20; i++) {
        mat.a[1][i*1]++;
        mat.a[1][i*2]++;
        mat.a[1][i*3]++;
        
        mat.a[0][i*2]++;
    }        
    mat.a[1][25]++; mat.a[1][50]++;
    mat.a[0][50]++;
    
    for (int i=1; i<60; i++) mat.a[i+1][i]++;
    
    mat.a[0][0]++;
    
    mat = power(mat, n);
    
    printf ("%d\n", mat.a[0][1]);
    return 0;
}
