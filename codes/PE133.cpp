#include <bits/stdc++.h>
using namespace std;

const int N = 30000001;
bool prime[N];

int main() {
    vector<int> ans = {0, 11, 17, 41, 73, 101, 137, 251, 257, 271, 353, 401, 449, 641, 751, 1201, 1409, 1601, 3541, 4001, 4801, 5051, 9091, 10753, 15361, 16001, 19841, 21001, 21401, 24001, 25601, 27961, 37501, 40961, 43201, 60101, 62501, 65537, 69857, 76001, 76801, 160001, 162251, 163841, 307201, 453377, 524801, 544001, 670001, 952001, 976193, 980801, 1146881, 1378001, 1514497, 1610501, 1634881, 1676321, 1920001, 2800001, 3072001, 5070721, 5767169, 5882353, 6144001, 6187457, 6576001, 6600001, 7019801, 8253953, 8257537, 9011201, 12600001, 16384001, 18453761, 18750001, 21408001, 26214401};
    vector<long long> sum(ans.size()); for (int i=1; i<ans.size(); i++) sum[i] = sum[i-1] + ans[i];
    
    memset(prime, 1, sizeof prime);
    vector<int> primes; primes.push_back(0);
    vector<long long> sprimes; sprimes.push_back(0);
    for (int i=2; i<N; i++) if (prime[i]) {
        for (int j=i*2; j<N; j+=i) prime[j] = 0;
        primes.push_back(i); sprimes.push_back(sprimes.back() + primes.back());
    }
    
    int t;
    scanf ("%d", &t);
    while(t--) {
        int n;
        scanf ("%d", &n);
        printf ("%lld\n", sprimes[lower_bound(primes.begin(), primes.end(), n) - primes.begin() - 1] - sum[lower_bound(ans.begin(), ans.end(), n) - ans.begin() - 1]);
    }
    return 0;
}
