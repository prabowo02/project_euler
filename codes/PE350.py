import functools
import math


def solve(G, L, N, mod=101**4):
    lpf = [i for i in range(L // G + 1)] # Largest prime factor
    for p in range(2, len(lpf)):
        if lpf[p] != p:
            continue
        for i in range(p+p, len(lpf), p):
            lpf[i] = p


    def factorize(n):
        ret = []
        while n > 1:
            p = lpf[n]
            e = 0
            while n % p == 0:
                n //= p
                e += 1
            ret.append((p, e))
        return ret


    # Number of sequences of integers of length n s.t. min = 0 and max = e
    @functools.cache
    def count(e, n):
        return (pow(e + 1, n, mod) - 2 * pow(e, n, mod) + pow(e - 1, n, mod)) % mod


    ans = 0
    for i in range(1, L // G + 1):
        # Count number of sequences when lcm = gcd * i <= L
        ans += math.prod(count(e, N) for _, e in factorize(i)) * (L//i - G + 1)

    return ans % mod


if __name__ == '__main__':
    print(solve(10, 100, 1))
    print(solve(10, 100, 2))
    print(solve(10, 100, 3))
    print(solve(10, 100, 1000))
    print(solve(10**6, 10**12, 10**18))
