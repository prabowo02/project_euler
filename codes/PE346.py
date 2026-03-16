# Any number n can be represented as repunit of base n-1
# So we just have to find whether it can be represented as 111, 1111, ...
# so just find all those numbers

# Note: From https://en.wikipedia.org/wiki/Goormaghtigh_conjecture, 
#   31 and 8191 are the only ones that have >= 3 repunit representation, so it is possible to optimise without sets

import itertools

def solve(N):
    s = set()

    b = 2
    while b*b < N:
        num = b + 1
        for i in itertools.count(2):
            num += b**i
            if num >= N:
                break
            s.add(num)
        b += 1

    return sum(s) + 1

if __name__ == '__main__':
    print(solve(50))
    print(solve(1000))
    print(solve(10**12))
