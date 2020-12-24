#include <bits/stdc++.h>
using namespace std;

unsigned long long N; int k;

vector<int> primes;
bool isprime(int n) {
  for (int i=2; i*i <= n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}

vector<long long> ham1, ham2;
void f(unsigned long long n = 1, int k = 0) {
  if (n > N) return;
  if (k == primes.size()) {
    ham1.push_back(n);
    return;
  }
  f(n, k+1); f(n * primes[k], k);
}

int main() {
  clock_t t = clock();
  scanf("%llu %d", &N, &k);
  
  for (int i=25; i<=k; i++) if (isprime(i)) primes.push_back(i);
  f();
  ham2 = ham1; ham1.clear();
  
  primes.clear();
  for (int i=2; i<=min(k, 25); i++) if (isprime(i)) primes.push_back(i);
  f();
  
  long long ans = 0;
  sort(ham2.begin(), ham2.end());
  for (long long num: ham1) {
    ans += upper_bound(ham2.begin(), ham2.end(), N / num) - ham2.begin();
  }
  printf("%lld\n", ans);
  
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  
  return 0;
}
