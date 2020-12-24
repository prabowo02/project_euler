#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long long d[1000005];

int gcd(int x, int y) {
    return y ? gcd(y, x % y) : x;
}

int main() {
    double e = exp(1);
    for (int n=5; n<=1000000; ++n) {
        int k = int(n / e);
        if (k*(log(n) - log(k)) < (k+1)*(log(n) - log(k+1))) ++k;
        
        k /= gcd(n, k);
        while (k % 2 == 0) k >>= 1;
        while (k % 5 == 0) k /= 5;
        if (k == 1) d[n] = -n; else d[n] = n;
        d[n] += d[n-1];
    }
    
    int q;
    scanf("%d", &q);
    while (q--) {
        int n;
        scanf("%d", &n);
        printf("%lld\n", d[n]);
    }
    return 0;
}
