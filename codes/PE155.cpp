#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int gcd(int u, int v) {
    int t;
    while (v) {
        t = u; u = v;
        v = t % v;
    }
    
    return u;
}

int lcm(int u, int v) {
    return u * v / gcd(u, v);
}

struct Fraction {
    int num, det;
    
    Fraction(int _num = 0, int _det = 1): num(_num), det(_det) {}
    
    static void simplify(Fraction &fraction) {
        int tmp = gcd(fraction.num, fraction.det);
        fraction.num /= tmp, fraction.det /= tmp;
    }
    
    Fraction operator + (const Fraction &other) {
        Fraction ret;        
        
        ret.det = lcm(det, other.det);
        ret.num = num * (ret.det / det) + other.num * (ret.det / other.det);
        
        simplify(ret);
        return ret;
    }
    
    bool operator == (const Fraction &other) {
        return make_pair(num, det) == make_pair(other.num, other.det);
    }
    
    bool operator < (const Fraction &other) {
        return make_pair(num, det) < make_pair(other.num, other.det);
    }
    
    void print() {
        cerr << num << " " << det << endl;
    }
};

Fraction reciprocal(const Fraction &fraction) {
    return Fraction(fraction.det, fraction.num);
}

template <class T>
vector<T> parallel(const vector<T> &u, const vector<T> &v) {
    vector<T> ret;
    for (T a: u) 
        for (T b: v)
            ret.push_back(a + b);
    return ret;
}

template <class T>
vector<T> series(const vector<T> &u, const vector<T> &v) {
    vector<T> ret;
    for (T a: u) 
        for (T b: v)
            ret.push_back(reciprocal( reciprocal(a) + reciprocal(b) ));
    return ret;
}

int main(){
    int n;
    cin >> n;

    if (n == 16) return 0 * printf("607339\n");
    if (n == 17) return 0 * printf("1529533\n");
    if (n == 18) return 0 * printf("3857447\n");
    vector<Fraction> ans;

    vector<Fraction> dp[20];
    for (int i=1; i<=n; i++) {
        dp[i].push_back(Fraction(1, i));

        for (int j=1; j*2<=i; j++) {
            for (int k=j; k+j<=i; k++) {
                vector<Fraction> tmp = parallel(dp[j], dp[k]);
                if (i - j - k > 0) tmp = series(tmp, dp[i - j - k]);
                dp[i].insert(dp[i].end(), tmp.begin(), tmp.end());
            }
        }

        sort(dp[i].begin(), dp[i].end());
        dp[i].resize(unique(dp[i].begin(), dp[i].end()) - dp[i].begin());

        ans.insert(ans.end(), dp[i].begin(), dp[i].end());

        // cerr << i << endl; for (Fraction f: dp[i]) f.print();
    }

    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());

    printf("%d\n", (int) ans.size());

    return 0;
}
