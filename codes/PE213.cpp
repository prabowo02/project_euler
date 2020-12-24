#include <bits/stdc++.h>
using namespace std;

const int N = 40;

const int MOD     = 1000000007;
const int HALF    =  500000004;
const int THIRD   =  333333336;
const int QUARTER =  250000002;

int n, m;
long long ans[N][N];

long long a[N][N];
long long na[N][N];

void reset(long long a[N][N], int val=0) {
    for (int i=0; i<n; i++) for (int j=0; j<n; j++) {
        a[i][j] = val;
    }
}

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};
void advance() {
    reset(na);
    
    // Corners
    na[1][0] += 1LL * a[0][0] * HALF;
    na[0][1] += 1LL * a[0][0] * HALF;
    
    na[n-1][n-2] += 1LL * a[n-1][n-1] * HALF;
    na[n-2][n-1] += 1LL * a[n-1][n-1] * HALF;
    
    na[0][n-2] += 1LL * a[0][n-1] * HALF;
    na[1][n-1] += 1LL * a[0][n-1] * HALF;
    
    na[n-1][1] += 1LL * a[n-1][0] * HALF;
    na[n-2][0] += 1LL * a[n-1][0] * HALF;
    
    // Edges
    for (int i=1; i<n-1; i++) {
        na[0][i-1] += 1LL * a[0][i] * THIRD;
        na[0][i+1] += 1LL * a[0][i] * THIRD;
        na[1][i] += 1LL * a[0][i] * THIRD;
        
        na[n-1][i-1] += 1LL * a[n-1][i] * THIRD;
        na[n-1][i+1] += 1LL * a[n-1][i] * THIRD;
        na[n-2][i] += 1LL * a[n-1][i] * THIRD;
        
        na[i-1][0] += 1LL * a[i][0] * THIRD;
        na[i+1][0] += 1LL * a[i][0] * THIRD;
        na[i][1] += 1LL * a[i][0] * THIRD;
        
        na[i-1][n-1] += 1LL * a[i][n-1] * THIRD;
        na[i+1][n-1] += 1LL * a[i][n-1] * THIRD;
        na[i][n-2] += 1LL * a[i][n-1] * THIRD;
    }
    
    // Centres
    for (int i=1; i<n-1; i++) for (int j=1; j<n-1; j++) {
        for (int k=0; k<4; k++) {
            na[i + dx[k]][j + dy[k]] += 1LL * a[i][j] * QUARTER;
        }
    }
    
    for (int i=0; i<n; i++) for (int j=0; j<n; j++) a[i][j] = na[i][j] % MOD;
}

int solve() {
    scanf("%d %d", &n, &m);
    
    reset(ans, 1);
    for (int i=0; i*2<n; i++) for (int j=0; j*2<n; j++) {
        reset(a);
        a[i][j] = 1;
        
        for (int k=0; k<m; k++) advance();
        
        for (int ii=0; ii<n; ii++) for (int jj=0; jj<n; jj++) a[ii][jj] = (MOD - a[ii][jj] + 1) % MOD;
        
        for (int ii=0; ii<n; ii++) for (int jj=0; jj<n; jj++) {
            ans[ii][jj] = ans[ii][jj] * a[ii][jj] % MOD 
                * a[n-ii-1][jj] % MOD 
                * a[ii][n-jj-1] % MOD
                * a[n-ii-1][n-jj-1] % MOD;
        }
    }
    
    long long res = 0;
    for (int i=0; i<n; i++) for (int j=0; j<n; j++) res += ans[i][j];
    
    printf("%lld\n", res % MOD);
    return 0;
}

int main() {
    int q;
    scanf("%d", &q);
    while (q--) solve();
    return 0;
}
