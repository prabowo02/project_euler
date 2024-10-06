import itertools
import math
import os
import pickle

R = 100000


# x^2 + y^2 = (x - a)^2 + (y + b)^2
# 2ax - 2yb = a^2 + b^2
# For lenticular holes of size a * b, find (x, y) s.t. circle with center origin containing (x, y) can satisfy it
def genr(a, b):
    if (a + b) % 2 != 0:
        return

    for y in itertools.count(-(a*a + b*b)//2 * pow(b, -1, a) % a, a):
        x, m = divmod(a*a + b*b + 2*y*b, 2*a)
        # assert m == 0
        yield x, y


# Get list of list of radiuses that can form lenticular holes.
# Two radiuses are in the same list if they can form the same hole size
def getRs():
    ls2 = []
    for a in range(1, 150, 2):
        for b in itertools.count(a, 2):
            if math.gcd(a, b) != 1:
                continue
            if next(genr(a, b))[0] > R:
                break

            ls = []
            for x, y in genr(a, b):
                h = x*x + y*y
                if h > R*R:
                    break

                if all((x-i)**2 + (y + (b*i + a-1)//a)**2 > h for i in range(1, a)):
                    ls.append(h)

            if ls:
                # print(a, b, len(ls))
                ls2.append(ls)

    return ls2


filename = f'PE295-{R}.pickle'
if os.path.isfile(filename):
    ls2 = pickle.load(open(filename, 'rb'))
else:
    ls2 = getRs()
    pickle.dump(ls2, open(filename, 'wb'))

# r2 contains numbers that appear in two lists of ls2
r, r2 = set(), set()
for ls in ls2:
    r2.update(set(ls).intersection(r))
    r.update(set(ls))

pairs = set()
ans = len(r)
for ls in ls2:
    ans += len(ls) * (len(ls) - 1) // 2
    ls = [n for n in ls if n in r2]

    # print(len(ls))

    for i in range(len(ls)):
        for j in range(i + 1, len(ls)):
            p = (ls[i], ls[j])
            if p not in pairs:
                pairs.add(p)
            else:
                ans -= 1

print(ans)
