#!/usr/bin/python3

import sys
import random

if len(sys.argv) < 3:
	print('usage: %s n k', sys.argv[0])
	sys.exit(1)

n = int(sys.argv[1])
k = int(sys.argv[2])

print(n, k)

max_ai = int(1e9)

rand1 = random.SystemRandom()
for x in range(n):
	ai = rand1.randrange(1, max_ai+1)
	print(ai, end=' ')
print()