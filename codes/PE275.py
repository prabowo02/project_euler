import functools


def solve(n):
    bitcount = [[] for _ in range(n + 1)]
    bitcount_mirror = [[] for _ in range(n + 1)]
    for mask in range(1 << n):
        bitcount[mask.bit_count()].append(mask)
        if all((mask >> (n//2-i) & 1) == (mask >> (n//2+i) & 1) for i in range(1, n//2 + 1)):
            bitcount_mirror[mask.bit_count()].append(mask)

    @functools.cache
    def transition(state, mask):
        n = len(state)
        comps = [[] for _ in range(max(state) + 1)]
        matched = [False for _ in range(max(state) + 1)]
        for i in range(n):
            if state[i] >= 0:
                comps[state[i]].append(i)
                if mask >> i & 1:
                    matched[state[i]] = True
        if not all(matched):
            return None

        nstate, cnt = [-1 for _ in range(n)], 0
        for i in range(n):
            if mask >> i & 1:
                if nstate[i - 1] == -1:
                    nstate[i], cnt = cnt, cnt + 1
                else:
                    nstate[i] = nstate[i - 1]

        pars = [i for i in range(max(nstate) + 1)]
        groups = [[i] for i in range(max(nstate) + 1)]
        def root(u):
            copy_u = u
            while u != pars[u]:
                u = pars[u]
            while copy_u != pars[copy_u]:
                pars[copy_u], copy_u = u, pars[copy_u]
            return u

        def join(u, v):
            u, v = root(u), root(v)
            if u == v:
                return
            if len(groups[u]) < len(groups[v]):
                u, v = v, u
            pars[v] = u
            groups[u].extend(groups[v])

        for comp in comps:
            c = comp[0]
            for i in comp[1:]:
                if nstate[i] >= 0:
                    c = i
                    break
            for i in comp:
                if nstate[c] >= 0 and nstate[i] >= 0:
                    join(nstate[c], nstate[i])

        ncomp, res = dict(), []
        for s in nstate:
            if s >= 0:
                s = root(s)
                if s not in ncomp:
                    ncomp[s] = len(ncomp)
                res.append(ncomp[s])
            else:
                res.append(-1)

        return tuple(res)

    def dp_bitcount(bitcount):
        @functools.cache
        def transitions(state, i):
            return [nstate for mask in bitcount[i] if (nstate := transition(state, mask))]

        weights = [i - n // 2 for i in range(n)]
        @functools.cache
        def dp(state, n, bal):
            if n == 0:
                return 1 if max(state) == 0 and bal == 0 else 0
            res = 0
            for i in range(1, n + 1):
                for nstate in transitions(state, i):
                    res += dp(nstate, n - i, bal + sum([weights[i] for i in range(len(state)) if nstate[i] != -1]))
            return res

        init_state = tuple(0 if i == n // 2 else -1 for i in range(n))
        # print(transitions((0, 0, -1, 1, -1, 0, -1), 3))
        # return 0
        return dp(init_state, n, 0)
    
    # print(dp_bitcount(bitcount), dp_bitcount(bitcount_mirror))
    return (dp_bitcount(bitcount) + dp_bitcount(bitcount_mirror)) // 2


if __name__ == '__main__':
    print(solve(10))
    print(solve(15))
    solve(solve(18))
