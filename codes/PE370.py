# Write r = q/p (q > p, gcd(p, q) = 1)
# Then our triangles are (kp^2, kpq, kq^2)

# for p^2 + pq < q^2, we need q < phi * p, where phi = (1 + sqrt(5)) / 2

# p^2 + pq + q^2 < N
# q < (sqrt(4N - 3p^2) - p) / 2

# Fixed p: iterate q and find blocks of k with same values
# Iterate p while 3p^2 <= N


PHI = (1 + 5**0.5) / 2


def solve(N):
    _n = int((N/3)**0.5 + 2)
    mu = [0 for _ in range(_n)]
    mu[1] = 1
    for i in range(1, len(mu)):
        for j in range(i*2, len(mu), i):
            mu[j] -= mu[i]

    squarefree_divisors = [[1] for _ in range(_n)]
    for i in range(2, len(squarefree_divisors)):
        if len(squarefree_divisors[i]) != 1:
            continue
        for j in range(i, len(squarefree_divisors), i):
            squarefree_divisors[j].extend([x * i for x in squarefree_divisors[j]])

    def count_coprime(p, l, r):
        ret = 0
        for d in squarefree_divisors[p]:
            ret += (r // d - (l - 1) // d) * mu[d]
        return ret

    # print('Done init')

    ans = 0
    p = 1
    while 3*p*p <= N:
        q = p
        qmax = min(int(PHI * p), int(((4*N - 3*p*p)**0.5 - p) / 2))

        # if p % 10000 == 0:
        #     print(p)

        while q <= qmax:
            k = N // (p*p + p*q + q*q)
            nextQ = min(int(PHI * p), int(((4*N//k - 3*p*p)**0.5 - p) / 2))

            ans += count_coprime(p, q, nextQ) * k

            q = nextQ + 1
        p += 1

    return ans


if __name__ == '__main__':
    print(solve(10**6))
    print(solve(25 * 10**12)) # ~2 mins
