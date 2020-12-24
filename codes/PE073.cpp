#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// prime factors of i
typedef long long LL;
vector <int> fact[2000000];

// number of fractions <= 1/a
LL solve (int a, int n) {
    LL ret = 0;
    for (int det = 2; det <= n; det++) {
        int num = det / a;        
        for (int i=0; i<1<<fact[det].size(); i++) {
            int prod = 1;
            for (int j=0; j<fact[det].size(); j++)
                if (i >> j & 1)
                    prod *= fact[det][j];
                
            if (__builtin_popcount(i) & 1)
                ret -= num / prod;
            else 
                ret += num / prod;
        }
    }
    
    return ret;
}

int main() {
    int n, a;
    scanf ("%d %d", &a, &n);
    
    for (int i=2; i<=n; i++) 
        if (fact[i].size() == 0) 
            for (int j=i; j<=n; j+=i) fact[j].push_back(i);
        
    printf ("%lld\n", solve(a, n) - solve(a+1, n) - 1);
    return 0;
}
