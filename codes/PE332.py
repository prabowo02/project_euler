import math


def main():
    squares = {i*i: i for i in range(1, 51)}
    points = {i: [] for i in range(1, 51)}
    for i in range(51):
        for j in range(51):
            for k in range(51):
                if (r2 := i*i + j*j + k*k) in squares:
                    points[squares[r2]].append((i, j, k))
                    if i != 0 and j != 0:
                        points[squares[r2]].append((i, j, -k))
                    
                    if i != 0 and k != 0:
                        points[squares[r2]].append((i, -j, k))
                    
                    if i != 0:
                        points[squares[r2]].append((i, -j, -k))

    # Make unique
    for i in points:
        points[i] = list(set(points[i]))

    def cross(u, v):
        return (u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2], u[0] * v[1] - u[1] * v[0])

    def dot(u, v):
        return u[0] * v[0] + u[1] * v[1] + u[2] * v[2]

    def angle(u, v):
        ret = math.acos((u[0] * v[0] + u[1] * v[1] + u[2] * v[2]) /
            math.sqrt(u[0]**2 + u[1]**2 + u[2]**2) / math.sqrt(v[0]**2 + v[1]**2 + v[2]**2))
        return ret

    def A(r):
        ps = points[r]
        n = len(ps)

        ans = None
        for i in range(n):
            for j in range(i+1, n):
                for k in range(j+1, n):
                    if dot(ps[i], cross(ps[j], ps[k])) == 0:
                        # Degenerate triangle
                        continue

                    dotIJ = dot(ps[i], ps[j])
                    dotIK = dot(ps[i], ps[k])
                    dotJK = dot(ps[j], ps[k])

                    cosa = dotIJ / r**2
                    cosb = dotIK / r**2
                    cosc = dotJK / r**2
                    sina = math.sqrt(1 - cosa**2)
                    sinb = math.sqrt(1 - cosb**2)
                    sinc = math.sqrt(1 - cosc**2)

                    # Law of cosines
                    A = (cosa - cosb * cosc) / (sinb * sinc)
                    B = (cosb - cosa * cosc) / (sina * sinc)
                    C = (cosc - cosa * cosb) / (sina * sinb)

                    if abs(A) > 1:
                        A = math.trunc(A)
                    if abs(B) > 1:
                        B = math.trunc(B)
                    if abs(C) > 1:
                        C = math.trunc(C)

                    # Girard's theorem
                    excess = math.acos(A) + math.acos(B) + math.acos(C) - math.pi

                    if ans is None or excess < ans:
                        ans = excess

        print(r, ans)
        return ans * r * r

    print(A(14))
    ans = sum(A(r) for r in range(1, 51))
    print(ans) # 2717.75152488109


if __name__ == '__main__':
    main()
