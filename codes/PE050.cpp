#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL limit = 10000000LL;

vector <LL> prefix;

bool isPrime (LL x) {
  for (LL i=2; i*i<=x; i++) {
    if (x % i == 0) return 0;
  }
  
  return 1;
}

bool prime[limit];

void init() {
  memset (prime, 1, sizeof prime);
  prime[0] = prime[1] = 0;
  prefix.push_back(0);
  
  for (LL i=2; i<limit; i++) {
    if (prime[i]) {
      for (LL j=2*i; j<limit; j+=i) prime[j] = 0;
      prefix.push_back(prefix.back() + i);
    }
  }
  
  fprintf(stderr, "%lld\n", prefix.back());
}

int Main () {
  LL n;
  scanf ("%lld", &n);
  
  LL largestPrime = -1;
  int cons = 0;
  for (int i=0; i<16; i++) {
    int idx = upper_bound(prefix.begin(), prefix.end(), n + prefix[i]) - prefix.begin() - 1;
    
    // printf ("%lld\n", prefix[idx] - prefix[i]);
    while (idx > i && !isPrime(prefix[idx] - prefix[i])) idx--;
    // printf ("%lld\n", prefix[idx] - prefix[i]);
    
    if (idx - i > cons) {
      cons = idx - i;
      largestPrime = prefix[idx] - prefix[i];
    } else if (idx - i == cons) {
      if (prefix[idx] - prefix[i] < largestPrime) 
        largestPrime = prefix[idx] - prefix[i];
    }
    
  }
  printf ("%lld %d\n", largestPrime, cons);
  return 0;
}

/*
  Some (helpful) tc:
  in: 14570093459
  out: 14570093459 49919
*/

int main () {
  init();
  
  int t;
  scanf ("%d", &t);
  while (t--) Main();
  
  return 0;
}
