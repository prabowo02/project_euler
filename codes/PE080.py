n = int(input())
p = int(input())

from decimal import *
getcontext().prec = p + 8

ans = 0
for i in map(Decimal, range(2, n + 1)):
    if (__import__("math").floor(i.sqrt()) ** 2 == i): continue

    s = ''.join(str(i.sqrt()).split('.'))
    for i in range(p):
        ans += int(s[i])
        
print(ans)
