N, K = map(int, input().split())
print("{:.10f}".format(N * (N-1) / (K*2), 10))