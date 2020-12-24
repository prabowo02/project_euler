#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

// Thanks to e-maxx.ru
LL gcd (LL a, LL b, LL & x, LL & y) {
  if (a == 0) {
    x = 0; y = 1;
    return b;
  }
  LL x1, y1;
  LL d = gcd (b%a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}
 
bool find_any_solution (LL a, LL b, LL & x0, LL & y0) {
  gcd (abs(a), abs(b), x0, y0); 
  return true;
}

int Main () {
    LL a, b, n;
    scanf ("%lld %lld %lld", &a, &b, &n);
    
    LL x, y;
    find_any_solution(a, b, x, y);
    // (-y) / x
    
    LL step = (n - x) / b;
    x += step * b;
    y -= step * a;
    
    printf ("%lld %lld\n", -y, x);
    return 0;
}

int main() {
    int t;
    scanf ("%d", &t);
    while (t--) Main();
    return 0;
}
