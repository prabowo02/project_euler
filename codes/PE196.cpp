#include <bits/stdc++.h>
using namespace std;

const int N = 50000005;

long long get(int x, int y) {
  return 1LL * x * (x-1) / 2 + y;
}

bool prime[N], segprime[N];
long long S(int n) {
  if (n == 1) return 0;
  if (n == 2 || n == 3) return 5;  
  
  long long st = get(n-2, 1);
  long long en = get(n+2, n+2);
  
  for (long long i=0; i*i <= en; i++) prime[i] = 1;  
  for (long long i=0; i<=en-st; i++) segprime[i] = 1;  
  
  for (long long i = 2; i*i <= en; ++i) {
    if (!prime[i]) continue;
    for (long long j=i*2; j*j<=en; j+=i) prime[j] = 0;
    
    for (long long j = st + (st % i == 0 ? 0 : i - st % i); j <= en; j += i)
      segprime[j - st] = 0;
  }  
  
  long long ret = 0;
  int dx[9] = {0, -1, -1, -1, 0, 1, 1, 1, 0};
  int dy[9] = {1, 1, 0, -1, -1, -1, 0, 1, 0};
  for (int i=1; i<=n; i++) {    
    if (!segprime[get(n, i) - st]) continue;
        
    for (int j=0; j<9; j++) {
      int cnt = 0;
      int x = n + dx[j];
      int y = i + dy[j];
      if (y < 1 || y > x) continue;
      if (!segprime[get(x, y) - st]) continue;
      
      for (int k=0; k<8; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        
        if (ny < 1 || ny > nx) continue;
        cnt += segprime[get(nx, ny) - st];
      }
      
      if (cnt >= 2) {
        ret += get(n, i);
        break;
      }
    }
  }
  
  return ret;
}

int main() {
  int a, b;
  scanf("%d %d", &a, &b);
  printf("%lld\n", S(a) + S(b));
  return 0;
}
