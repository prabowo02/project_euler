# After around 10k steps, there is a repeating pattern for every 104 steps

def solve(n):
    blacks = set()
    dirs = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    d, x, y = 0, 0, 0
    cnt = [0]
    for _ in range(104 * 200):
        if (x, y) in blacks:
            blacks.discard((x, y))
            d = (d + 1) % 4
        else:
            blacks.add((x, y))
            d = (d - 1) % 4

        x, y = x + dirs[d][0], y + dirs[d][1]
        cnt.append(len(blacks))

    if n < len(cnt):
        return cnt[n]

    delta = cnt[-1] - cnt[-105]


    return cnt[104 * 199 + n % 104] + delta * (n // 104 - 199)


if __name__ == '__main__':
    print(solve(10**18))
