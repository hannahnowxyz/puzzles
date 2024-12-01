import itertools as it

heavens = [line.strip() for line in open('input.txt').readlines()]
num_rows, num_cols = len(heavens), len(heavens[0])
empty_rows = [
    i for i in range(num_rows)
    if all(heavens[i][j] != '#' for j in range(num_cols))
]
empty_cols = [
    j for j in range(num_cols)
    if all(heavens[i][j] != '#' for i in range(num_rows))
]

def distance(a, b):
    min_row, max_row = min(a[0], b[0]), max(a[0], b[0])
    min_col, max_col = min(a[1], b[1]), max(a[1], b[1])
    delta_row = max_row - min_row + sum(min_row < r < max_row for r in empty_rows)
    delta_col = max_col - min_col + sum(min_col < c < max_col for c in empty_cols)
    return delta_row + delta_col

galaxies_pos = [
        (i, j)
        for i, j in it.product(range(num_rows), range(num_cols))
        if heavens[i][j] == '#'
]

grand_sum = 0
for a, b in it.combinations(galaxies_pos, 2):
    grand_sum += distance(a, b)

print(grand_sum)
