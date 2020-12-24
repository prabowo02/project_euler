#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long LL;
const int N = 1005;

vector <int> prime;
bool sieve[N];

LL dp[N][170];
LL f(int n, int idx) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (~dp[n][idx]) return dp[n][idx];
    
    LL ret = 0;
    for (int i=0; i<idx; i++) {
        ret += f(n-prime[i], i + 1);
    }
    return dp[n][idx] = ret;
}

int main() {
    memset(sieve, 1, sizeof sieve);
    for (int i=2; i<N; i++)
        if (sieve[i]) {
            for (int j=2*i; j<N; j+=i)
                sieve[j] = 0;
        
            prime.push_back(i);
        }
    
    int t;
    scanf ("%d", &t);
    memset(dp, -1, sizeof dp);
    while (t--) {
        int n;
        scanf ("%d", &n);
        printf ("%lld\n", f(n, prime.size()));
    }
    return 0;
}
