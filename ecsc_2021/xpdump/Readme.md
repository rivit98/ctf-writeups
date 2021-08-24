# European Cyber Security Challenge Eliminations 2021, xpdump, forensics

## Description
There is a secured material from some running PC. Check it out.

## Solution
We have file called `xpdump`. It is memory dump. Using volatility we check list of processes:

`python2 vol.py --profile WinXPSP3x86 pstree -f ../xpdump`
```
Name                                                  Pid   PPid   Thds   Hnds Time
-------------------------------------------------- ------ ------ ------ ------ ----
 0x80e93da0:System                                      4      0     51    153 1970-01-01 00:00:00 UTC+0000
. 0x80ccb8c8:smss.exe                                 344      4      3     19 2021-06-16 22:48:40 UTC+0000
.. 0x80de06e8:winlogon.exe                            428    344     21    456 2021-06-16 22:48:40 UTC+0000
... 0x80dbf9f8:lsass.exe                              484    428     25    351 2021-06-16 22:48:41 UTC+0000
... 0x80dc39a8:services.exe                           472    428     15    242 2021-06-16 22:48:41 UTC+0000
.... 0xffb5f2d0:svchost.exe                           748    472     80   1292 2021-06-16 22:48:42 UTC+0000
..... 0xffab26e8:wscntfy.exe                         1636    748      1     35 2021-06-16 22:48:45 UTC+0000
.... 0xffb6ca50:svchost.exe                           712    472     10    212 2021-06-16 22:48:42 UTC+0000
.... 0xffb8ac80:svchost.exe                           632    472     20    165 2021-06-16 22:48:41 UTC+0000
.... 0xffb59da0:svchost.exe                           808    472      5     59 2021-06-16 22:48:42 UTC+0000
.... 0xffb4f020:svchost.exe                           840    472     12    177 2021-06-16 22:48:42 UTC+0000
.... 0xffab2268:alg.exe                              1668    472      7     98 2021-06-16 22:48:45 UTC+0000
.... 0xffb24d10:spoolsv.exe                          1032    472     13    126 2021-06-16 22:48:43 UTC+0000
.. 0x80d00020:csrss.exe                               404    344     11    338 2021-06-16 22:48:40 UTC+0000
 0xffaffa20:explorer.exe                             1336   1312     15    336 2021-06-16 22:48:44 UTC+0000
. 0xffaa2468:ctfmon.exe                              1720   1336      1     74 2021-06-16 22:48:45 UTC+0000
. 0xffad9020:FLAG.EXE                                 156   1336      1      7 2021-06-16 22:49:21 UTC+0000
```
We see FLAG.EXE, so let's dump it using this command:
`python2 vol.py --profile WinXPSP3x86 procdump --pid 156 -f ../xpdump --dump-dir=dmp`
and open in IDA. Disassembled code is in [FLAG.c](./FLAG.C)
The logic is really simple, program is xoring two arrays and print output (flag), so it is enough to extract data and use python to do the job.

Flag: ecsc21{yo_dawg_live_VMz}
Solve script: [solve.py](./solve.py)
