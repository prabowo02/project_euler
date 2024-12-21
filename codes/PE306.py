import functools

# Similar to Dawson's Chess
# Has period 34 with the only exceptions at n=0, 1, 15, 17, 18, 32, 35 and 52
@functools.cache
def f(n):
    if n <= 1:
        return 0
    if n == 2:
        return 1
    ls = [False for _ in range(n)]
    for i in range(1, n-1):
        ls[f(i) ^ f(n-i-2)] = True
    for i in range(n):
        if not ls[i]:
          return i

nim = [f(34*2 + i) for i in range(34)]
diff = [1, 15, 17, 18, 32, 35, 52]

def solve(n):
    ret = 0
    for i in range(34):
        if nim[i]:
            continue
        # nim[i] is not 0 fortunately, otherwise too lazy to handle
        ret += n // 34 + (i <= n % 34)

    for i in diff:
        if i > n:
            continue
        if not nim[i % 34]:
            ret -= 1 
        if not f(i):
            ret += 1

    return n - ret


if __name__ == '__main__':
    print(solve(5))
    print(solve(50))
    print(solve(1000000))
