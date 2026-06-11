def solve(n, mod=10**8 + 7):
    fact = [1 for i in range(n)]
    for i in range(1, n):
        fact[i] = fact[i - 1] * i % mod
    ifact = [1 for i in range(n)]
    ifact[-1] = pow(fact[-1], -1, mod)
    for i in range(n - 2, -1, -1):
        ifact[i] = ifact[i + 1] * (i + 1) % mod
    
    def C(n, k):
        if k < 0 or k > n:
            return 0
        return fact[n] * ifact[k] * ifact[n - k] % mod

    def count(n, left, right):
        ret = 0
        for three in range(n//3 + 1):
            if (n - three*3) % 2 != 0:
                continue
            two = (n - three*3) // 2

            ret += fact[two + three + 1] * fact[three + left + right] * pow(2, three, mod) * fact[two + three] * C(two + three, two)
        return ret % mod

    return (count(n-1, 0, 0) + count(n-2, 0, 1) + count(n-2, 1, 0) + count(n-3, 1, 1)) % mod


if __name__ == '__main__':
    print(solve(10))
    print(solve(1000))
    print(solve(1000000))
