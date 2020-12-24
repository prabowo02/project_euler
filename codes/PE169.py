dp = dict()
def f(n, e, x):
    if (x < 0): return 0
    if (n < 0): return 0
    if (n == 0): return 1
    if (e < 0): return 0
    if ((n, e, x) in dp): return dp[(n, e, x)]
    dp[(n, e, x)] = (f(n - (1 << e), e, x-1) if n < (1 << e) * (x + 2) else 0) + f(n, e-1, 2)
    return dp[(n, e, x)]
    
print(f(int(input()), 100, 2))
