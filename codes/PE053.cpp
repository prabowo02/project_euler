#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 1005;

LL dp[N][N];

LL C(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (n == 0 && k == 0) return 1;
    if (~dp[n][k]) return dp[n][k];
    
    return dp[n][k] = min(C(n-1, k-1) + C(n-1, k), 1000000000000000001LL);
}

int main() {
    memset (dp, -1, sizeof dp);
    int n; LL k;
    scanf ("%d %lld", &n, &k);
    
    int ans = 0;
    for (int i=1; i<=n; i++) {
        int j;
        for (j=0; j<=i && C(i, j)<=k; j++);
        if (j <= i) ans += (i + 1) - 2 * j;
    }
    
    printf ("%d\n", ans);
    return 0;
}
