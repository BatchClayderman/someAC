from sys import exit
from time import perf_counter
EXIT_SUCCESS = 0
EXIT_FAILURE = 1


def method1(maxDigit:int = 4) -> int:
	count = 9
	leftVectors = [[0] * (i * 9 + 1) for i in range(1, maxDigit + 1)] # vectors[count - 1][sum]
	rightVectors = [[0] * (i * 9 + 1) for i in range(1, maxDigit + 1)] # vectors[count - 1][sum]
	
	rightVectors[0][0] = 1
	for i in range(1, 10):
		leftVectors[0][i] = 1
		rightVectors[0][i] = 1
	
	for digit in range(1, maxDigit):
		rightVectors[digit][0] = 1
		for i in range(1, 10):
			rightVectors[digit][i] += rightVectors[digit - 1][i]
			for j in range(1, i + 1):
				leftVectors[digit][i] += rightVectors[digit - 1][i - j]
			rightVectors[digit][i] += leftVectors[digit][i]
			count += leftVectors[digit][i] * rightVectors[digit][i]
		for i in range(10, digit * 9 + 1):
			rightVectors[digit][i] += rightVectors[digit - 1][i]
			for j in range(1, 10):
				leftVectors[digit][i] += rightVectors[digit - 1][i - j]
			rightVectors[digit][i] += leftVectors[digit][i]
			count += leftVectors[digit][i] * rightVectors[digit][i]
		for i in range(digit * 9 + 1, (digit + 1) * 9 + 1):
			for j in range(i - digit * 9, 10):
				leftVectors[digit][i] += rightVectors[digit - 1][i - j]
			rightVectors[digit][i] += leftVectors[digit][i]
			count += leftVectors[digit][i] * rightVectors[digit][i]
	
	return count

def method2(maxDigit:int = 4) -> int:
	count = 9
	leftVector = [0] + [1] * 9 # vector[sum]
	rightVector = [1] * 10 # vector[sum]
	
	for digit in range(1, maxDigit):
		newLeftVector = [0] * ((digit + 1) * 9 + 1)
		newRightVector = [1] + [0] * ((digit + 1) * 9)
		for i in range(1, 10):
			newRightVector[i] += rightVector[i]
			for j in range(1, i + 1):
				newLeftVector[i] += rightVector[i - j]
			newRightVector[i] += newLeftVector[i]
			count += newLeftVector[i] * newRightVector[i]
		for i in range(10, digit * 9 + 1):
			newRightVector[i] += rightVector[i]
			for j in range(1, 10):
				newLeftVector[i] += rightVector[i - j]
			newRightVector[i] += newLeftVector[i]
			count += newLeftVector[i] * newRightVector[i]
		for i in range(digit * 9 + 1, (digit + 1) * 9 + 1):
			for j in range(i - digit * 9, 10):
				newLeftVector[i] += rightVector[i - j]
			newRightVector[i] += newLeftVector[i]
			count += newLeftVector[i] * newRightVector[i]
		leftVector, rightVector = newLeftVector, newRightVector
	
	return count

def method3(maxDigit:int = 4) -> int:
	count = 9
	leftVector = (0, ) + (1, ) * 9 # vector[sum]
	rightVector = (1, ) * 10 # vector[sum]
	
	for digit in range(1, maxDigit):
		cut2 = digit * 9 + 1
		cut1 = cut2 - 10
		leftVector = tuple(sum(leftVector[:i]) for i in range(1, 10)) + tuple(sum(leftVector[i:i + 10]) for i in range(cut1)) + tuple(sum(leftVector[i:]) for i in range(cut1, cut2))
		rightVector = tuple(sum(rightVector[:i]) for i in range(1, 10)) + tuple(sum(rightVector[i:i + 10]) for i in range(cut1)) + tuple(sum(rightVector[i:]) for i in range(cut1, cut2))
		for i in range(cut2 + 9):
			count += leftVector[i] * rightVector[i]
	
	return count

def baseline1() -> int:
	count = 9
	for i in range(1000, 10000):
		if i // 1000 + i % 1000 // 100 == i % 100 // 10 + i % 10:
			count += 1
	for i in range(100000, 1000000):
		if i // 100000 + i % 100000 // 10000 + i % 10000 // 1000 == i % 1000 // 100 + i % 100 // 10 + i % 10:
			count += 1
	for i in range(10000000, 100000000):
		if i // 10000000 + i % 10000000 // 1000000 + i % 1000000 // 100000 + i % 100000 // 10000 == i % 10000 // 1000 + i % 1000 // 100 + i % 100 // 10 + i % 10:
			count += 1
	return count

def baseline2() -> int:
	count = 9
	for i in range(1000, 10000):
		if i // 1000 + i // 100 % 10 == i // 10 % 10 + i % 10:
			count += 1
	for i in range(100000, 1000000):
		if i // 100000 + i // 10000 % 10 + i // 1000 % 10 == i // 100 % 10 + i // 10 % 10 + i % 10:
			count += 1
	for i in range(10000000, 100000000):
		if i // 10000000 + i // 1000000 % 10 + i // 100000 % 10 + i // 10000 % 10 == i // 1000 % 10 + i // 100 % 10 + i // 10 % 10 + i % 10:
			count += 1
	return count

def baseline3() -> int:
	count = 9
	for i in range(1000, 10000):
		vec = [int(j) for j in str(i)]
		if vec[0] + vec[1] == vec[2] + vec[3]:
			count += 1
	for i in range(100000, 1000000):
		vec = [int(j) for j in str(i)]
		if vec[0] + vec[1] + vec[2] == vec[3] + vec[4] + vec[5]:
			count += 1
	for i in range(10000000, 100000000):
		vec = [int(j) for j in str(i)]
		if vec[0] + vec[1] + vec[2] + vec[3] == vec[4] + vec[5] + vec[6] + vec[7]:
			count += 1
	return count

def baseline4() -> int:
	count = 9
	for i in range(1000, 10000):
		string = str(i)
		if int(string[0]) + int(string[1]) == int(string[2]) + int(string[3]):
			count += 1
	for i in range(100000, 1000000):
		string = str(i)
		if int(string[0]) + int(string[1]) + int(string[2]) == int(string[3]) + int(string[4]) + int(string[5]):
			count += 1
	for i in range(10000000, 100000000):
		string = str(i)
		if int(string[0]) + int(string[1]) + int(string[2]) + int(string[3]) == int(string[4]) + int(string[5]) + int(string[6]) + int(string[7]):
			count += 1
	return count

def baseline5() -> int:
	count = 9
	for i in range(1000, 10000):
		vec = [ord(j) for j in str(i)]
		if vec[0] + vec[1] == vec[2] + vec[3]:
			count += 1
	for i in range(100000, 1000000):
		vec = [ord(j) for j in str(i)]
		if vec[0] + vec[1] + vec[2] == vec[3] + vec[4] + vec[5]:
			count += 1
	for i in range(10000000, 100000000):
		vec = [ord(j) for j in str(i)]
		if vec[0] + vec[1] + vec[2] + vec[3] == vec[4] + vec[5] + vec[6] + vec[7]:
			count += 1
	return count

def baseline6() -> int:
	count = 9
	for i in range(1000, 10000):
		string = str(i)
		if ord(string[0]) + ord(string[1]) == ord(string[2]) + ord(string[3]):
			count += 1
	for i in range(100000, 1000000):
		string = str(i)
		if ord(string[0]) + ord(string[1]) + ord(string[2]) == ord(string[3]) + ord(string[4]) + ord(string[5]):
			count += 1
	for i in range(10000000, 100000000):
		string = str(i)
		if ord(string[0]) + ord(string[1]) + ord(string[2]) + ord(string[3]) == ord(string[4]) + ord(string[5]) + ord(string[6]) + ord(string[7]):
			count += 1
	return count

def main() -> int: # Calculate the number of natural numbers in 100000000 that have an even number of digits and the sum of the digits in the first half is equal to the sum of the digits in the second half. 
	proposedFunctions = (method1, method2, method3)
	for i, func in enumerate(proposedFunctions):
		startTime = perf_counter()
		result = func()
		endTime = perf_counter()
		print("The result of proposed Function {0} is {1}, which cost {2:.9f} second(s). ".format(i + 1, result, endTime - startTime))
	baselineFunctions = (baseline1, baseline2, baseline3, baseline4, baseline5, baseline6)
	for i, func in enumerate(baselineFunctions):
		startTime = perf_counter()
		result = func()
		endTime = perf_counter()
		print("The result of baseline Function {0} is {1}, which cost {2:.9f} second(s). ".format(i + 1, result, endTime - startTime))
	return EXIT_SUCCESS



if "__main__" == __name__:
	exit(main())
