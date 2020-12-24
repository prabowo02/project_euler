#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int nxt(int n) {
    int ret = 0;
    while (n) {
        ret += (n % 10) * (n % 10);
        n /= 10;
    }
    return ret;
}

bool happy (int n) {
    if (n == 1) return 1;
    if (n == 89) return 0;
    return happy(nxt(n));
}

const int K = 202;
const int MOD = 1000000007;

int dp[K][100000];
int f(int k, int sum) {
    if (k == 0) return sum == 0;
    if (~dp[k][sum]) return dp[k][sum];
    
    int &ret = dp[k][sum] = 0;
    for (int i=0; i<10; i++) {
        if (sum - i*i < 0) break;
        ret += f(k-1, sum - i*i);
        
        if (ret >= MOD) ret -= MOD;
    }
    
    return ret;
}

int main() {
    int k;
    scanf ("%d", &k);
    
    int tenK = 1;
    if (k < 5) for (int i=0; i<k; i++) tenK *= 10;    
    else tenK = 100000;
    
    memset (dp, -1, sizeof dp);
    int ans = 0;
    for (int i=1; i<tenK; i++) if (!happy(i)) {
        // cout << i << " " << f(k, i) << endl;
        ans += f(k, i) + (nxt(i) >= tenK);
        ans %= MOD;
    }
    printf ("%d\n", ans);
    return 0;
}
