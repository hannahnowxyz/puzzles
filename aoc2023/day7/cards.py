# https://adventofcode.com/2023/day/7

# interpret each hand string as a number in base 13,
# adding the hand's type as a leading digit that dominates the face values.
# then convert each hand to base 10 and sort.
# (basically, map every possible hand string to an integer in 0-2599050).
hands_bids = [line.split() for line in open('input.txt').readlines()]
faces = '23456789TJQKA'
face_count_strings = ['11111', '11122', '12222', '11333', '22333', '14444', '55555']
face_count_sums = [sum(int(c) for c in s) for s in face_count_strings]
base13 = {f: i for (i, f) in enumerate(faces)}
type_value_map = {fs: i for (i, fs) in enumerate(face_count_sums)}
evaluate_type = lambda h: type_value_map[sum(h.count(c) for c in h)]
evaluate_hand = lambda h: (
        evaluate_type(h)*(13**5)
        + sum(base13[h[-i-1]]*(13**i) for i in range(5))
    )
print(f"max hand value: {evaluate_hand('AAAAA')}")

# sort and compute puzzle solution.
hands_bids.sort(key=lambda hb: evaluate_hand(hb[0]))
print(sum((i+1)*int(hb[1]) for i, hb in enumerate(hands_bids)))
