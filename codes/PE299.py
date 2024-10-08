# There are two cases:
# 1. The triangles are similar by rotations.
#    We can then see that DP and BP are angular bisectors of OBD. Hence, P is the incenter of OBD.
#    The radius of incenter is given by (a + b - c) / 2, and since radius is integer,
#      then c will always be integer, hence OBD has to be a Pythagorean triangle.
#    Finding Pythagorean triangles are sufficient, because their inradii are always integer.
#    So we just need to find all Pythagorean triangles (OB, OD, BD) s.t. |OB| + |OD| < n
#    
# 2. The triangles are similar by reflections
#    It must be that b = d, and angle of BPD is 135 degree.
#    The circumcircle of BDP has radius BD/(2sin(BPD)) = b, and its center is at
#      the perpendicular bisector of BD, and we can infer that (b, b) will be its center.
#    This also implies that P must be on a line of a circle with radius b and center (b, b).
#    Hence, we just need to find the lattice points of that cirle.
#    That is, we just need to find all Pythagorean triples such that its hypothenuse's length * 2 is < n.


def solve(N):
    q, ans = [(1, 2)], 0
    for n, m in q:
        a = m*m - n*n
        b = 2*m*n
        c = m*m + n*n

        if a + b >= N:
            continue

        q.append((n, n + m))
        q.append((m, n + m))

        if n % 2 == 1 and m % 2 == 1:
            continue

        ans += (N - 1) // (a + b) * 2  # (3, 4, 5) and (4, 3, 5) are distinct
        ans += (N - 1) // (c * 2)

    return ans


if __name__ == '__main__':
    print(solve(100))
    print(solve(10**5))
    print(solve(10**8))
