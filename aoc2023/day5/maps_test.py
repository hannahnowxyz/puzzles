import itertools as it

input = open('input.txt').readlines()
#lookups = (int(token) for token in input[0].split()[1:])
lookup_maps = [
    [[int(token) for token in mapping[:-1].split()]
        for mapping in sorted(group, key=lambda line: int(line.split()[1]))]
    for key, group in it.groupby(input[2:], key=lambda line: line[0].isnumeric())
    if key == True]
print('map 0 sorted by start of source range:\n' + str(lookup_maps[0]) + '\n')
lookup_maps2 = []
for lookup_map in lookup_maps:
    #(start index, effective offset)
    source_ranges = [(0, 0)]
    for i, mapping in enumerate(lookup_map):
        source_ranges.append((mapping[1], mapping[0] - mapping[1]))
        if i == len(lookup_map) - 1 or mapping[1] + mapping[2] < lookup_map[i + 1][1]:
            source_ranges.append((mapping[1] + mapping[2], 0))
    lookup_maps2.append(source_ranges)
print('map 0 source intervals and effective offsets:\n' + str(lookup_maps2[0]) + '\n')
