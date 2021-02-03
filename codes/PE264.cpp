// The triangles apparently satisfies x1 + x2 + x3 = 0 and y1 + y2 + y3 = 5
// From there, iterate for every pair of points with the same distance to origin

#include <bits/stdc++.h>
using namespace std;

const int R = 1000000;

vector<pair<int, int>> points[R];

int main() {
  double ans = 0;

  // seems iterating until 350 is enough, since answer does not increase any further
  for (int lR = 0; lR < R*1000; lR += R) {
    // cerr << lR / R << " " << ans << endl;
    int rR = lR + R;

    for (int i = 0; i < R; ++i) points[i].clear();

    // generate points with distance sqrt(lR) to sqrt(rR)
    for (int x = 0; x*x < rR; ++x) {
      int cSqrt; // ceil(sqrt)
      if (lR < x*x) {
        cSqrt = 0;
      } else {
        cSqrt = ceil(sqrt(lR - x*x));
      }

      for (int y = cSqrt; x*x + y*y < rR; ++y) {
        int n = x*x + y*y - lR;
        points[n].emplace_back(x, y);
        if (x > 0) points[n].emplace_back(-x, y);
        if (y > 0) points[n].emplace_back(x, -y);
        if (x > 0 && y > 0) points[n].emplace_back(-x, -y);
      }
    }

    for (int r = lR; r < rR; ++r) {
      for (pair<int, int> p : points[r - lR]) {
        for (pair<int, int> q : points[r - lR]) {
          if (p >= q) continue;
          pair<int, int> r = {-p.first - q.first, 5 - p.second - q.second};
          if (q >= r) continue;
          if (1LL*r.first*r.first + 1LL*r.second*r.second != p.first*p.first + p.second*p.second) continue;

          double peri = hypot(p.first - q.first, p.second - q.second);
          peri += hypot(q.first - r.first, q.second - r.second);
          peri += hypot(p.first - r.first, p.second - r.second);
          if (peri  <= 100000) {
            ans += peri;
            // Not that many triangles exists
            cerr << peri << ": " << p.first << ", " << p.second << "; " << q.first << ", " << q.second << "; "
                 << r.first << ", " << r.second << endl;
          }
        }
      }
    }
  }

  printf("%.8lf\n", ans);
  printf("%.4lf\n", ans);
  return 0;
}

/* Some of the largest triangles

41508.5: -4291, -6738; -3690, 7085; 7981, -342
41508.5: -7981, -342; 3690, 7085; 4291, -6738
42206: -4589, -6702; -3510, 7325; 8099, -618
42206: -8099, -618; 3510, 7325; 4589, -6702
43682.2: -5287, 6536; -3016, -7847; 8303, 1316
43682.2: -8303, 1316; 3016, -7847; 5287, 6536
44149.8: -5532, -6449; -2820, 8015; 8352, -1561
44149.8: -8352, -1561; 2820, 8015; 5532, -6449
44642.9: -5808, -6331; -2580, 8195; 8388, -1859
44642.9: -8388, -1859; 2580, 8195; 5808, -6331
45211.5: -6155, -6150; -2250, 8405; 8405, -2250
45211.5: -8405, -2250; 2250, 8405; 6155, -6150
45852.6: -6603, -5854; -1770, 8645; 8373, -2786
45852.6: -8373, -2786; 1770, 8645; 6603, -5854
46719.8: -7504, -4953; -540, 8975; 8044, -4017
46719.8: -8044, -4017; 540, 8975; 7504, -4953
46797.8: -7725, -4630; -150, 9005; 7875, -4370
46797.8: -7875, -4370; 150, 9005; 7725, -4630
68604.8: -10560, 7925; -1581, -13108; 12141, 5188
68604.8: -12141, 5188; 1581, -13108; 10560, 7925
77963.1: -9000, 12005; -5896, -13797; 14896, 1797
77963.1: -14896, 1797; 5896, -13797; 9000, 12005
87321.3: -14555, -8400; 0, 16805; 14555, -8400
89303.1: -10549, 13568; -6475, -15920; 17024, 2357
89303.1: -17024, 2357; 6475, -15920; 10549, 13568
96239.8: -15457, -10204; -1111, 18488; 16568, -8279
96239.8: -16568, -8279; 1111, 18488; 15457, -10204

*/
