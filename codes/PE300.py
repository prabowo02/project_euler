def solve(N):
    neighs = set()

    s = {}
    def dfs(n, x, y):
        s[(x, y)] = n
        if n == 0:
            neigh = []
            for x, y in s:
                for nx, ny in ((x + 1, y), (x, y + 1)):
                    if (nx, ny) not in s:
                        continue
                    u, v = s[(x, y)], s[(nx, ny)]
                    if u > v:
                        u, v = v, u
                    neigh.append((u, v))

            neighs.add(tuple(sorted(neigh)))
            del s[(x, y)]
            return

        for nx, ny in ((x + 1, y), (x - 1, y), (x, y - 1), (x, y + 1)):
            if (nx, ny) in s or abs(nx) > N // 2 or abs(ny) > N // 2:
                continue
            dfs(n - 1, nx, ny)

        del s[(x, y)]

    dfs(N - 1, 0, 0)
    # print(len(neighs))

    ans = 0
    for i in range(1 << N):
        res = 0
        for neigh in neighs:
            res = max(res, sum([i >> x & i >> y & 1 for x, y in neigh]))
        ans += res

    return ans, 2**N, ans / 2**N


if __name__ == '__main__':
    print(solve(8))
    print(solve(15))
