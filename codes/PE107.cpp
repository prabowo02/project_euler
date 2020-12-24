#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 3000;

int n, m;
int par[N];

struct Edge {
    int u, v, w;
    bool operator < (const Edge &other) {
        return w < other.w;
    }
} edge[N * (N - 1) >> 1];

int dsu(int u) {
    if (u == par[u]) return u;
    return par[u] = dsu(par[u]);
}

int main() {
    scanf ("%d %d", &n, &m);
    for (int i=0; i<n; i++) par[i] = i;
    
    for (int i=0; i<m; i++) {
        scanf ("%d %d %d", &edge[i].u, &edge[i].v, &edge[i].w);
        edge[i].u--, edge[i].v--;
    }
    
    sort (edge, edge + m);
    
    int sum = 0;
    for (int i=0; i<m; i++) {
        if (dsu(edge[i].u) == dsu(edge[i].v)) continue;
        
        par[dsu(edge[i].u)] = dsu(edge[i].v);
        sum += edge[i].w;
        
        if (--n == 0) break;
    }
    
    return 0 * printf ("%d\n", sum);
}
