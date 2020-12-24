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
/*
    for (int b=1; b<=10; b++) {
        LL lim = power(b, b+1);
        
        LL cnt[b]; for (int i=0; i<b; i++) cnt[i] = 0;
        for (LL i=1; i<lim; i++) {
            LL tmp = i;
            while (tmp) {
                cnt[tmp % b]++;
                tmp /= b;
            }
            
            for (int j=0; j<b; j++) if (cnt[j] == i) ans[b][j] += i;
        }
    }
    
    for (int b=0; b<=10; b++) {
        printf("{");
        for (int j=0; j<b; j++) printf("%lld, ", ans[b][j]);
        printf("},\n");
    }
*/
vector<vector<long long>> ans = {
{},
{0 },
{0, 3 },
{0, 22, 27 },
{0, 256, 256, 768 },
{0, 1300, 3125, 98556, 18750 },
{0, 56750, 427590, 139968, 3029084, 466560 },
{0, 209110, 2686937, 2470629, 20917610, 81904445, 12353145 },
{0, 27097870, 180748120LL, 531627804LL, 100663296LL, 2400255700LL, 6529679574LL, 352321536LL },
{0, 375313612LL, 5136788201LL, 2391484500LL, 2324522934LL, 66650672610LL, 86393233341LL, 418575538185LL, 10847773692LL },
{0, 22786974071LL, 73737982962LL, 372647999625LL, 741999999540LL, 100000000000LL, 2434703999430LL, 1876917059570LL, 15312327487352LL, 360000000000LL}
};

int main(){
    int b;
    int M;
    cin >> b >> M;
    vector<int> arr(M);
    for(int arr_i = 0;arr_i < M;arr_i++){
       cin >> arr[arr_i];
    }
    
    long long sum = 0;
    for (int i=0; i<M; i++) sum += ans[b][arr[i]];
    cout << sum << endl;
    return 0;
}
