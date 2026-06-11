import math
import functools
import sys

sys.setrecursionlimit(10**6)


def solve(n):
    sn = math.isqrt(n)
    is_primes = [True for _ in range(sn + 100)]
    primes = []
    for p in range(2, len(is_primes)):
        if not is_primes[p]:
            continue
        for i in range(p*2, len(is_primes), p):
            is_primes[i] = False
        primes.append(p)


    # Generate possible (unordered) prime exponents of integer <= n
    # Each item in the generated is non-increasing
    def gen_expos():
        res = []

        ls = []
        def dfs(x, n):
            e = 1
            pe = primes[x]

            while pe <= n and (not ls or e <= ls[-1]):
                ls.append(e)
                res.append(tuple(ls))
                dfs(x + 1, n // pe)
                ls.pop()

                e += 1
                pe *= primes[x]
        
        dfs(0, n)
        return res


    # Number of ways p0^expo[0] * ... can be factored s.t. all factors are squarefree
    def count_ways(expo):
        # Returns a list of tuple t such that t[i] <= groups[i], and sum(t[i]) <= s
        def gen_transitions(s, groups):
            res = []
            ls = [0 for _ in groups]
            def dfs(x, s):
                if x == len(groups):
                    res.append(tuple(ls))
                    return
                for i in range(groups[x] + 1):
                    if i > s:
                        break
                    ls[x] = i
                    dfs(x + 1, s - i)
            dfs(0, s)
            return res

        @functools.cache
        def dfs(x, groups):
            if x == len(expo):
                return 1

            ret = 0
            for t in gen_transitions(expo[x], groups):
                ngroup = [groups[i] - t[i] for i in range(len(groups)) if t[i] < groups[i]]
                ngroup += [t[i] for i in range(len(groups)) if t[i] > 0]
                if sum(t) < expo[x]:
                    ngroup += [expo[x] - sum(t)]

                ngroup = tuple(sorted(ngroup))

                ret += dfs(x + 1, ngroup)

            return ret

        return dfs(0, ())

    def build_count_primes():
        ns = [n // i for i in range(1, sn + 1)] + [i for i in range(1, sn + (1 if sn*sn != n else 0))][::-1]
        count = {
          x: x - 1 for x in ns
        }

        for p in range(2, sn + 1):
            if count[p] == count[p - 1]:
                continue

            for x in ns:
                if p*p > x:
                    break
                count[x] -= count[x // p] - count[p - 1]

        return count

    count_primes = build_count_primes()

    # Number of integer <= n s.t. its sorted prime exponents is `expo` 
    def count_expo(expo):
        def dfs(x, expo, n):
            if len(expo) == 0:
                return 1
            if len(expo) == 1 and expo[-1] == 1:
                return count_primes[n] - x

            if primes[x]**sum(expo) > n:
                return 0

            ret = dfs(x + 1, expo, n)
            for i in range(len(expo)):
                if i > 0 and expo[i] == expo[i - 1]:
                    continue
                nexpo = expo[:i] + expo[i+1:]
                ret += dfs(x + 1, nexpo, n // primes[x]**expo[i])

            return ret

        return dfs(0, expo, n)

    return sum(count_ways(expo) * count_expo(expo) for expo in gen_expos())


if __name__ == '__main__':
    print(solve(100))
    print(solve(10**10))
