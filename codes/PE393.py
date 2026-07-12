import functools


def solve(n):
    @functools.cache
    def f(row, col, lft, ups):
        if row == n:
            return 1 if ups == tuple(0 for i in range(n)) else 0
        if col == n:
            return f(row + 1, 0, 0, ups) if lft == 0 else 0

        def newUps(val):
            ret = list(ups)
            ret[col] = val
            return tuple(ret)

        up = ups[col]
        if lft != 0 and up != 0:
            return f(row, col + 1, 0, newUps(0)) if lft != up else 0

        if lft != 0:
            return f(row, col + 1, lft, newUps(0)) + \
                f(row, col + 1, 0, newUps(lft))

        if up != 0:
            return f(row, col + 1, up, newUps(0)) + \
                f(row, col + 1, 0, newUps(up))

        return f(row, col + 1, 1, newUps(-1)) + \
            f(row, col + 1, -1, newUps(1))

    return f(0, 0, 0, tuple(0 for i in range(n)))


if __name__ == '__main__':
    print(solve(4))
    print(solve(10))
