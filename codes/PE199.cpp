#include <bits/stdc++.h>
using namespace std;

const double PI = 3.1415926535897932384626433;

double descartes(double a, double b, double c) {
  return a + b + c + sqrt(a*b + b*c + a*c)*2;
}

double descartesR(double a, double b, double c) {
  return 1.0 / descartes(1.0 / a, 1.0 / b, 1.0 / c);
}

struct three {
  double a, b, c;
  int n;
  
  three(double _a, double _b, double _c, int _n): a(_a), b(_b), c(_c), n(_n) {}
};

int n, m;

double A;
void dfs(double a, double b, double c, int n, int depth=1) {
    if (m == depth) return;
    
    double r = descartesR(a, b, c);
    A -= n * r*r;
    
    dfs(a, b, r, n, depth+1);
    dfs(a, r, c, n, depth+1);
    dfs(r, b, c, n, depth+1);
}

int main() {  
  scanf("%d %d", &n, &m);
  
  double r0 = 1.0 / (1 + 1.0/sin(PI / n));
  A = 1 - n * r0*r0;
  
  double r11 = 1 - r0*2;
  double r12 = descartesR(r0, r0, -1);
  
  A -= r11*r11;
  A -= n * r12*r12;
  
  dfs(r0, r0, r11, n);
  dfs(r0, r0, r12, n);
  dfs(r0, r12, -1, n*2);

  printf("%.12lf\n", A);
  
  return 0;
}
