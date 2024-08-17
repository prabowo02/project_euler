import functools

MOD = 10**9

def solve(n):
    ORDER = 22  # 10^ORDER = 1 (mod 23)
    r = [pow(10, i, 23) for i in range(ORDER)]
    c = [n // ORDER + (i < n % ORDER) for i in range(ORDER)]

    assert sum(c) == n

    @functools.cache
    def C(n, k):
        if k < 0 or k > n:
            return 0
        ret = 1
        for i in range(k):
            ret = ret * (n - i) // (i + 1)
        return ret % MOD

    # Put k balls into n bags such that each bag has [1, 9] balls
    @functools.cache
    def bag1(n, k):
        if k < 0:
            return 0
        if n == 0:
            return k == 0
        return sum([bag1(n - 1, k - i) for i in range(1, 10)]) % MOD


    # Put k balls into n bags such that each bag has [0, 9] balls
    # n is large, k is small
    @functools.cache
    def bag0(n, k):
        return sum([C(n, i) * bag1(i, k) for i in range(k + 1)]) % MOD

    @functools.cache
    def f(n, k, s):
        if n == ORDER:
            return k == 0 and s == 0
        return sum([bag0(c[n], i) * f(n + 1, k - i, (s + i * r[n]) % 23) 
                    for i in range(k + 1)]) % MOD

    print(f(0, 23, 0))


if __name__ == '__main__':
    solve(9)
    solve(42)
    solve(11**12)
