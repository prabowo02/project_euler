#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MOD = 1000000;

vector<int> S(1);

int par[MOD], sz[MOD];
int dsu(int u) {
    if (u == par[u]) return u;
    return par[u] = dsu(par[u]);
}

int main() {
    for (int i=1; i<=55; ++i) S.push_back((300007LL*i*i*i + 100003 - 200003*i) % MOD);
    for (int i=56; i<=8834916*2; ++i) S.push_back((S[i-24] + S[i-55]) % MOD);
    
    int number, p;
    cin >> number >> p;
    
    for (int i=0; i<MOD; ++i) par[i] = i, sz[i] = 1;
    int i, cnt, misdialed = 0;
    for (i=1, cnt=1; sz[dsu(number)] * 100 < MOD * p; ++i) {
        int u = S[i*2-1];
        int v = S[i*2];
        if (u == v) ++misdialed;
        if (dsu(u) == dsu(v)) continue;
        sz[dsu(v)] += sz[dsu(u)];
        par[dsu(u)] = dsu(v);
    }
    
    cout << i - misdialed - 1 << endl;
    
    return 0;
}
