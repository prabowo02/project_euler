B = int(input())
bound = 10 ** 100

ans = []
for i in range(2, 10**len(str(B)) * 30):
    num = i
    while (num < bound):
        s = 0
        tmp = num
        cnt = 0
        while (tmp): 
            s += tmp % B
            tmp //= B
            cnt += 1
        
        if (cnt > 1) and (s == i):
            ans.append(num)
        num *= i
        
for num in sorted(ans): print(num, end = " ")
