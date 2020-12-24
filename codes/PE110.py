n = int(input())

def isPrime(n):
    i = 2
    while (i * i <= n):
        if (n % i == 0): return False
        i += 1
        
    return True

prime = []
for i in range(2, 200): 
    if (isPrime(i)): prime.append(i)
        
def f(cur, prod, lim, sol):
    if ((sol + 1) // 2 >= n): return prod
    
    mul = 1
    candidate = []
    for i in range(lim):
        mul *= prime[cur]
        candidate.append(f(cur+1, prod * mul, i + 1, sol * (2*i + 3)))
        
    return min(candidate)

print (f(0, 1, 10, 1))
