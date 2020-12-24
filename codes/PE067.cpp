#include <cstring>
#include <cstdio>
#include <algorithm>

const int N = 100;
int n;
int a[N][N];

int dp[N][N];
int f(int x, int y) {
    if (x == n) return 0;
    if (~dp[x][y]) return dp[x][y];
    
    return dp[x][y] = a[x][y] + std::max(f(x+1, y), f(x+1, y+1));
}

int Main () {
    memset (dp, -1, sizeof dp);
        
    scanf ("%d", &n);
    for (int i=0; i<n; i++) {
        for (int j=0; j<=i; j++)
            scanf ("%d", &a[i][j]);
    }
    
    printf ("%d\n", f(0, 0));
    return 0;
}

int main() {
    int t;
    scanf ("%d", &t);
    while (t--) Main();
    return 0;
}
