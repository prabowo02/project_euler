def left(A, B):
    # Move B by -A
    A, B = [A[0], A[1]], [B[0] - A[0], B[1] - A[1]]

    # Rotate cos(theta) = 4/5; sin(theta) = 3/5 and scale by 4/5
    B[0], B[1] = (B[0] * 16 - B[1] * 12) / 25, (B[0] * 12 + B[1] * 16) / 25

    # Translate A by 90 deg CCW rotation of B
    A[0] += -B[1]
    A[1] += B[0]

    # Move back B wrt A
    B[0] += A[0]
    B[1] += A[1]

    return A, B


def right(A, B):
    # Move A by -B
    A, B = [A[0] - B[0], A[1] - B[1]], [B[0], B[1]]

    # Rotate cos(theta) = 3/5; sin(theta) = -4/5 and scale by 3/5
    A[0], A[1] = (A[0] * 9 + A[1] * 12) / 25, (-A[0] * 12 + A[1] * 9) / 25

    # Translate B by 90 deg CW rotation of A
    B[0] += A[1]
    B[1] += -A[0]

    # Move back A wrt B
    A[0] += B[0]
    A[1] += B[1]

    return A, B


def solve():
    EPS = 1e-11
    def findLim(a, b, delta):
        ret = -1
        def dfs(A, B, distA, distB, depth=0):
            nonlocal ret
            ret = max(ret, distA, distB)

            nA, nB = left(A, B)
            dA, dB = delta(A, nA), delta(B, nB)
            if depth < 5 or max(dA, dB) > EPS and max(distA + dA*3, distB + dB*3) > ret:
                dfs(nA, nB, distA + dA, distB + dB, depth+1)

            nA, nB = right(A, B)
            dA, dB = delta(A, nA), delta(B, nB)
            if depth < 5 or max(dA, dB) > EPS and max(distA + dA*3, distB + dB*3) > ret:
                dfs(nA, nB, distA + dA, distB + dB, depth+1)

        dfs([0, 0], [1, 0], a, b)
        return ret

    R = findLim(0, 1, lambda A, nA: nA[0] - A[0])
    L = -findLim(0, -1, lambda A, nA: A[0] - nA[0])
    U = findLim(1, 1, lambda A, nA: nA[1] - A[1])
    D = -findLim(-1, -1, lambda A, nA: A[1] - nA[1])

    print(L, R, U, D)

    return (U - D) * (R - L)


if __name__ == '__main__':
    print('{:.10f}'.format(solve())) # Takes minutes
