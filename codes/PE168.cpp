#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int m;
    scanf("%d", &m);
    
    long long ans = 0;
    for (int i=1; i<10; i++) {
        for (int st=1; st<10; st++) {
            int tmp = st;
            int num = st;
            int ten = 1;
            int bef = 0;
            for (int j=0; j<m; j++) {    
                bef = tmp;
                tmp = (tmp % 10) * i + tmp / 10;
                
                if (tmp == st && bef % 10 > 0) ans += num;// cerr << num << " " << i << endl;
                
                ten *= 10, ten %= 100000, num += ten * (tmp % 10);
            }
        }
    }

    printf("%lld\n", (ans - 45) % 100000);
    
    return 0;
}
