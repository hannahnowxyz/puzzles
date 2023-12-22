#strange math problem disguised as a coding challenge

import random

def solution(pegs):
	"""
	to calculate the first radius:
	let p(0), ..., p(N) be the sequence of pegs.
	let r(0), ..., r(N) be the sequence of solution radii.
	given any 1 radius, the others are fully determined by the relations
		r(1) + r(0) = p(1) - p(0)
		r(2) + r(1) = p(2) - p(1)
		...
		r(N) + r(N - 1) = p(N) - p(N - 1)
		since each gear must fit exactly with its neighbors.
	therefore, we can construct r(N) as a function of r(0) by the chain of substitutions
		r(1) = p(1) - p(0) - r(0)
		r(2) = p(2) - p(1) - r(1) = p(2) - p(1) - (p(1) - p(0) - r(0)) = p(2) - 2 p(1) + p(0) + r(0)
		...
		r(N) = p(N) - 2 p(N - 1) + ... - 2 (-1)^N p(1) + (-1)^N p(0) + (-1)^N r(0)
		and set r(N) = r(0)/2 to solve for r(0):
			r(0) = -2/(2 (-1)^N - 1) (p(N) + ... + (-1)^N p(0))
	the factor -2/(2 (-1)^N - 1) is either 2/3 if the number of pegs is even
	or -2 if it's odd. however, to avoid floating point math, we use an expression
	which evaluates to either 2 or -6 in the even and odd cases respectively,
	effectively calculating 3 times the first radius.
	"""
	l = len(pegs)
	alt_sum = sum((1 - 2*(i % 2))*pegs[l - i - 1] for i in range(l))
	first_radius_x3 = (2 - 8*(l % 2))*(2*alt_sum - pegs[l - 1] - (-1 + 2*(l % 2))*pegs[0])
	#verify that solution exists
	if first_radius_x3 < 3:
		return [-1, -1]
	last_radius = first_radius_x3
	for i in range(l - 1):
		next_radius = 3*(pegs[i + 1]  - pegs[i]) - last_radius
		if next_radius < 3:
			return [-1, -1]
		last_radius = next_radius
	#solution exists, denominator 1 or 3?
	if first_radius_x3 % 3 == 0:
		return [int(first_radius_x3/3), 1]
	return [first_radius_x3, 3]
