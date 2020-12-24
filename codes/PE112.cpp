/**
 * We start from p = 0, and q = 100 (as all integer from 1 to 100 are not bouncy).
 * We assume the next k integer after q are all bouncy.
 * Therefore, in each iteration, p <- p+k, q <- q+k, where k is the minimum integer where (p+k)/(q+k) >= n/m.
 * Iterate until p/q is actually >= n/m.
 */

#include <bits/stdc++.h>
using namespace std;

typedef __int128 int128;

class Bouncy {
private:
  vector<int> v;

  void convert(int128 n) {
    v.clear();
    while (n) {
      v.push_back(n % 10);
      n /= 10;
    }
  }
  
  int128 dp[30][2][11];
  
  int128 increasing(int x, int lim, int lst) {
    if (x == -1) return 1;
    if (~dp[x][lim][lst]) return dp[x][lim][lst];
    
    int m = (lim ? v[x] : 9);
    int128 ret = 0;
    for (int i=lst; i<=m; i++) {
      ret += increasing(x-1, lim * (i == v[x]), i);
    }
    return dp[x][lim][lst] = ret;
  }
  
  int128 increasing() {
    memset(dp, -1, sizeof dp);
    return increasing((int) v.size() - 1, 1, 0);
  }
  
  int128 decreasing(int x, int lim, int lst) {
    if (x == -1) return 1;
    if (~dp[x][lim][lst]) return dp[x][lim][lst];
    
    int128 ret = 0;
    int st = 0, en;
    if (lst == 10) {
      ret += decreasing(x-1, 0, 10);
      st = 1;
    }
    en = min(lim ? v[x] : 9, lst);
    for (int i=st; i<=en; i++) {
      ret += decreasing(x-1, lim * (i == v[x]), i);
    }
    
    return dp[x][lim][lst] = ret;
  }
  
  int128 decreasing() {
    memset(dp, -1, sizeof dp);
    return decreasing((int) v.size() - 1, 1, 10);
  }
  
  int128 increasingDecreasing() {
    int128 ret = v.back() - 1 + ((int) v.size() - 1) * 9 + 1;
    
    bool ok = 1;
    for (int i=(int)v.size()-2; i>=0; i--) {
      if (v[i] < v.back()) {
        ok = 0;
        break;
      }
      if (v[i] > v.back()) break;
    }
    
    return ret + ok;
  }
  
public:
  int128 count(int128 n);
};

int128 Bouncy::count(int128 n) {
  convert(n);
  return n - increasing() - decreasing() + increasingDecreasing() + 1;
}

int128 ceil(int128 n, int128 m) {
  return (n + m - 1) / m;
}

Bouncy bouncy = Bouncy();

ostream & operator << (ostream &os, __int128 x) {
  vector<int> v;
  if (x == 0) v.push_back(0);
  while (x > 0) v.push_back(x % 10), x /= 10;
  reverse(v.begin(), v.end());
  for (int d: v) os << d;
  return os;
}

long long solve() {
  long long n, m;
  scanf("%lld %lld", &n, &m);  
  
  int128 p = 0;
  int128 q = 100;  
  while (p*m < q*n) {    
    int128 k = ceil(q*n - p*m, (int128) m-n);
    q += k;
    p = bouncy.count(q);
  }
  
  cout << q << endl;
  
  return 0;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) solve();
  return 0;
}