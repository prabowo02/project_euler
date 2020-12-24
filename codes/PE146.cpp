#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long LL;
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

vector <int> A = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
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

bool candidates[10000005];

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 47, 53, 57, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271};

int Main() {
  int l;
  cin >> l;
  
  int a[6];
  for (int i=0; i<6; i++) cin >> a[i];
  
  for (int i=0; i<l; i++) candidates[i] = 1;
  for (int prime: primes) {
    for (int i=0; i<prime; i++) {
      
      for (int j=0; j<6; j++) {       
        if ((1LL * i * i + a[j]) % prime == 0) {  
          // if (1LL * i * i % prime == 100 % prime) cerr << prime << " " << i << " " << a[j] << endl;
          for (int k=i+prime; k<l; k+=prime) candidates[k] = 0;
        }
      }
      
    }
  }
  
  // int cnt = 0; for (int i=0; i<l; i++) cnt += candidates[i]; cerr << cnt << endl;
  
  long long ans = 0;
  for (int n=1; n<l; n++) {
    if (!candidates[n]) continue;
    bool ok = 1;
    for (int i=1; i<6; i++) {
      for (int j=a[i-1]+1; j<a[i]; j++) {
        if (isPrime(1LL*n*n + j)) {
          ok = 0;
          break;
        }
      }
      if (!ok) break;
    }
    if (!ok) continue;
    
    for (int i=0; i<6; i++) {
      if (!isPrime(1LL*n*n + a[i])) {
        ok = 0;
        break;
      }
    }
    
    if (ok) ans += n;
  }
  
  cout << ans << "\n";
  
  return 0;
}

int main() {
    
    memset (prime, 1, sizeof prime);
    prime[0] = prime[1] = 0;
    for (int i=2; i<N; i++) if (prime[i]) {
        for (int j=i*2; j<N; j+=i) prime[j] = 0;
    }

  int t;
  cin >> t;
  while (t--) Main();
}
