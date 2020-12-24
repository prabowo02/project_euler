a = int(input())
b = int(input())
k = int(input())

u = (a + (2*b - a) / 5**0.5) / 2
v = a - u

digit = [str(i+1) for i in range(k)]

def G(n):
    if (n < 200):
        return u * ((1 + 5**0.5) / 2)**n + v * ((1 - 5**0.5) / 2)**n
    else: 
        Gn = n * __import__("math").log10((1 + 5**0.5) / 2) + __import__("math").log10(u)
        return 10 ** (Gn - int(Gn)) * 10**k

ten = 10 ** k
n = 0

for i in range(2000000):
    if (sorted(str(a)) == digit):
        if (sorted('{:f}'.format(G(n))[:k]) == digit):
            print(n+1)
            exit(0)
            
    a, b = b, (a + b) % ten
    n += 1
            
print ('no solution')
