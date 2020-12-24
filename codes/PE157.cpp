#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1000005;
bool prime[N];

long long multiply (long long a, long long b, long long mod) { // a * b % mod
  long long y = (long long) ((long double) a * (long double) b / mod + 0.5);
  y = y * mod;
  long long x = a * b;
  long long ret = x - y;
  if (ret < 0) ret += mod;
  return ret;
}

LL gcd(LL u, LL v)
{
    int shift;
    if (u == 0) return v;
    if (v == 0) return u;
    shift = __builtin_ctzll(u | v);
    u >>= __builtin_ctzll(u);
    do {
        v >>= __builtin_ctzll(v);
        if (u > v) {
            LL t = v;
            v = u;
            u = t;
        }  
        v = v - u;
    } while (v != 0);
    return u << shift;
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

LL power (LL x, LL y) {
    LL ret = 1;
    LL mul = x;
    
    while (y) {
        if (y & 1) ret = ret * mul;                    
        
        y >>= 1;
        mul = mul * mul;
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

LL sqr(LL n) { return n * n; }

bool isSquare(LL n) {
    return sqr(sqrt((long double) n)) == n;
}

LL numOfDivisors(LL n) {
    LL ret = 1;
    
    while (n % 2 == 0) {
        ret++;
        n /= 2;
    }
    
    for (LL i=3; i<N; i+=2) {
        if (i * i > n) break;
        
        if (n % i == 0) {
            int tmp = 1;
            do {
                n /= i;
                tmp++;
            } while (n % i == 0);
            
            ret *= tmp;
        }
    }
    
    if (n == 1) return ret;
    if (isPrime(n)) return ret *= 2;
    if (isSquare(n)) return ret *= 3;
    return ret *= 4;
}

int main() {
    
    memset (prime, 1, sizeof prime);
    prime[0] = prime[1] = 0;
    for (int i=2; i<N; i++) if (prime[i]) {
        for (int j=i*2; j<N; j+=i) prime[j] = 0;
    }
    
    int t;
    scanf("%d", &t);
    while (t--) {
        LL p1, r1, p2, r2;
        scanf("%lld %lld %lld %lld", &p1, &r1, &p2, &r2);
        
        LL p[r1 + 1]; p[0] = 1; for (int i=1; i<=r1; i++) p[i] = p[i-1] * p1;
        LL q[r2 + 1]; q[0] = 1; for (int i=1; i<=r2; i++) q[i] = q[i-1] * p2;
        
        LL ans = 0;
        for (int bi=0; bi<=r1; bi++) for (int bj=0; bj<=r2; bj++) {
            LL b = p[bi] * q[bj];
            
            int sump = 0, sumq = 0;
            
            b++;
            while (b % p1 == 0) {
                b /= p1;
                sump++;
            }
            
            while (b % p2 == 0) {
                b /= p2;
                sumq++;
            }
            
            sump = (r1 + max(1, bi) - bi*2 + sump*2 + 2) * (r1 - max(1, bi) + 1) >> 1;
            sumq = (r2 + max(1, bj) - bj*2 + sumq*2 + 2) * (r2 - max(1, bj) + 1) >> 1;
            
            ans += numOfDivisors(b) * sump * sumq;
        }
        
        for (int bi=1; bi<=r1; bi++) for (int aj=1; aj<=r2; aj++) {
            if (q[aj] > p[bi]) continue;
            LL a = q[aj], b = p[bi];            
            
            int sump = (r1 + bi - bi*2 + 2) * (r1 - bi + 1) >> 1;
            int sumq = (r2 + aj - aj*2 + 2) * (r2 - aj + 1) >> 1;
            
            ans += numOfDivisors(a + b) * (sump) * (sumq);
            
        }
        
        for (int ai=1; ai<=r1; ai++) for (int bj=1; bj<=r2; bj++) {
            if (p[ai] > q[bj]) continue;
         
            LL a = p[ai], b = q[bj];
            
            /*
            for (int i=ai; i<=r1; i++) for (int j=bj; j<=r2; j++) {
                ans += numOfDivisors(p[i] * q[j] / (a * b) * (a + b));
            } continue; */
            //int sump = (r1 + ai - ai*2 + 2) * (r1 - ai + 1) * (r2 - bj + 1) >> 1;
            //int sumq = (r2 + bj - bj*2 + 2) * (r1 - ai + 1) * (r2 - bj + 1) >> 1;
            
            int sump = (r1 - ai + 1) * (r1 - ai + 2) >> 1;
            int sumq = (r2 - bj + 1) * (r2 - bj + 2) >> 1;
            
            ans += numOfDivisors(a + b) * (sump) * (sumq);
        }
        
        printf("%lld\n", ans);
    }
    
    return 0;
}
