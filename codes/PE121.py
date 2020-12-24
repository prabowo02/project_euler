def gcd(x, y):
    return gcd(y, x % y) if y else x

d = dict()

N = 0
def f(n, b):
    if (n == 0):
        if (b > N - b): return (1, 1)
        else: return (0, 1)
        
    if ((n, b) in d): return d[(n, b)]
        
    num1, det1 = f(n-1, b)
    num1 *= n
    det1 *= n+1
    
    num2, det2 = f(n-1, b+1)
    num2 *= 1
    det2 *= n+1
    
    #if (det1 != det2): 1 // 0
    d[(n, b)] = (num1 + num2, det1)
    return (num1 + num2, det1)
    
for tc in range(int(input())):
    N = int(input())
    
    d = dict()
    num, det = f(N, 0)
    
    #print(f(N, 0))
    
    print (det // num)
