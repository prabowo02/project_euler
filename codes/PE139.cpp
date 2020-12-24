#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    vector<long long> V = {12, 70};
    while(V.back() <= 1000000000000000000LL) V.push_back(-V[V.size()-2] + V.back() * 6);
    int t;
    scanf ("%d", &t);
    
    long long n;
    while (t--) {
        scanf("%lld", &n); --n;
        
        long long ans = 0;
        for (long long v: V) ans += n / v;
        printf("%lld\n", ans);
    }
    return 0;
}
