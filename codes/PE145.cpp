#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

int n;
int digits[20];

LL dp[12][2][2][3];
LL f(int x, bool send, bool receive, int safe) {
  // cerr << x << " " << send << " " << receive << " " << safe << endl;
  if (x < 0) return (safe >= 1) && !send;
  LL &ret = dp[x][send][receive][safe]; // cerr << ret << endl;
  if (~ret) return ret;
  
  ret = 0;
  for (int i=(x==0); i<10; i++) {
    for (int j=(x==0); j<10; j++) {
      if ((n & 1) && (x == n >> 1)) {
        if (i != j) continue;
      } else if (i + j + receive & 1); else continue;
      if ((i + j > 9) != send) continue;
      
      // cerr << i << " " << j << endl;
      
      int nsafe = safe;
      if (i < digits[n - x - 1]) nsafe = 1;
      else if (i > digits[n - x - 1]) nsafe = 0;
      
      if (nsafe == 2) {
        if (j < digits[x]) nsafe = 1;
        else if (j > digits[x]) nsafe = 0;
      }
      
      ret += f(x-1, 1 - (i + j & 1), i + j + receive > 9, nsafe);
    }
  }
  
  return ret;
}

LL g[20] = {0, 0, 20, 100, 600, 0, 18000, 50000, 540000, 0, 16200000, 25000000, 486000000, 0, 14580000000LL, 12500000000LL, 437400000000LL, 0, 13122000000000LL, 6250000000000LL};

int main() {
  int t;
  scanf("%d", &t);
    
  for (int i=1; i<20; i++) g[i] += g[i-1];
  
  long long N;
  while (t--) {
    scanf("%lld", &N);
        
        if (N < 10) {
            printf("0\n");
            continue;
        }
        
    N--;
    
    n = 0;
    while (N) {
      digits[n++] = N % 10;
      N /= 10;
    }
    
    // cerr << n << endl;
    
    for (int i=0; i<=n-1>>1; i++) {
      for (int j=0; j<4; j++) for (int k=0; k<3; k++) dp[i][j & 1][j >> 1 & 1][k] = -1;
    }
    
    printf("%lld\n", f(n-1>>1, 0, 0, 2) + g[n-1]);
  }
  return 0;
}
