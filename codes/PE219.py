for tc in range(int(input())):
    n, a, b = [int(i) for i in input().split()]

    ls = [0 for i in range(600)]
    ls[0] = 1

    cnt, sum = 1, 0
    for i in range(len(ls)):
        if cnt + ls[i] >= n:
            sum += (n - cnt) * (a + b + i)
            break
        
        sum += ls[i] * (a + b + i)
        cnt += ls[i]

        ls[i+a] += ls[i]
        ls[i+b] += ls[i]

    print(sum % 1000000007)
