Heard there's RC6 somewhere, is that true?

injects SC into explorer.exe


getmodulehandle self
createnamedpipe \\.\pipe\whereami
mutex named "welcome_main"


rc4 bytes - 0x67, 0xC6, 0x8F, 0x1E, 0xDA, 0xAD, 0x12, 0x60



bp:

eip >= 0x0720000 && eip <= 0x07f0000

0x{p:cip} {i:cip}



second_stage entrypoint:
0x18BD

call sth with pipe - stack [second_stage base addr, 1, first stage addr (ret?)]

(02D11293)


first handler - 0x05D 2420



debug012:00B61291 call    esi


bp on:
debug012:00B60511 call    [ebp+var_4]


https://github.com/stephenfewer/ReflectiveDLLInjection/
