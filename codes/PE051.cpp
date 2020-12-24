#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10000000;
bool prime[N];

int n, k, l;
vector <int> ans;

int main() {
    memset (prime, 1, sizeof prime);
    prime[0] = prime[1] = 0;
    for (int i=2; i<N; i++) if (prime[i]) for (int j=2*i; j<N; j+=i) prime[j] = 0;
    
    scanf ("%d %d %d", &n, &k, &l);
    
    int lower = 1;
    for (int i=1; i<n; i++) lower *= 10;
    
    int brute = 1;
    for (int i=0; i<n-k; i++) brute *= 10;
    
    for (int i=0; i<1<<n; i++) {
        if (__builtin_popcount(i) ^ k) continue;
                
        for (int j=0; j<brute; j++) {
            vector <int> v;
            
            for (int dig = 0; dig < 10; dig++) {
                int num = 0;
                int tmp = j;
                for (int k=0; k<n; k++) {
                    num *= 10;
                    if (i >> k & 1) num += dig;
                    else num += tmp % 10, tmp /= 10;
                }
                
                if (num >= lower && prime[num]) v.push_back(num);
            }
            
            if (v.size() >= l) {
                if (ans.size()) ans = min(ans, v);
                else ans = v;
            }
        }
    }
    
    for (int i=0; i<l; i++) printf ("%d ", ans[i]);
    
    return 0;
}
