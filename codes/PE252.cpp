// https://www.cs.princeton.edu/research/techreps/TR-153-88

#include <algorithm>
#include <iostream>
using namespace std;

#define x first
#define y second

typedef pair<int, int> Point;

const int N = 750;

int n, m;
Point points[N], polygon[N*2];

int qfront[N], qback[N];
int q[N][N];

int outSz[N];
int outEdges[N][N];

int inSz[N];
int inEdges[N][N];

int areas[N][N];
long long counts[N][N];

int areaAns;
long long cntAns;

int cross(const Point &p, const Point &q, const Point &r) {
  return (q.x - p.x) * (r.y - q.y) - (q.y - p.y) * (r.x - q.x);
}

int dist(Point p, Point q) {
  return (p.x-q.x)*(p.x-q.x) + (p.y-q.y)*(p.y-q.y);
}

bool visible(const Point &p, const Point &q, const Point &r) {
  int area = cross(p, q, r);
  if (area != 0) return area > 0;
  return dist(p, q) + dist(q, r) == dist(p, r);
}

void proceed(int i, int j) {
  while (qfront[i] < qback[i] && visible(polygon[q[i][qfront[i]]], polygon[i], polygon[j])) {
    proceed(q[i][qfront[i]], j);
    ++qfront[i];
  }
  outEdges[i][outSz[i]++] = j;
  inEdges[j][inSz[j]++] = i;
  q[j][qback[j]++] = i;
}
// Returns visibility graph of a star-shaped polygon with points.back() as kernel.
void constructVisibilityGraph() {
  for (int i = 0; i+1 < m; ++i) {
    qfront[i] = qback[i] = 0;
    outSz[i] = inSz[i] = 0;
  }

  for (int i = 0; i+2 < m; ++i) {
    proceed(i, i+1);
  }

  // cerr << "Done construct" << endl;
}

void largestConvexArea() {
  for (int i = 0; i < m-1; ++i) {
    for (int j = 0; j < m-1; ++j) {
      areas[i][j] = counts[i][j] = 0;
    }
  }

  for (int i = ::m-2; i >= 0; --i) {
    int m = 0;
    long long s = 0;
    int l = outSz[i] - 1;
    for (int j = inSz[i] - 1; j >= 0; --j) {
      while (l >= 0 && cross(polygon[inEdges[i][j]], polygon[i], polygon[outEdges[i][l]]) > 0) {
        m = max(m, areas[i][outEdges[i][l]]);
        s += counts[i][outEdges[i][l]];
        --l;
      }
      int area = cross(polygon[::m-1], polygon[inEdges[i][j]], polygon[i]);
      areaAns = max(areaAns,
        areas[inEdges[i][j]][i] = m + area
      );
      if (area > 0) cntAns += counts[inEdges[i][j]][i] = s + 1;
    }
    // if (polygon[::m-1] == make_pair(-1, 0)) cerr << cntAns << endl;
    // if (::m == n) cerr << cntAns << endl;
  }

  // cerr << areaAns << " " << cntAns << endl;
}

void largestEmptyConvexArea() {
  sort(points, points + n);
  n = unique(points, points + n) - points;

  for (int i = 0; i < n; ++i) {
    m = 0;
    for (int j = i; j < n; ++j) {
      polygon[m++] = points[j];
    }
    swap(polygon[0], polygon[m-1]);
    sort(polygon, polygon + m-1, [&](Point p, Point q) {
      int kross = cross(polygon[m-1], p, q);
      if (kross == 0) return dist(p, polygon[m-1]) < dist(q, polygon[m-1]);
      return kross > 0;
    });

    {
      int mm = 0;
      Point npolygon[m*2];
      for (int i = 0, j; i < m-1; i = j) {
        j = i;
        while (j < m-1 && cross(polygon[m-1], polygon[i], polygon[j]) == 0) ++j;

        for (int k = j-1; k > i; --k) npolygon[mm++] = polygon[k];
        for (int k = i; k < j; ++k) npolygon[mm++] = polygon[k];
      }
      npolygon[mm++] = polygon[m-1];

      m = mm;
      for (int i = 0; i < m; ++i) {
        polygon[i] = npolygon[i];
        // cerr << "poly: " << polygon[i].x << " " << polygon[i].y << endl;
      }
    }

    constructVisibilityGraph();
    largestConvexArea();
  }

  return;
}

void readPoints() {
  int s0, m;
  cin >> n;
  cin >> s0;
  cin >> m;

  for (int i = 0; i < n; ++i) {
    s0 = 1LL * s0 * s0 % m;
    int x = s0 % 2000 - 1000;
    s0 = 1LL * s0 * s0 % m;
    int y = s0 % 2000 - 1000;

    points[i] = make_pair(x, y);
  }
}

void testPoints() {
  n = 0;
  points[n++] = {-1, 0};
  points[n++] = {0, 0};
  points[n++] = {1, 0};
  points[n++] = {1, 1};
  points[n++] = {1, 2};
  // points[n++] = {1, -1};
  // points[n++] = {1, -2};
}

int main() {
  readPoints();
  // testPoints();
  largestEmptyConvexArea();
  cout << areaAns/2 << "." << areaAns%2 * 5 << endl;
  cout << cntAns << endl;
  return 0;
}
