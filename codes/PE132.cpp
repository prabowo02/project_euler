#include <bits/stdc++.h>
using namespace std;

const int N = 10000000;

vector<int> primes;
int lprime[N];

int power(int a, int b, int mod) {
    long long mul = a, ret = 1;
    for (; b; b >>= 1) {
        if (b & 1) ret = ret * mul % mod;
        mul = mul * mul % mod;
    }
    return ret;
}

vector<int> two[4] = {
    {0, 11, 28, 69, 142, 243, 380, 631, 888, 1159, 1512, 1913, 2362, 3003, 3754, 4955, 6364, 7965, 11506, 15507, 20308, 25359, 34450, 45203, 60564, 76565, 96406, 117407, 138808, 162809, 188410, 216371, 253872, 294833, 338034, 398135, 460636, 530493, 606494, 683295, 843296, 1005547, 1458924, 1983725, 2527726, 3197727},
    {0, 11, 28, 69, 142, 243, 380, 631, 888, 1159, 1512, 1913, 2362, 3003, 3754, 4955, 6364, 7965, 11506, 15507, 20308, 25359, 34450, 45203, 60564, 76565, 96406, 117407, 138808, 162809, 188410, 216371, 253872, 294833, 338034, 398135, 460636, 530493, 606494, 683295, 843296, 1005547, 1312748, 1766125, 2290926, 2834927},
    {0, 11, 28, 69, 142, 243, 380, 631, 888, 1159, 1512, 1913, 2362, 3003, 3754, 4955, 6364, 7965, 11506, 15507, 20308, 25359, 34450, 45203, 60564, 76565, 96406, 117407, 138808, 162809, 188410, 216371, 253872, 294833, 338034, 398135, 460636, 530493, 606494, 683295, 843296, 1005547, 1169388, 1476589, 1929966, 2454767},
    {0, 11, 28, 69, 142, 243, 380, 631, 888, 1159, 1512, 1913, 2362, 3003, 3754, 4955, 6364, 7965, 11506, 15507, 20308, 25359, 34450, 45203, 60564, 76565, 96406, 117407, 138808, 162809, 188410, 216371, 253872, 294833, 338034, 398135, 460636, 526173, 596030, 672031, 748832, 908833, 1071084, 1234925, 1542126, 1995503}
};

int main() {
    clock_t t = clock();
    
    for (int i=2; i<N; i++) if (lprime[i] == 0) {
        for (int j=i; j<N; j+=i) lprime[j] = i;
        primes.push_back(i);
    }
    
    int T;
    scanf("%d", &T);
    while (T--) {
    
        int a, b, k;
        scanf("%d %d %d", &a, &b, &k);
        
        int tmp = a;
        while (tmp % 5 == 0) tmp /= 5;
        int e = 0;
        while (tmp % 2 == 0) tmp /= 2, e++;
        
        if (tmp % 3 != 0) {
            set<int> s;
            if (1LL * b * e >= 16) {
                for (int i=0; i<k; i++) s.insert(two[3][i+1] - two[3][i]);
            } else if (b * e >= 13) {
                for (int i=0; i<k; i++) s.insert(two[2][i+1] - two[2][i]);
            } else if (b * e >= 11) {
                for (int i=0; i<k; i++) s.insert(two[1][i+1] - two[1][i]);
            } else {
                for (int i=0; i<k; i++) s.insert(two[0][i+1] - two[0][i]);
            }            
            
            while (tmp > 1) {
                int p = lprime[tmp];
                do {
                    tmp /= p;
                } while (tmp % p == 0);
                
                for (int i=p*2; i<*s.rbegin(); i+=p) {
                    if (lprime[i+1] == i+1 && power(10, power(a, b, i), i+1) == 1) {
                        s.insert(i+1);
                        if (s.size() > k) s.erase(*s.rbegin());
                    }
                }
            }
            
            int ans = 0;
            while (s.size()) ans += *s.begin(), s.erase(s.begin());
            printf("%d\n", ans);
            
            continue;
        }
        
        int sum = 3;
        --k;
        
        for (int i=3; k; i++) {
            int p = primes[i];
            if (power(10, power(a, b, p-1), p) == 1) {
                // if (k == 1)  cerr << i << " " << p << endl;
                sum += p;
                k--;
            }
        }
        
        printf("%d\n", sum);
    }
    
    cerr << (double) (clock() - t) / CLOCKS_PER_SEC << " sec" << endl;
    return 0;
}   
