def S(N):
    x, y = 1 % N, 1 % N
    points = set()
    for i in range(N*2):
        points.add((x, y))
        x = x * 2 % N
        y = y * 3 % N

    vals = [0 for _ in range(N)]

    def update(x, val):
        x += 1
        while x <= N:
            vals[x - 1] = max(vals[x - 1], val)
            x += x & -x

    def query(x):
        ret, x = 0, x + 1
        while x > 0:
            ret = max(ret, vals[x - 1])
            x -= x & -x
        return ret

    for x, y in sorted(points):
        update(y, query(y) + 1)

    return query(N - 1)


if __name__ == '__main__':
    print(S(22))
    print(S(123))
    print(S(10000))
    print(sum(S(k**5) for k in range(1, 31)))
