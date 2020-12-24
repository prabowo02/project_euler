#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;

int power(int x, int y) {
    int ret = 1;
    int mul = x;
    
    for (; y; y >>= 1) {
        if (y & 1) ret = 1LL * ret * mul % MOD;
        mul = 1LL * mul * mul % MOD;
    }
    
    return ret;
}

map <vector<int>, int> dp;
int f(vector<int> u) {
    if (dp.find(u) != dp.end()) return dp[u];
    
    int sum = 0;
    for (int i=0; i<u.size(); i++) sum += u[i];
    int ret = (sum == 1 ? 1 : 0);
    
    int isum = power(sum, MOD - 2);
    
    for (int i=0; i<u.size(); i++) {
        if (u[i] == 0) continue;
        vector<int> v = u;
        v[i]--;
        for (int j=i+1; j<v.size(); j++) v[j]++;
        
        ret = (1LL * u[i] * isum % MOD * f(v) + ret) % MOD;
    }
    
    return dp[u] = ret;
}

int main() {
    int n;
    scanf("%d", &n);
    
    vector<int> v(n-1);
    for (int i=0; i<n-1; i++) v[i] = 1;
    f(v);
    
    for (map<vector<int>, int>::iterator it = dp.begin(); it != dp.end(); ++it) {
        printf("0");
        for (int i=0; i<it->first.size(); ++i) printf(" %d", it->first[i]);
        printf(": %d\n", it->second);
    }
    printf("1"); for (int i=1; i<n; i++) printf(" 0"); printf(": %d\n", (f(v) + 1) % MOD);
    return 0;
}
