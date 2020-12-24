n = int(input())

a, b = 2, 1
for i in range(n):
    a, b = 2 * a + b, a
    if (len(str(a - b)) > len(str(b))): print(i+1)
