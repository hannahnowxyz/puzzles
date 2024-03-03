#https://adventofcode.com/2023/day/4

input = open('input.txt').readlines()
win_sum = 0
for line in input:
    #extract numbers and hash as set, no need to parse to int
    data_part = line.split(':')[1]
    winning_nums = set(data_part.split('|')[0].split())
    pow2 = -1
    for scratch_num in data_part.split('|')[1].split():
        pow2 += scratch_num in winning_nums
    #if no scratch numbers win, this adds int(0.5) = 0
    win_sum += int(2**pow2)
print(win_sum)
