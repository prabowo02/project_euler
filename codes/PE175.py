"""
- f is a stern-brocot sequence
- f(n)/f(n-1) is a fraction in stern-brocot tree
- traverse right => append 0, otherwise 1
- append 1 again at the end
- ans will the reversed list
"""

def gcd(x, y):
    return gcd(y, x % y) if y else x

p, q = map(int, input().split())
p, q = p // gcd(p, q), q // gcd(p, q)

def ceil(p, q):
    if (p % q): return p // q 
    return p // q - 1

ans = []
a, b, c, d = 0, 1, 1, 0
while ((a+c) != p or (b+d) != q):
    if ((a+c)*q > (b+d)*p):
        k = ceil(c*q - d*p, b*p - a*q)
        c, d = c + k*a, d + k*b
    else:
        k = ceil(b*p - a*q, c*q - d*p)
        a, b = a + k*c, b + k*d
    ans.append(k)
    
if (p < q):
    if (len(ans) % 2 == 1): 
        ans[-1] += 1
    else:
        ans.append(1)
elif (p > q):
    if (len(ans) % 2 == 0):
        ans[-1] += 1
    else:
        ans.append(1)
else:
    ans.append(1)
    
print(','.join(map(str, ans[::-1])))
        