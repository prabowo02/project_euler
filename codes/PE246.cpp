// Some observations
// - The two given points are already foci of ellipse
// - Major axis = r
// - Simply use the Isoptic equation of ellipse

#include <bits/stdc++.h>
using namespace std;

const __int128 ONE = 1;

int x1, x2, y;
int r;
int p, q;

int dx;
long long p2, q2, r2, dx2;

bool insideEllipse(int x, int y) {
  return 4LL * (ONE*(r2 - dx2)*x*x + ONE*r2*y*y) <= r2*(r2 - dx2);
}

bool insideOrthoptic(int x, int y) {
  return 4LL*x*x + 4LL*y*y <= r2 + (r2 - dx2);
}

bool largeTangent(int x, int y) {
  if (insideOrthoptic(x, y)) return true;
  long long x2 = 1LL * x * x;
  long long y2 = 1LL * y * y;

  __int128 lhs = p * (4*x2 + 4*y2 - 2*r2 + dx2);
  lhs *= lhs;

  __int128 rhs = ONE*16*q2*(ONE*r2*y2 + ONE*(r2 - dx2)*x2) - ONE*4*q2*r2*(r2 - dx2);

  return lhs <= rhs;
}

long long solve() {
  auto searchRight = [&](int y) {
    int r = 1;
    while (insideEllipse(r, y) || largeTangent(r, y)) r *= 2;
    if (r == 1) return 1;
    int l = r / 2;

    int x = r;
    while (l <= r) {
      int mid = l + r >> 1;

      if (insideEllipse(mid, y) || largeTangent(mid, y)) {
        l = mid + 1;
      } else {
        r = mid - 1;
        x = mid;
      }
    }

    return x;
  };

  auto searchLeft = [&](int y) {
    int r = 1;
    while (insideEllipse(r, y)) r *= 2;
    if (r == 1) return 1;
    int l = r / 2;

    int x = r;
    while (l <= r) {
      int mid = l + r >> 1;

      if (insideEllipse(mid, y)) {
        l = mid + 1;
      } else {
        r = mid - 1;
        x = mid;
      } 
    }

    return x;
  };

  long long ans = (searchRight(0) - searchLeft(0)) * 2;
  for (int y = 1; insideEllipse(0, y) || largeTangent(0, y); ++y) {
    if (!insideEllipse(0, y)) ans += 2;
    ans += (searchRight(y) - searchLeft(y)) * 4;
    // cout << y << " " << searchLeft(y) << " " << searchRight(y) << endl;
  }

  return ans;
}

int main() {
  scanf("%d %d %d", &x1, &x2, &y);
  scanf("%d", &r);
  scanf("%d %d", &p, &q);

  if (x2 < x1) swap(x1, x2);
  dx = x2 - x1;
  dx2 = dx * dx;
  p2 = p * p;
  q2 = q * q;
  r2 = r * r;

  // shift to "center"
  x1 = -dx / 2;
  x2 = dx / 2;
  y = 0;

  largeTangent(1, 1); largeTangent(2, 2); largeTangent(3, 3); largeTangent(4, 4);
  printf("%lld\n", solve());
  return 0;
}
