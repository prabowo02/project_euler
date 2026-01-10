import itertools
import math


def solve(N):
    def find_AB(p):
        C = [[1 if k in (0, n) else 0 for k in range(p)] for n in range(p)]
        for n in range(2, p):
            for k in range(1, n):
                C[n][k] = (C[n - 1][k - 1] + C[n - 1][k]) % p

        def lucas(n, k):
            prod = 1
            while n > 0 or k > 0:
                prod = prod * C[n % p][k % p] % p
                n //= p
                k //= p
            return prod

        factorials = [1]
        for n in range(1, p):
            factorials.append(factorials[-1] * n % p)

        # for n in itertools.count():
        #     A.append(factorials[n] if n < p else 0)
        #     for k in range(1, n + 1):
        #         A[n] = (A[n] + lucas(n, k) * A[n - k]) % p

        #     if n >= p*2 and A[p:p*2] == A[-p:]:
        #         # Probably found the period
        #         print('Period length:', n - p*2)
        #         break

        # It looks like periodA = periodB = p^2 - p - 1. Idk why
        # Periodic starts from A[p]

        # Also note worthy:
        # E.G.F. of A is 1/[(2 - e^x)(1 - x)]
        # E.G.F. of B is (e^x)/[(2 - e^x)(1 - x)]
        # and ordered bell number has E.G.F. 1/(2 - e^x), whose mod p is periodic with length p-1

        B_const = []
        for n in range(p):
            B_const.append(sum(pow(factorials[k], -1, p) for k in range(n + 1)) * factorials[n] % p)

        A, B = [1], [1]
        for n in range(1, p**2):
            A.append(factorials[n] if n < p else 0)
            B.append(B_const[n % p])

            L = [lucas(n, k) for k in range(n + 1)]
            A[n] = (A[n] + sum(L[k] * A[n - k] for k in range(1, n + 1))) % p
            B[n] = (B[n] + sum(L[k] * B[n - k] for k in range(1, n + 1))) % p

        period = len(A) - p
        valA = A[p + (N - p) % period] if N >= p else A[N]
        valB = B[p + (N - p) % period] if N >= p else B[N]

        return valA, valB

    # 77777777
    primes = [
      7, 11,
      73, 101, 137
    ]
    As, Bs = [], []

    for p in primes:
        a, b = find_AB(p)
        As.append(a)
        Bs.append(b)
        print(p, a, b)

    def crt(ms, ps):
        M = math.prod(ps)
        return sum(M // p * pow(M // p, -1, p) * m for m, p in zip(ms, ps)) % M

    A, B = crt(As, primes), crt(Bs, primes)
    print(A, B)
    return (A - B) % math.prod(primes)


if __name__ == '__main__':
    # print(solve(10))
    print(solve(10**9))  # Takes around 3 minutes to run
