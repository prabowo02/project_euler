#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1000005;

bitset<N> prime;
bitset<1500005> prime2;

LL multiply(LL a, LL b, LL mod) {   
    long long y = (long long) ((long double) a * (long double) b / mod + 0.5);
  y = y * mod;
  long long x = a * b;
  long long ret = x - y;
  if (ret < 0) ret += mod;
  return ret;
}

LL power(LL x, LL y, LL mod) {
    LL ret = 1, mul = x;
    for (; y; y >>= 1) {
        if (y & 1) ret = multiply(ret, mul, mod);
        mul = multiply(mul, mul, mod);
    }
    return ret;
}

int main() {    
    LL L, R;
    scanf ("%lld %lld", &L, &R);
    int n = R - L + 1;
        
    prime2 = ~prime2;    
    prime = ~prime;
    for (LL i=2; i*i<=R; i++) if (prime.test(i)) {
        for (int j=i*2; j<N; j+=i) prime[j] = 0;
        LL j = L / i * i; if (j < L) j += i; if (j == i) j += i;
        for (; j<=R; j+=i) prime2[j - L] = 0;
    }
    
    for (int i=1-(L&1); i<n; i+=2) {
        LL c = L + i;        
        if (prime2.test(i)) continue;
        if (power(10, c-1, c + (c << 3)) == 1) printf ("%lld\n", c);
    }
    return 0;
}
