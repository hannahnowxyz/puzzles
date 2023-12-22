#do you have the alphabet memorized as an array or as a linked list (alphabet song)?
#array memorizers drastically outperform at this task

import os
import random
import time
alphabet = sorted([l for l in "QWERTYUIOPASDFGHJKLZXCVBNM"])
num_attempts = 0
num_correct = 0
#clears terminal on both Windows and the nixes
os.system("cls||clear")
print("You will have 1 minute to complete as many trials as possible.")
print("At each trial you will be shown 2 different letters.")
print("Enter \"q\" if the left letter is first alphabetically, or \"w\" for the right.")
print("Each correct answer is worth 1 point.")
print("But, to disincentivize guessing, each incorrect answer is worth -1 point.")
input("Press Enter to continue...")
start_time = time.time()
while True:
	alph = alphabet.copy()
	random.shuffle(alph)
	left = alph.pop(0)
	right = alph[0]
	while True:
		os.system("cls||clear")
		print(left + "  |  " + right)
		ans = input()
		if ans == "q":
			if alphabet.index(left) < alphabet.index(right):
				num_attempts += 1
				num_correct += 1
			else: num_attempts += 1
			break
		elif ans == "w":
			if alphabet.index(left) > alphabet.index(right):
				num_attempts += 1
				num_correct += 1
			else: num_attempts += 1
			break
	if time.time() - start_time > 60: break
os.system("cls||clear")
print("TIME. YOUR SCORE: " + str(num_correct - (num_attempts - num_correct)))
print("Correct attempts: " + str(num_correct) + " of " + str(num_attempts) + " (" + str(int(100*num_correct/num_attempts)) + "% correct)")
