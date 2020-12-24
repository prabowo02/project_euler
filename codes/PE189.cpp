#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int n, c;

int power[15];

int ****dp;
int g(int x, int y, int prv, int mask) {
    if (x == 0) return 1;
    if (y == x) return g(x-1, 0, 0, mask / c);
    if (~dp[x][y][prv][mask]) return dp[x][y][prv][mask];
    
    long long ret = 0;
    if (y & 1) {
        int rgt = mask / power[y] % c;
        for (int i=0; i<c; i++) {
            if (i == prv || i == rgt) continue;
            ret += g(x, y+1, i, mask - rgt*power[y] + i*power[y]);
        }
    } else {
        int rgt = mask / power[y] % c;
        for (int i=0; i<c; i++) {
            if (i == rgt) continue;
            ret += g(x, y+1, i, mask - rgt*power[y] + i*power[y]);
        }
    }
    
    return dp[x][y][prv][mask] = ret % MOD;
}

int f(int x, int mask = 0) {
    if (x == 0) {
        long long ret = g(n-1, 0, 0, mask / c);
        return ret * ret % MOD;
    }
    long long ret = 0;
    if (x & 1) {
        int prv = mask % c;
        for (int i=0; i<c; i++) ret += (prv != i || x == n ? f(x-1, mask*c + i) : 0);
    } else {
        for (int i=0; i<c; i++) ret += f(x-1, mask*c + i);
    }
    return ret % MOD;
}

int main() {
    scanf("%d %d", &n, &c);
    
    power[0] = 1;
    for (int i=1; i<=n; i++) power[i] = power[i-1] * c;
    
    dp = (int****) malloc(n * sizeof(int***));
    for (int i=0; i<n; i++) {
        dp[i] = (int***) malloc(i * sizeof(int**));
        for (int j=0; j<i; j++) {
            dp[i][j] = (int**) malloc(c * sizeof(int*));
            for (int k=0; k<c; k++) {
                dp[i][j][k] = (int*) malloc(power[i] * sizeof(int));
                for (int l=0; l<power[i]; l++) {
                    dp[i][j][k][l] = -1;
                }
            }
        }
    }
    
    printf("%d\n", f(n));
    return 0;
}
