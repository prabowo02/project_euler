import itertools


# Position of n-th integer in S
def pos(n):
    ret = 0
    ln = len(str(n))
    for i in range(1, ln):
        ret += 10**(i-1) * 9 * i
    ret += ln * (n - 10**(ln-1))
    return ret + 1


def f(n):
    occ, sn = [], str(n)

    # Part of two numbers with length < length(n)
    for i in range(1, len(sn) // 2 + 1):
        s = str(int(sn[i:]) - 1) + sn[i:]
        if sn in s:
            occ.append(pos(int(sn[i:])) - i)
    for i in range(len(sn) // 2 + 1, len(sn)):
        s = sn[:i] + str(int(sn[:i]) + 1)
        if sn in s:
            occ.append(pos(int(sn[i:])) - i)        

    for i in range(len(sn) + 1):
        # Part of a single number
        for j in range(10**i):
            sj = '0' * (i - len(str(j))) + str(j) if i > 0 else ''
            if sj.startswith('0'):
                occ.append(pos(int(sn + sj)))
                continue
            for k in range(len(sj) + 1):
                s = sj[:k] + sn + sj[k:]
                occ.append(pos(int(s)) + k)

        # Part of two numbers
        for j in range(10**i):
            sj = '0' * (i - len(str(j))) + str(j) if i > 0 else ''
            for k in range(1, len(sn)):
                s = sn[k:] + sj + sn[:k]
                if s.startswith('0'):
                    continue
                occ.append(pos(int(s)) + len(s) - k)

        if len(occ) >= n:
            break

    # Assume the given n is not part of > 2 numbers

    # assert len(occ) == len(set(occ))
    occ.sort()

    return occ[n - 1]


def brute(n):
    sn, s = str(n), ''
    for i in range(1, 20000):
        s += str(i)

    ret = []
    for i in range(len(s) - len(sn)):
        if s[i:i+len(sn)] == sn:
            ret.append(i + 1)

    return ret


if __name__ == '__main__':
    print(f(1))
    print(f(5))
    print(f(12))
    print(f(7780))
    print(sum([f(3**i) for i in range(1, 14)]))  # ~1 min
