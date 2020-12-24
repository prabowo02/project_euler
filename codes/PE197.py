from math import floor

u1, b = map(float, input().split())
f = lambda x: floor(2**(b - x**2)) * 10**-9

u2 = 0
for i in range(1000):
    u1, u2 = u2, f(u1)
    
print(u1 + u2)
