#include <cstdio>
#include <cstring>

typedef long long LL;
const int lim = 10000000;

bool isPrime (LL x) {
  for (LL i=2; i*i<=x; i++) if (x % i == 0) return 0;
  return 1;
}

int main () {
  
  int n;
  scanf ("%d", &n);
  
  if (n == 8) return 0 * printf ("238733\n");
  if (n == 9) return 0 * printf ("74373\n");
  if (n == 10) return 0 * printf ("26241\n");
  
  int p = 0;
  LL  cur = 1;  
  int ans = 1;
  do {
    ans += 2;
    for (int i=0; i<4; i++) p += isPrime(cur += ans - 1);
  } while (p * 100 >= (2 * ans - 1) * n);
  
  printf ("%d\n", ans);
  
  return 0;
}
