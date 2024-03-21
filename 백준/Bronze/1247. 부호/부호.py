T = 3
for _ in range(T):
    N = int(input())
    sum = 0
    for __ in range(N):
        x = int(input())
        sum += x
    if sum==0:
        print(0)
    elif sum>0:
        print('+')
    else:
        print('-')