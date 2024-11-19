# https://adventofcode.com/2023/day/8

import math

# with periodic instructions over finite nodes, each path must end in a cycle:
instructions, _, *tokenized_node_strings = [line.split() for line in open('input.txt').readlines()]
N = len(instructions[0])
left_right = [c == 'R' for c in instructions[0]]
network = {s[0]: (s[2][1:-1], s[3][:-1]) for s in tokenized_node_strings}
cycle_lengths = []
for start_node in filter(lambda n: n[2] == 'A', network):
    already_seen = {}
    path_length = 0
    current_node = start_node
    # cycle found when arriving at a previously seen node at the same instruction state
    while not already_seen.get(current_node, math.inf) % N == path_length % N:
        already_seen[current_node] = path_length
        current_node = network[current_node][left_right[path_length % N]]
        path_length += 1
    # the "prelude length" is the pre-cycle path length
    prelude_length = already_seen[current_node]
    cycle_length = path_length - already_seen[current_node]
    print(f'found cycle [{start_node} -> {current_node} -> ... -> {current_node}] '
          f'of length {cycle_length}:\n'
          f'prelude length = {prelude_length}, cycle length % N = {cycle_length % N}')
    cycle_lengths.append(cycle_length)

# luckily*******, the cycles are particularly nice:
# (1) each path ends in a cycle of unique length, so each cycle must be unique too.
# (2) with equal numbers of start and end nodes,
#     each cycle must contain exactly 1 unique end node (else no solution).
# (3) each cycle starts on an end node.
# (4) the length of each cycle is equal to its prelude length,
#     so that computationally, each cycle might as well start at the start node.
# (5) the length of each cycle divides the length of the instructions.
# under these specially formulated conditions,
# the puzzle answer is just the LCM of the cycle lengths.
print(math.lcm(*cycle_lengths))
