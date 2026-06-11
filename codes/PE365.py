def solve(n, k, pL, pR):
    def C(n, k, p):
        def base(n, p):
            ret = []
            while n > 0:
                ret.append(n % p)
                n //= p
            return ret

        n = base(n, p)
        k = base(k, p)
        n += [0] * max(0, len(k) - len(n))

        fact = [1 for _ in range(p)]
        for i in range(1, p):
            fact[i] = fact[i - 1] * i % p

        ret = 1
        for x, y in zip(n, k):
            if x < y:
                return 0
            ret *= fact[x] * pow(fact[y], -1, p) * pow(fact[x-y], -1, p)
            ret %= p
        return ret

    def is_prime(n):
        i = 2
        while i*i <= n:
            if n % i == 0:
                return False
            i += 1
        return True

    ps = [n for n in range(pL, pR) if is_prime(n)]
    rems = [C(n, k, p) for p in ps]

    ans = 0
    for i in range(len(ps)):
        for j in range(i+1, len(ps)):
            for k in range(j+1, len(ps)):
                p, q, r = ps[i], ps[j], ps[k]
                res = (
                    rems[i] * q * r * pow(q * r, -1, p) +
                    rems[j] * p * r * pow(p * r, -1, q) +
                    rems[k] * p * q * pow(p * q, -1, r)
                ) % (p * q * r)
                ans += res
    return ans


if __name__ == '__main__':
    print(solve(10**18, 10**9, 1000, 5000))
