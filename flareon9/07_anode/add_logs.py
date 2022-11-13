with open("code.js", "rt") as f:
	data = f.read().splitlines()

new_lines = []

case_started = False
for line in data:
	new_lines.append(line)

	if line.strip().startswith('b['):
		indent = line[0:line.index("b[")]
		new_lines.append(f'{indent}console.log(\"{line.strip().removesuffix(";")}\")')


with open("code2.js", "wt") as f:
	f.write('\n'.join(new_lines))