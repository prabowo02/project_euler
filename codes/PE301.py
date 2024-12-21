def solve(n):
    a, b = 1, 1
    for _ in range(n):
        a, b = b, a + b
    return b


if __name__ == '__main__':
    print(solve(30))
