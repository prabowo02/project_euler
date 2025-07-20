# OEIS also gives a linear recurrence with 23 terms

import itertools

MOD = 100000007

def solve(n):
    def dfs(x):
        def get(x, i, j):
            return x >> (i * 3 + j) & 1

        def _hash(x):
            x >>= 9
            ret = []
            ls = [[get(x, i, j) for j in range(3)] for i in range(3)]
            for _ in range(2):
                ls = [[ls[i][2 - j] for j in range(3)] for i in range(3)]
                for _ in range(4):
                    ls = [[ls[j][2 - i] for j in range(3)] for i in range(3)]
                    ret.append(sum(ls[i][j] << (i * 3 + j) for i in range(3) for j in range(3)))
            return min(ret)

        trans = {}
        def _dfs(x):
            for i, j in itertools.product(range(3), repeat=2):
                if get(x, i, j):
                    continue
                x |= 1 << i * 3 + j
                if j < 2 and not get(x, i, j + 1):
                    _dfs(x | 1 << (i * 3 + j + 1))
                if i < 2 and not get(x, i + 1, j):
                    _dfs(x | 1 << (i * 3 + j + 3))
                _dfs(x | 1 << (i * 3 + j + 9))
                return
            h = _hash(x)
            trans[h] = trans.get(h, 0) + 1

        _dfs(x)
        return trans

    q = [0]
    adj = {0: dfs(0)}
    for u in q:
        for v in adj[u]:
            if v in adj:
                continue
            adj[v] = dfs(v)
            q.append(v)

    comp = {}
    for u in adj:
        if u not in comp:
            comp[u] = len(comp)

    A = [[0 for j in range(len(comp))] for i in range(len(comp))]
    for u in adj:
        for v in adj[u]:
            A[comp[u]][comp[v]] = adj[u][v]

    sz = len(A)
    def multiply(A, B):
        return [[sum(A[i][k] * B[k][j] for k in range(sz)) % MOD for j in range(sz)] for i in range(sz)]

    res = [[1 if i == j else 0 for j in range(sz)] for i in range(sz)]
    while n:
        if n & 1:
            res = multiply(res, A)
        A = multiply(A, A)
        n >>= 1

    # print(res)
    return res[0][0]


if __name__ == '__main__':
    print(solve(2))
    print(solve(4))
    print(solve(10))
    print(solve(10**3))
    print(solve(10**6))
    print(solve(10**10000))
