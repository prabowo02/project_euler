#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 50000005;

int pre[N];
bool primes[N];

int main() {
    memset(primes, 1, sizeof primes);
    for (int i=2; i<N; i++) {
        if (primes[i]) {
            for (int j=i*2; j<N; j+=i) primes[j] = 0;
            pre[i] = 1;
        }
        pre[i] += pre[i-1];
    }
    
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        --n;
        
        long long ans = 0;
        for (int i=2; i*i<=n; i++) {
            if (!primes[i]) continue;
            ans += (pre[n/i] - pre[i-1]);
        }
        
        printf("%lld\n", ans);
    }
    return 0;
}
