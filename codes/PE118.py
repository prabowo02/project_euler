import itertools

primes = [2, 3, 5, 7]
def isPrime(n):
    if (n == 2) or (n == 3): return True
    if ( (n <= 1) or (n & 1 == 0) ): return False
    
    # 2^s * d = n-1
    s = 0
    while ( (n - 1) >> s & 1 == 0): s += 1
    d = n - 1 >> s
    
    for a in primes:
        if (a > n - 2): break
        if (pow(a, d, n) == 1): continue
        
        composite = 1
        for r in range(s):
            if (pow(a, d * (1 << r), n) == n - 1):
                composite = 0
                break
                
        if (composite): return False
        
    return True

d = dict()
for ii in range(1, (1 << 9) - 1):
    s = ''
    for j in range(9):
        if (ii >> j & 1): s += str(j + 1)    
    d[int(s)] = [int(''.join(i)) for i in itertools.permutations(s) if (isPrime(int(''.join(i))))]    
    
d[123456789] = []
    
ans = []
s = []
def p(x, ss):
    if (x == len(ans)): 
        s.append(ss)    
        return
        
    for num in d[ans[x]]:
        p(x+1, ss + num)
    
def solve(x):
    if (len(x) == 0):
        p(0, 0)
        return

    for i in range(1 << len(x) - 1):
        take = x[0]        
        nxt = ''
        
        for j in range(len(x)-1):
            if (i >> j & 1): take += x[j+1]
            else: nxt += x[j+1]
            
        ans.append(int(take))
        solve(nxt)
        ans.pop()

            
for tc in range(int(input())):          
    s = []
    solve(input())
    for num in sorted(s):
        print(num)
    print()
