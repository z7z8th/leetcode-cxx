#!/usr/bin/python3

import sys
import random

if len(sys.argv) < 3:
	print('usage: %s n x', sys.argv[0])
	sys.exit(1)

n = int(sys.argv[1])
x = int(sys.argv[2])
print(n, x)
rand1 = random.SystemRandom()
for i in range(n):
	print(rand1.randrange(1, 100+1), end=' ')
print()
