import math


moduli = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43]
# moduli = [7, 13]


def crt(rems, moduli):
    mod = math.prod(moduli)
    return sum(r * (mod//m) * pow(mod//m, -1, m) for r, m in zip(rems, moduli)) % mod


def dfs(rems, moduli):
    if len(rems) == len(moduli):
        yield crt(rems, moduli)
    else:
        m = moduli[len(rems)]
        for i in range(m):
            if pow(i, 3, m) == 1:
                rems.append(i)
                yield from dfs(rems, moduli)
                rems.pop()


print(sum(dfs([], moduli)) - 1)
