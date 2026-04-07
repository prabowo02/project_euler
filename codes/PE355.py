# Weighted bipartite matching
def hungarian(cost):
    n = len(cost) + 1
    m = len(cost[0]) + 1

    u = [0 for _ in range(n)]
    v = [0 for _ in range(m)]
    p = [0 for _ in range(m)]

    for i in range(1, n):
        p[0] = i
        j0 = 0 # dummy
        dist = [10**9 for _ in range(m)]
        pre = [-1 for _ in range(m)]
        done = [False for _ in range(m + 1)]

        while True:
            done[j0] = True
            i0 = p[j0]
            delta = 10**9

            for j in range(1, m):
                if done[j]:
                    continue
                cur = cost[i0 - 1][j - 1] - u[i0] - v[j]
                if cur < dist[j]:
                    dist[j] = cur
                    pre[j] = j0
                if dist[j] < delta:
                    delta = dist[j]
                    j1 = j

            for j in range(m):
                if done[j]:
                    u[p[j]] += delta
                    v[j] -= delta
                else:
                    dist[j] -= delta
            j0 = j1

            if not p[j0]:
                break

        # Update alternating path
        while j0:
            j1 = pre[j0]
            p[j0] = p[j1]
            j0 = j1

    return -v[0]

# Conjecture: the set consists of only either p^k, or q*p^k, where p <= sqrt(n) and q > sqrt(n)

def solve(n):
    primes = [True for _ in range(n + 1)]

    L, R = [], []
    for p in range(2, len(primes)):
        if not primes[p]:
            continue
        for i in range(p+p, len(primes), p):
            primes[i] = False

        if p*p <= n:
            L.append(p)
            R.append(0)
        else:
            R.append(p)

    def ilog(n, b):
        ret = 0
        while n >= b:
            ret += 1
            n //= b
        return ret

    cost = [[r - (l**ilog(n//r, l) * r) if r else -l**ilog(n, l) for r in R] for l in L]

    return sum(R) - hungarian(cost) + 1


if __name__ == '__main__':
    print(solve(10))
    print(solve(30))
    print(solve(100))
    print(solve(200000))
