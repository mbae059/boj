import sys
input = sys.stdin.readline
N, M = map(int, input().split())

matrix = [input() for _ in range(N)]

dp = [[0]*(M+1) for _ in range(N+1)]

for i in range(N):
    dp[i][0] = 1

for j in range(M):
    dp[0][j] = 1

answer =0
for i in range(1,N):
    for j in range(1,M):
        dp[i][j] = 1
        if matrix[i-1][j-1]==matrix[i][j] and matrix[i-1][j]==matrix[i][j-1] and matrix[i][j]!=matrix[i-1][j]:
            dp[i][j] = min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]) + 1

for i in range(N):
    for j in range(M):
        answer += dp[i][j]
print(answer)