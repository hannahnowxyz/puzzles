#!/usr/bin/env python3

import itertools as it
import graphlib as grl

rules, updates = [part.strip().split('\n') for part in open('input.txt').read().split('\n\n')]
rules = {pair for pair in [tuple(int(page) for page in rule.split('|')) for rule in rules]}
updates = [[int(page) for page in update.split(',')] for update in updates]
relevant_pages = {page for page in it.chain.from_iterable(list(rules) + updates)}

middle_sum = 0
for update in updates:
	if not all(pair in rules for pair in it.combinations(update, 2)):
		relevant_rules = rules & set(it.product(update, relevant_pages))
		da_graph = {}
		for rule in relevant_rules:
			da_graph.setdefault(rule[0], []).append(rule[1])
		topo_sorted = [page for page in grl.TopologicalSorter(da_graph).static_order() if page in update]
		middle_sum += topo_sorted[len(topo_sorted)//2]

print(middle_sum)
