#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int m;
double S[5];
bool vis[30000];

void solve (int mask) {    
    if (__builtin_popcount(mask) == 1) {
        int idx = __builtin_ctz(mask);
        if (fabs(S[idx] - round(S[idx])) < 1e-7 && S[idx] > 0)            
            vis[(int) (S[idx] + 0.5)] = 1;      
        return;
    }
    
    for (int i=0; i<m; i++) {
        if (mask >> i & 1)
            for (int j=i+1; j<m; j++)
                if (mask >> j & 1) {
                    double tmp = S[i];
            
                    S[i] = tmp + S[j];
                    solve (mask & ~(1 << j));
          S[i] = tmp - S[j];
                    solve (mask & ~(1 << j));
                    S[i] = S[j] - tmp;
                    solve (mask & ~(1 << j));
          S[i] = tmp * S[j];
                    solve (mask & ~(1 << j));
          S[i] = tmp / S[j];
                    solve (mask & ~(1 << j));
          S[i] = S[j] / tmp;
                    solve (mask & ~(1 << j));
            
                    S[i] = tmp;
                }
    }
}

int main() {
    scanf ("%d", &m);
    for (int i=0; i<m; i++) scanf ("%lf", S + i);
    
    solve ((1 << m) - 1);
    
    int mex = 1;
    while (vis[mex++]);
    printf ("%d\n", mex - 2);
    return 0;
}
