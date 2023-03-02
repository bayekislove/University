#!/usr/bin/env python

print("VSZ   " + str(sum(int(line.split()[2]) for line in open('z5.txt', 'r').readlines()[1:])))
print("RSS   " + str(sum(int(line.split()[1]) for line in open('z5.txt', 'r').readlines()[1:])))