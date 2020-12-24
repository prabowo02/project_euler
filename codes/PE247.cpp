#include <bits/stdc++.h>
using namespace std;

#define double long double

int k, l, b;

int cnt;
tuple<int, int, double, double> stek[20];

int area_cnt;
double area[400];

void dfs(double limit) {
  int cur = 0;
  stek[cur++] = {0, 0, 1, 1};

  area_cnt = cnt = 0;

  int l, b; double c, x;
  while (cur) {
    tie(l, b, c, x) = stek[--cur];

    double dc = (c + sqrt(c*c + 4)) / 2 - x;
    if (dc < limit) continue;

    if (l == ::l && b == ::b) {
      area[area_cnt++] = dc;
    }
    ++cnt;

    stek[cur++] = {l+1, b, c + dc, x + dc};
    stek[cur++] = {l, b+1, c - dc, x};
  }
}

int C(int n, int k) {
  long long ret = 1;
  for (int i = 1; i <= k; ++i) {
    ret = ret * (n-i+1) / i;
  }

  return ret;
}

int main() {
  scanf("%d %d %d", &k, &l, &b);
  
  dfs(0.00011);
  k = k - (C(l+b, b) - area_cnt) - 1;
  nth_element(area, area + k, area + area_cnt);

  dfs(area[k]);
  printf("%d\n", cnt);
  return 0;
}
