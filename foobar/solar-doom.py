"""
given the total available surface area of some solar panel material as an integer between 1 and 1000000 inclusive,
create the largest possible individual square solar panels of integer side length. write a function solution(area)
that returns the list of squares.
for example:
solution(12) = [9, 1, 1, 1]
solution(15324) = [15129, 169, 25, 1]
"""

import math

def solution(area):
	squares_list = []
	while math.sqrt(area) >= 1:
		next_square = int(math.sqrt(area))**2
		squares_list.append(next_square)
		area -= next_square
		print(next_square)
	return squares_list
