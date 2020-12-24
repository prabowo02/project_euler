#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;
const int N = 60005;

int dp[N];
int p(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (~dp[n]) return dp[n];
    
    int ret = 0;
    for (int i=1;; i++) {
        int m = i + 1 >> 1;
        if (i & 1); else m *= -1;
        
        if (m * (3 * m - 1) >> 1 > n) break;
        
        int neg = -1;
        if (__builtin_popcount(i & 3) & 1) neg = 1;
        
        ret += neg * p(n - (m * (3 * m - 1) >> 1));
        ret %= MOD;
    }
    
    return dp[n] = ret;
}

int main() {
    int t;
    scanf ("%d", &t);
    memset (dp, -1, sizeof dp);
    while (t--) {
        int n;
        scanf ("%d", &n);
        printf ("%d\n", (p(n) + MOD) % MOD);
    }
    return 0;
}
