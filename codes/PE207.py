for tc in range(int(input())):
  a, b = map(int, input().split())

  n = 1
  while b * n >= a * ((1 << n + 1) - 2):
    n += 1

  res = (b * n - a * ((1 << n) - 1)) // a + 1 + (1 << n)
  print(res*res - res)
