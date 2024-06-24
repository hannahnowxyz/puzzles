#https://adventofcode.com/2023/day/5

import math
import itertools as it

#the strategy in part2 is to reduce the number of required lookups.
#   each mapped range is linearly increasing,
#   so each map is effectively a piecewise linear function:
#       m(x) = {
#           start0 <= x < start1: x + offset0
#           start1 <= x < start2: x + offset1
#           start2 <= x < start3: x + offset2
#           ...
#       }
#   therefore, compose these functions such that M(x) = m6(m5(...m0(x)))
#   and use the composed map M(x) to get the critical points
#   at which "lookups" are required.

#parse input
input = open('input.txt').readlines()
lookup_maps = [
    [list(map(int, mapping.split()))
        for mapping in sorted(group, key=lambda line: int(line.split()[1]))]
    for key, group in it.groupby(input[2:], key=lambda line: line[0].isnumeric())
    if key == True]

#transform data:
#   a "map" will now be a list of "mappings", where a "mapping" is a 2-tuple
#       ex. (inclusive_start_index, effective_offset)
#   a mapping's end index is implicitly defined by the next mapping's start,
#   such that all integers >= 0 will be mapped (no gaps in the number line),
#   with extra zero-offset mappings being added where necessary to achieve this.
piecewise_linear_maps = []
for lookup_map in lookup_maps:
    piecewise_linear_map = [(0, 0)] if lookup_map[0][1] > 0 else []
    for mapping, next_mapping in zip(lookup_map, lookup_map[1:]):
        piecewise_linear_map.append((mapping[1], mapping[0] - mapping[1]))
        if mapping[1] + mapping[2] < next_mapping[1]:
            piecewise_linear_map.append((mapping[1] + mapping[2], 0))
    piecewise_linear_map.append((lookup_map[-1][1] + lookup_map[-1][2], 0))
    piecewise_linear_maps.append(piecewise_linear_map)

offset_at = lambda lookup_map, index: next(mapping for mapping in reversed(lookup_map) if index >= mapping[0])[1]

#compose all maps
def compose_maps(*maps):
    fully_composed = maps[0]
    def compose2(inner_map, outer_map):
        #as more maps are composed, the number of mappings can only increase,
        #   which occurs when an inner mapping codomain splits over multiple outer mapping domains
        added_starts = [
            outer_mapping[0] - inner_mapping[1]
            for outer_mapping in outer_map
            for inner_mapping, next_inner_mapping in zip(inner_map, inner_map[1:] + [(math.inf, 0)])
            if inner_mapping[0] < outer_mapping[0] - inner_mapping[1] < next_inner_mapping[0]]
        return [(start, offset_at(inner_map, start) + offset_at(outer_map, start + offset_at(inner_map, start)))
            for start in sorted([mapping[0] for mapping in inner_map] + added_starts)]
    for map in maps[1:]:
        fully_composed = compose2(fully_composed, map)
    return fully_composed

#check critical values
fully_composed_map = compose_maps(*piecewise_linear_maps)
minimum_distance = math.inf
for start, length in it.batched(map(int, input[0].split()[1:]), n=2):
    #each lookup range can itself be considered a map with all-zero offsets
    mappings_to_check = compose_maps([(0, math.inf), (start, 0), (start + length, math.inf)], fully_composed_map)
    #finally, apply M(x) to all critical points!
    #   but how to know which seed numbers are critical? since each lookup range is increasing,
    #   and all we're doing is adding an offset, only the start indices need to be considered.
    critical_values = map(sum, mappings_to_check)
    minimum_distance = min(minimum_distance, *critical_values)

print(minimum_distance)
