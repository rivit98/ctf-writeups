

to_translate = "gincgnmgznagc ngz n itnstyft naolr"

# seen = set()
# for c in to_translate:
# 	if c in seen:
# 		continue

# 	seen.add(c)
# 	print(f'\'{c}\': \'_\',')


t_d = {
	'g': 'o',
	'i': 'h',
	'n': ' ',
	'c': 'n',
	'm': 'y',
	'z': 'u',
	'a': 'f',
	' ': 't',
	't': 'e',
	's': 's',
	'y': 'c',
	'f': 'r',
	'o': 'l',
	'l': 'a',
	'r': 'g',
}
out = []
for c in to_translate:
	out.append(t_d[c])


print('ecsc21{' + ''.join(out) + '}')
