import collections
import fractions


def solve2(s):
    return sum(10**i for i in range(1, len(s) + 1) if s[-i:] == s[:i]) - len(s) + 1


def solve(s):
    alpha = '0123456789'
    def nxt(cur):
        for i in range(len(cur), 0, -1):
            if s.startswith(cur[-i:]):
              return i
        return 0

    step = fractions.Fraction(1, len(alpha))
    E = [collections.defaultdict(fractions.Fraction) for _ in range(len(s) + 1)]
    for i in range(len(s) - 1, 0, -1):
        for c in alpha:
            E[i][nxt(s[:i] + c)] += step
        for k, v in E[i+1].items():
            E[i][k] += step * v
        E[i][-1] += 1

        mul = 1 / (1 - E[i][i])
        E[i] = {k: v * mul for k, v in E[i].items() if k < i}

    return (10 + E[1][-1]) / (1 - E[1][0]) - len(s) + 1


if __name__ == '__main__':
    print(solve2('535'))
    print(sum(solve2(str(10**6 // n)) for n in range(2, 1000)))
    print(sum(solve2(str(10**16 // n)) for n in range(2, 1000000)))