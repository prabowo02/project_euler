#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;

int dp[102][10][10][10];
int f(int m, int a, int b, int c) {
    if (a + b + c > 9) return 0;
    if (m == 0) return 1;
    
    if (~dp[m][a][b][c]) return dp[m][a][b][c];
    
    long long ret = 0;
    for (int i=0; i<10; i++) ret += f(m-1, b, c, i);
    return dp[m][a][b][c] = ret % MOD;
}

int main() {
    int m;
    scanf("%d", &m);
    memset(dp, -1, sizeof dp);
    printf("%d\n", (f(m, 0, 0, 0) - f(m-1, 0, 0, 0) + MOD) % MOD);
    return 0;
}
