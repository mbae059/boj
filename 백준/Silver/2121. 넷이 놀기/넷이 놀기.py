import sys
input = sys.stdin.readline

N = int(input())

A, B = map(int, input().split())

points = [list(map(int, input().split())) for _ in range(N)]
points.sort(key=lambda x : (x[1], x[0]))

d = {}
for point in points:
    d[point[0], point[1]] = 1
    
count = 0
for point in points:
    a = point[0]+A, point[1]
    b = point[0], point[1] + B
    c = point[0]+A, point[1]+B
    
    if (a in d) and (b in d) and (c in d) :
        count+=1

print(count)