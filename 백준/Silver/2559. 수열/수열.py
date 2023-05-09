import sys
input = sys.stdin.readline

N, K = map(int, input().split())

arr = list(map(int, input().split()))

dp = [0] * N

dp[0] = arr[0]

for i in range(1,K):
    dp[i] = dp[i-1] + arr[i]
l = 0
r = K

mx = dp[K-1]
for i in range(K, N):
    dp[i] = dp[i-1] + arr[r] - arr[l]
    r+=1
    l+=1
    mx = max(mx, dp[i])
    
print(mx)
