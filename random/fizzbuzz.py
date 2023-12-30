"""
print a string for integers 1 to n, where the string is:
(1) "Fizz" if the integer is divisible by 3 but not 5
(2) "Buzz" if the integer is divisible by 5 but not 3
(3) "FizzBuzz" if the integer is divisible by 3 and 5
(4) the integer itself if not divisible by either 3 or 5
"""

#normie solution
def fizzbuzz_branchy(n):
	for i in range(1, n + 1):
		if i % 3 == 0:
			if i % 5 == 0:
				print("FizzBuzz")
			else:
				print("Fizz")
		elif i % 5 == 0:
			print("Buzz")
		else:
			print(i)

#one-liner with conditional expressions, "FizzBuzz" case automatically handled by "Fizz" and "Buzz" cases
def fizzbuzz_conditionals(n):
	for i in range(1, n + 1):
		print(("Fizz" if i % 3 == 0 else "") + ("Buzz" if i % 5 == 0 else "") + (str(i) if not (i % 3 == 0 or i % 5 == 0) else ""))

#branchless by using pointer-like behavior to make sequence periodic in LCM(3, 5) = 15
def fizzbuzz_branchless(n):
	current_int_ref = [0]
	index_map = [["FizzBuzz"], current_int_ref, current_int_ref, ["Fizz"], current_int_ref,
				["Buzz"], ["Fizz"], current_int_ref, current_int_ref, ["Fizz"],
				["Buzz"], current_int_ref, ["Fizz"], current_int_ref, current_int_ref]
	for i in range(1, n + 1):
		current_int_ref[0] += 1
		print(index_map[i % 15][0])

fizzbuzz_branchless(100)
