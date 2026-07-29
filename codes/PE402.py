# Following fundamental theorem of algebra, since P is of degree 4, it is sufficient to ensure
# P(0) = P(1) = P(2) = P(3) = P(4) = 0 (mod m) then P is divisible by m for all P(n)

# If we write P(n) = C(n, 4) * A + C(n, 3) * B + C(n, 2) * C + C(n, 1) * D + E
# When P(0) is divisible by m, then m divides E
# When P(1) is divisible by m, then m divides D (because C(1, 1) = 1 and m divides E)
# When P(2) is divisible by m, then m divides C (because C(2, 2) = 1 and m divides both D and E)
# and so on

# We can find that P(n) = 24 * C(n, 4) + (6*a + 36) * C(n, 3) + (6*a + 2*b + 14) * C(n, 2) + (a + b + c + 1) * n
# So we just have to find the gcd of those

# So we brute for all possible a, b, c mod 24
# For a certain a b c mod 24, they all have the same gcd, so we just have to count how many a b c in <= N for those fixed residues,
# which is (N/24 + 0/1)(N/24 + 0/1)(N/24 + 0/1), i.e. each term is floor(N/24) + {either 0 or 1} depending on a b c mod 24

# It boils down to finding (Fibo(i)/24)^3 which can be found by rewriting ((Fibo(i) - Fibo(i)%24) / 24)^3 mod 24^3 * 10^9
# and find the sum for a fixed residue of i

import math


def multiply(A, B, mod):
    n = len(A)
    return [[sum(A[i][k] * B[k][j] for k in range(n)) % mod for j in range(n)] for i in range(n)]


def power(A, n, mod):
    ret = [[1 if i == j else 0 for j in range(len(A))] for i in range(len(A))]
    mul = A
    while n:
        if n & 1:
            ret = multiply(ret, mul, mod)
        mul = multiply(mul, mul, mod)
        n >>= 1
    return ret


def gen24(n, mod, A, seed):
    A24 = power(A, 24, mod)
    for row in A24:
        row.append(0)
    A24.append([0] * (len(A24[0]) - 2) + [1, 1])

    def sumprod(p, q):
        return sum(map(lambda x, y: x*y, p, q))

    A24n0 = power(A24, n // 24, mod)
    A24n1 = multiply(A24n0, A24, mod)
    ret = []
    for i in range(24):
        M = A24n1 if i <= n % 24 else A24n0
        ret.append(sumprod(M[-1], seed[::-1]) % mod)
        seed = seed[1:] + [sumprod(A[0], seed[::-1])]
        # print(seed)
    return ret

def fibo0(n, mod):
    A = [[1]]
    return gen24(n, mod, A, [1])


def fibo1(n, mod):
    A = [
      [1, 1],
      [1, 0],
    ]
    return gen24(n, mod, A, [0, 1])


def fibo2(n, mod):
    A = [
      [2, 2, -1],
      [1, 0, 0 ],
      [0, 1, 0 ],
    ]
    return gen24(n, mod, A, [0, 1, 1])

# sum of fibo(i)^3 for i = k (mod 24) for 0 <= i <= n
def fibo3(n, mod):
    A = [
      [3, 6, -3, -1],
      [1, 0, 0, 0],
      [0, 1, 0, 0],
      [0, 0, 1, 0],
    ]
    return gen24(n, mod, A, [0, 1, 1, 8])


def S(n):
    cnt = [1 if 1 <= i <= n % 24 else 0 for i in range(24)]
    ans = 0
    for a in range(24):
        for b in range(24):
            for c in range(24):
                g = math.gcd(24, 6*a + 36, 6*a + 2*b + 14, a + b + c + 1)
                e = cnt[a] + cnt[b] + cnt[c]
                t = 0
                t += (n // 24)**3
                t += (n // 24)**2 * e
                t += (n // 24)**1 * e * (e - 1) // 2
                t += e * (e - 1) * (e - 2) // 6
                ans += t * g
    return ans


def solve(n, mod=10**9):
    if n == 0:
        return 0
    fib0 = fibo0(n, mod * 24**3)
    fib1 = fibo1(n, mod * 24**3)
    fib2 = fibo2(n, mod * 24**3)
    fib3 = fibo3(n, mod * 24**3)

    residue = [0, 1]
    for _ in range(2, 24):
        residue.append((residue[-1] + residue[-2]) % 24)

    fib24 = []
    for r, f0, f1, f2, f3 in zip(residue, fib0, fib1, fib2, fib3):
        fib24.append((
            f0 % mod,
            (f1 - r * f0) // 24 % mod,
            (f2 - 2 * r * f1 + r**2 * f0) // 24**2 % mod,
            (f3 - 3 * r * f2 + 3 * r**2 * f1 - r**3 * f0) // 24**3 % mod,
        ))

    def cnt(r, n):
        return 1 if 1 <= r <= n else 0

    ans = 0
    for a in range(24):
        for b in range(24):
            for c in range(24):
                for k in range(24):
                    r = residue[k]
                    e = cnt(a, r) + cnt(b, r) + cnt(c, r)
                    g = math.gcd(24, 6*a + 36, 6*a + 2*b + 14, a + b + c + 1)
                    ans += g * (fib24[k][3] + fib24[k][2] * e + fib24[k][1] * e*(e-1)//2 + fib24[k][0] * e*(e-1)*(e-2)//6)

    # Subtract S(Fib(1))
    return (ans - 2) % mod


if __name__ == '__main__':
    print(S(10))
    print(S(10000))
    # n = 200
    # fib = [1, 2]
    # for i in range(2, n):
    #     fib.append(fib[-1] + fib[-2])
    # print([S(fib[-1-i]) % 10**9 for i in range(24)])
    # print([(solve(n + 1 - i) - solve(n - i)) % 10**9 for i in range(24)])
    print(solve(1234567890123))
