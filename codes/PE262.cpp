#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-7;

double h(double x, double y) {
  // the "abs" part is actually a circle, with center around (700, 700)
  return ( 5000-0.005*(x*x+y*y+x*y)+12.5*(x+y) ) * exp( -abs(0.000001*(x*x+y*y)-0.0015*(x+y)+0.7) );
}

double partial_hx(double x, double y) {
  return (h(x + EPS, y) - h(x, y)) / EPS;
}

double partial_hy(double x, double y) {
  return (h(x, y + EPS) - h(x, y)) / EPS;
}

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

const int PREC = 50;
const int INIT = 200*PREC;
const int BOUND = 1600*PREC;
bool vis[BOUND + 1][BOUND + 1];

bool bfs(double f) {
  memset(vis, false, sizeof vis);
  queue<pair<int, int>> q;
  if (h(INIT, INIT) > f) return false;
  q.emplace(INIT, INIT);
  vis[INIT][INIT] = true;

  while (q.size()) {
    int x, y;
    tie(x, y) = q.front();
    q.pop();

    for (int k = 0; k < 4; ++k) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx > BOUND || ny < 0 || ny > BOUND || nx > ny) continue;
      if (vis[nx][ny] || h((double) nx / PREC, (double) ny / PREC) > f) continue;
      vis[nx][ny] = true;
      q.emplace(nx, ny);
    }
  }

  return vis[1400*PREC][1400*PREC];
}

double findFmin() {
  double l = 10396.46218, r = 10396.46220;
  for (int it = 0; it < 10; ++it) {
    double mid = (l + r) / 2;
    if (bfs(mid)) {
      r = mid;
    } else {
      l = mid;
    }
    fprintf(stderr, "%d %.8lf %.8lf\n", it, l, r);
  }
  return l;
}

pair<double, double> findTangent(double x0, double y0) {
  for (int i = 600*PREC; i <= BOUND; ++i) {
    if (i % 1600 == 0) cerr << (double) i / PREC << endl;
    for (int j = 0; j <= BOUND; ++j) {
      double x = (double) i / PREC;
      double y = (double) j / PREC;

      if (fabs(h(x, y) - 10396.462194) > 0.001) continue; 
      // cerr << x << " "  << y << " " << (y - y0) / (x - x0) << " " << -partial_hx(x, y) / partial_hy(x, y) << endl;
      if (fabs((y - y0) / (x - x0) + partial_hx(x, y) / partial_hy(x, y)) > 0.01) continue;
      // cerr << partial_hx(x, y) << " " << partial_hy(x, y) << endl;
      return {x, y};
    }
  }
  return {-1, -1};
}

double path(double x, double y, double xx, double yy) {
  double ret = 0;
  int it = 0;
  while (hypot(x - xx, y - yy) > 1) {
    if (it % 100000 == 0) cerr << x << " " << y << endl;
    ++it;
    
    double dy = -partial_hx(x, y) * EPS;
    double dx = partial_hy(x, y) * EPS;
    ret += hypot(dx, dy);
    x += dx;
    y += dy;
  }
  return ret;
}

int main() {
  // printf("%.8lf\n", findFmin());
  double f = 10396.462194;

  // pair<double, double> p = findTangent(200, 200);
  // pair<double, double> q = findTangent(1400, 1400);
  // printf("%.8lf %.8lf\n", p.first, p.second);
  // printf("%.8lf %.8lf\n", q.first, q.second);
  pair<double, double> p = {48.252876, 624.651883};
  pair<double, double> q = {873.040123, 1536.042073};

  cerr << path(p.first, p.second, q.first, q.second) << endl;
  cout << hypot(p.first - 200, p.second - 200) + path(p.first, p.second, q.first, q.second) + hypot(q.first - 1400, q.second - 1400);

  return 0;
}
