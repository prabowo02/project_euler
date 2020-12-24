// https://arxiv.org/pdf/1107.4890.pdf

#include <bits/stdc++.h>
using namespace std;

const int N = 10000001;

long long n, k;

int distinctPrimeCount[N];

int mu(int n) {
  if (distinctPrimeCount[n] < 0) return 0;
  if (distinctPrimeCount[n] & 1) return -1;
  return 1;
}

// floor(sqrt(n / i))
int xsqrt(long long n, int i) {
  int ret = sqrt((long double) n / i);  
  while (1LL * ret * ret * i > n) ret--;
  while (1LL * (ret+1) * (ret+1) * i <= n) ret++;
  return ret;
}

long long solve(long long n, int k) {
    long long ans = 0;
    for (int i=1; i<N; i++) {
        if (mu(i) == 0) continue;
        long long tmp = n;
        for (int j=0; j<k; j++) tmp /= i;
        if (tmp == 0) break;
        
        ans += tmp * mu(i);
    }
    return ans;
}

int main() {
    scanf("%lld %lld", &n, &k);
    
    if (k == 1) return 0 * printf("1\n");
    if (k >= 60) return 0 * printf("%lld\n", n);
    
    for (int i=2; i<N; i++) {
        if (distinctPrimeCount[i] != 0) continue;
        for (long long j=1LL*i*i; j<N; j+=i*i) distinctPrimeCount[j] = -1000000000;
        for (int j=i; j<N; j+=i) distinctPrimeCount[j]++;
    } 
    
    if (k > 2 || n < 1000000) return 0 * printf("%lld\n", solve(n, k));
    
    int I = pow((long double) 0.25 * n, (long double) 1.0 / 3) - 10;
    if (n > 1000000000000000LL) I = pow((long double) n, (long double) 0.2) * pow(log(log((long double) n)), (long double) 0.8);
    int D = xsqrt(n, I); 
    
    cerr << "I = " << I << endl;
    cerr << "D = " << D << endl;
    
    vector<int> M(D+1, 0);
    for (int i=1; i<=D; i++) {
      M[i] = M[i-1] + mu(i);
    }
    
    // M[x_i]
    vector<int> Mx(I);
    
    long long ans = -1LL * (I-1) * M[D];
    for (int i=I-1; i>=1; i--) {
      int xi = xsqrt(n, i); 
      assert(xi > D);
      // if ((int) sqrt(xi) * (int) sqrt(xi) == xi) cerr << "Perfect" << endl;
      Mx[i] = 1;
      
      int d;
      for (d=2; 1LL*d*d<=xi; d++) {
        if (xi > 1LL*D*d) Mx[i] -= Mx[d*d*i];
        else Mx[i] -= M[xi/d]; 
      }
      
      int sum = d-2;

      // cerr << "d: " << d << endl;
      // cerr << "xi: " << xi << endl;

      int xd = xi/d;
      // (x/d)**2 < xi
      for (int xid = 1; 1LL*xid <= xd; xid++) {     
        Mx[i] -= M[xid] * (xi/xid - xi/(xid+1));

        sum += xi/(xid) - xi/(xid+1);
        // cerr << "sum: " << xi/xid << " " << xi/(xid+1) << endl;
      }

      if (sum != xi-1) cerr << "Sum" << endl;
      
      ans += Mx[i];
    }
    
    for (int d=1; d<=D; d++) ans += n / d / d * mu(d);
    
    printf("%lld\n", ans);
    
    return 0;
}
