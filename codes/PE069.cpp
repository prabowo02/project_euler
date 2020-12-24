#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

vector <LL> ans;

bool isPrime (LL x) {
    for (int i=2; i*i<=x; i++) if (x % i == 0) return 0;
    return 1;
}

int main() { 
    ans.push_back(1);
    for (int i=2; i<50; i++) if (isPrime(i)) ans.push_back(ans.back() * i);
        
    int t;
    scanf ("%d", &t);
    while (t--) {
        LL n;
        scanf ("%lld", &n);
        printf ("%lld\n", *(lower_bound(ans.begin(), ans.end(), n) - 1));
    }
    return 0;
}
