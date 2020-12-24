s = 0
for tc in range(int(input())):
    a, b, c, d = map(int, input().split())
    s += (a * pow(b, c, 10**12) + d) % 10**12
    
s %= 10 ** 12
print('0' * (12 - len(str(s))), s, sep = '')
