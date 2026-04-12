# The binary expression of s an integer may appear as a substring of a Thue-Morse sequence if and only if s is an overlap-free string.
# A binary string is non overlapping if there is no substring of s of the form 0t0t0 or 1t0t1 where t is any binary string.
#   That is, any binary string with critical exponent at most 2 will appear in the Thue-Morse sequence

# Let mu(s) be the Thue-Morse morphism such that every character of s is substituted by the rule 0 --> 01; 1 --> 10. E.g. mu(11010) = 1010011001
# Let S(n) be the set of all overlap-free string of a length exactly n
# S(1) = {0, 1}
# S(2) = {00, 01, 10, 11}
# S(3) = {001, 010, 011, 100, 101, 110}
# For n >= 4, S(n) can be generate uniquely by:
#   If n even:
#   S(n) = {mu(s) for s in S(n/2)} U {s[0]' + mu(s[1:-1]) + s[-1] for s in S(n/2 + 1))}
#   If n odd:
#   S(n) = {s[0]' + mu(s[1:]) in S(n)} U {mu(s[:-1])}
# Where + is concatenation, s' means complement (i.e. every 0 becomes 1, and vice versa), s[x:y] is slicing: taking the x-th character to (y-1)-th character (and -1 means (n-1)-th character).

# We can also infer that for n >= 4
# |S(n)| = |S(n/2)| + |S(n/2 + 1)| if n even
# |S(n)| = 2|S((n+1)/2)| if n odd

# Notice that, for those starting with 0, the lexicographically smallest of mu(s) starts with 0101, and the lexicographically largest s[0]' + mu(s[1:]) starts with 01001.
# Meaning that, when generating overlap-free words that start with 0, s[0]' + mu(s[1:]) generates all words that lexicographically precedes mu(s)
# Similar thing can be inferred when generating words that start with 1.

# To handle the modulo 10^9, the tricky part is when handling mu
# To evaluate mu, you'll need to maintain the sequence where the k-th bit represents 2^k, 2^{k*2}, 2^{k*2^2}, 2^{k*2^3}, ...
# Also, the lack of inverse under mod 1e9 also requires you to keep the sequence except the last one, i.e. s[:-1]

import functools

@functools.cache
def count(n):
    if n == 1:
        return 1
    if n == 2:
        return 2
    if n == 3:
        return 3
    if n % 2 == 0:
        return count(n // 2) + count(n // 2 + 1)
    return 2 * count(n // 2 + 1)


@functools.cache
def prefcount(n):
    if n <= 0:
        return 0
    if n == 1:
        return 1
    if n == 2:
        return 3
    if n == 3:
        return 6
    if n % 2 == 0:
        return prefcount(n // 2 + 1) + 3 * prefcount(n // 2) - 4
    return prefcount(n // 2 + 1) * 3 + prefcount(n // 2) - 4


def mu(s):
    return ''.join(['01' if c == '0' else '10' for c in s])


def inv(s):
    return ''.join(['1' if c == '0' else '0' for c in s])


def S(n, k, starts):
    if n == 1:
        return [['0'], ['1']][starts][k]
    if n == 2:
        return [['00', '01'], ['10', '11']][starts][k]
    if n == 3:
        return [['001', '010', '011'], ['100', '101', '110']][starts][k]

    if n % 2 == 0:
        if starts == 0:
            c = count(n//2 + 1)
            if k < c:
                s = S(n//2 + 1, k, 1)
                return inv(s[0]) + mu(s[1:-1]) + s[-1]
            else:
                s = S(n//2, k - c, 0)
                return mu(s)
        else:
            c = count(n//2)
            if k < c:
                s = S(n//2, k, 1)
                return mu(s)
            else:
                s = S(n//2 + 1, k - c, 0)
                return inv(s[0]) + mu(s[1:-1]) + s[-1]
    else:
        if starts == 0:
            c = count(n//2 + 1)
            if k < c:
                s = S(n//2 + 1, k, 1)
                return inv(s[0]) + mu(s[1:])
            else:
                s = S(n//2 + 1, k - c, 0)
                return mu(s[:-1]) + s[-1]
        else:
            c = count(n//2 + 1)
            if k < c:
                s = S(n//2 + 1, k, 1)
                return mu(s[:-1]) + s[-1]
            else:
                s = S(n//2 + 1, k - c, 0)
                return inv(s[0]) + mu(s[1:])


# Same as `S`, but has modulo
def Smod(n, k, starts, mod):
    # 2^0 + 2^2^k + 2^{2*2^k} + ... + 2^{(n-1)*2^k}
    @functools.cache
    def twos(n, k):
        if n == 0:
            return 0
        if n == 1:
            return 1
        return (twos(n//2, k) + twos((n+1)//2, k) * pow(2, (n//2)<<k, mod)) % mod

    class Sval:
        def __init__(self, length, front, back):
            self.length = length
            self.front = front
            self.back = back
            self.vals = []
            self.popped = None

        @classmethod
        def from_bin_str(cls, s, prec):
            ret = Sval(len(s), int(s[0]), int(s[-1]))
            ret.vals = [sum(pow(2, j<<i, mod) for j in range(len(s)) if s[-1-j] == '1') % mod for i in range(prec)]
            if len(s) > 1:
                ret.popped = Sval.from_bin_str(s[:-1], prec)
            return ret

        def popback(self):
            return self.popped

        def popfront(self):
            ret = Sval(self.length - 1, None, self.back)
            ret.vals = [(val - self.front * pow(2, (self.length - 1) << i, mod)) % mod for i, val in enumerate(self.vals)]
            if self.popped:
                ret.popped = self.popped.popfront()
            return ret

        def pushback(self, back):
            ret = Sval(self.length + 1, self.front, back)
            ret.vals = [(val * pow(2, 1<<i, mod) + back) % mod for i, val in enumerate(self.vals)]
            ret.popped = self
            return ret

        def pushfront(self, front):
            ret = Sval(self.length + 1, front, self.back)
            ret.vals = [(val + front * pow(2, self.length << i, mod)) % mod for i, val in enumerate(self.vals)]
            if self.popped:
                ret.popped = self.popped.pushfront(front)
            return ret

        def mu(self):
            ret = Sval(self.length * 2, self.front, 1 - self.back)
            ret.vals = [(twos(self.length, i) + self.vals[i] * (pow(2, (1<<(i-1)), mod) - 1)) % mod for i in range(1, len(self.vals))]
            if self.popped:
                ret.popped = self.popped.mu()
                ret.popped.length += 1
                ret.popped.back = self.back
                ret.popped.vals = [(val * pow(2, 1<<i, mod) + self.back) % mod for i, val in enumerate(ret.popped.vals)]
                ret.popped.popped = None
            return ret

        def __str__(self):
            return 'length: {}; front={}; back={}; vals={}'.format(self.length, self.front, self.back, self.vals)

    def S(n, k, starts, depth=1):
        if n == 1:
            return Sval.from_bin_str([['0'], ['1']][starts][k], depth)
        if n == 2:
            return Sval.from_bin_str([['00', '01'], ['10', '11']][starts][k], depth)
        if n == 3:
            return Sval.from_bin_str([['001', '010', '011'], ['100', '101', '110']][starts][k], depth)

        if n % 2 == 0:
            if starts == 0:
                c = count(n//2 + 1)
                if k < c:
                    s = S(n//2 + 1, k, 1, depth+1)
                    return s.popfront().popback().mu().pushback(s.back).pushfront(1 - s.front)
                else:
                    s = S(n//2, k - c, 0, depth+1)
                    return s.mu()
            else:
                c = count(n//2)
                if k < c:
                    s = S(n//2, k, 1, depth+1)
                    return s.mu()
                else:
                    s = S(n//2 + 1, k - c, 0, depth+1)

                    return s.popfront().popback().mu().pushback(s.back).pushfront(1 - s.front)
        else:
            if starts == 0:
                c = count(n//2 + 1)
                if k < c:
                    s = S(n//2 + 1, k, 1, depth+1)
                    return s.popfront().mu().pushfront(1 - s.front)
                else:
                    s = S(n//2 + 1, k - c, 0, depth+1)
                    return s.popback().mu().pushback(s.back)
            else:
                c = count(n//2 + 1)
                if k < c:
                    s = S(n//2 + 1, k, 1, depth+1)
                    return s.popback().mu().pushback(s.back)
                else:
                    s = S(n//2 + 1, k - c, 0, depth+1)
                    return s.popfront().mu().pushfront(1 - s.front)

    return S(n, k, starts).vals[0]


def A(n, mod=None):
    if n == 0:
        return 0

    l, r = 1, int(n**0.5) * 2
    Alen = None
    while l <= r:
        mid = (l + r) // 2
        if prefcount(mid) >= n:
            Alen = mid
            r = mid - 1
        else:
            l = mid + 1

    if mod is None:
        return int(S(Alen, n - prefcount(Alen - 1) - 1, 1), 2)
    return Smod(Alen, n - prefcount(Alen - 1) - 1, 1, mod)


if __name__ == '__main__':
    print(A(100))
    print(A(1000))
    print(sum(A(10**k, 10**9) for k in range(1, 19)) % 10**9)
