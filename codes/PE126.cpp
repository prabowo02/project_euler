#include <bits/stdc++.h>
using namespace std;

const int N = 2000000;
int lprime[N];

int main() {
    for (int i=2; i<N; i++) if (lprime[i] == 0) 
        for (int j=i; j<N; j+=i) lprime[j] = i;
        
    clock_t t = clock();
    int tc;
    scanf ("%d", &tc);
    while (tc--) {
        int n;
        scanf ("%d", &n);        
        
        if (n & 1) {
            printf("0\n");
            continue;
        }
        
        int nhalf = n >> 1;
        
        int cnt = 0;
        
        for (int k=1; 4*k*k + 2 <= n; k++) {
            for (int a=1; 6*a*a + 4*(k-1)*(a*3 + k - 2) <= n; a++) {
                
                int num = nhalf + a*(a + 2*k - 2) + 2*k*(k-1);
                vector<int> divisors;
                divisors.push_back(1);
                
                while (num > 1) {
                    int p = lprime[num];
                    int sz = divisors.size();
                    int d = 1;
                    
                    do {
                        d *= p;
                        for (int i=0; i<sz; i++) {
                            divisors.push_back(divisors[i] * d);
                            
                            int b = divisors.back() - (a + 2*k - 2);
                            if (b < a) continue;
                            
                            long long num = 1LL*nhalf - 1LL*a*b - 2LL*(k-1)*(a+b+k-2);
                            long long det = 2LL*(k-1) + a + b;
                            
                            if (num < det * b) {
                                divisors.pop_back();
                                continue;
                            }
                            
                            cnt++;
                        }
                    } while (lprime[num /= p] == p);
                }
            }
        }
        
        printf ("%d\n", cnt);
    }
    fprintf (stderr, "%lf sec\n", (double) (clock() - t) / CLOCKS_PER_SEC);
    
    // int sum = 0; for (int i=0; i<N; i++) sum += cnt[i]; cerr << sum << " operations" << endl;
    // for (int i=0; i<200; i+=2) cerr << i << " " << cnt[i] << endl;
        
    return 0;
}
