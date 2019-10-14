#!/usr/bin/python3

import sys
import random

if len(sys.argv) < 2:
	print('usage: %s n' % sys.argv[0])
	sys.exit(1)

n = int(sys.argv[1])
print('{ ', end='')
rand1 = random.SystemRandom()
for i in range(n):
	print(rand1.randrange(0, n), end=', ')
print(' } ')
