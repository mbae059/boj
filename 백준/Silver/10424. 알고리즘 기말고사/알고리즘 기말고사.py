import sys,heapq

input = sys.stdin.readline

N = int(input())

arr = list(map(int, input().split()))

mid = [0] * (N+1)
for i in range(N):
    mid[arr[i]] = i+1

for i in range(1,N+1):
    print(i-mid[i])