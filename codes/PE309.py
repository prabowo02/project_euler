# Crossing ladders problem
# Let X and Y be the "height" of ladders with length x and y respectively
# It can be proven that if w, x, y, h are integers, then X and Y must be integers
# So we want:
# - Triple pythagorean of (w, X, x) and (w, Y, y)
# - Integer solution for optic 1/h = 1/X + 1/Y


def solve(N):
    triples = [[] for _ in range(N)]

    q = [(1, 2)]
    for n, m in q:
        if n*n + m*m > N:
            continue

        if n > m:
            n, m = m, n

        if m % 2 == 0 or n % 2 == 0:
            a, b, c = m*m - n*n, 2*m*n, m*m + n*n
            for k in range(1, (N - 1) // c + 1):
                triples[k*a].append((k*a, k*b, k*c))
                triples[k*b].append((k*b, k*a, k*c))

        q.append((n + m, m))
        q.append((n, n + m))

    ret = 0
    for w in range(1, N):
        for i in range(len(triples[w])):
          for j in range(i):
              X, Y = triples[w][i][1], triples[w][j][1]
              if X * Y % (X + Y) == 0:
                  ret += 1
    return ret


if __name__ == '__main__':
    print(solve(200))
    print(solve(1000000))
