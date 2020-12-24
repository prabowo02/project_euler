'''
from decimal import *
from math import floor

getcontext().prec = 44

def pellX (D):
    a0 = divmod(D.sqrt(), 1)[0]    
    an = divmod(1 / (D.sqrt() - a0), 1)[0]
    
    p0 = a0
    p1 = a0 * an + 1
    pn = p1
    
    cur = 1
    now = 1 / (D.sqrt() - a0)    
    while (an != 2 * a0):
        cur += 1
        
        now = 1 / (now - an)
        an = divmod(now, 1)[0]        
        
        pn = an * p1 + p0
        p0 = p1
        p1 = pn
       
    if (cur - 1 & 1): return p0
        
    for i in range(1, cur):
        now = 1 / (now - an)
        an = divmod(now, 1)[0]
        
        pn = an * p1 + p0
        p0 = p1
        p1 = pn
        
    return p1

n = int(input())
maks = -1
x = -1

idx = 1

for i in list(map(Decimal, range(2, n + 1))):    
    if (floor(i.sqrt()) ** 2 == i): continue
        
    tmp = pellX(i)
    #print(idx, tmp); idx += 1
    if (maks < tmp):
        maks = tmp
        x = i
        
print (x)
'''

# and thanks to A03316 for the complete sequence

ans = [1, 2, 5, 10, 13, 29, 46, 53, 61, 109, 181, 277, 397, 409, 421, 541, 661, 1021, 1069, 1381, 1549, 1621, 2389, 3061, 3469, 4621, 4789, 4909, 5581, 6301, 6829, 8269, 8941, 9949, 12541]

n = int(input())
i = 0
while (ans[i] <= n): i += 1
print(ans[i-1])
