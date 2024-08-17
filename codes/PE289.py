import functools


def merge(comp, x, y):
    if not (-len(comp) <= x < len(comp) and -len(comp) <= y < len(comp)):
        raise Exception('Invalid indices')
    if comp[x] == comp[y]:
        raise Exception('Merging same component')

    ncomp = list(comp)
    for i in range(len(ncomp)):
        if ncomp[i] == comp[y]:
            ncomp[i] = comp[x]
    return tuple(ncomp)


def normalize(comp):
    mapper = {}
    ret = []
    for c in comp:
        if c not in mapper:
            mapper[c] = len(mapper)
        ret.append(mapper[c])
    return tuple(ret)


@functools.cache
def f(x, y, comp):
    ret = 0
    if x == N:
        if y == M:
            assert len(comp) == 2 and comp[0] == comp[1]
            return 1
        if y == 0:
            return f(x, y + 1, comp)

        if comp[0] != comp[1]:
            ncomp = merge(comp, 0, 1)
            ret += f(x, y + 1, normalize(ncomp[2:]))
        if comp[1] != comp[2]:
            ncomp = merge(comp, 1, 2)
            ret += f(x, y + 1, normalize([ncomp[0]] + list(ncomp[3:])))

        return ret

    if x == 0:
        if y == M:
            return f(x + 1, 0, comp)
        if y == 0:
            return f(x, y + 1, (0, 0))

        ncomp = list(comp) + [len(comp), len(comp)]
        ret += f(x, y + 1, normalize(ncomp))

        ncomp = list(comp[:-1]) + [len(comp), len(comp), comp[-1]]
        ret += f(x, y + 1, normalize(ncomp))

        return ret

    if y == M:
        if comp[-1] != comp[-2]:
            ncomp = merge(comp, -1, -2)
            ret += f(x + 1, 0, normalize(ncomp[:-2]))
        if comp[-2] != comp[-3]:
            ncomp = merge(comp, -2, -3)
            ret += f(x + 1, 0, normalize(list(ncomp[:-3]) + [ncomp[-1]]))
        return ret

    if y == 0:
        ret += f(x, y + 1, normalize([comp[0], len(comp), len(comp)] + list(comp[1:])))
        ret += f(x, y + 1, normalize([len(comp), len(comp), comp[0]] + list(comp[1:])))
        return ret

    i = y * 2 - 1
    if comp[i] != comp[i + 1]:
        ncomp = merge(comp, i, i + 1)
        if ncomp[i + 2] != ncomp[i + 3]:
            nncomp = merge(ncomp, i + 2, i + 3)
            ret += f(x, y + 1, normalize(list(nncomp[:i]) + [len(nncomp), len(nncomp) + 1, len(nncomp) + 1, len(nncomp)] + list(nncomp[i+4:])))
            ret += f(x, y + 1, normalize(list(nncomp[:i]) + [len(nncomp), len(nncomp), len(nncomp) + 1, len(nncomp) + 1] + list(nncomp[i+4:])))
        ret += f(x, y + 1, normalize(list(ncomp[:i]) + [ncomp[i+2], ncomp[i+3], len(ncomp), len(ncomp)] + list(ncomp[i+4:])))
        ret += f(x, y + 1, normalize(list(ncomp[:i]) + [ncomp[i+2], len(ncomp), len(ncomp), ncomp[i+3]] + list(ncomp[i+4:])))
        ret += f(x, y + 1, normalize(list(ncomp[:i]) + [len(ncomp), len(ncomp), ncomp[i+2], ncomp[i+3]] + list(ncomp[i+4:])))

    if comp[i + 1] != comp[i + 2]:
        ncomp = merge(comp, i + 1, i + 2)
        if ncomp[i] != ncomp[i + 3]:
            nncomp = merge(ncomp, i + 0, i + 3)
            ret += f(x, y + 1, normalize(list(nncomp[:i]) + [len(nncomp), len(nncomp) + 1, len(nncomp) + 1, len(nncomp)] + list(nncomp[i+4:])))
            ret += f(x, y + 1, normalize(list(nncomp[:i]) + [len(nncomp), len(nncomp), len(nncomp) + 1, len(nncomp) + 1] + list(nncomp[i+4:])))
        ret += f(x, y + 1, normalize(list(ncomp[:i]) + [ncomp[i], len(ncomp), len(ncomp), ncomp[i+3]] + list(ncomp[i+4:])))
        ret += f(x, y + 1, normalize(list(ncomp[:i]) + [len(ncomp), len(ncomp), ncomp[i], ncomp[i+3]] + list(ncomp[i+4:])))
        ret += f(x, y + 1, normalize(list(ncomp[:i]) + [ncomp[i], ncomp[i+3], len(ncomp), len(ncomp)] + list(ncomp[i+4:])))

    if comp[i + 2] != comp[i + 3]:
        ncomp = merge(comp, i + 2, i + 3)
        ret += f(x, y + 1, normalize(list(ncomp[:i]) + [len(ncomp), len(ncomp), ncomp[i+0], ncomp[i+1]] + list(ncomp[i+4:])))
        ret += f(x, y + 1, normalize(list(ncomp[:i]) + [ncomp[i+0], ncomp[i+1], len(ncomp), len(ncomp)] + list(ncomp[i+4:])))
        ret += f(x, y + 1, normalize(list(ncomp[:i]) + [ncomp[i+0], len(ncomp), len(ncomp), ncomp[i+1]] + list(ncomp[i+4:])))

    ret += f(x, y + 1, comp)
    return ret


if __name__ == '__main__':
    N, M = [int(s) for s in input().split()]
    if N < M:
        N, M = M, N
    print(f(0, 0, ()) % 10**10)
