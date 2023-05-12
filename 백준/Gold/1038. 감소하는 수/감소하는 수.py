import sys

input = sys.stdin.readline

N = int(input())

cnt = 0

decreasingNumber = []


def dfs(num):
    decreasingNumber.append(num)

    digit = num % 10

    for i in range(digit):
        nextNum = num * 10 + i
        dfs(nextNum)

for i in range(10):
    dfs(i)

decreasingNumber.sort()

if N>=len(decreasingNumber):
    print(-1)
else :
    print(decreasingNumber[N])