"""
Case e=2
    R(a, e) = max(2 * n * a mod a^2, 2) = a^2 - a if a odd else a^2 - 2a
    
Case e=3
    R(a, e) = max(2*n*a mod a^3, 2 + n*(n-1)*a*a mod a^3)
    if a = 1, R(a, e) = 0
    if a even, R(a, e) = a^3 - 2a
    if a = 3, R(a, e) = 27 - 7
    if a odd, R(a, e) = a^3 - 3a

s = 0
for a in range(2, 7):
    maks = 0
    for n in range(a**3):
        maks = max(maks, ((a-1)**n + (a+1)**n) % a**2)
    print(a, maks, a**3 - maks)
    s += maks
    print(s)
"""
for tc in range(int(input())):
    n, e = map(int, input().split())
    ans = 0
    
    if (e == 2):
        ans = n * (n + 1) * (2*n + 1) // 6 + 2
    else: ans = (n * (n+1)) ** 2 // 4
    ans -= (n + 1 >> 1) ** 2
    ans -= (n // 2) * (n // 2 + 1) * 2
    
    if (n == 1): ans = 0
    print(ans % 1000000007)
