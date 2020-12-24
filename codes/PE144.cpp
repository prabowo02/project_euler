#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define double long double

#define x first
#define y second

typedef pair<double, double> point;

const double EPS = 1e-7;
const double R = 1;

struct Line {
    double a, b, c;
    
    Line(point p, point q) {
        a = q.y - p.y;
        b = p.x - q.x;
        c = a * p.x + b * p.y;
        
        a *= R, b *= R, c *= R;
    }
};

double a, b, c;

pair<point, point> intersect(Line l) {
    double A = a * l.b * l.b + b * l.a * l.a;
    double B = l.a * b * l.c * -2;
    double C = b * l.c * l.c - l.b * l.b * c;
    
    double D = B*B - A*C*4;
    double x = (-B + sqrt(D)) / (A * 2);
    double xx = (-B - sqrt(D)) / (A * 2);
        
    B = a * l.b * l.c * -2;
    C = a * l.c * l.c - c * l.a * l.a;
    
    D = B*B - A*C*4;    
    double y = (-B + sqrt(D)) / (A * 2);
    double yy = (-B - sqrt(D)) / (A * 2);
    
    if (l.a * l.b <= 0) return {{x, y}, {xx, yy}};
    return {{x, yy}, {xx, y}};
}

bool equals (point p, point q) {
    return (fabs(p.x - q.x) < EPS && fabs(p.y - q.y) < EPS);
}

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        cin >> a >> b >> c;
        double A = sqrt(c / a);
        double B = sqrt(c / b);
        a *= R, b *= R, c *= R;
        
        point p, q;
        cin >> p.x >> p.y >> q.x >> q.y;
        
        pair<point, point> ppp = intersect(Line(p, q));
        // cerr << ppp.x.x << " " << ppp.x.y << " " << ppp.y.x << " " << ppp.y.y << endl;
        
        int cnt = 0;
        while (q.y < EPS || fabs(q.x) > 1e-2 + EPS) {            
            // cerr << q.x << " " << q.y << endl;
                        
            double N = hypot(q.x / A / A, q.y / B / B);
            double nx = -q.x / A / A / N;
            double ny = -q.y / B / B / N;
                        
            double dn = nx * (q.x - p.x) + ny * (q.y - p.y);
            point nq = {(q.x - p.x) - 2*dn*nx, (q.y - p.y) - 2*dn*ny};
            nq.x += q.x, nq.y += q.y;
            
            pair<point, point> points = intersect(Line(q, nq));
            
            if (equals(points.first, q)) nq = points.second;
            else nq = points.first;
            
            p = q;
            q = nq;
                        
            cnt++;
        }
        
        cout << cnt << "\n";
    }
    return 0;
}
