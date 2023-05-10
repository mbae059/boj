import bisect, sys
from collections import deque

input = sys.stdin.readline

N = int(input())

arr = list(enumerate(map(int, input().split())))

lis = []
dp = [1]*N

for i, value in arr:
    idx = bisect.bisect_left(lis, value)
    if idx==len(lis):
        lis.append(value)
        dp[i] = len(lis)
    else :
        lis[idx] = value
        dp[i] = idx+1
        
sz = max(dp)
print(sz)

stack = deque()
for i in range(N-1, -1, -1):
    if sz==dp[i]:
        stack.appendleft(arr[i][1])
        sz-=1

while stack:
    print(stack[0])
    stack.popleft()