#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 10000000;
bitset<N> prime;
vector<int> primes;

void divisors (LL n, vector<LL> &ret) {
    vector<LL> primeDivisors;
    for (int i=0; i < primes.size() && 1LL*primes[i]*primes[i] <= n; i++) {
        if (n % primes[i] == 0) {
            do {
                primeDivisors.push_back(primes[i]);
                n /= primes[i];
            } while (n % primes[i] == 0);
        }
    }
    if (n > 1) primeDivisors.push_back(n);
        
    ret.push_back(1);
    for (int i=0, j; i < primeDivisors.size(); i=j) {
        j = i;
        while (j < primeDivisors.size() && primeDivisors[j] == primeDivisors[i]) j++;
        
        LL mul = 1; int sz = ret.size();
        for (int k=i; k<j; k++) {
            mul *= primeDivisors[k];            
            for(int l=0; l<sz; l++) ret.push_back(mul * ret[l]);
        }
    }
}

LL power(LL x, LL y, LL mod) {
    __int128 ret = 1, mul = x;
    for (; y; y >>= 1) {
        if (y & 1) ret = ret * mul % mod;
        mul = mul * mul % mod;
    }
    return ret;
}

LL phi(LL n) {
    LL ret = n;
    for(int i=0; i < primes.size() && 1LL*primes[i]*primes[i] <= n; i++) if (n % primes[i] == 0) {
        ret /= primes[i]; ret *= primes[i] - 1;
        do n /= primes[i]; while (n % primes[i] == 0);
    }
    if (n > 1) ret /= n, ret *= n - 1;
    return ret;
}

int Main() {
    LL n; scanf ("%lld", &n); n += (n << 3);
    
    LL p = phi(n);
    
    vector<LL> div; divisors(p, div);
    LL ans = p;
    for (int i=0; i<div.size(); i++) {
        if (power(10, div[i], n) == 1) ans = min(ans, div[i]);
    }
    
    return 0 * printf ("%lld\n", ans);
}

int main() {
    prime = ~prime; prime[0] = prime[1] = 0;
    for (int i=2; i<N; i++) if (prime.test(i)) {
        for (int j=i*2; j<N; j+=i) prime[j] = 0;
        primes.push_back(i);
    }
    
    int t;
    scanf ("%d", &t);
    while (t--) Main();
    return 0;
}
