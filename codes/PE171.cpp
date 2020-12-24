#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MOD = 1000000007;

string S;
int n;
int s[102];
int dp[102][2][8102];
int ten[102];

bool isSquare[8102];

int f(int x, bool y, int sum) {
    if (x == n) return (isSquare[sum] ? 1 : 0);
    if (~dp[x][y][sum]) return dp[x][y][sum];
    
    long long ret = 0;
    for (int i=0; i<(y ? 10 : s[x]+1); i++) {        
        ret += f(x+1, y | (i < s[x]), sum + i*i);    
    }
    
    return dp[x][y][sum] = ret % MOD;
}

int dp2[102][2][8202];
int g(int x, int y, int sum) {
    if (x == n) return 0;
    if (~dp2[x][y][sum]) return dp2[x][y][sum];
    
    long long ret = 0;
    for (int i=0; i<(y ? 10 : s[x] + 1); i++) {
        ret += 1LL * i * ten[x] % MOD * f(x+1, y | (i < s[x]), sum + i*i) % MOD + g(x+1, y | (i < s[x]), sum + i*i);
    }
    
    return dp2[x][y][sum] = ret % MOD;
}

int main() {
    memset(dp, -1, sizeof dp);
    memset(dp2, -1, sizeof dp2);
    
    for (int i=0; i<=90; i++) isSquare[i*i] = 1;
    
    cin >> S;
    n = S.size();
    for (int i=0; i<n; i++) s[i] = S[i] - '0';
    
    ten[n-1] = 1;
    for (int i=n-2; i>=0; i--) ten[i] = 1LL * ten[i+1] * 10 % MOD;
    
    cout << g(0, 0, 0) << endl;
    
    return 0;
}
