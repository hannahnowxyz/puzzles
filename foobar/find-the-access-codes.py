import random
import math
import timeit

def solution(l):
	#we can improve over brute force (triple-nested for loops, cubic time) by
	#keeping a list of how many previous elements divide the i-th element.
	#for example, if we find that l[20] divides l[24], and we know 3 previous
	#elements divided l[20], then we can conclude without additional checking
	#that l[24] must be the endpoint of 3 newly found triples.
	num_previous_divisors = [0]*len(l)
	#iterate through list in quadratic time
	num_triples = 0
	for i in range(len(l)):
		for j in range(i):
			if l[i]%l[j] == 0:
				num_previous_divisors[i] += 1
				num_triples += num_previous_divisors[j]
	return num_triples

def binary_search(arr, x):
	low = 0
	high = len(arr) - 1
	mid = 0
	while low <= high:
		mid = (high + low)//2
		if arr[mid][1] < x:
			low = mid + 1
		elif arr[mid][1] > x:
			high = mid - 1
		else:
			return mid
	return mid

#interestingly faster solution by exploiting finite size of list, but breaks on duplicates
#would be cool to fix
def solution_hmm(l):
	s = sorted([[i, l[i]] for i in range(len(l))], key = lambda e: e[1])
	startpoint_max_index = binary_search(s, s[-1][1]//4)
	endpoint_only_min_index = binary_search(s, s[-1][1]//2) + 1
	num_triples = 0
	dupes = []
	for i in range(startpoint_max_index + 1):
		for j in range(binary_search(s, 2*s[i][1]), endpoint_only_min_index):
			if s[j][0] > s[i][0] and s[j][1]%s[i][1] == 0:
				for k in range(binary_search(s, 2*s[j][1]), len(s)):
					if s[k][0] > s[j][0] and s[k][1]%s[j][1] == 0:
						#print("found " + str(l[i]) + ", " + str(l[j]) + ", " + str(l[k]))
						num_triples += 1
	return num_triples

test1 = [1, 2, 3, 4, 5, 6]
print(test1)
print(solution_hmm(test1))
print(solution(test1))
print()

test2 = [1, 1, 1]
print(test2)
print(solution_hmm(test2))
print(solution(test2))
print()

test3 = [1, 4, 9, 1, 9, 9]
print(test3)
print(solution_hmm(test3))
print(solution(test3))
print()

test4 = [1, 2]
print(test4)
print(solution_hmm(test4))
print(solution(test4))
print()

test5 = [1, 3]
print(test5)
print(solution_hmm(test5))
print(solution(test5))
print()

test6 = [1, 2, 3, 4, 5, 6, 7, 8, 9]
print(test6)
print(solution_hmm(test6))
print(solution(test6))
print()

"""
num_nonzero = 0
all_matching = True
solhmm_total_time = 0
sol_total_time = 0
num_tests = 100
num_time_tests_per_test = 5
max_observation = 5000 #actual value -1 bc range()
list_length = 500

for i in range(num_tests):
	testl = list(set(random.randint(1, max_observation) for j in range(list_length)))
	print(testl)
	testlshmm = solution_hmm(testl)
	solhmm_total_time += timeit.timeit(lambda: solution_hmm(testl), "gc.enable()", number = num_time_tests_per_test)/num_time_tests_per_test
	testls = solution(testl)
	sol_total_time += timeit.timeit(lambda: solution(testl), "gc.enable()", number = num_time_tests_per_test)/num_time_tests_per_test
	print(testlshmm)
	print(testls)
	print("matching: " + str(testlshmm == testls))
	print()
	if testlshmm > 0:
		num_nonzero += 1
	if testlshmm != testls:
		all_matching = False

print("num nonzero: " + str(num_nonzero) + " out of " + str(num_tests))
print("all matching: " + str(all_matching))
print("avg avg solution_hmm time (sec): " + str(solhmm_total_time/num_tests))
print("avg avg solution time (sec): " + str(sol_total_time/num_tests))
"""