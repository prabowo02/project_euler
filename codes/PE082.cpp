#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 1000;

int n;
int a[N][N];

LL dp[N][N][2][2];
LL f(int x, int y, bool up, bool down) {
    if (x < 0 || x >= n) return 1000000000000000000LL;
    if (y == n - 1) return a[x][y];
    if (~dp[x][y][up][down]) return dp[x][y][up][down];
    
    dp[x][y][up][down] = f(x, y + 1, 0, 0) + a[x][y];
    if (!up) dp[x][y][up][down] = min(dp[x][y][up][down], f(x - 1, y, 0, 1) + a[x][y]);
    if (!down) dp[x][y][up][down] = min(dp[x][y][up][down], f(x + 1, y, 1, 0) + a[x][y]);
    return dp[x][y][up][down];
}

int main() {
    scanf ("%d", &n);
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            scanf ("%d", &a[i][j]);
        
    memset (dp, -1, sizeof dp);
    LL ans = 1000000000000000000LL;
    for (int i=0; i<n; i++) ans = min(ans, f(i, 0, 0, 0));
    printf ("%lld\n", ans);
    return 0;
}
