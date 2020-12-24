#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1001;
const int MOD = 1000000007;

int dp[N][N<<1];
int f(int n, int last) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (~dp[n][last]) return dp[n][last];
    
    return dp[n][last] = ((f(n-1, 1) - f(n-last-1, last+1) + f(n-1, last+1)) % MOD + MOD) % MOD;
}

int main() {
    memset(dp, -1, sizeof dp);
    int t;
    scanf ("%d", &t);
    while (t--) {
        int n;
        scanf ("%d", &n);
        printf ("%d\n", (f(n, n) - f(n-1, n+1) - 1 + MOD) % MOD);
    }
    return 0;
}
