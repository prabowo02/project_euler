// Suppose we would like to fill room of size r * s, r ≤ s without 4 tatami meet at a point
// If r * s is odd, then obviously you cant fill it
// If r = 1 or r = 2, there is a way to fill it
// If room size is of the form a * (a + 1), a ≥ 2, then there is a way to fill it
//   starts from size 2 * 3, then repeatedly fill its perimeter (i.e. from size x * (x + 1), you obtain (x + 1) * (x + 2))
// If room size is of the form a * a or a * (a + 2), a ≥ 2, then there is also a way to fill it.
//   The way to construct it is similar to the a * (a + 1) case
// If r is odd, then the room can be decomposed into several rooms of the form r * (r + 1) and r * (r - 1)
// If r is even, then the room can be decomposed into several rooms of the form r * 1, r * r, and r * (r - 2), where
//   r * 1 must alternate with the other two types
// These cases are sufficient. Sketch of proof can be found here: https://oeis.org/A068920/a068920.txt

// Therefore, if r is odd, c must be expressible by a(r-1) + b(r+1), for some non-negative integers a, b
//   r-1 and r+1 are both even, so c must be even
//   Notice that gcd(r-1, r+1) = 2, so:
//   - if c/2 > ((r-1)(r+1)/4 - (r-1)/2 - (r+1)/2), then c is expressible
//   - if c/2 is divisible by either (r-1)/2 or (r+1)/2, then c is expressible
//   - otherwise c is not expressible
//   - These are consequences of chicken mcnugget theorem

// If r is even, then either c, c-1, or c+1, must be expressible by a*(r+1) + b*(r-1)
//   r+3 and r-1 are coprime
//   Using chicken mcnugget, we can easily check expressibility of c, c-1, and c+1

#include <bits/stdc++.h>
using namespace std;

// Assume x and y coprime, can we express z as a*x + b*y for some non-negative integers a, b
// ix is x^-1 mod y, iy is y^-1 mod x
bool chickenMcNugget(int x, int y, int z, int ix, int iy) {
  if (z >= (x-1) * (y-1)) return true;
  int a = z * ix % y, b = z * iy % x;
  return a*x + b*y == z;
}

// Assume r <= c, and r*c is even
bool tatamiFree(int r, int c) {
  if (r <= 2) return false;
  if (r % 2 == 1) return !chickenMcNugget((r-1)/2, (r+1)/2, c/2, (r-1)/2, 1);
  int ix = (r + 2) / 2 * r % (r + 1), iy = r / 2;
  return !chickenMcNugget(r-1, r+1, c-1, ix, iy) && !chickenMcNugget(r-1, r+1, c, ix, iy) && !chickenMcNugget(r-1, r+1, c+1, ix, iy);
}

const int N = 100000000;

int T[N];

int main() {
  for (int r = 1; r*r < N; ++r) {
    int step = r % 2 + 1;
    for (int c = r + (r % 2); r*c < N; c += step) {
      T[r*c] += tatamiFree(r, c);
    }
  }

  int n;
  scanf("%d", &n);

  for (int i = 2; i < N; i += 2) {
    if (T[i] == n) {
      printf("%d\n", i);
      break;
    }
  }
  return 0;
}
