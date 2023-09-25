from subprocess import Popen, PIPE, STDOUT


def check_char(c):
	p = Popen(['zoom_zoom_vision.exe'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
	stdout_data = p.communicate(input=c.encode())[0]
	
	data = stdout_data.decode().strip().split()

	try:
		num = data[2]
		return int(num)
	except:
		return None


letters = dict()

for i in range(0x20, 0x80):
	c = chr(i)
	v = check_char(c)
	if v is None:
		print(f"{c} not found")
	else: 
		print(f"{c} -> {v}")

	# letters[c] = v
	letters[v] = c

print(letters)


target = "1584 1776 1824 1584 1856 1632 1968 1664 768 1728 784 784 784 784 784 1520 1840 1664 784 784 784 784 784 784 816 816 816 816 816 816 1856 1856 1856 1856 1856 1520 784 1856 1952 1520 1584 688 688 528 2000 "

nums = target.strip().split(' ')
print(nums)
nums = list(map(int, nums))


for n in nums:
	print(letters[n], end='')
