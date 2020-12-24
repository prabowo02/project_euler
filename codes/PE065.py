num = 0; det = 1

n = int(input())

for i in range(n - 2, -1, -1):
    frac = 0
    if (i % 3 == 1): frac = 2 * (i // 3 + 1)
    else: frac = 1
        
    num += det * frac
    num, det = det, num

num += 2 * det

print(sum(list(map(int, list(str(num))))))
