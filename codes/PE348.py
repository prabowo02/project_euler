import itertools

def solve():
    N = 10**9
    d = {}
    for i in range(1, N):
        if i**2 > N:
            break
        for j in range(1, N):
            num = i**2 + j**3
            if num > N:
                break
            if str(num) != str(num)[::-1]:
                continue

            d[num] = d.get(num, 0) + 1

    nums = [k for k, v in d.items() if v == 4]
    print(nums)
    return sum(sorted(nums)[:5])


if __name__ == '__main__':
    print(solve())
