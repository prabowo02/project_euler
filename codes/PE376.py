import functools


def solve(N):
    @functools.cache
    def f(num, a, b, c, winA, winB, winC):
        if num == 0:
            return 1 if (a, b, c, winA, winB, winC) == (6, 6, 6, 19, 19, 19) else 0

        ret = 0
        for i in range(7-a):
            for j in range(7-b):
                for k in range(7-c):
                    ret += f(num - 1, a+i, b+j, c+k,
                             min(19, winA + i*b),
                             min(19, winB + j*c),
                             min(19, winC + k*a))
        return ret

    return f(N, 0, 0, 0, 0, 0, 0) // 3


if __name__ == '__main__':
    print(solve(7))
    print(solve(30))
