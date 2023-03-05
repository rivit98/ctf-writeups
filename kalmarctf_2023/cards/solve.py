from collections import defaultdict
import pyshark

cap = pyshark.FileCapture('./cards.pcap')
ftps = defaultdict(dict)

latest_cwd = None

for c in cap:
	sid = int(c.tcp.stream)

	if hasattr(c, 'ftp'):
		if rarg := getattr(c.ftp, 'response_arg', None):
			if 'Entering Passive Mode' in rarg:
				toks = rarg.removesuffix(').').removeprefix('Entering Passive Mode (').split(',')
				port = int(toks[4]) * 256 + int(toks[5])
				ftps[sid]['port'] = port

			if 'Opening BINARY' in rarg:
				latest_cwd = sid

		if rcmd := getattr(c.ftp, 'request_command', None):
			if 'CWD' in rcmd:
				ftps[sid]['cwd'] = int(getattr(c.ftp, 'request_arg', None))

	if hasattr(c, 'tcp') and not hasattr(c, 'ftp'):
		if int(c.tcp.flags, 16) == 0x0018 and latest_cwd is not None:
			port = int(c.tcp.port)
			f = ftps[latest_cwd]
			if f.get('port') == port:
				ftps[latest_cwd]['data'] = int(c.tcp.payload, 16)


flag = []
for v in sorted(map(lambda d: (d.get('cwd'), chr(d.get('data', ord('?')))), ftps.values()), key=lambda t: t[0]):
	flag.append(v[1])

print(''.join(flag))
