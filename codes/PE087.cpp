#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10000005;

bool sieve[N];
vector <int> prime;

int cnt[N];

int main() {
    memset (sieve, 1, sizeof sieve);
    for (int i=2; i<N; i++) if (sieve[i]) {
        for (int j=2*i; j<N; j+=i) sieve[j] = 0;
        prime.push_back(i);
    }
    
    for (int u: prime) {
        if (u * u >= N) break;
        for (int v: prime) {
            if (u * u + v * v * v >= N) break;
            for (int w: prime) {
                if (u*u + v*v*v + w*w*w*w >= N) break;
                cnt[u*u + v*v*v + w*w*w*w] = 1;
            }
        }
    }
    
    for (int i=1; i<N; i++) cnt[i] += cnt[i-1];
    
    int t;
    scanf ("%d", &t);
    while (t--) {
        int n;
        scanf ("%d", &n);
        printf("%d\n", cnt[n]);
    }
    return 0;
}
