# For an ellipse with equation x^2 / a^2 + y^2 / b^2 = 1, it has this parametric equation:

# 1/r^2 = cos^2(t) / a^2 + sin^2(t) / b^2
# Using double angle identity, both the trigonometries function can be written as cos(2t):
# 1/r^2 = (a^2 + b^2) / 2a^2b^2 + (b^2 - a^2) / 2a^2b^2 cos(2t)

# So for a rotated ellipse by s, we simply set t = t - s

# So the intersection happens when cos(2t) = cos(2(t - s))
# which are t = s/2 and t = s/2 + pi/2

# Their distances:
# ab sqrt(2 / ((a^2 + b^2) +/- (b^2 - a^2) cos(s)))

# Now, our ellipse is specifically: x^2 / 4a^2 + y^2 / a^2 = 1
# So we have b = 2a sqrt(2 / (5 - 3 cos t)); c = 2a sqrt(2 / (5 + 3 cos t))

# 1/b^2 + 1/c^2 = 5 / 4a^2
# (2a/b)^2 + (2a/c)^2 = 5

# Parametrisation:
# u = 2p^2 - 2pq - 2q^2
# v = p^2 + 4pq - q^2
# w = p^2 + q^2$$
# ==> b = 2aw/u; c = 2aw/v
# For p > 3q > 0; gcd(p, q) = 1

import math

def C(N):
    stack = [(1, 1)]
    ret = 0
    
    while stack:
        k, q = stack.pop()
        p = 3*q + k
        
        u = 2*p**2 - 2*p*q - 2*q**2
        v = p**2 + 4*p*q - q**2

        if u * v > 16000 * N:
            continue
            
        w = p**2 + q**2
        a = math.lcm(u // math.gcd(u, w*2), v // math.gcd(v, w*2))

        ret += N // a

        stack.append((k + q, q))
        stack.append((k, k + q))

    return ret // 2

if __name__ == '__main__':
    print(C(1000))
    print(C(10000))
    print(C(1000000))
    print(C(10**17))
