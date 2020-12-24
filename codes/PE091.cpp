#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int gcd (int x, int y) {
    return y ? gcd(y, x % y) : x;
}

int n;
int count (int x, int y) {
    int fpb = gcd(x, y);
    int dx = x / fpb, dy = y / fpb;
         
    return min((n-y) / dx, x / dy) + min((n-x) / dy, y / dx);
}

int main() {
    scanf ("%d", &n);
    
    long long ans = n * n * 3;
    for (int i=1; i<=n; i++)
        for (int j=1; j<=n; j++) 
            ans += count(i, j);
        
    printf ("%lld\n", ans);
    return 0;
}
