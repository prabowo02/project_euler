def legendre(n, p):
    ret = 0
    while n > 0:
        n //= p
        ret += n
    return ret


def ilegendre(n, p):
    l, r, ans = 1, n * p, n
    while l <= r:
        mid = (l + r) // 2
        if legendre(mid, p) >= n:
            r, ans = mid - 1, mid
        else:
            l = mid + 1
    return ans


def solve(n):
    mod = 10**18
    ediv = 1234567890

    n += 1
    pfactors = [[] for _ in range(n)]
    for p in range(2, n):
        if pfactors[p]:
            continue
        for i in range(p, n, p):
            t, e = i, 0
            while t % p == 0:
                e += 1
                t //= p
            pfactors[i].append((p, e))

    ans, fact = 0, 0
    exponents = {}
    for i in range(2, n):
        for p, e in pfactors[i]:
            exponents[p] = exponents.get(p, 0) + e * ediv
            fact = max(fact, ilegendre(exponents[p], p))

        if i >= 10:
            ans += fact
            ans %= mod

    return ans


if __name__ == '__main__':
    print(solve(1000))
    print(solve(1000000))
