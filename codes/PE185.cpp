#include <bits/stdc++.h>
using namespace std;

int n;
string s[33];
int c[33];

map<long long, string> mitm;

int main() {
    scanf("%d", &n);
    for (int i=0; i<n; ++i) {
        cin >> s[i];
        cin >> c[i];
    }
    
    for (int i=0; i<1000000; ++i) {
        string num = "";
        int tmp = i;
        for (int j=0; j<6; ++j) {
            num += tmp % 10 + '0';
            tmp /= 10;
        }
        
        bool ok = 1;
        long long key = 0;
        for (int j=0; j<n; ++j) {
            int cnt = 0;
            for (int k=0; k<6; ++k) {
                cnt += s[j][k] == num[k];
            }
            
            if (cnt > c[j]) {
                ok = 0; 
                break;
            }
            
            key *= 4;
            key += cnt;
        }
        
        if (ok) mitm[key] = num;
    }
    
    for (int i=0; i<1000000; ++i) {
        string num = "";
        int tmp = i;
        for (int j=0; j<6; ++j) {
            num += tmp % 10 + '0';
            tmp /= 10;
        }
        
        bool ok = 1;
        long long key = 0;
        for (int j=0; j<n; ++j) {
            int cnt = 0;
            for (int k=0; k<6; ++k) {
                cnt += s[j][6+k] == num[k];
            }
            
            if (cnt > c[j]) {
                ok = 0; 
                break;
            }
            
            key *= 4;
            key += c[j] - cnt;
        }
        
        if (ok && mitm.find(key) != mitm.end()) {
            cout << mitm[key] + num << endl;
            return 0;
        }
    }
    
    return 0;
}
