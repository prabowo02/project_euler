MOD = 10**9


def find_cycle(num, mul, k):
    seq, vis, cyc_st = [], dict(), -1

    while True:
        if num in vis:
            cyc_st = vis[num]
            break

        vis[num] = len(seq)
        seq.append(num)
        num = num * mul % k

    return seq, cyc_st


def find_residue_count(n, k):
    counter = [0 for i in range(k)]
    d, m = divmod(n, k)
    for i in range(k):
        seq, cyc_st = find_cycle(pow(i+1, i+1, k), pow(i+1, k, k), k)
        for i in range(cyc_st):
            counter[seq[i]] += 1

        cyc_len, elem_cnt = len(seq) - cyc_st, d + (1 if i < m else 0) - cyc_st
        for i in range(cyc_st, len(seq)):
            counter[seq[i]] += elem_cnt//cyc_len + (1 if i-cyc_st < elem_cnt%cyc_len else 0)

    return counter


def multiply(dp1, dp2):
    n = len(dp1)
    ret = [0 for i in range(n+n)]
    for i in range(n):
        for j in range(n):
            ret[i+j] += dp1[i] * dp2[j]

    return [(ret[i] + ret[i+n]) % MOD for i in range(n)]


def power(dp, k):
    n = len(dp)
    ret = [0 for i in range(n)]
    ret[0] = 1
    while k:
        if k & 1:
            ret = multiply(ret, dp)
        dp = multiply(dp, dp)
        k >>= 1
    return ret


def generating_function(residue_counter):
    k = len(residue_counter)
    minimum_nonzero = min([r for r in residue_counter if r > 0])
    gf = [0 for i in range(k)]
    gf[0] = 1

    for i in range(k):
        if residue_counter[i] == 0:
            continue

        residue_counter[i] -= minimum_nonzero

        mul = [0 for i in range(k)]
        mul[0] = mul[i] = 1

        gf = multiply(gf, mul)

    return power(gf, minimum_nonzero)


def solve(n, k):
    residue_counter = find_residue_count(n, k)
    dp = [0 for i in range(k)]
    dp[0] = pow(2, residue_counter[0], MOD)
    residue_counter[0] = 0

    while any(residue_counter):
        dp = multiply(dp, generating_function(residue_counter))

    return (dp[0] - 1) % MOD


if __name__ == '__main__':
    n, k = [int(s) for s in input().split()]
    print(solve(n, k))
