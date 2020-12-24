#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const LL N = 100000000000LL;

LL gcd(LL x, LL y) {
    return y ? gcd(y, x % y) : x;
}

const int SN = 1000005;
LL BIT[SN];

void update(int x, LL val) {    
    for (int i=x+1; i<SN; i+=i&-i)
        BIT[i] += val;
}

LL query(int x) {
    LL ret = 0;
    for (int i=x+1; i; i-=i&-i)
        ret += BIT[i];
    return ret;
}

int main() {
    clock_t ct = clock();
    vector<LL> ans;
    for (LL a = 2; a*a*a < N; a++) {        
        for (LL b = 1; b < a; b++) {
            if (a*a*a*b + b*b >= N) break;
            if (gcd(a, b) > 1) continue;
            
            for (LL c = 1;; c++) {
                LL n = a*a*a*b*c*c + b*b*c;
                if (n >= N) break;
                
                ans.push_back(n);
            }
        }
    }
    
    for (LL n = 2; n * (n+1) < N; n++) ans.push_back(n * (n+1));
    
    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
    
    // cerr << (double) (clock() - ct) / CLOCKS_PER_SEC << endl;
    
    int t;
    scanf("%d", &t);
    int k; LL l;
    pair<pair<LL, int>, int> queries[t];
    for (int i=0; i<t; i++) {
        scanf("%d %lld", &k, &l);

        queries[i] = {{l, k}, i};
    }
    
    sort(queries, queries + t);
    LL sum[t];    
    
    LL cur = 0;
    for (int i=0; i<t; i++) {
        while (cur < ans.size() && ans[cur] < queries[i].first.first) {
            LL tmp = floor(sqrt(ans[cur]) + 1e-7);
            update(min(ans[cur] - tmp*tmp, (tmp+1) * (tmp+1) - ans[cur]), ans[cur]);            
            cur++;
        }
        
        sum[queries[i].second] = query(queries[i].first.second);
    }
    
    for (int i=0; i<t; i++) printf("%lld\n", sum[i]);
    
    return 0;
}
