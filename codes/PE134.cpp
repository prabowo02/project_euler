#include <cassert>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1001001;
bool prime[N];

int tenlen(int n) {
    int ret = 1;
    while (n) {
        n /= 10;
        ret *= 10;
    }
    
    return ret;
}

int power(int x, int y, int mod) {
    long long ret = 1, mul = x;
    for (; y; y >>= 1) {
        if (y & 1) ret = ret * mul % mod;
        mul = mul * mul % mod;
    }
    return ret;
}

int Main() {
    int L, R;
    scanf ("%d %d", &L, &R);
    
    for (int i=0; i<=R-L+1000; i++) prime[i] = 1;
    bool prime2[R-L+1001]; for (int i=0; i<R-L+1001; i++) prime2[i] = 1;
    
    for (long long i=2; i*i<=R+1000; i++) {
        if (prime[i]) {
            // cerr << i << endl;
            for (long long j=i*2; j*j<=R+1000; j+=i) prime[j] = 0;
            int j = L / i * i; if (j < L) j += i; if (j == i) j += i;
            for (; j<=R+1000; j+=i) prime2[j-L] = 0;
        }
    }
    
    vector<int> primes;
    for (int i=L; i<=R; i++) if (prime2[i-L]) primes.push_back(i); // cerr << i << endl;    
    if (primes.size() == 0) return 0 * printf ("0\n");
        
    for (int j=primes.back()+1; ; j++) if (prime2[j-L]) {
        primes.push_back(j);
        break;
    }

    __int128 ans = 0;
    for (int i=0; i+1<primes.size(); i++) {
        int p1 = primes[i];
        int p2 = primes[i+1];
        
        long long tmp = tenlen(p1);
        long long S = 1LL * power(tmp, p2 - 2, p2) * (-p1) % p2;
        if (S < 0) S += p2;
        
        // cerr << S << " " << p1 << endl;
        ans += S * tmp + p1;        
        // cerr << ans << endl;
    }
    
    string s;
    while (ans > 0) {
        s += ans % 10 + '0';
        ans /= 10;
    }
    reverse(s.begin(), s.end());
    
    cout << s << endl;
    return 0;
}

int main() {
    int t;
    scanf ("%d", &t);
    while (t--) Main();
    return 0;
}
