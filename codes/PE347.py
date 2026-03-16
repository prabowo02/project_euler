# Any number n can be represented as repunit of base n-1
# So we just have to find whether it can be represented as 111, 1111, ...
# so just find all those numbers

# Note: From https://en.wikipedia.org/wiki/Goormaghtigh_conjecture, 
#   31 and 8191 are the only ones that have >= 3 repunit representation, so it is possible to optimise without sets

import itertools

def solve(N):
    is_prime = [True for _ in range(N + 1)]
    primes = []
    for p in range(2, N + 1):
        if not is_prime[p]:
            continue
        primes.append(p)
        for i in range(p*2, N + 1, p):
            is_prime[i] = False

    ans = 0
    for i in range(len(primes)):
        p = primes[i]
        for j in range(i+1, len(primes)):
            q = primes[j]
            if p*q > N:
                break

            num = 0
            pe = p
            while pe * q <= N:
                qe = q
                while pe * qe <= N:
                    num = max(num, pe * qe)
                    qe *= q
                pe *= p

            ans += num

    return ans


if __name__ == '__main__':
    print(solve(100))
    print(solve(10**7))
