import sys

input = sys.stdin.readline

N, K = map(int, input().split())

coins = [0]
for _ in range(N):
    coins.append(int(input()))
coins.sort()

dp = [[0]*(K+1) for _ in range(N+1)]

for i in range(0,N+1):
    for j in range(1,K+1):
        dp[i][j] = 999999
    

for i in range(1,N+1):
    for j in range(1,K+1): 
        if j >= coins[i] :
            dp[i][j] = min(dp[i-1][j], dp[i][j-coins[i]]+1)
        else :
            dp[i][j] = dp[i-1][j]
if dp[N][K]==999999:
    print(-1)
else :
    print(dp[N][K])
