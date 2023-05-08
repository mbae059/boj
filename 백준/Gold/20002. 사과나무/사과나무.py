import sys
input = sys.stdin.readline

N = int(input())

matrix = [list(map(int, input().split())) for _ in range(N)]

dp = [[0] * 333 for _ in range(333)]

for i in range(1,N+1):
    for j in range(1,N+1):
        dp[i][j] = -dp[i-1][j-1] + dp[i-1][j] + dp[i][j-1] + matrix[i-1][j-1]

answer = dp[1][1]
for k in range(1,N+1):
    for i in range(1, N-k+2):
        for j in range(1, N-k+2):
            answer = max(answer, dp[i+k-1][j+k-1] - dp[i-1][j+k-1] - dp[i+k-1][j-1] + dp[i-1][j-1])
            
print(answer)