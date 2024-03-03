#https://adventofcode.com/2023/day/5

import math
import itertools as it

#notes about puzzle input:
#mapped indices do not overlap
#maps are given in convenient sequence
input = open('input.txt').readlines()
lookups = (int(token) for token in input[0].split()[1:])
lookup_maps = [
    list(group)
    for key, group in it.groupby(input[2:], key=lambda line: line[0].isnumeric())
    if key == True]
minimum_distance = math.inf
#just chain the lookups
#spiritually equivalent to 'locations = map6[map5[...map0[seeds]]]'
for lookup in lookups:
    current_source_index = lookup
    for lookup_map in lookup_maps:
        for mapping in lookup_map:
            tokens = [int(token) for token in mapping[:-1].split()]
            if tokens[1] <= current_source_index < tokens[1] + tokens[2]:
                current_source_index = tokens[0] + current_source_index - tokens[1]
                break
        print(f'seed {lookup}: mapped previous index to {current_source_index}')
    #current seed now mapped to location
    minimum_distance = min(minimum_distance, current_source_index)
print(f'minimum distance: {minimum_distance}')
