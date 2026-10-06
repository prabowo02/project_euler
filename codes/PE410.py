# Fix a and r:
# We have: r = a(b+c) / sqrt(4a^2 + (b-c)^2)
# ==> 4a^2 r^2 + (r^2 - a^2)(b^2 + c^2) = 2bc(a + r)

# Let g = gcd(a, r); a = a'g; r = r'g
# We have, a'^2 (b + c)^2 - r^2 (b - c)^2 = 4a^2 r^2 g^2
# It must be that (b + c) = ur' and (b - c) = va' for some integers u and v
# So, u^2 - v^2 = 4g^2
# If d | g, then it simply is u = d + g/d, v = d - g/d
# Since b and c have to be integers, we require ur' = va' (mod 2), 
# so when r' and a' have different parities, d and g/d must be even.

# So, when a' and r' are both odd, then the contribution is 2 * #div(g^2) (take into account negative divisors too)
# When a' and r' have different parities, then contribution is 2 * #div((g/2)^2)

# Number of coprime pairs with different parities can be found with Mobius-like transform


def F(A, R):
    if A > R:
        A, R = R, A

    odds, diff = [0 for _ in range(A + 1)], [0 for _ in range(A + 1)]

    for i in range(1, len(odds)):
        odds[i] = ((A // i) * (R // i) + 1) // 2
        diff[i] = (A // i) * (R // i) // 2

    for i in range(A, 0, -1):
        for j in range(i*2, A+1, i):
            if j // i % 2 == 0:
                odds[i] -= odds[j] + diff[j]
            else:
                odds[i] -= odds[j]
                diff[i] -= diff[j]

    divs = [1 for _ in range(A + 1)]
    for p in range(2, len(divs)):
        if divs[p] != 1:
            continue
        for i in range(p, len(divs), p):
            num, e = i, 0
            while num % p == 0:
                num //= p
                e += 1
            divs[i] *= e*2 + 1

    ans = 0
    for i in range(1, A + 1):
        ans += 2 * odds[i] * divs[i]
        if i % 2 == 0:
            ans += 2 * diff[i] * divs[i // 2]
        else:
            ans += 2 * diff[i] * divs[i]

    return ans


if __name__ == '__main__':
    print(F(1, 5))
    print(F(2, 10))
    print(F(10, 100))
    print(F(10**8, 10**9) + F(10**9, 10**8))
