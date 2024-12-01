lists_a_b = [line.split() for line in open('input.txt').readlines()]
list_a = [int(row[0]) for row in lists_a_b]
list_b = [int(row[1]) for row in lists_a_b]
freq_list_b = {b: 0 for b in list_b}
for val in list_b:
    freq_list_b[val] += 1
similarity = 0
for val in list_a:
    similarity += val*freq_list_b.get(val, 0)
print(similarity)
