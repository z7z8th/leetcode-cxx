#!/usr/bin/python3

import sys
import random

if len(sys.argv) < 5:
	print('usage: %s n m k t', sys.argv[0])
	sys.exit(1)

n = int(sys.argv[1])
m = int(sys.argv[2])
k = int(sys.argv[3])
t = int(sys.argv[4])

print(n, m, k)

rand1 = random.SystemRandom()

for ki in range(k):
	x = rand1.randrange(0, n)
	y = rand1.randrange(0, m)
	c = rand1.randrange(0, 1000)
	print(x, y, c)

print(t)

for ti in range(t):
	op = rand1.randrange(0,3)
	a = rand1.randrange(0, n)
	b = rand1.randrange(0, m)
	print(op, a, b)
