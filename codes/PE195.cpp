/**
 * Using parametrization , we obtain the three sides a, b, c of the 60-degree triangle by:
 * a = u*u - v*v
 * b = 2*u*v - v*v
 * c = u*u - u*v + v*v
 * where u, v positive integers, gcd(u, v) = 1 and u > v. 
 *
 * The incircle r = {AreaOfTriangle} / {Semiperimeter}
 * r = sqrt(3) * v * (u-v) / (gcd(a, b, c) * 2)
 * gcd(a, b, c) takes only the value 1 or 3.
 * gcd(a, b, c) = 3 if and only if 3 | u + v.
 *
 * Thus, we are to find sum (2*n*d/(sqrt(3) * v * (u-v))) where d = gcd(a, b, c)
 * It is easier to calculate if we substitute (u-v) with another variable w, and 2n/sqrt(3) with N
 * Now we are to compute the sum of N*d/(v*w) where pair (v, w) are coprime and v < w
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 60000;

long long n;
vector<int> primeFactors[N];
vector<int> prods[N];

const int GCD = 1000;
int gcds[GCD][GCD];
int gcd(int x, int y) {
    if (x < GCD && y < GCD) return gcds[x][y];
    return y ? gcd(y, x % y) : x;
}

int initgcd(int x, int y) {
    return y ? initgcd(y, x % y) : x;
}

// returns floor(2n / sqrt(3))
long long floor3(long long n) {
    long long x = n*2 / sqrt(3);
    long long ret = -1;
    __int128 n128 = n;
    for (__int128 i=x-10; i<=x+10; i++) {
        if (i*i*3 <= n128*n128*4)
            ret = i;
    }
    return ret;
}

void init() {
    for (int i=2; i<N; i++) {
        if (primeFactors[i].size() == 0) for (int j=i; j<N; j+=i)
            primeFactors[j].push_back(i);
    }
        
    for (int i=1; i<N; i++) {
        for (int j=0; j<1<<primeFactors[i].size(); j++) {
            int prod = 1;
            for (int k=0; k<primeFactors[i].size(); k++) {
                if (j >> k & 1) prod *= primeFactors[i][k];
            }
            prods[i].push_back(prod);
        }
    }
    
    for (int i=0; i<GCD; i++) for (int j=0; j<GCD; j++) gcds[i][j] = initgcd(i, j);
}

// Find number of integer 1..n s.t. coprime to x and = mod3 (mod 3)
long long countCoprime(long long n, int x, int mod3) {
    long long ret = 0;
    for (int i=0; i<1<<primeFactors[x].size(); i++) {
        int prod = prods[x][i];
        
        long long res;
        if (mod3 == 0) {
            if (prod % 3 == 0) {
                res = n / (prod);
            } else {
                res = n / (prod * 3);
            }
        } else if (prod % 3 == 0) {
            res = 0;
        } else if (prod % 3 != mod3) {
            res = n / (prod * 3) + (prod * 2 <= n % (prod * 3));
        } else {
            res = n / (prod * 3) + (prod <= n % (prod * 3));
        }
        
        if (__builtin_popcount(i) & 1) ret -= res;
        else ret += res;
    }
    
    return ret;
}

int Main() {
    const int K = 20;
    scanf("%lld", &n);
    long long n3 = floor3(n * 3);
    n = floor3(n);
    
    long long ans = 0;
    double first = 0, second = 0;
    for (long long i=1; i*i<=n; i++) {  
        clock_t t = clock();
        
        long long j;
        for (j=i+1; j*j <= n/i*K; j++) {
            if ((i - j) % 3 != 0 && gcd(i, j) == 1) ans += n / i / j;
        }
        
        first += (double) (clock() - t) / CLOCKS_PER_SEC;
        t = clock();
        
        long long k;
        for (k=1; n/i/k>=j; k++) {
            ans += countCoprime(n/i/k, i, (i+1)%3) + countCoprime(n/i/k, i, (i+2)%3);
        }
        ans -= (k-1) * (countCoprime(j-1, i, (i+1) % 3) + countCoprime(j-1, i, (i+2)%3));
        
        second += (double) (clock() - t) / CLOCKS_PER_SEC;
    }
    cerr << first << " " << second << endl;
    
    for (long long i=1; i*i<=n3; i++) {  
        long long j;
        for (j=i+3; j*j <= n3/i*K; j+=3) {
            if (gcd(i, j) == 1) ans += n3 / i / j;
        }
        
        long long k;
        for (k=1; n3/i/k>=j; k++) {
            ans += countCoprime(n3/i/k, i, i%3);
        }
        ans -= (k-1) * countCoprime(j-1, i, i%3);
    }
    
    cout << ans << endl;
    // cerr << (double)(clock() - t) / CLOCKS_PER_SEC << endl;
    return 0;
}

int main() {
    clock_t t = clock();
    init();
    cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
    
    int q;
    scanf("%d", &q);
    while (q--) {
        Main();
    }
    
    cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
    return 0;
}
