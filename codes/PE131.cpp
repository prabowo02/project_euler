#include <bits/stdc++.h>
using namespace std;

const int N = 3000000;

long long num[N];

int main() {
    
    clock_t t = clock();
    
    for (int i=1; i<N; i++) {
        num[i] = 1LL*(i+1)*(i+1)*(i+1) - 1LL*i*i*i;
    }
    
    vector<long long> ans;
    for (int i=1; i<N; i++) {
        if (num[i] == 1) continue;
        if (num[i] == 1LL*(i+1)*(i+1)*(i+1) - 1LL*i*i*i) {
            ans.push_back(num[i]);
        }
        
        long long p = num[i];
        
        for (long long j=i; j<N; j+=p) {
            while (num[j] % p == 0) num[j] /= p;
        }
        
        for (long long j=p-i-1; j<N; j+=p) {
            while (num[j] % p == 0) num[j] /= p;
        }
    }
    
    int tc;
    scanf ("%d", &tc);
    while(tc--) {
        long long n;
        scanf ("%lld", &n);
        printf ("%d\n", lower_bound(ans.begin(), ans.end(), n) - ans.begin());
    }
    return 0;
} 