
import re

lines = open("conditions_dumped", "rt").read().splitlines()


new_lines = []
for i, line in enumerate(lines):
	if "Math.floor" in line:
		val = int(lines[i-1])
		new_lines.append(line.replace('Math.floor(Math.random() * 256)', str(val)))
		

	elif line.strip().lower().startswith('b'):
		new_lines.append(line)


with open("conditions_reparsed.py", "wt") as f:
	f.write('\n'.join(new_lines))
