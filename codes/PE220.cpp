#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int n;
char m[N];
int bits[N*4];

struct Big {
    int n;
    int *a;
    int sign;
    int bitcount;
    
    Big(int _n) {
        n = _n;
        a = (int *) malloc(n * sizeof(int));
        for (int i=0; i<n; i++) a[i] = 0;
        sign = 0;
        bitcount = 0;
    }
    
    ~Big() {
        free(a);
    }
    
    void real_add(int x) {
        while (a[x] == 1) {
            a[x++] = 0;
            --bitcount;
        }
        ++bitcount;
        a[x] = 1;
    }
    
    void real_sub(int x) {
        
        while (a[x] == 0) {
            a[x++] = 1;
            ++bitcount;
        }
        --bitcount;
        a[x] = 0;
        
        if (bitcount == 0) sign = 0;
    }
    
    void sub(int x) {
        if (x == 0) return;
        if (x < 0) {
            add(-x);
            return;
        }
        
        --x;
        
        if (sign == 0) {
            a[x] = 1;
            sign = -1;
            bitcount = 1;
            return;
        }
        
        if (sign > 0) real_sub(x);
        else real_add(x);
    }
    
    void add(int x) {
        if (x == 0) return;
        if (x < 0) {
            sub(-x);
            return;
        }
        
        --x;
        
        if (sign == 0) {
            a[x] = 1;
            sign = 1;
            bitcount = 1;
            return;
        }
        
        if (sign > 0) real_add(x);
        else real_sub(x);
    }
    
    void print() {
        if (sign < 0) printf("-");
        
        bool zero = true;
        for (int i=(n-1)/4; i>=0; i--) {
            int num = (a[4*i + 0] << 0) + (a[4*i + 1] << 1) + (a[4*i + 2] << 2) + (a[4*i + 3] << 3);
            
            if (zero && num == 0) continue;
            zero = false;
            
            if (0 <= num && num <= 9) printf("%c", '0' + num);
            else printf("%c", 'A' + num - 10);
        }
        
        if (zero) printf("0");
    }
};

pair<int, int> rotate(pair<int, int> step, int dir) {
    dir %= 4;
    if (dir < 0) dir += 4;
    
    if (dir == 0) return step;
    if (dir == 1) return {step.second, -step.first};   
    if (dir == 2) return {-step.first, -step.second};
    if (dir == 3) return {-step.second, step.first};
    
    return {0, 0};    
}

// D_n will translate (2^{step.first-1}, 2^{step.second-1})
// If step is negative, translate -2^(step-1)
// If 0, then 0
pair<int, int> step(int n) {
    int x, y;
    if (n % 4 == 0) {
        x = 0;
    } else {
        x = n / 2 + 1;
        if (n % 8 >= 4) x *= -1;
    }
    
    if (n % 4 == 2) {
        y = 0;
    } else {
        y = n / 2 + 1;
        if (3 <= n % 8 && n % 8 <= 6) y *= -1;
    }
    
    return {x, y};
}

vector<pair<int, int>> getSteps(int n, int bits[]) {
    int dir = 0;
    int rev = 0;
    vector<pair<int, int>> ret;
    
    for (int i=0; i<n; i++) {
        int pos = n - i - 1;
        if (bits[i]) {
            if (rev) {
                dir -= 1;
                ret.push_back(rotate(step(pos), dir));
                dir += 1;
                rev = 1;
            } else {
                ret.push_back(rotate(step(pos), dir));
                dir += 3;
                rev = 1;
            }
        } else {
            if (rev) {
                dir -= 1;
                rev = 0;
            } else {
                rev = 0;
            }
        }
    }
    
    return ret;
}

int solve() {
    scanf("%d", &n);
    scanf("%s", m);
    
    int len = strlen(m);
    
    for (int i=0; i<len; i++) {
        for (int j=0; j<4; j++) {
            if ('0' <= m[i] && m[i] <= '9') bits[i*4 + j] = m[i] - '0' >> 3 - j & 1;
            else bits[i*4 + j] = m[i] - 'A' + 10 >> 3 - j & 1;
        }
    }
    
    vector<pair<int, int>> ans = getSteps(len*4, bits);
    
    Big x(len*4 + 4), y(len*4 + 4);
    for (pair<int, int> p: ans) {
        // fprintf(stderr, "%d %d\n", p.first, p.second);
        x.add(p.first);
        y.add(p.second);
    }
    
    x.print(); printf("\n");
    y.print(); printf("\n");
    
    return 0;
}

int main() {
    int q;
    scanf("%d", &q);
    while (q--) solve();
    return 0;
}
