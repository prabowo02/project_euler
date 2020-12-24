// Best approximation of x bounded by d can be done by stern-brocot tree 
// (i.e. iterate through the tree until either one of the fractions has denominator > d)
// To speed up the tree traversal, we use an algorithm (available on wiki) 
// which can calculate the a for the continued fraction [a0; a1, a2, ...]
// therefore, we can traverse R a0 times, L a1 times, R a2 times, and so on.
// Big Integer is implemented using bit manipulation

#include <bits/stdc++.h>
using namespace std;

#define int128 unsigned __int128

typedef int128 int256[2];
typedef int128 int384[3];

const int MN = 1500001;
const long long MOD = 1LL * 1000000007 * 1000000009;

int m;
long long denominator;

int floorS[MN];

// cout << int128;
std::ostream& operator << ( std::ostream& os, int128 value ) {
    vector<int> v;
    while (value > 0) {
        v.push_back(value % 10);
        value /= 10;
    }
    if (v.size() == 0) v.push_back(0);
    reverse(v.begin(), v.end());
    for (int d: v) os << d; 
    return os;
}

// x * y = z
void multiply128128(int128 x, int128 y, int256 z) {
    int128 x1 = (x >> 64);
    int128 x2 = (x & ~0uLL);
    int128 y1 = (y >> 64);
    int128 y2 = (y & ~0uLL);
        
    int128 carry = (x1*y2 & ~0uLL) + (x2*y1 & ~0uLL) + (x2*y2 >> 64);
    z[1] = ((carry & ~0uLL) << 64) + (x2*y2 & ~0uLL);
    z[0] = (carry >> 64) + (x1*y2 >> 64) + (x2*y1 >> 64) + x1*y1;    
}

// x * y = z
void multiply128256(int128 x, int256 y, int384 z) {
    int128 xy0[2], xy1[2];
    multiply128128(x, y[0], xy0);
    multiply128128(x, y[1], xy1);
    
    int128 carry = (xy0[1] >> 64) + (xy1[0] >> 64) + ( (xy0[1] & ~0uLL) + (xy1[0] & ~0uLL) >> 64 );
    
    z[2] = xy1[1];
    z[1] = xy0[1] + xy1[0];
    z[0] = (carry >> 64) + xy0[0];
}

// x += y
void add256256(int256 x, int256 y) {
    int128 carry = (x[1] >> 64) + (y[1] >> 64) + ((x[1] & ~0uLL) + (y[1] & ~0uLL) >> 64);
    x[1] += y[1];
    x[0] += y[0] + (carry >> 64);
}

// x += y
void add384256(int384 x, int256 y) {
    int128 carry = (x[2] >> 64) + (y[1] >> 64) + ((x[2] & ~0uLL) + (y[1] & ~0uLL) >> 64);
    x[2] += y[1];
    int128 carry2 = (x[1] >> 64) + (y[0] >> 64) + ((x[1] & ~0uLL) + (y[0] & ~0uLL) + (carry >> 64) >> 64);
    x[1] += y[0] + (carry >> 64);
    x[0] += carry2 >> 64;
}

// x < y
bool compare384384(int384 x, int384 y) {
    if (x[0] != y[0]) return x[0] < y[0];
    if (x[1] != y[1]) return x[1] < y[1];
    return x[2] < y[2];
}

// True if sqrt(x) - p/q < r/s - sqrt(x)
// Since p and r may take more than 64 bits, we subtract both the fractions with floor(sqrt(x))
// After the subtraction, p < q and r < s.
// So we have to solve p/q + r/s - 2fx < 2sqrt(x), where fx = floor(sqrt(x))
bool closer(int128 p, int128 q, int128 r, int128 s, int128 x) {
    p -= q * floorS[x];
    r -= s * floorS[x];
    
    // Until here, all <= 10**18.
    
    int128 mn = p*s + q*r;
    int128 md = s*q*2;
    
    // xmdmd < mnmn + md(4fxmn + fxfxmd)
    // fx: floor(sqrt(x))
    
    int256 mdmd, mnmn, fxmn, fxfxmd;
    multiply128128(md, md, mdmd); multiply128128(mn, mn, mnmn); 
    multiply128128((int128) (floorS[x] * 2), mn, fxmn); 
    multiply128128((int128) (floorS[x] * floorS[x]), md, fxfxmd);
    add256256(fxmn, fxfxmd);
    
    int384 lhs, rhs;
    multiply128256(x, mdmd, lhs); multiply128256(md, fxmn, rhs);
    add384256(rhs, mnmn);

    return compare384384(lhs, rhs);    
}

long long find_largest_denominator(long long x) {
    int a0 = floorS[x];
    
    int m = 0, d = 1, a = a0; 
    
    int128 p = 0, q = 1, r = 1, s = 0;
    bool right = true;
        
    while (true) {        
        if (right) {
            if (q + s*a > denominator) {
                long long k = (denominator - q) / s;
                p += r*k;
                q += s*k;                                   
                if (closer(p, q, r, s, x)) return q;
                else return s;
            }
            
            p += r*a;
            q += s*a;
        } else {
            if (q*a + s > denominator) {
                long long k = (denominator - s) / q;
                r += p*k;
                s += q*k;                          
                if (closer(p, q, r, s, x)) return q;
                else return s;
            }
            
            r += p*a;
            s += q*a;
        }
        
        right = !right;
        
        m = d*a - m;
        d = (x - m*m) / d;
        a = (m + a0) / d;
    }
    
    return -1;
}

int main() {
    scanf("%d %lld", &m, &denominator);
    for (int i=1; i*i<=m; i++) floorS[i*i] = i;
    for (int i=1; i<=m; i++) floorS[i] = (floorS[i] > 0 ? floorS[i] : floorS[i-1]);
    
    int128 sum = 0;
    for (int i=1; i<=m; i++) if (floorS[i-1] == floorS[i]) {
        sum += find_largest_denominator((long long) i);        
    }    
    
    cout << (long long) (sum % MOD) << endl;
    
    return 0;
}
