def f(n):
    mod = 10**18
    moves0, moves1 = {}, {0: 1}
    nim0, nim1 = 0, 1

    for i in range(2, n):
        nmoves = {0: 1}
        for nim, cnt in moves0.items():
            k = (nim ^ nim1) + 1
            nmoves[k] = (nmoves.get(k, 0) + cnt) % mod

        for nim, cnt in moves1.items():
            k = (nim ^ nim0) + 1
            nmoves[k] = (nmoves.get(k, 0) + cnt) % mod

        moves0, moves1 = moves1, nmoves
        nim0, nim1 = nim1, (nim0 ^ nim1) + 1

    return (moves0.get(nim1, 0) + moves1.get(nim0, 0)) % mod



if __name__ == '__main__':
    print(f(2))
    print(f(3))
    print(f(4))
    print(f(5))
    print(f(6))
    print(f(10))
    print(f(10000))
