#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 3400005;
int edge[N];
int color[N];
bool st[N];

void dfs (int u, int c) {    
    while (!color[u]) {
        color[u] = c;
        u = edge[u];
    }
    
    st[u] |= color[u] == c;
}

void find (int u, int &len, int &mini) {    
    do {
        len++;
        mini = min(mini, u);
        u = edge[u];
    } while (!st[u]);
}

int main() {
    int n;
    scanf ("%d", &n); n++;
    
    for (int i=1; i<n; i++) {
        for (int j=2*i; j<n; j+=i)
            edge[j] += i;
    }
    
    int c = 0;
    for (int i=2; i<n; i++) if (!color[i]) dfs(i, ++c);
    
    int maks = 0; int mini = 1000000000;
    for (int i=2; i<n; i++) if (st[i]) {
        int tMaks = 0;
        int tMini = 1000000000;
        
        find(i, tMaks, tMini);
        if (tMaks > maks) maks = tMaks, mini = tMini;
        else if (tMaks == maks && tMini < mini) mini = tMini;
    }
        
    printf ("%d\n", mini);
    
    return 0;
}
