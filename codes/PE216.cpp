#include <bits/stdc++.h>
using namespace std;

int power(int x, int y, int m) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % m;
    x = 1LL * x * x % m;
  }
  return ret;
}

int tonelli_shanks(int n, int p) {
  int s = __builtin_ctz(p-1);
  if (s == 1) return power(n, p+1>>2, p);
  
  int q = p-1 >> s;
  int z;
  for (z=2; power(z, p-1>>1, p) == 1; z++);
  
  int m = s;
  int c = power(z, q, p);
  int t = power(n, q, p);
  int r = power(n, q+1>>1, p);
  
  while (t != 1) {
    int i, tt;
    for (i=1, tt=1LL*t*t%p; tt != 1; ++i, tt=1LL*tt*tt%p);
    
    int b = power(c, 1<<m-i-1, p);
    
    m = i;
    c = 1LL * b * b % p;
    t = 1LL * t * c % p;
    r = 1LL * r * b % p;
  }
  
  return r;
}

const int N = 14200000;
const int M = 10000001;

long long p[M];
int ans[M];

bool composite[N];

int a = 2, b = 100, c = 10000000;
long long D = 1LL * b * b - 4LL * a * c;
void sieve() {
  for (int i=3; i<N; i+=2) {
    if (composite[i]) continue;
    for (long long j=1LL*i*i; j<N; j+=i) {
      composite[j] = true;
    }
    
    int d = D % i + (D < 0 ? i : 0);
    
    if (d == 0 || d == i) {
      int den = 1LL * (i+1 >> 1) * (a == 1 ? 1 : i+1 >> 1) % i;
      int x = 1LL * (-b) * den % i;
      if (x < 0) x += i;
      
      for (int j=x; j<M; j+=i) {
        ans[j] &= (p[j] == i);
      }
    } else if (power(d, i-1>>1, i) == i-1); 
    else {
      int x = tonelli_shanks(d, i);
      
      int den = 1LL * (i+1 >> 1) * (a == 1 ? 1 : i+1 >> 1) % i;
      
      int x1 = 1LL * (-b + x) * den % i;
      if (x1 < 0) x1 += i;
      
      int x2 = 1LL * (-b - x) * den % i;
      if (x2 < 0) x2 += i;
      
      for (int j=x1; j<M; j+=i) {
        ans[j] &= (p[j] == i);
      }
      
      for (int j=x2; j<M; j+=i) {
        ans[j] &= (p[j] == i);
      }
    }
  }
}

int solve() {
  scanf("%d %d %d", &a, &b, &c);
  D = 1LL * b * b - 4LL * a * c;
  
  for (int i=0; i<M; i++) {
    p[i] = 1LL * a * i * i + 1LL * b * i + c;
    ans[i] = (p[i] > 1 && ((p[i] & 1) || p[i] == 2));
  }
  
  sieve();
  
  for (int i=1; i<M; i++) ans[i] += ans[i-1];
  
  int q;
  scanf("%d", &q);
  while (q--) {
    int n;
    scanf("%d", &n);
    
    printf("%d\n", ans[n]);
  }
  
  return 0;
}

int main() {
  clock_t t = clock();
  solve();
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}
