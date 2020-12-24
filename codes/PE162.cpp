#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;

int dp[102][8];
int f(int x, int mask) {
    if (x == 0) return mask == 0;
    if (~dp[x][mask]) return dp[x][mask];
    
    long long ret = 0;
    ret += f(x-1, mask & ~1);
    ret += f(x-1, mask & ~2);
    ret += f(x-1, mask & ~4);
    ret += 13LL * f(x-1, mask);
    return dp[x][mask] = ret % MOD;
}

int main() {
    int n;
    scanf("%d", &n);
    
    memset(dp, -1, sizeof dp);
    long long ans = 0;
    for (int i=3; i<=n; i++) ans += f(i, 7) - f(i-1, 3);
    printf("%lld\n", (ans % MOD + MOD) % MOD);
    return 0;
}
