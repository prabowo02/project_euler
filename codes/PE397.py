# slope = (b^2 - a^2) / k / (b - a) = (b + a) / k

# So the direction matrix of a side of the triangle can be represented as (k, a+b)

# For a 45 deg, it's dot product equals the cross product.
# For angle B:
# k^2 + (a+b)(b+c) = k(a+b) - k(b+c)
# k^2 = (k + (a+b))(k - (b+c)) - k^2
# 2k^2 = (k + (a+b))(k - (b+c))

# So we can factorise 2k^2 = p*q, and find all the a, b, c satisfying the factors:
# k + (a+b) = p; k - (b+c) = q
# For a fixed b, both a and c are implied as well, we just have to find b that still respect
# |a|, |c| <= X and a < b < c
# a = p-b-k
# c = k-b-q
# -X <= a ==> b <= p-k+X
# a < b ==> (p-k)/2 < b
# b < c ==> b < (k-q)/2
# c <= X ==> k-q-X <= b
# Also note that a < c implies p+q < 2k which can only happen when both p and q takes the negative sign

# Similarly when A is the 45 deg angle:
# k + (a+c) = p; k - (a+b) = q
# For a fixed a:
# c = p-a-k
# b = k-a-q
# -X <= a
# b < c ==> 2k < p+q (so p and q must be positive)
# a < b ==> a < (k-q)/2
# c <= X ==> p-k-X <= a

# Double count:
# If A and C are both 45:
# k + (a+c) = p1; k - (a+b) = q1; k + (b+c) = p2; k - (a+c) = q2
# c = p1-k-a; b = k-a-q1; k + (b+c) = k+p1-q1-2a = p2; (2k-p1)(k+p1-q1-2a) = 2k^2

# If A and B are both 45:
# k + (a+b) = p1; k - (b+c) = q1; k + (a+c) = p2; k - (a+b) = q2
# a = p1-k-b; c = k-b-q1; k + (a+c) = k+p1-q1-2b = p2; (2k-p1)(k+p1-q1-2b) = 2k^2


def F(K, X):
    divs = [[] for _ in range(K + 1)]
    for i in range(2, len(divs), 2):
            divs[i].append((2, (i & -i).bit_length() * 2 - 1))

    for p in range(3, len(divs)):
        if divs[p]:
            continue
        for i in range(p, len(divs), p):
            num, e = i // p, 2
            while num % p == 0:
                num //= p
                e += 2
            divs[i].append((p, e))

    for i in range(1, len(divs), 2):
        divs[i].append((2, 1))

    # Divisors of 2n^2
    def divisors(n):
        ret = [1]
        for p, e in divs[n]:
            pe, l = 1, len(ret)
            for j in range(e):
                pe *= p
                for i in range(l):
                    ret.append(ret[i] * pe)
        return ret

    ret = 0
    for k in range(1, K + 1):
        for p in divisors(k):
            # Angle A
            q = 2*k*k // p
            lft, rgt = max(-X, p-k-X), (k-q-1)//2
            if lft <= rgt:
                ret += (rgt - lft + 1) * 2

            # Angle B
            p, q = -p, -q
            lft, rgt = max(k-q-X, (p-k)//2+1), min(p-k+X, (k-q-1)//2)
            if lft <= rgt:
                ret += rgt - lft + 1

            # Angle A, C
            # (2k-p)(k+p-q-2a) = 2k^2
            p, q = -p, -q
            if (2*k - p) != 0 and 2*k*k % (2*k-p) == 0:
                a2 = k + p - q - 2*k*k // (2*k-p)
                if a2 % 2 == 0:
                    a = a2 // 2
                    b = k - a - q
                    c = p - k - a
                    if -X <= a < b < c <= X:
                        ret -= 1

            # Angle A, B
            # (2k-p)(k+p-q-2b) = 2k^2
            p, q = -p, -q
            if 2*k*k % (2*k-p) == 0:
                b2 = k + p - q - 2*k*k // (2*k-p)
                if b2 % 2 == 0:
                    b = b2 // 2
                    a = p - k - b
                    c = k - b - q
                    if -X <= a < b < c <= X:
                        ret -= 2

    return ret

if __name__ == '__main__':
    print(F(1, 10))
    print(F(10, 100))
    print(F(10**6, 10**9))
