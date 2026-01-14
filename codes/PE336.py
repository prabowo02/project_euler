import itertools
import string


def solve(N, K):
    start = string.ascii_uppercase[:N]

    def greedy(s):
        ret = 0
        for i in range(N):
            if s[i] == start[i]:
                continue

            for j in range(i, N):
                if s[j] == start[i]:
                    break

            if j != N - 1:
                ret += 1
                s = s[:j] + s[j:][::-1]

            ret += 1
            s = s[:i] + s[i:][::-1]

        assert s == start
        return ret

    worst = 0
    maximix = []
    for s in itertools.permutations(start):
        s = ''.join(s)
        cost = greedy(s)
        if cost > worst:
            worst = cost
            maximix = [s]
        elif cost == worst:
            maximix.append(s)

    return maximix[K - 1]

if __name__ == '__main__':
    print(solve(4, 1))
    print(solve(4, 2))
    print(solve(6, 10))
    print(solve(11, 2011))
