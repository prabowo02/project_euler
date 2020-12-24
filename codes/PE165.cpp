#include<bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef pair<int, int> frac;
typedef pair<frac, frac> point;

point intersect(vector<int> x, vector<int> y) {
    return { 
        { 
            (x[0]*y[1] - y[0]*x[1]) * (x[2] - x[3]) - (x[0] - x[1]) * (x[2]*y[3] - y[2]*x[3]), 
            (x[0] - x[1]) * (y[2] - y[3]) - (y[0] - y[1]) * (x[2] - x[3]) 
        }, 
        {
            (x[0]*y[1] - y[0]*x[1]) * (y[2] - y[3]) - (y[0] - y[1]) * (x[2]*y[3] - y[2]*x[3]),
            (x[0] - x[1]) * (y[2] - y[3]) - (y[0] - y[1]) * (x[2] - x[3])
        }
    };
}

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

void simplify(frac &f) {
    if (f.y < 0) {
        f.x *= -1;
        f.y *= -1;
    }
    int tmp = gcd(abs(f.x), f.y);
    f.x /= tmp; f.y /= tmp;
}

void simplify(point &p) {
    simplify(p.x); simplify(p.y);
}

bool inRange(frac x, int l, int r) {
    if (l > r) swap(l, r);
    if (x.y < 0) x.x *= -1, x.y *= -1;
    return 1LL * l * x.y <= x.x && x.x <= 1LL * r * x.y;
}

bool interior(point p, vector<int> x, vector<int> y) {
    point ep1 = {{x[0], 1}, {y[0], 1}}; simplify(ep1);
    point ep2 = {{x[1], 1}, {y[1], 1}}; simplify(ep2);
    simplify(p);
    return inRange(p.x, x[0], x[1]) && inRange(p.y, y[0], y[1]) && p != ep1 && p != ep2;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int s = 290797;
    int line[n][4];
    for (int i=0; i<n; i++) {
        for (int j=0; j<4; j++) {
            line[i][j] = (s = 1LL * s * s % 50515093) % 500;
            // cerr << line[i][j] << " ";
        } // cerr << endl;
    }
    
    vector<point> ans;
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            point tmp = intersect({line[i][0], line[i][2], line[j][0], line[j][2]}, {line[i][1], line[i][3], line[j][1], line[j][3]});
            if (tmp.x.y == 0) continue;
            if (!interior(tmp, {line[i][0], line[i][2]}, {line[i][1], line[i][3]}) || !interior(tmp, {line[j][0], line[j][2]}, {line[j][1], line[j][3]})) continue;
            
            
            simplify(tmp);
            ans.push_back(tmp);
        }
    }
    
    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
    
    printf("%d\n", ans.size());
    
    return 0;
}
