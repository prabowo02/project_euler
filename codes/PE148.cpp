#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;

int n, m;
int digs[2][25];

int dp[25][2][2];
int f(int x, bool lim1, bool lim2) {
    if (x < 0) return 1;
    if (~dp[x][lim1][lim2]) return dp[x][lim1][lim2];
    
    int ret = 0;
    for (int i=0; i <= (lim1 ? digs[0][x] : 6); ++i) {
        for (int j=0; j<=(lim2 ? digs[1][x] : 6); ++j) {
            if (i < j) break;
            ret += f(x-1, lim1 & (i == digs[0][x]), lim2 & (j == digs[1][x]));
            if (ret >= MOD) ret -= MOD;
        }
    }
    
    return dp[x][lim1][lim2] = ret;
}

int main() {
    int t;
    scanf("%d", &t);
    
    long long r, c;
    while (t--) {
        scanf("%lld %lld", &r, &c);
        --r, --c;
        
        if (r < 0 || c < 0) {
            printf("0\n");
            continue;
        }
        
        memset(digs, 0, sizeof digs);
        
        n = 0, m = 0;
        while (r) {
            digs[0][n++] = r % 7;
            r /= 7;
        }
        
        while (c) {
            digs[1][m++] = c % 7;
            c /= 7;
        }
        
        memset(dp, -1, sizeof dp);
        printf("%d\n", f(max(n, m) - 1, 1, 1));
    }
    return 0;
}
