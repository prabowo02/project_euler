def Tr(n):
    Td = [1 for _ in range(n + 2)]
    for p in range(2, len(Td)):
        if Td[p] > 1:
            continue
        for i in range(p, len(Td), p):
            e, num = 1, i // p
            while num % p == 0:
                num //= p
                e += 1
            Td[i] *= e + 1

    for i in range(2, len(Td)):
        Td[i - 1] *= Td[i]
        t = (i * (i - 1) & -i * (i - 1)).bit_length()
        Td[i - 1] //= t
        Td[i - 1] *= t - 1

    Td.pop()

    # Only about 300 for n=6*10^7
    comp = {v: k for k, v in enumerate(sorted(set(Td)))}

    pref1, pref2, pref3 = [[0 for _ in range(len(comp) + 1)] for _ in range(3)]
    for d in Td[1:]:
        d = comp[d]

        for i in range(d + 1):
            pref1[i] += 1
        for i in range(d + 1):
            pref2[i] += pref1[d + 1]
        for i in range(d + 1):
            pref3[i] += pref2[d + 1]

    return pref3[0]


if __name__ == '__main__':
    print(Tr(20))
    print(Tr(100))
    print(Tr(1000))
    print(Tr(60000000) % 10**18)
