import collections
import functools
import itertools
import math

from fractions import Fraction


def partition(n, seq=()):
    if n == 0:
        yield seq
    for i in range(seq[-1] if seq else 1, n + 1):
        yield from partition(n - i, tuple(list(seq) + [i]))


def cycle_to_perm(cycles):
    ret = []
    for l in cycles:
        ret.extend([len(ret) + (i + 1) % l for i in range(l)])
    return tuple(ret)


def perm_to_cycle(perm):
    ret = []
    vis = [False for _ in perm]
    for i in perm:
        if vis[i]:
            continue
        cnt = 0
        while not vis[i]:
            vis[i] = True
            i = perm[i]
            cnt += 1
        ret.append(cnt)
    return tuple(sorted(ret))


class Eq:
    def __init__(self, step=0, edge=None):
        self.step = Fraction(step)
        self.edge = collections.defaultdict(Fraction)
        if edge is not None:
            self.edge = edge.copy()

    def mul(self, c):
        res = Eq()
        res.step = self.step * c
        for e in self.edge:
            res.edge[e] = self.edge[e] * c
        return res

    def add(self, eq):
        res = Eq()
        res.step = self.step + eq.step
        for e in self.edge:
            res.edge[e] += self.edge[e]
        for e in eq.edge:
            res.edge[e] += eq.edge[e]
        return res

    def __str__(self):
        return str(self.step) + ' | ' + str(self.edge)


def solve(n):
    parts = sorted(partition(n), key=lambda s: sum(s) - len(s))
    eqs = dict()
    total = n * (n - 1) * (n - 2)

    for cycle in parts[:0:-1]:
        perm = cycle_to_perm(cycle)

        eq = Eq(1)

        @functools.cache
        def expand(p):
            if p not in eqs:
                return Eq(0, {p: Fraction(1)})
            res = Eq(eqs[p].step)
            for e in eqs[p].edge:
                res = res.add(expand(e).mul(eqs[p].edge[e]))
            return res

        for i in range(n):
            for j in range(i+1, n):
                for k in range(j+1, n):
                    nperm = list(perm)
                    for ni, nj, nk in itertools.permutations([i, j, k]):
                        nperm[i], nperm[j], nperm[k] = perm[ni], perm[nj], perm[nk]
                        p = perm_to_cycle(nperm)
                        eq = eq.add(expand(p).mul(Fraction(1, total)))

        mul = Fraction(1, (1 - eq.edge.pop(cycle)))
        eq = eq.mul(mul)
        eqs[cycle] = eq

    vals = {parts[0]: 0}
    for cycle in parts[1:]:
        vals[cycle] = eqs[cycle].step
        for e in eqs[cycle].edge:
            vals[cycle] += vals[e] * eqs[cycle].edge[e]

    ret = 0
    # Can be optimised by counting how many perms of 1..n that satisfy a given cycle
    for p in itertools.permutations(range(n)):
        ret += vals[perm_to_cycle(p)]
    return ret / math.factorial(n)


if __name__ == '__main__':
    print(float(solve(4)))
    print(float(solve(11)))
