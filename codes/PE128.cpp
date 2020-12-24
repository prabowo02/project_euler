#include <bits/stdc++.h>
using namespace std;

const int N = 10000000;

bitset<N*12> prime;
vector <long long> ans;

int main() {
    prime = ~prime; prime[0] = prime[1] = 0;
    for (int i=2; i*i<N*12; i++) if (prime.test(i)) for (int j=i*2; j<N*12; j+=i) prime[j] = 0;

    for (int r=1; r<N; r++) {
        if (prime.test(r*6-1) && prime.test(r*6+1) && prime.test(r*12+5)) ans.push_back(3LL*r*r - 3*r + 2);
        if (prime.test(r*6-1) && prime.test(r*6+5) && prime.test(r*12-7)) ans.push_back(3LL*r*r + 3*r + 1);
    }
    ans[1] = 2; ans[0] = 1;
    // cerr << ans.size() << endl;    
    // for (int i=0; i<20; i++) cerr << ans[i] << endl;
    
    int t, k;
    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &k);
        printf ("%lld\n", ans[--k]);
    }
    return 0;
}
