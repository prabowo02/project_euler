from math import factorial


def divisors(n):
    ret = []
    for d in range(1, n + 1):
        if d * d == n:
            ret.append(d)
            break
        if d * d > n:
            break
        if n % d == 0:
            ret.append(d)
            ret.append(n // d)
    return sorted(ret)

phi = [i for i in range(1000)]
for i in range(2, 1000):
    if phi[i] != i:
        continue
    for j in range(i, 1000, i):
        phi[j] = phi[j] // i * (i - 1)

def f(m, n):
    ret = 0
    for d in divisors(n):
        ret += phi[d] * factorial(m * n // d) // factorial(n // d)**m
    return ret // (n * m)


def main():
    ans = 0
    for n in range(1, 100):
        m = 2
        while (s := f(m, n)) <= 10**15:
            ans += s
            m += 1
    print(ans)


if __name__ == '__main__':
    main()
