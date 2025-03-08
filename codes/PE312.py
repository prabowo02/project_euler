# Let f(n) be the number of ways to traverse Sn from one corner to another passing each vertex exactly once
# Let g(n) be the same, but you do not have to traverse the third corner
# We have:
#   C(n) = f(n - 1)^3
#   f(n+1) = 2 f(n) f(n) g(n); f(2) = 2
#   g(n+1) = 2 f(n) g(n) g(n); g(2) = 3
# We can imply g(n) = f(n) * 3/2, hence f(n+1) = 3 * f(n)^3
# And so we have the closed form f(n+2) = 2^3^n * 3^((3^n - 1)/2) and C(n+2) = 2^3^n * 3^((3^n - 3)/2) 

def phi(n):
    return {
        10**8: 4 * 10**7,
        13**8: 2**2 * 3 * 13**7,
        2**2 * 3 * 13**7: 2**4 * 3 * 13**6,
        2**4 * 3 * 13**6: 2**6 * 3 * 13**5,
        2**6 * 3 * 13**5: 2**8 * 3 * 13**4,
        2**8 * 3 * 13**4: 2**10 * 3 * 13**3,
    }[n]


# Return (3**n - 3) / 2 % mod
def pow3(n, mod):
    def add(a, b):
        return (a * b * 2 + 3 * a + 3 * b + 3) % mod
    one, res = 0, -1
    while n:
        if n % 2 == 1:
            res = add(res, one)
        one = add(one, one)
        n //= 2
    return res


def solve(n, mod=None):
    if n <= 2:
        return 1
    n -= 2
    if mod is None:
        return 2**3**n * 3**((3**n - 3) // 2)

    return pow(2, pow(3, n, phi(mod)), mod) * pow(3, pow3(n, phi(mod)), mod) % mod


def main():
    res = solve(10000, 2**8 * 3 * 13**4)
    res = solve(res, 2**4 * 3 * 13**6)
    res = solve(res, 13**8)
    return res


if __name__ == '__main__':
    print(solve(1))
    print(solve(2))
    print(solve(3))
    print(solve(4))
    print(solve(5))
    print(solve(10000, 10**8))
    print(solve(10000, 13**8))
    print(main())
