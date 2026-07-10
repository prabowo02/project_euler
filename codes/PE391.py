# Suppose we keep track of "how far" a position is from the next losing position.

# We have a function f that "jumps" 2^k numbers, such that you input with the next
# losing distance after those 2^k numbers, then output the next losing distance of
# the first of that 2^k numbers.

# You start with a bunch of functions that give mapping for numbers in [2^i - 2^k, 2^k)
# Then you iteratively double the range of that numbers.

# Also the function eventually becomes constant very quickly as you iterate,
# so you can just stop after that


def M(n):
    func = [[i + j if i + j <= n else 0 for j in range(n + 1)] for i in range(n + 2)]
    while len(func) > 1:
        nfunc = [[func[i - 1][func[i][j]] for j in range(n + 1)] for i in range(1, len(func))]
        func = nfunc
        if [func[0][0] for _ in range(n + 1)] == func[0]:
            break
    return func[0][0]


if __name__ == '__main__':
    print(M(2))
    print(M(7))
    print(M(20))
    print(sum(M(i)**3 for i in range(1, 21)))
    print(sum(M(i)**3 for i in range(1, 1001)))
