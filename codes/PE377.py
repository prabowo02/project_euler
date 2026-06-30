import functools


def f(n):
    mod = 10**9
    def mul(A, B):
        n = len(A)
        return [[sum(A[i][k] * B[k][j] for k in range(n)) % mod
                 for j in range(n)] for i in range(n)]

    def power(A, y):
        ret = [[1 if i == j else 0 for j in range(len(A))] for i in range(len(A))]
        op = A
        while y:
            if y & 1:
                ret = mul(ret, op)
            op = mul(op, op)
            y //= 2
        return ret

    @functools.cache
    def left(n):
        if n < 0:
            return 0
        A = [[0 for _ in range(9)] for _ in range(9)]
        for j in range(9):
            A[0][j] = 1
        for i in range(1, 9):
            A[i][i - 1] = 1
        return power(A, n)[0][0]

    @functools.cache
    def right(n, s):
        if n == 0:
            return 1 if s == 0 else 0
        return sum(right(n - 1, s - i) for i in range(1, 10))

    ret = 0
    for i in range(9):
        for d in range(1, 10):
            for s in range(i, min(n - d, 9*i) + 1):
                ret += left(n - d - s) * right(i, s) * d * 10**i
    return ret % mod


if __name__ == '__main__':
    print(f(5))
    print(sum(f(13**i) for i in range(1, 18)) % 10**9)
