def solve(starts, ends):
    L, R = 10**len(starts) // (int(starts) + 1) + 1, 10**len(starts) // int(starts)

    # 10 is primitive root mod p
    def is_cyclic(p):
        d = 2
        while d*d <= p - 1:
            if pow(10, (p - 1) // d, p) == 1:
                return False
            d += 1
        return True


    for p in range(L, R + 1):
        if p % 2 == 0 or p % 5 == 0:
            continue
        if pow(10, p - 1, p) != 1:
            continue
        if (-1 * pow(p, -1, 10**len(ends))) % 10**len(ends) != int(ends):
            continue
        if not is_cyclic(p):
            continue
        
        x, ret = 1, 0
        for i in range(p - 1):
            x *= 10
            ret += x // p
            x %= p
        return ret


if __name__ == '__main__':
    print(solve('00000000137', '56789'))