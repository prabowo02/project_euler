import functools


def sumdig(n):
	return sum([int(c) for c in list(str(n))])


@functools.cache
def f(x, carry, diff):
	if x == 0:
		return diff + sumdig(carry) == 0

	ret = 0
	for i in range(10):
		d, m = divmod(i * 137 + carry, 10)
		ret += f(x - 1, d, diff + m - i)
	return ret


def brute(n):
	cnt = 0
	for i in range(10**n):
		if sumdig(137 * i) == sumdig(i):
			cnt += 1
	return cnt


if __name__ == '__main__':
	n = 18
	# n = int(input())
	# print(brute(n))
	print(f(n, 0, 0))
