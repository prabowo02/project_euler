d = {"I": 1, "V": 5, "X": 10, "L": 50, "C": 100, "D": 500, "M": 1000}

t = int(input())
for tc in range(t):
    s = input()
    num = 0
    for key in d:
        num += s.count(key) * d[key]
        
    ans = ""
    
    ans += num // 1000 * "M"; num %= 1000
    ans += num // 900 * "CM"; num %= 900
    ans += num // 500 * "D"; num %= 500
    ans += num // 400 * "CD"; num %= 400
    ans += num // 100 * "C"; num %= 100
    ans += num // 90 * "XC"; num %= 90
    ans += num // 50 * "L"; num %= 50
    ans += num // 40 * "XL"; num %= 40
    ans += num // 10 * "X"; num %= 10
    ans += num // 9 * "IX"; num %= 9
    ans += num // 5 * "V"; num %= 5
    ans += num // 4 * "IV"; num %= 4
    ans += num // 1 * "I"; num %= 1
    
    print(ans)
