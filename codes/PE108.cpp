#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 1000005;

bool prime[N];
vector <int> primes;

LL multiply (LL a, LL b, LL mod) { // a * b % mod
    vector <int> v;
    
    for (LL carry = 0; a > 0 || carry > 0; carry >>= 1, a >>= 1) {        
        carry += b * (a & 1);
        v.push_back(carry & 1);
    }
    
    reverse(v.begin(), v.end());
    
    LL ret = 0;
    for (int dig: v) {
        ret <<= 1;
        ret += dig;
        
        if (ret >= mod) ret %= mod;
    }
    
    return ret;
}

LL power (LL x, LL y, LL mod) {
    LL ret = 1;
    LL mul = x;
    
    while (y) {
        if (y & 1) ret = multiply(ret, mul, mod);                    
        
        y >>= 1;
        mul = multiply(mul, mul, mod);
    }
    
    return ret;
}

vector <int> A = {2, 3, 5, 7, 11, 13, 17, 19, 23};
bool isPrime (LL n) {
    if (n < N) return prime[n];
    
    // 2^s * d = n-1
    int s = __builtin_ctzll(n-1);
    LL d = (n - 1) >> s;
    for (int a: A) {
        if (power(a, d, n) == 1) continue;
        
        bool fail = 0;
        for (int r=0; r<s; r++) {
            if (power(a, d * (1LL << r), n) == n-1) {
                fail = 1;
                break;
            }
        }
        
        if (!fail) return 0;
    }
    
    return 1;
}

int isSquare (LL n) {    
    int l = 1;
    int r = min(1000000000LL, n);
    while (l <= r) {        
        LL mid = l + r >> 1;
        
        if (mid * mid < n) l = mid + 1;
        else if (mid * mid > n) r = mid - 1;
        else return 1;
    }
    
    return 0;
}

LL solve() {
    LL n;
    scanf ("%lld", &n);
    
    LL ans = 1;
    for (int p: primes) {
        int e = 0;
        while (n % p == 0) {
            n /= p;
            e++;
        }
        
        ans *= 2 * e + 1;
    }
    
    if (n == 1) return ans;
    if (isSquare(n)) return ans * 5; // p * p
    if (isPrime(n)) return ans * 3; // p
    return ans * 9; // p * q
}

int main() {
    
    memset (prime, 1, sizeof prime);
    prime[0] = prime[1] = 0;
    for (int i=2; i<N; i++) if (prime[i]) {
        for (int j=i*2; j<N; j+=i) prime[j] = 0;
        primes.push_back(i);
    }
    
    int t;
    scanf ("%d", &t);
    while (t--) printf ("%lld\n", solve() + 1 >> 1);
    return 0;
}
