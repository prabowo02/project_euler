import functools


@functools.cache
def M(C, R):
    if R == 0:
        return 1
    return max(0, (M(C, R - 1) - 2) // (C - 2)) * 2 + M(C, R - 1) + 1


def solve(C, R):
    ans = [M(c, R) for c in range(3, C + 1)]
    print(ans)
    return sum(ans)


if __name__ == '__main__':
    print(solve(4, 6))
    print(solve(10, 10))
    print(solve(40, 30))
