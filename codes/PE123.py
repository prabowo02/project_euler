from bisect import bisect_right

B = [0]
idx = [0]
N = 3000000
prime = [1 for i in range(N)]

n = 0
for i in range(2, N):
    if (prime[i]):
        n += 1
        for j in range(2*i, N, i):
            prime[j] = 0
    
        tmpB = (pow(i-1, n, i**2) + pow(i+1, n, i**2)) % i**2 
        if (tmpB > B[-1]):
            B.append(tmpB)         
            idx.append(n)
    
#print(B[-1])
    
for tc in range(int(input())):
    print(idx[bisect_right(B, int(input()))])
