#https://adventofcode.com/2023/day/6

import math

#parse input
input = open('input.txt').readlines()
total_times = [int(token) for token in input[0].split()[1:]]
record_distances = [int(token) for token in input[1].split()[1:]]

#we have:
#   total_time = time_held + time_moving
#   speed = time_held
#   total_distance = speed*time_moving = time_held*(total_time - time_held)
#       = total_time*time_held - time_held^2
#therefore:
#   total_distance > record_distance iff.
#   total_time*time_held - time_held^2 > record_distance iff.
#   https://www.wolframalpha.com/input?i=Reduce%5Ba*x+-+x%5E2+%3E+b%2C+x%5D
#however, because of symmetry, we only need the exclusive lower bound
#   lower_bound = floor((total_time - sqrt(total_time^2 - 4*record_distance))/2)
#   so that num_ways = total_time - 2*lower_bound - 1

num_ways = lambda t, d: t - 2*int((t - math.sqrt(t**2 - 4*d))/2) - 1

product = math.prod(num_ways(t, d) for t, d in zip(total_times, record_distances))
print(product)

#part 2 changes nothing
big_time = int(''.join(input[0].split()[1:]))
big_dist = int(''.join(input[1].split()[1:]))
print(num_ways(big_time, big_dist))
