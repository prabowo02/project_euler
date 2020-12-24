#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    long long n;
    scanf("%lld", &n);
    
    long long ans = 0;
    for (long long a = 2; a*a < n; a+=2) {
        ans += n/a - a >> 1;
    }
    printf("%lld\n", ans);
    return 0;
}
