#https://adventofcode.com/2023/day/4

#assign each card a multiplier for how many copies we have of it
input = [[1, line] for line in open('input.txt').readlines()]
num_cards = 0
for i, [multiplier, line] in enumerate(input):
    #extract numbers and hash as set, no need to parse to int
    data_part = line.split(':')[1]
    winning_nums = set(data_part.split('|')[0].split())
    win_count = 0
    for scratch_num in data_part.split('|')[1].split():
        win_count += scratch_num in winning_nums
    #add multiplier to next few cards,
    #because we win one copy of each for each winning copy of this card
    for j in range(win_count):
        input[min(i + j + 1, len(input) - 1)][0] += multiplier
    num_cards += multiplier
print(num_cards)
