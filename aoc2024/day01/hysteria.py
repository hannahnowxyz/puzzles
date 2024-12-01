lists_a_b = [line.split() for line in open('input.txt').readlines()]
list_a = sorted([int(row[0]) for row in lists_a_b])
list_b = sorted([int(row[1]) for row in lists_a_b])
total_distance = sum(abs(a - b) for a, b in zip(list_a, list_b))
print(total_distance)
