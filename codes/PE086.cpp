#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int M = 400005;

LL cnt[M];

int main() {
    for (LL m = 2; m < 4000; m++) {
        for (LL n = 1; n < m && m*n*2 < M*2; n++) {
            if (m - n & 1); else continue;
            if (__gcd(m, n) > 1) continue;
            
            LL a = m*m - n*n;
            LL b = m*n*2;
            
            if (a >= M*2) continue;
            if (a > b) swap(a, b);
            
            for (int k=1; b*k < M*2; k++) {
                if (b * k < M) cnt[b * k] += a * k >> 1;
                if (a * k < M) cnt[a * k] += max((a*k*2 - b*k >> 1) + 1, 0LL);
            }
        }
    }
    
    for (int i=1; i<M; i++) cnt[i] += cnt[i-1];
    
    int t;
    scanf ("%d", &t);
    while (t--) {
        int m;
        scanf ("%d", &m);
        printf ("%lld\n", cnt[m]);
    }
    return 0;
}
