N = int(input())

init = N//255 * 255
mod = int(1e9+7)
answer = 0
if init%1023==0:
    answer = (answer * pow(2, init, mod)) % mod
else:
    answer = init

for i in range(init+1, N+1):
    answer = abs(answer-i)

    if i%3==0:
        answer = answer * i % mod
    if i%15==0:
        answer &= i
    if i%63==0:
        answer ^= i
    if i%255==0:
        answer |= i
    if i%1023==0:
        answer = answer * pow(2, i, mod) % mod
        
print(answer)