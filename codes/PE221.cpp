#include <bits/stdc++.h>
using namespace std;

const int N = 1280000;
const __int128 ONE = 1;

long long a[N];
vector<pair<long long, int>> pfactors[N];

long long ans[2500005];

vector<long long> divisors(vector<pair<long long, int>> v) {
    vector<long long> ret = {1LL};
    
    for (pair<long long, int> pe: v) {
        long long p = pe.first;
        int e = pe.second;
        
        int sz = ret.size();
        
        long long num = 1;
        for (int i=0; i<e; i++) {
            num *= p;
            for (int j=0; j<sz; j++) {
                ret.push_back(ret[j] * num);
            }
        }
    }
    
    return ret;
}

void init() {
    for (int i=1; i<N; i++) a[i] = 1LL * i * i + 1;
    
    for (int i=1; i<N; i++) {
        if (a[i] == 1) continue;
        
        long long p = a[i];
        
        for (long long j=i; j<N; j+=p) {
            if (a[j] % p > 0) continue;
            int e = 0;
            do {
                a[j] /= p;
                ++e;
            } while (a[j] % p == 0);
            
            pfactors[j].push_back({p, e});
        }
        
        for (long long j=p-i; j<N; j+=p) {
            if (a[j] % p > 0) continue;
            int e = 0;
            do {
                a[j] /= p;
                ++e;
            } while (a[j] % p == 0);
            
            pfactors[j].push_back({p, e});
        }
    }
    
    int idx = 0;
    for (int i=1; i<N; i++) {
        long long n = 1LL * i * i + 1;
        for (long long d: divisors(pfactors[i])) {
            if (d > n/d) continue;
            
            __int128 num = ONE * i * (d + i) * (n/d + i);
            if (num <= 8198903464888101966LL) {
                ans[idx++] = num;
            }
        }
    }
    sort(ans, ans + idx);
    cerr << idx << endl;
    cerr << ans[2500000 - 1] << endl;
}

int solve() {
    int q;
    scanf("%d", &q);
    while (q--) {
        int n;
        scanf("%d", &n);
        printf("%lld\n", ans[n-1]);
    }
    
    return 0;
}

int main() {
    clock_t t = clock();
    init();
    solve();
    cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
    return 0;
}
