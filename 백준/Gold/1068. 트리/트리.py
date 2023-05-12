import sys,heapq

input = sys.stdin.readline

N = int(input()) 
tree = list(enumerate(map(int, input().split())))
cut = int(input())
root = 0

edge =[[] for _ in range(N)]
for i, value in tree:
    if value==-1:
        root = i
    else :
        edge[value].append(i)

leafNode = 0
def dfs(num):
    global leafNode
    
    childNode = 0
    for next in edge[num]:
        if next==cut :
            continue
        dfs(next)
        childNode+=1
    if childNode==0:
        leafNode+=1

if root!=cut:
    dfs(root)
print(leafNode)