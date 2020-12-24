#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 20000;

int n, k;

bool prime[N];
vector <int> p;

void sieve() {
  for (int i=2; i<n; i++) prime[i] = 1;
    for (int i=2; i<n; i++) if (prime[i]) {
        for (int j=2*i; j<n; j+=i) prime[j] = 0;        
    p.push_back(i);
  }
}

LL power (LL x, LL y, LL mod) {
  LL ret = 1;
  LL mul = x;
  while (y) {
    if (y & 1) {
      ret *= mul;
      ret %= mod;
    }
    mul *= mul; mul %= mod;
    y >>= 1;
  }
  return ret;
}

bool isPrime (int n) {
  if (n % 2 == 0) return 0;
  
  int s = __builtin_ctzll(n - 1);
  LL d = n - 1 >> s;
  
  int A[] = {2, 3, 5, 7};
  for (int i=0; i<4; i++) {
    int a = A[i];
    if (a > n-1) break;
    LL now = power(a, d, n);
    
    if (now == 1) continue;
    
    bool composite = 1;
    for (int i=0; i<s; i++) {
      if (now == n - 1) {
        composite = 0;
        break;
      }
      now = now * now % n;
    }
    
    if (composite) return 0;
  }
  
  return 1;
}

bool isPrime (int i, int j) {
  int tmp = i;
  for (LL ten = 1; ten <= j; ten *= 10) tmp *= 10;
  return isPrime( tmp + j );
}

int find (int x, vector <int> &v) {
  vector <int>::iterator p = lower_bound(v.begin(), v.end(), x);
  if (p == v.end()) return -1;
  if (*p != x) return -1;
  return p - v.begin();
}

vector <int> edge[N];

vector <int> ans;
void solve (int k, int u, vector <int> &primes) {
  if (k == 0) {
    int sum = 0;
    for (int i=0; i<primes.size(); i++) sum += primes[i];
    // for (int i=0; i<primes.size(); i++) {printf ("%d", primes[i]); if (i + 1 == primes.size()) printf ("\n"); else printf (" ");}
    ans.push_back(sum);
    return;
  }
  
  for (int i=0; i<edge[u].size(); i++) {
    int v = edge[u][i];
    
    bool can = 1;
    for (int i=0; i<(int)primes.size()-1; i++) {
      if (find(v, edge[primes[i]]) == -1) {
        can = 0;
        break;
      }
    }
    
    if (can) {
      primes.push_back(v);
      solve(k-1, v, primes);
      primes.pop_back();
    }
  }
}

int main () {
  
  scanf ("%d %d", &n, &k);

  // clock_t t = clock();
  sieve(); // cout << p.size() << endl;
  for (int i=1; i<p.size(); i++) {        // cout << i << endl;
    for (int j=i+1; j<p.size(); j++) {
      if (isPrime(p[i], p[j]) && isPrime(p[j], p[i])) {
        edge[p[i]].push_back(p[j]);
        // printf ("%d %d\n", p[i], p[j]);
      }
    }
  }
  // printf ("%lf\n", ((double) clock() - t) / CLOCKS_PER_SEC);
  
  
  vector <int> tmp;
  
  for (int i=1; i<p.size(); i++) edge[0].push_back(p[i]);
  solve(k, 0, tmp);
  
  sort (ans.begin(), ans.end());
  for (int i=0; i<ans.size(); i++) printf ("%d\n", ans[i]);
  
  return 0;
} 