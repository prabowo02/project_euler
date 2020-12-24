#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 160;
const int MOD = 1000000007;

int dp[N+2][N+2][2][N+2];

int main() {
    for (int dn=0; dn<=N; ++dn) for (int dm=0; dm<=N; ++dm) dp[0][0][dn&1][dm] = 1;
    
    for (int dn=N; dn>=0; --dn) for (int n=dn; n<=N; ++n) for (int m=0; m<=N; ++m) for (int dm=m; dm>=0; --dm) {
        if (dn == 0 && dm == 0) continue;
        int sum = 0;
        sum += (m-dm < dm ? dp[n-dn][m-dm][dn+1&1][0] : dp[n-dn][m-dm][dn&1][dm]);
        sum += (dm == m ? dn == n ? 0 : dp[n][m][dn+1&1][0] : dp[n][m][dn&1][dm+1]);
        if (sum >= MOD) sum -= MOD;
        dp[n][m][dn&1][dm] = sum;
    }
    
    int q;
    scanf("%d", &q);
    while (q--) {
        int n, m;
        scanf("%d %d", &n, &m);
        printf("%d\n", m == 0 ? dp[n][m][1][0] : dp[n][m][0][1]);
    }
    return 0;
}
