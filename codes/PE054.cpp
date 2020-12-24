#include <cmath>
#include <cstdio>
#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Card {
    int val; char suit;
    bool operator < (const Card &other) const {
        return val < other.val;
    }
};

bool flush (vector <Card> p) {
    bool ret = 1;
    for (int i=0; i<4; i++) ret &= p[i].suit == p[i+1].suit;
    return ret;
}

int straight (vector <Card> p) {
    bool can = 1;    
    
    for (int i=0; i<4; i++) can &= p[i].val + 1 == p[i+1].val;
    if (can) return p[4].val;
    
    can = 1;
    for (int i=0; i<4; i++) can &= p[i].val == i + 2;
    if (can && p[4].val == 14) return 5;
    
    return 0;
}

int four (vector <Card> p) {
    for (int i=0; i<2; i++) {
        bool can = 1;
        for (int j=0; j<3; j++) can &= p[i+j].val == p[i+j+1].val;
        if (can) return p[i].val;
    }
    return 0;
}

int full (vector <Card> p) {
    if (p[0].val == p[1].val && p[3].val == p[4].val) {
        if (p[1].val == p[2].val) return p[0].val;
        else if (p[2].val == p[3].val) return p[2].val;
    } 
    return 0;
}

int three (vector <Card> p) {
    for (int i=0; i<3; i++) {
        if (p[i].val == p[i+1].val && p[i+1].val == p[i+2].val) return p[i].val;
    }
    return 0;
}

int two (vector <Card> p) { // return kicker
    if (p[0].val == p[1].val) {
        if (p[2].val == p[3].val) return p[4].val;
        if (p[3].val == p[4].val) return p[2].val;
    } else if (p[1].val == p[2].val && p[3].val == p[4].val) return p[0].val;
    
    return 0;
}

int one (vector <Card> p) {
    for (int i=0; i<4; i++)
        if (p[i].val == p[i+1].val) return p[i].val;
        
    return 0;
}

int high(vector <Card> p, vector <Card> q) {
    while (p.size()) {
        if (p.back() < q.back()) return -1;
        if (q.back() < p.back()) return 1;
        p.pop_back(); q.pop_back();
    }
    
    return 0;
}

// 1: win, -1: lose, 0: tie
int check(vector<Card> p1, vector<Card> p2) {
    sort (p1.begin(), p1.end());
    sort (p2.begin(), p2.end());
    
    // Royal Flush
    if (flush(p1) && straight(p1) == 14) return 1;
    if (flush(p2) && straight(p2) == 14) return -1;
    
    // Straight Flush
    if (flush(p1) && straight(p1)) {
        if (flush(p2) && straight(p2)) {
            if (straight(p1) < straight(p2)) return -1;
            if (straight(p2) < straight(p1)) return 1;
            return 0;
        }
        return 1;
    }
    if (flush(p2) && straight(p2)) return -1;
    
    // Four of a kind
    if (four(p1)) {
        if (four(p2)) {
            if (four(p1) < four(p2)) return -1;
            if (four(p2) < four(p1)) return 1;
            return 0;
        }
        return 1;
    }
    if (four(p2)) return -1;
    
    // Full House
    if (full(p1)) {
        if (full(p2)) {
            if (full(p1) < full(p2)) return -1;
            if (full(p2) < full(p1)) return 1;
            return 0;
        }
        return 1;
    }
    if (full(p2)) return -1;
    
    // Flush
    if (flush(p1)) {
        if (flush(p2)) {
            for (int i=0; i<5; i++) {
                if (p1[i].val < p2[i].val) return -1;
                if (p1[i].val > p2[i].val) return 1;
            }
            return 0;
        }
        return 1;
    }
    if (flush(p2)) return -1;
    
    // Straight
    if (straight(p1)) {
        if (straight(p2)) {
            if (straight(p1) < straight(p2)) return -1;
            if (straight(p2) < straight(p1)) return 1;
            return 0;
        }
        return 1;
    }
    if (straight(p2)) return -1;
    
    // Three of a kind
    if (three(p1)) {
        if (three(p2)) {
            if (three(p1) < three(p2)) return -1;
            if (three(p2) < three(p1)) return 1;            
            return 0;
        }
        return 1;
    }
    if (three(p2)) return -1;
    
    // Two pairs
    if (two(p1)) {
        if (two(p2)) {
            if (p1[3].val < p2[3].val) return -1;
            if (p2[3].val < p1[3].val) return 1;
            
            if (p1[1].val < p2[1].val) return -1;
            if (p2[1].val < p1[1].val) return 1;
            
            if (two(p1) < two(p2)) return -1;
            if (two(p2) < two(p1)) return 1;
            
            return 0;
        }
        
        return 1;
    }
    if (two(p2)) return -1;
    
    if (one(p1)) {
        if (one(p2)) {
            if (one(p1) < one(p2)) return -1;
            if (one(p2) < one(p1)) return 1;
            
            for (int i=0; i<4; i++) {
                if (p1[i].val == p1[i+1].val) {
                    p1.erase(p1.begin() + i, p1.begin() + i + 2);
                    break;
                }
            }
            
            for (int i=0; i<4; i++) {
                if (p2[i].val == p2[i+1].val) {
                    p2.erase(p2.begin() + i, p2.begin() + i + 2);
                    break;
                }
            }
            
            return high(p1, p2);
        }
        return 1;
    }
    if (one(p2)) return -1;
    
    return high(p1, p2);
}

void read(vector <Card> &p) {
    char a, b;
    scanf ("%c%c", &a, &b); getchar();
    Card card;
    if (a == 'T') a = 10; 
    else if (a == 'J') a = 11;
    else if (a == 'Q') a = 12;
    else if (a == 'K') a = 13;
    else if (a == 'A') a = 14;
    else a -= '0';
    
    card.val = a; card.suit = b;
    p.push_back(card);
}

int Main () {
    vector <Card> p1, p2;
    for (int i=0; i<5; i++) read(p1);
    for (int i=0; i<5; i++) read(p2);    
    
    if (check(p1, p2) == 1) printf ("Player 1\n");
    else printf ("Player 2\n");
    return 0;
}

int main() {
    int t;
    scanf ("%d", &t); getchar();
    while (t--) Main();
    return 0;
}
