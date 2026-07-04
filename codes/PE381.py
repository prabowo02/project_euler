# A sublinear solution also exists

def solve(n):
    primes = [True for _ in range(n)]
    ans = 0
    for p in range(2, n):
        if not primes[p]:
            continue
        for i in range(p*2, n, p):
            primes[i] = False
        if p < 5:
            continue
        ans += -1 * (
                    1 + pow(p-1, -1, p) * (
                        1 + pow(p-2, -1, p) * (
                            1 + pow(p-3, -1, p) * (
                                1 + pow(p-4, -1, p)
                                )
                            )
                        )
                    ) % p

    return ans


if __name__ == '__main__':
    print(solve(100))
    print(solve(10**8))
