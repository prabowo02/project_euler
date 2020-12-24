def factorize(n):
    ret = []
    i = 2
    
    while i*i <= n:
        if n % i == 0:
            ret.append(i)
            while n % i == 0:
                n //= i
        i += 1
    
    if n > 1: 
        ret.append(n)

    return ret

def merge(a, b):
    return sorted(set(a + b))

p, q = map(int, input().split())

factors = merge(factorize(p-1), factorize(q-1))[1:]

two = (4 if (p-1) % 4 == 0 or (q-1) % 4 == 0 else 2)

ans = 0
for i in range(1 << len(factors)):
    mod = two

    idxs = []
    for j in range(len(factors)):
        if i >> j & 1:
            mod *= factors[j]
            idxs.append(j)

    crts = []
    for idx in idxs:
        factor = factors[idx]
        crts.append(pow(mod // factor, factor-2, factor) * (mod // factor))

    sign = (-1 if len(idxs) % 2 else 1)

    initSum = mod // two % two * (mod // two) * (two-1)
    for j in range(1 << len(idxs)):
        first = initSum
        for k in range(len(idxs)):
            if j >> k & 1:
                first += crts[k]
        first %= mod

        num = (p-1) * (q-1) // mod
        term = num * (num - 1) // 2 * mod + first * num

        ans += sign * term

print(ans % 1000000007)
