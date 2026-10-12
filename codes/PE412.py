def LC(M, N, mod=76543217):
    ans = 1
    for i in range(M-N):
        for j in range(M):
            ans = ans * ((M-i + M-j - 1) if j < M - N else (M-N-i + M-j - 1)**2) % mod
    ans = pow(ans, -1, mod)
    for i in range(M*M - N*N):
        ans = ans * (i + 1) % mod
    return ans


if __name__ == '__main__':
    print(LC(3, 0))
    print(LC(5, 3))
    print(LC(6, 3, 10**12 + 39))
    print(LC(10000, 5000))
