def C(m, k): # k small
    ret = 1
    for i in range(k):
        ret *= (m - i)
        ret //= i + 1
    return ret

def f(n, m):
    k = 0; ret = 0
    while (n - k * m + 2 * k - (k - 1) >= 2 * k):
        ret += C(n - k * m + 2 * k - (k - 1), 2 * k)
        k += 1
    return ret

for tc in range(int(input())):
    m, x = map(int, input().split())
        
    l = 0
    r = 100 * m
    ans = -1
    while (l <= r):
        mid = (l + r) // 2
        
        s = 0
        if (f(mid, m) > x):
            ans = mid
            r = mid - 1
        else: l = mid + 1
    print (ans)
