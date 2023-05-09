import sys
input = sys.stdin.readline

N = int(input())

dp = [[0]*2 for _ in range(99)]

dp[1][1] = 1

for i in range(2,N+1):
    dp[i][0] = dp[i-1][0] + dp[i-1][1]
    dp[i][1] = dp[i-1][0]

sum = dp[N][0] + dp[N][1]

print(sum)