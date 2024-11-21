# https://adventofcode.com/2023/day/9

import itertools as it

histories = [[int(t) for t in line.split()] for line in open('input.txt').readlines()]
grand_sum = 0
for history in histories:
    for i in reversed(range(len(history))):
        history[:i] = [b - a for a, b in it.pairwise(history[:i+1])]
    grand_sum += sum(history)
print(grand_sum)
