# 1 2 3 4 5 6 7 8 910 1 2 3 4 5 6 7 8 920 1 2 3 4 5 6 7 8  9 30 
# 1 2 2 3 3 4 4 4 5 5 5 6 6 6 6 7 7 7 7 8 8 8 8 9 9 9 9 9 10 10 10 10 10 11 11 11 11 11 

def solve(N):
    groups = [(2, 3)]

    idx = 0
    g = 4
    total = 11
    lastG = 5

    ans = 1 + 4 # G(1) + G(2)
    queries = [n**3 for n in range(3, N)]
    qidx = 0

    while total < queries[-1]:
        for _ in range(groups[idx][0]):
            groups.append((groups[idx][1], g))
            total += groups[idx][1] * g
            lastG += groups[idx][1]

            while qidx < len(queries) and queries[qidx] <= total:
                ans += lastG - (total - queries[qidx]) // g
                qidx += 1

            g += 1

        idx += 1

    return ans

if __name__ == '__main__':
    print(solve(1000))
    print(solve(10**6))
