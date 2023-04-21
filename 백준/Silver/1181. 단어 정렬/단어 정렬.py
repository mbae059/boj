T = int(input())

li = []

for _ in range(T) :
    str = input()
    li.append(str)

sli = set(li)
li = list(sli)
li.sort()
li.sort(key=len)

for str in li :
    print(str)