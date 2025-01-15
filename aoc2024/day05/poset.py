#!/usr/bin/env python3

import itertools as it

rules, updates = [part.strip().split('\n') for part in open('input.txt').read().split('\n\n')]
rules = {pair for pair in [tuple(int(page) for page in rule.split('|')) for rule in rules]}
updates = [[int(page) for page in update.split(',')] for update in updates]

middle_sum = 0
for update in updates:
	if all(pair in rules for pair in it.combinations(update, 2)):
		middle_sum += update[len(update)//2]

print(middle_sum)
