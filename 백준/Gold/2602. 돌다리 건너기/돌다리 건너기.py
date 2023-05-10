import sys

input = sys.stdin.readline
str = input()
s1 = input()
s2 = input()

dp = [[[0]*2 for _ in range(len(str))] for _ in range(len(s1))]

for i in range(len(s1)):
    if s1[i]==str[0]:
        dp[i][0][0] = 1
        
    if s2[i]==str[0]:
        dp[i][0][1] = 1


for i in range(len(s1)):
    for j in range(len(str)):
        if s1[i]==str[j]:
            for k in range(i):
                dp[i][j][0] += dp[k][j-1][1]
        
        if s2[i]==str[j]:
            for k in range(i):
                dp[i][j][1] += dp[k][j-1][0]

sum = 0
for i in range(len(s1)):
    sum += dp[i][len(str)-1][0]
    sum += dp[i][len(str)-1][1]

print(sum)


        
