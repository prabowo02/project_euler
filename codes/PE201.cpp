#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int s[101];

short dp[100][100][10001];
int f(int x, int y, int sum) {
    if (y == m) return sum == 0;
    if (x == n) return 0;
    if (sum < 0) return 0;
    if (~dp[x][y][sum]) return dp[x][y][sum];    
    
    return dp[x][y][sum] = min(2, f(x+1, y, sum) + f(x+1, y+1, sum - s[x]));
}

int main() {
    memset(dp, -1, sizeof dp);
    scanf("%d %d", &n, &m);
    for (int i=0; i<n; i++) scanf("%d", s + i);
    
    int ans = 0;
    for (int i=m; i<=100*m; i++) if (f(0, 0, i) == 1) {        
        ans += i;
    }
    printf("%d\n", ans);
        
    return 0;
}
