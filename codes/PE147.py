def f(n, m):
  return (n-1)*n*(2*n**4 + 4*n**3 - n**2 - 11*n - 8) // 60 + \
    n*(n+1)*(5*m**2 * (2*n**2 + 2*n - 1) - m*(8*n**3 + 2*n**2 - 12*n + 17) + 10*(n-1)) // 60
    
def g(n, m):
  return (n+2)*(n+1)*n*(m+2)*(m+1)*m // 36
  
for tc in range(int(input())):
  n, m = map(int, input().split())
  if n > m: n, m = m, n
  
  print(g(n, m) % 1000000007, f(n, m) % 1000000007)
