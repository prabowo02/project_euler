primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]

def isPrime(n):
    if ( (n <= 1) or (n & 1 == 0) ): return False
    if (n == 2): return True
    
    # 2^s * d = n-1
    s = 0
    while (n >> s & 1 == 0): s += 1
    d = n - 1 >> s
    
    for a in primes:
        if (pow(a, d, n) == 1): continue
        
        composite = 1
        for r in range(s):
            if (pow(a, d * (1 << r), n) == n - 1):
                composite = 0
                break
                
        if (composite): return False
        
    return True

for tc in range(int(input())):
    n, d = map(int, input().split())    
    
    num = int(str(d) * n)
    if (isPrime(num)):
        print(num)
        continue
        
    ls = []
    for i in range(n):
        for dig in range(10):
            if (dig == d): continue
                
            num = int(str(d) * i + str(dig) + str(d) * (n-i-1))
            if (num < 10 ** (n-1)): continue
                
            if (isPrime(num)):
                ls.append(num)
                
    if (len(ls) > 0):
        print(" ".join(str(sorted(ls))[1:-1].split(", ")))
        continue
        
    for i in range(n):
        for j in range(i+1, n):
            for dig1 in range(10):
                if (dig1 == d): continue
                for dig2 in range(10):
                    if (dig2 == d): continue
                        
                    num = int(str(d) * i + str(dig1) + str(d) * (j - i - 1) + str(dig2) + str(d) * (n - j - 1))
                    if (num < 10 ** (n-1)): continue
                        
                    if (isPrime(num)):
                        ls.append(num)
                        
                
    if (len(ls) > 0):
        print(" ".join(str(sorted(ls))[1:-1].split(", ")))
        continue
        
    for i in range(1):
        for j in range(i+1, n):
            for k in range(max(j+1, n-1), n):
                for dig1 in range(10):
                    if (dig1 == d): continue
                    for dig2 in range(10):
                        if (dig2 == d): continue
                        for dig3 in range(10):
                            if (dig3 == d): continue
                                
                            num = int(str(d) * i + str(dig1) + str(d) * (j - i - 1) + str(dig2) + str(d) * (k - j - 1) + str(dig3) + str(d) * (n - k - 1))
                            if (num < 10 ** (n-1)): continue

                            if (isPrime(num)):
                                ls.append(num)


    if (len(ls) > 0):
        print(" ".join(str(sorted(ls))[1:-1].split(", ")))
        continue
        
    print()
