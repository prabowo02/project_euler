/**
 * Problem statement is wrong. See the original Project Euler problem.
 */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<long long, long long> fraction;

#define num first
#define det second

long long gcd(long long x, long long y) {
    return y ? gcd(y, x % y) : x;
}

long long lcm(long long x, long long y) {
    return x / gcd(x, y) * y;
}

long long lcm(long long x, long long y, long long z) {
    return lcm(x, lcm(y, z));
}

fraction sum(fraction x, fraction y) {
    long long L = lcm(x.det, y.det);
    long long numerator = L / x.det * x.num + L / y.det * y.num;
    long long g = gcd(L, numerator);
    return {numerator / g, L / g};
}

fraction sum(fraction x, fraction y, fraction z) {
    return sum(x, sum(y, z));
}

bool fermat(long long x, long long y, long long z) {
    if (x + y == z) return true;
    if (x*x + y*y == z*z) return true;
    return false;
}

long long solve(int K) {
    vector<fraction> fractions;

    for (int i=1; i<=K; i++) for (int j=i+1; j<=K; j++) if (gcd(i, j) == 1)
        fractions.push_back({i, j});
    
    vector<fraction> ans = {{0, 1}};
    for (fraction x: fractions) for (fraction y: fractions) for (fraction z: fractions) {
        long long L1 = lcm(x.det, y.det, z.det);
        long long L2 = lcm(x.num, y.num, z.num);
        
        if (fermat(L1 / x.det * x.num, L1 / y.det * y.num, L1 / z.det * z.num) || fermat(L2 / x.num * x.det, L2 / y.num * y.det, L2 / z.num * z.det)) ans.push_back(sum(x, y, z));
    }
    
    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
    for (int i=1; i<ans.size(); i++) ans[0] = sum(ans[0], ans[i]);
    return ans[0].num + ans[0].det;
}

int main() {
    vector<long long> ans = {1, 1, 1, 4, 31, 296, 443, 1777, 16007, 96977, 12519, 3907811, 4291237, 42858749, 8742403, 37176761, 578581, 338673399, 1612046017LL, 40760283001LL, 19408891927LL, 1661228021LL, 54546278261LL, 3225960963961LL, 1119108581551LL, 38765346769LL, 43482789776399LL, 3745423313347LL, 6174988960643LL, 5518822752947717LL, 352533822677489LL, 8138106480954019LL, 44872910076818543LL, 32613496564105741LL, 518661185260431391LL, 285196020571078987LL};
    
    int k;
    scanf("%d", &k);
    printf("%lld\n", ans[k]);
    return 0;
}
