#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int N = 1000000000;

long long dfs(int x, int y) {
  if (1LL * (x+y) * y > N) return (N/x - y) / x + 1;
  if (1LL * x * (x+y) > N) return (N/y - x) / y + 1;

  return 1LL + dfs(x+y, y) + dfs(x, x+y);
}

vector<int> primes[40000];
long long all() {
  for (int i=2; i*i<=N; i++) {
    if (primes[i].size()) continue;
    for (int j=i; 1LL*j*j<=N; j+=i) {
      primes[j].push_back(i);
    }
  }
  
  long long res = 0;
  for (int i=1; i*i<N; i++) {
    res += N/i - i;
    for (int mask=1; mask<1<<primes[i].size(); mask++) {
      int prod = 1;
      for (int j=0; j<primes[i].size(); j++) {
        if (mask >> j & 1) prod *= primes[i][j];
      }
      
      if (__builtin_popcount(mask) & 1) {
        res -= N/i/prod - i/prod;
      } else {
        res += N/i/prod - i/prod;
      }
    }
  }
  
  return res * 2 + 1;
}

map<pair<int, int>, long long> memo;
long long query(int x, int y) {
  if (1LL * x * y > N) return 0;

  if (1LL * x * y <= 50) {
    if (memo.find({x, y}) != memo.end()) return memo[{x, y}];
    
    long long mem;
    
    if (x == 1) mem = query(1, y-1) - query(y, y-1) - 1;
    else if (y == 1) mem = query(1, x-1) - query(x, x-1) - 1;
    else mem = query(x, x+y) + query(x+y, y) + 1;
    
    return memo[{x, y}] = memo[{y, x}] = mem;
  }
  
  return dfs(x, y);
}

void init() {
  memo[{1, 1}] = all();
  memo[{1, 2}] = memo[{2, 1}] = memo[{1, 1}] - 1 >> 1;
}

bool same;
int p, q;
long long find(int a, int b, int c, int d) {
  if (1LL * b * d > N) return 0;
  
  long long num = 1LL * a * d + 1LL * b * c;
  long long det = 2LL * b * d;
  
  if (num * q == det * p) same = true;
  
  long long add = (num * q <= det * p);
  
  if (1LL * a * q == 1LL * b * p) return 0;
  if (1LL * c * q == 1LL * d * p) return query(b, d);
  
  if (1LL * b * (b+d) > N) {
    if (add == 0) return 0;
    long long x = 2LL * b * d * p - 1LL * a * d * q - 1LL * b * c * q;
    long long y = 2LL * d * (1LL * c * q - 1LL * d * p);
    
    if (y == 0) return (N/d - b) / d + 1;
    
    long long k = x / y;
    
    if ((k*d + b) * d > N) {
      return (N/d - b) / d + 1;
    }
    
    if (x % y == 0) same = true;
    return k + 1;
  }
  
  if (1LL * (b+d) * d > N) {
    if (add == 1) return (N/b - d) / b + 1;
    
    long long x = 2LL * b * d * p - 1LL * a * d * q - 1LL * b * c * q;
    long long y = 2LL * b * (1LL * a * q - 1LL * b * p);
    
    if (y == 0) return 0;
    
    long long k = x / y + (x % y ? 1 : 0);
    
    if ((k*b + d) * b > N) return 0;
    
    if (x % y == 0) same = true;
    return (N/b - d) / b - k + 1;
  }
  
  if (1LL * p * (b+d) <= 1LL * q * (a+c)) return add + find(a, b, a+c, b+d);
  return add + query(b, b+d) + find(a+c, b+d, c, d);
}

long long find(int _p, int _q, bool _same) {
  long long k = _p / _q;
  p = _p % _q; q = _q; same = false;
  
  long long ret = k * query(1, 1) + find(0, 1, 1, 1);
  if (!_same && same) --ret;
  return ret % MOD;
}

int solve() {
  int a, b, c, d;
  scanf("%d %d %d %d %d", &a, &b, &c, &d, &N);
  N /= 2;
  
  init();
  
  printf("%lld\n", (find(c, d, false) - find(a, b, true) + MOD) % MOD);
  return 0;
}

int main() {
  clock_t t = clock();
  solve();
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}
