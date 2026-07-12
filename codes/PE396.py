def G(n):
    mod = 10**9
    g = [int(b) for b in bin(n)[2:]][::-1]
    k = 1

    while True:
        k += g[0]
        g[0] = 0

        if g == [0]:
            break

        k *= pow(2, g[1], mod)
        k += pow(2, g[1] + 1, mod) - 2
        g[1] = 0
        if g == [0, 0]:
            break

        k += 1
        k %= mod

        # Subtract by 1
        for i in range(len(g)):
            if g[i] != 0:
                g[i] -= 1
                for j in range(i):
                    g[j] = k
                while g[-1] == 0:
                    g.pop()
                break

    return k - 1


if __name__ == '__main__':
    print(G(2))
    print(G(4))
    print(G(6))
    print(sum(G(i) for i in range(1, 8)))
    print(sum(G(i) for i in range(1, 16)) % 10**9)
