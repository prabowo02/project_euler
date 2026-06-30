def M(N):
    def nxt(s):
        return s*s % 50515093

    s = nxt(290797)
    lst = {-1: -1}
    stack = [(-1, -1)]
    n, acc = 0, 0
    ans = 0

    def push(s, n):
        nonlocal acc
        while s <= stack[-1][0]:
            acc -= (stack[-1][1] - stack[-2][1]) * stack[-1][0]
            stack.pop()
        stack.append((s, n))
        acc += (n - stack[-2][1]) * s

    while s not in lst:
        lst[s] = n
        push(s, n)

        ans += acc

        n += 1
        s = nxt(s)

        if n == N:
          return ans
 
    cycle = n - lst[s]
    for i in range(cycle):
        push(s, n)

        cnt = (N - n - 1) // cycle + 1
        ans += (acc + acc + cycle * stack[1][0] * (cnt - 1)) * cnt // 2

        n += 1
        s = nxt(s)

        if n == N:
            return ans

    return ans


if __name__ == '__main__':
    print(M(10))
    print(M(10000))
    print(M(2 * 10**9))
