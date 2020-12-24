#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 1000;

int a[N][N];

LL dp[N][N];
LL f(int x, int y) {
    if (x < 0 || y < 0) return 1000000000000000000LL;
    if (x == 0 && y == 0) return a[0][0];
    if (~dp[x][y]) return dp[x][y];
    
    return dp[x][y] = 1LL * a[x][y] + min(f(x-1, y), f(x, y-1));
}

int main() {
    int n;
    scanf ("%d", &n);
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            scanf ("%d", &a[i][j]);
        
    memset (dp, -1, sizeof dp);
    printf ("%lld\n", f(n-1, n-1));
    return 0;
}
