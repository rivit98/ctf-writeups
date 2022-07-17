label_0000:
	// Inputs[1] { @0007  msg.data.length }
	0000    60  PUSH1 0x80
	0002    60  PUSH1 0x40
	0004    52  MSTORE
	0005    60  PUSH1 0x04
	0007    36  CALLDATASIZE
	0008    10  LT
	0009    61  PUSH2 0x004c
	000C    57  *JUMPI
	// Stack delta = +0
	// Outputs[1] { @0004  memory[0x40:0x60] = 0x80 }
	// Block ends with conditional jump to 0x004c, if msg.data.length < 0x04

label_000D:
	// Incoming jump from 0x000C, if not msg.data.length < 0x04
	// Inputs[1] { @000F  msg.data[0x00:0x20] }
	000D    60  PUSH1 0x00
	000F    35  CALLDATALOAD
	0010    7C  PUSH29 0x0100000000000000000000000000000000000000000000000000000000
	002E    90  SWAP1
	002F    04  DIV
	0030    63  PUSH4 0xffffffff
	0035    16  AND
	0036    80  DUP1
	0037    63  PUSH4 0x4b64e492
	003C    14  EQ
	003D    61  PUSH2 0x0051
	0040    57  *JUMPI
	// Stack delta = +1
	// Outputs[1] { @0035  stack[0] = 0xffffffff & msg.data[0x00:0x20] / 0x0100000000000000000000000000000000000000000000000000000000 }
	// Block ends with conditional jump to 0x0051, if 0x4b64e492 == 0xffffffff & msg.data[0x00:0x20] / 0x0100000000000000000000000000000000000000000000000000000000

label_0041:
	// Incoming jump from 0x0040, if not 0x4b64e492 == 0xffffffff & msg.data[0x00:0x20] / 0x0100000000000000000000000000000000000000000000000000000000
	// Inputs[1] { @0041  stack[-1] }
	0041    80  DUP1
	0042    63  PUSH4 0x80e10aa5
	0047    14  EQ
	0048    61  PUSH2 0x0094
	004B    57  *JUMPI
	// Stack delta = +0
	// Block ends with conditional jump to 0x0094, if 0x80e10aa5 == stack[-1]

label_004C:
	// Incoming jump from 0x004B, if not 0x80e10aa5 == stack[-1]
	// Incoming jump from 0x000C, if msg.data.length < 0x04
	// Inputs[1] { @0050  memory[0x00:0x00] }
	004C    5B  JUMPDEST
	004D    60  PUSH1 0x00
	004F    80  DUP1
	0050    FD  *REVERT
	// Stack delta = +0
	// Outputs[1] { @0050  revert(memory[0x00:0x00]); }
	// Block terminates

label_0051:
	// Incoming jump from 0x0040, if 0x4b64e492 == 0xffffffff & msg.data[0x00:0x20] / 0x0100000000000000000000000000000000000000000000000000000000
	// Inputs[1] { @0052  msg.value }
	0051    5B  JUMPDEST
	0052    34  CALLVALUE
	0053    80  DUP1
	0054    15  ISZERO
	0055    61  PUSH2 0x005d
	0058    57  *JUMPI
	// Stack delta = +1
	// Outputs[1] { @0052  stack[0] = msg.value }
	// Block ends with conditional jump to 0x005d, if !msg.value

label_0059:
	// Incoming jump from 0x0058, if not !msg.value
	// Inputs[1] { @005C  memory[0x00:0x00] }
	0059    60  PUSH1 0x00
	005B    80  DUP1
	005C    FD  *REVERT
	// Stack delta = +0
	// Outputs[1] { @005C  revert(memory[0x00:0x00]); }
	// Block terminates

label_005D:
	// Incoming jump from 0x0058, if !msg.value
	// Inputs[2]
	// {
	//     @0065  msg.data.length
	//     @006C  msg.data[0x04:0x24]
	// }
	005D    5B  JUMPDEST
	005E    50  POP
	005F    61  PUSH2 0x0092
	0062    60  PUSH1 0x04
	0064    80  DUP1
	0065    36  CALLDATASIZE
	0066    03  SUB
	0067    81  DUP2
	0068    01  ADD
	0069    90  SWAP1
	006A    80  DUP1
	006B    80  DUP1
	006C    35  CALLDATALOAD
	006D    73  PUSH20 0xffffffffffffffffffffffffffffffffffffffff
	0082    16  AND
	0083    90  SWAP1
	0084    60  PUSH1 0x20
	0086    01  ADD
	0087    90  SWAP1
	0088    92  SWAP3
	0089    91  SWAP2
	008A    90  SWAP1
	008B    50  POP
	008C    50  POP
	008D    50  POP
	008E    61  PUSH2 0x00ab
	0091    56  *JUMP
	// Stack delta = +1
	// Outputs[2]
	// {
	//     @005F  stack[-1] = 0x0092
	//     @0088  stack[0] = 0xffffffffffffffffffffffffffffffffffffffff & msg.data[0x04:0x24]
	// }
	// Block ends with unconditional jump to 0x00ab

	0092    5B    JUMPDEST
	0093    00    *STOP
label_0094:
	// Incoming jump from 0x004B, if 0x80e10aa5 == stack[-1]
	// Inputs[1] { @0095  msg.value }
	0094    5B  JUMPDEST
	0095    34  CALLVALUE
	0096    80  DUP1
	0097    15  ISZERO
	0098    61  PUSH2 0x00a0
	009B    57  *JUMPI
	// Stack delta = +1
	// Outputs[1] { @0095  stack[0] = msg.value }
	// Block ends with conditional jump to 0x00a0, if !msg.value

label_009C:
	// Incoming jump from 0x009B, if not !msg.value
	// Inputs[1] { @009F  memory[0x00:0x00] }
	009C    60  PUSH1 0x00
	009E    80  DUP1
	009F    FD  *REVERT
	// Stack delta = +0
	// Outputs[1] { @009F  revert(memory[0x00:0x00]); }
	// Block terminates

label_00A0:
	// Incoming jump from 0x009B, if !msg.value
	00A0    5B  JUMPDEST
	00A1    50  POP
	00A2    61  PUSH2 0x00a9
	00A5    61  PUSH2 0x02e4
	00A8    56  *JUMP
	// Stack delta = +0
	// Outputs[1] { @00A2  stack[-1] = 0x00a9 }
	// Block ends with call to 0x02e4, returns to 0x00A9

label_00A9:
	// Incoming return from call to 0x02E4 at 0x00A8
	00A9    5B  JUMPDEST
	00AA    00  *STOP
	// Stack delta = +0
	// Outputs[1] { @00AA  stop(); }
	// Block terminates

label_00AB:
	// Incoming jump from 0x0091
	00AB    5B  JUMPDEST
	00AC    60  PUSH1 0x00
	00AE    80  DUP1
	00AF    61  PUSH2 0x00b6
	00B2    61  PUSH2 0x0502
	00B5    56  *JUMP
	// Stack delta = +3
	// Outputs[3]
	// {
	//     @00AC  stack[0] = 0x00
	//     @00AE  stack[1] = 0x00
	//     @00AF  stack[2] = 0x00b6
	// }
	// Block ends with call to 0x0502, returns to 0x00B6

label_00B6:
	// Incoming return from call to 0x0502 at 0x00B5
	// Inputs[3]
	// {
	//     @00B7  address(this)
	//     @00CE  address(0xffffffffffffffffffffffffffffffffffffffff & address(this)).balance
	//     @00D2  stack[-4]
	// }
	00B6    5B  JUMPDEST
	00B7    30  ADDRESS
	00B8    73  PUSH20 0xffffffffffffffffffffffffffffffffffffffff
	00CD    16  AND
	00CE    31  BALANCE
	00CF    61  PUSH2 0x0fff
	00D2    85  DUP6
	00D3    73  PUSH20 0xffffffffffffffffffffffffffffffffffffffff
	00E8    16  AND
	00E9    16  AND
	00EA    14  EQ
	00EB    15  ISZERO
	00EC    15  ISZERO
	00ED    61  PUSH2 0x00f5
	00F0    57  *JUMPI
	// Stack delta = +0
	// Block ends with conditional jump to 0x00f5, if !!(0xffffffffffffffffffffffffffffffffffffffff & stack[-4] & 0x0fff == address(0xffffffffffffffffffffffffffffffffffffffff & address(this)).balance)

label_00F1:
	// Incoming jump from 0x00F0, if not !!(0xffffffffffffffffffffffffffffffffffffffff & stack[-4] & 0x0fff == address(0xffffffffffffffffffffffffffffffffffffffff & address(this)).balance)
	// Inputs[1] { @00F4  memory[0x00:0x00] }
	00F1    60  PUSH1 0x00
	00F3    80  DUP1
	00F4    FD  *REVERT
	// Stack delta = +0
	// Outputs[1] { @00F4  revert(memory[0x00:0x00]); }
	// Block terminates

label_00F5:
	// Incoming jump from 0x00F0, if !!(0xffffffffffffffffffffffffffffffffffffffff & stack[-4] & 0x0fff == address(0xffffffffffffffffffffffffffffffffffffffff & address(this)).balance)
	// Inputs[6]
	// {
	//     @00FA  stack[-4]
	//     @0137  memory[0x40:0x60]
	//     @013D  memory[0x40:0x60]
	//     @016F  memory[memory[0x40:0x60] + 0x20:memory[0x40:0x60] + 0x20 + 0x20]
	//     @019A  memory[0x40:0x60]
	//     @019E  memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20]
	// }
	00F5    5B  JUMPDEST
	00F6    60  PUSH1 0x00
	00F8    15  ISZERO
	00F9    15  ISZERO
	00FA    84  DUP5
	00FB    73  PUSH20 0xffffffffffffffffffffffffffffffffffffffff
	0110    16  AND
	0111    63  PUSH4 0x4b64e492
	0116    7C  PUSH29 0x0100000000000000000000000000000000000000000000000000000000
	0134    02  MUL
	0135    60  PUSH1 0x40
	0137    51  MLOAD
	0138    60  PUSH1 0x24
	013A    01  ADD
	013B    60  PUSH1 0x40
	013D    51  MLOAD
	013E    60  PUSH1 0x20
	0140    81  DUP2
	0141    83  DUP4
	0142    03  SUB
	0143    03  SUB
	0144    81  DUP2
	0145    52  MSTORE
	0146    90  SWAP1
	0147    60  PUSH1 0x40
	0149    52  MSTORE
	014A    90  SWAP1
	014B    7B  PUSH28 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffff
	0168    19  NOT
	0169    16  AND
	016A    60  PUSH1 0x20
	016C    82  DUP3
	016D    01  ADD
	016E    80  DUP1
	016F    51  MLOAD
	0170    7B  PUSH28 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffff
	018D    83  DUP4
	018E    81  DUP2
	018F    83  DUP4
	0190    16  AND
	0191    17  OR
	0192    83  DUP4
	0193    52  MSTORE
	0194    50  POP
	0195    50  POP
	0196    50  POP
	0197    50  POP
	0198    60  PUSH1 0x40
	019A    51  MLOAD
	019B    80  DUP1
	019C    82  DUP3
	019D    80  DUP1
	019E    51  MLOAD
	019F    90  SWAP1
	01A0    60  PUSH1 0x20
	01A2    01  ADD
	01A3    90  SWAP1
	01A4    80  DUP1
	01A5    83  DUP4
	01A6    83  DUP4
	01A7    60  PUSH1 0x00
	01A9    5B  JUMPDEST
	01AA    83  DUP4
	01AB    81  DUP2
	01AC    10  LT
	01AD    15  ISZERO
	01AE    61  PUSH2 0x01c4
	01B1    57  *JUMPI
	// Stack delta = +11
	// Outputs[14]
	// {
	//     @00F9  stack[0] = !!0x00
	//     @0110  stack[1] = 0xffffffffffffffffffffffffffffffffffffffff & stack[-4]
	//     @0145  memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20] = (0x24 + memory[0x40:0x60]) - memory[0x40:0x60] - 0x20
	//     @0149  memory[0x40:0x60] = 0x24 + memory[0x40:0x60]
	//     @014A  stack[2] = memory[0x40:0x60]
	//     @0193  memory[memory[0x40:0x60] + 0x20:memory[0x40:0x60] + 0x20 + 0x20] = (memory[memory[0x40:0x60] + 0x20:memory[0x40:0x60] + 0x20 + 0x20] & 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffff) | (~0xffffffffffffffffffffffffffffffffffffffffffffffffffffffff & 0x0100000000000000000000000000000000000000000000000000000000 * 0x4b64e492)
	//     @019A  stack[3] = memory[0x40:0x60]
	//     @019B  stack[4] = memory[0x40:0x60]
	//     @01A3  stack[5] = 0x20 + memory[0x40:0x60]
	//     @01A3  stack[6] = memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20]
	//     @01A4  stack[7] = memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20]
	//     @01A5  stack[8] = memory[0x40:0x60]
	//     @01A6  stack[9] = 0x20 + memory[0x40:0x60]
	//     @01A7  stack[10] = 0x00
	// }
	// Block ends with conditional jump to 0x01c4, if !(0x00 < memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20])

label_01B2:
	// Incoming jump from 0x01B1, if not !(0x00 < memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20])
	// Incoming jump from 0x01B1, if not !(stack[-1] < stack[-4])
	// Inputs[4]
	// {
	//     @01B2  stack[-1]
	//     @01B3  stack[-2]
	//     @01B5  memory[stack[-2] + stack[-1]:stack[-2] + stack[-1] + 0x20]
	//     @01B7  stack[-3]
	// }
	01B2    80  DUP1
	01B3    82  DUP3
	01B4    01  ADD
	01B5    51  MLOAD
	01B6    81  DUP2
	01B7    84  DUP5
	01B8    01  ADD
	01B9    52  MSTORE
	01BA    60  PUSH1 0x20
	01BC    81  DUP2
	01BD    01  ADD
	01BE    90  SWAP1
	01BF    50  POP
	01C0    61  PUSH2 0x01a9
	01C3    56  *JUMP
	// Stack delta = +0
	// Outputs[2]
	// {
	//     @01B9  memory[stack[-3] + stack[-1]:stack[-3] + stack[-1] + 0x20] = memory[stack[-2] + stack[-1]:stack[-2] + stack[-1] + 0x20]
	//     @01BE  stack[-1] = stack[-1] + 0x20
	// }
	// Block ends with unconditional jump to 0x01a9

label_01C4:
	// Incoming jump from 0x01B1, if !(0x00 < memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20])
	// Incoming jump from 0x01B1, if !(stack[-1] < stack[-4])
	// Inputs[3]
	// {
	//     @01C9  stack[-6]
	//     @01C9  stack[-5]
	//     @01CB  stack[-7]
	// }
	01C4    5B  JUMPDEST
	01C5    50  POP
	01C6    50  POP
	01C7    50  POP
	01C8    50  POP
	01C9    90  SWAP1
	01CA    50  POP
	01CB    90  SWAP1
	01CC    81  DUP2
	01CD    01  ADD
	01CE    90  SWAP1
	01CF    60  PUSH1 0x1f
	01D1    16  AND
	01D2    80  DUP1
	01D3    15  ISZERO
	01D4    61  PUSH2 0x01f1
	01D7    57  *JUMPI
	// Stack delta = -5
	// Outputs[2]
	// {
	//     @01CE  stack[-7] = stack[-5] + stack[-7]
	//     @01D1  stack[-6] = 0x1f & stack[-5]
	// }
	// Block ends with conditional jump to 0x01f1, if !(0x1f & stack[-5])

label_01D8:
	// Incoming jump from 0x01D7, if not !(0x1f & stack[-5])
	// Inputs[10]
	// {
	//     @01D8  stack[-1]
	//     @01D9  stack[-2]
	//     @01DC  memory[stack[-2] - stack[-1]:stack[-2] - stack[-1] + 0x20]
	//     @01F3  stack[-4]
	//     @01FA  memory[0x40:0x60]
	//     @01FF  stack[-5]
	//     @0200  msg.gas
	//     @0201  address(stack[-5]).delegatecall.gas(msg.gas)(memory[memory[0x40:0x60]:memory[0x40:0x60] + (0x20 + (stack[-2] - stack[-1])) - memory[0x40:0x60]])
	//     @0201  memory[memory[0x40:0x60]:memory[0x40:0x60] + (0x20 + (stack[-2] - stack[-1])) - memory[0x40:0x60]]
	//     @0207  stack[-6]
	// }
	01D8    80  DUP1
	01D9    82  DUP3
	01DA    03  SUB
	01DB    80  DUP1
	01DC    51  MLOAD
	01DD    60  PUSH1 0x01
	01DF    83  DUP4
	01E0    60  PUSH1 0x20
	01E2    03  SUB
	01E3    61  PUSH2 0x0100
	01E6    0A  EXP
	01E7    03  SUB
	01E8    19  NOT
	01E9    16  AND
	01EA    81  DUP2
	01EB    52  MSTORE
	01EC    60  PUSH1 0x20
	01EE    01  ADD
	01EF    91  SWAP2
	01F0    50  POP
	01F1    5B  JUMPDEST
	01F2    50  POP
	01F3    91  SWAP2
	01F4    50  POP
	01F5    50  POP
	01F6    60  PUSH1 0x00
	01F8    60  PUSH1 0x40
	01FA    51  MLOAD
	01FB    80  DUP1
	01FC    83  DUP4
	01FD    03  SUB
	01FE    81  DUP2
	01FF    85  DUP6
	0200    5A  GAS
	0201    F4  DELEGATECALL
	0202    91  SWAP2
	0203    50  POP
	0204    50  POP
	0205    15  ISZERO
	0206    15  ISZERO
	0207    14  EQ
	0208    15  ISZERO
	0209    15  ISZERO
	020A    61  PUSH2 0x0212
	020D    57  *JUMPI
	// Stack delta = -6
	// Outputs[2]
	// {
	//     @01EB  memory[stack[-2] - stack[-1]:stack[-2] - stack[-1] + 0x20] = ~(0x0100 ** (0x20 - stack[-1]) - 0x01) & memory[stack[-2] - stack[-1]:stack[-2] - stack[-1] + 0x20]
	//     @0201  memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x00] = address(stack[-5]).delegatecall.gas(msg.gas)(memory[memory[0x40:0x60]:memory[0x40:0x60] + (0x20 + (stack[-2] - stack[-1])) - memory[0x40:0x60]])
	// }
	// Block ends with conditional jump to 0x0212, if !!(!!address(stack[-5]).delegatecall.gas(msg.gas)(memory[memory[0x40:0x60]:memory[0x40:0x60] + (0x20 + (stack[-2] - stack[-1])) - memory[0x40:0x60]]) == stack[-6])

label_020E:
	// Incoming jump from 0x020D, if not !!(!!address(stack[-5]).delegatecall.gas(msg.gas)(memory[memory[0x40:0x60]:memory[0x40:0x60] + (0x20 + (stack[-2] - stack[-1])) - memory[0x40:0x60]]) == stack[-6])
	// Incoming jump from 0x020D, if not !!(!!address(stack[-5]).delegatecall.gas(msg.gas)(memory[memory[0x40:0x60]:memory[0x40:0x60] + stack[-2] - memory[0x40:0x60]]) == stack[-6])
	// Inputs[1] { @0211  memory[0x00:0x00] }
	020E    60  PUSH1 0x00
	0210    80  DUP1
	0211    FD  *REVERT
	// Stack delta = +0
	// Outputs[1] { @0211  revert(memory[0x00:0x00]); }
	// Block terminates

label_0212:
	// Incoming jump from 0x020D, if !!(!!address(stack[-5]).delegatecall.gas(msg.gas)(memory[memory[0x40:0x60]:memory[0x40:0x60] + (0x20 + (stack[-2] - stack[-1])) - memory[0x40:0x60]]) == stack[-6])
	// Incoming jump from 0x020D, if !!(!!address(stack[-5]).delegatecall.gas(msg.gas)(memory[memory[0x40:0x60]:memory[0x40:0x60] + stack[-2] - memory[0x40:0x60]]) == stack[-6])
	0212    5B  JUMPDEST
	0213    61  PUSH2 0x021a
	0216    61  PUSH2 0x04b5
	0219    56  *JUMP
	// Stack delta = +1
	// Outputs[1] { @0213  stack[0] = 0x021a }
	// Block ends with call to 0x04b5, returns to 0x021A

label_021A:
	// Incoming return from call to 0x04B5 at 0x0219
	// Inputs[7]
	// {
	//     @021B  stack[-1]
	//     @021C  stack[-4]
	//     @021E  stack[-2]
	//     @021F  stack[-5]
	//     @0225  memory[0x40:0x60]
	//     @0253  memory[0x40:0x60]
	//     @0258  memory[memory[0x40:0x60]:memory[0x40:0x60] + (0x10 + memory[0x40:0x60]) - memory[0x40:0x60]]
	// }
	021A    5B  JUMPDEST
	021B    80  DUP1
	021C    93  SWAP4
	021D    50  POP
	021E    81  DUP2
	021F    94  SWAP5
	0220    50  POP
	0221    50  POP
	0222    50  POP
	0223    60  PUSH1 0x40
	0225    51  MLOAD
	0226    80  DUP1
	0227    80  DUP1
	0228    7F  PUSH32 0x676574666c61672875696e743235362900000000000000000000000000000000
	0249    81  DUP2
	024A    52  MSTORE
	024B    50  POP
	024C    60  PUSH1 0x10
	024E    01  ADD
	024F    90  SWAP1
	0250    50  POP
	0251    60  PUSH1 0x40
	0253    51  MLOAD
	0254    80  DUP1
	0255    91  SWAP2
	0256    03  SUB
	0257    90  SWAP1
	0258    20  SHA3
	0259    7B  PUSH28 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffff
	0276    19  NOT
	0277    16  AND
	0278    83  DUP4
	0279    7B  PUSH28 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffff
	0296    19  NOT
	0297    16  AND
	0298    14  EQ
	0299    15  ISZERO
	029A    15  ISZERO
	029B    61  PUSH2 0x02a3
	029E    57  *JUMPI
	// Stack delta = -2
	// Outputs[3]
	// {
	//     @021C  stack[-4] = stack[-1]
	//     @021F  stack[-5] = stack[-2]
	//     @024A  memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20] = 0x676574666c61672875696e743235362900000000000000000000000000000000
	// }
	// Block ends with conditional jump to 0x02a3, if !!(~0xffffffffffffffffffffffffffffffffffffffffffffffffffffffff & stack[-2] == ~0xffffffffffffffffffffffffffffffffffffffffffffffffffffffff & keccak256(memory[memory[0x40:0x60]:memory[0x40:0x60] + (0x10 + memory[0x40:0x60]) - memory[0x40:0x60]]))

label_029F:
	// Incoming jump from 0x029E, if not !!(~0xffffffffffffffffffffffffffffffffffffffffffffffffffffffff & stack[-2] == ~0xffffffffffffffffffffffffffffffffffffffffffffffffffffffff & keccak256(memory[memory[0x40:0x60]:memory[0x40:0x60] + (0x10 + memory[0x40:0x60]) - memory[0x40:0x60]]))
	// Inputs[1] { @02A2  memory[0x00:0x00] }
	029F    60  PUSH1 0x00
	02A1    80  DUP1
	02A2    FD  *REVERT
	// Stack delta = +0
	// Outputs[1] { @02A2  revert(memory[0x00:0x00]); }
	// Block terminates

label_02A3:
	// Incoming jump from 0x029E, if !!(~0xffffffffffffffffffffffffffffffffffffffffffffffffffffffff & stack[-2] == ~0xffffffffffffffffffffffffffffffffffffffffffffffffffffffff & keccak256(memory[memory[0x40:0x60]:memory[0x40:0x60] + (0x10 + memory[0x40:0x60]) - memory[0x40:0x60]]))
	// Inputs[6]
	// {
	//     @02A7  stack[-1]
	//     @02C6  address(this)
	//     @02C7  address(this).balance
	//     @02C8  stack[-2]
	//     @02CA  memory[stack[-1]:stack[-1] + 0x20]
	//     @02D6  memory[0x00 + stack[-1]:0x00 + stack[-1] + 0x20]
	// }
	02A3    5B  JUMPDEST
	02A4    61  PUSH2 0x02e4
	02A7    81  DUP2
	02A8    60  PUSH1 0x00
	02AA    01  ADD
	02AB    90  SWAP1
	02AC    67  PUSH8 0xffffffffffffffff
	02B5    16  AND
	02B6    90  SWAP1
	02B7    81  DUP2
	02B8    67  PUSH8 0xffffffffffffffff
	02C1    16  AND
	02C2    81  DUP2
	02C3    52  MSTORE
	02C4    50  POP
	02C5    50  POP
	02C6    30  ADDRESS
	02C7    31  BALANCE
	02C8    82  DUP3
	02C9    82  DUP3
	02CA    51  MLOAD
	02CB    01  ADD
	02CC    03  SUB
	02CD    81  DUP2
	02CE    52  MSTORE
	02CF    61  PUSH2 0x02de
	02D2    81  DUP2
	02D3    60  PUSH1 0x00
	02D5    01  ADD
	02D6    51  MLOAD
	02D7    63  PUSH4 0xffffffff
	02DC    16  AND
	02DD    56  *JUMP
	// Stack delta = +1
	// Outputs[3]
	// {
	//     @02C3  memory[0x00 + stack[-1]:0x00 + stack[-1] + 0x20] = 0xffffffffffffffff & 0xffffffffffffffff & 0x02e4
	//     @02CE  memory[stack[-1]:stack[-1] + 0x20] = (memory[stack[-1]:stack[-1] + 0x20] + stack[-2]) - address(this).balance
	//     @02CF  stack[0] = 0x02de
	// }
	// Block ends with unconditional jump to 0xffffffff & memory[0x00 + stack[-1]:0x00 + stack[-1] + 0x20]

	02DE    5B    JUMPDEST
	02DF    50    POP
	02E0    50    POP
	02E1    50    POP
	02E2    50    POP
	02E3    56    *JUMP
label_02E4:
	// Incoming call from 0x00A8, returns to 0x00A9
	// Inputs[5]
	// {
	//     @0309  msg.sender
	//     @030C  memory[0x40:0x60]
	//     @0348  memory[0x40:0x60]
	//     @0357  memory[0x40:0x60]
	//     @035B  memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20]
	// }
	02E4    5B  JUMPDEST
	02E5    7F  PUSH32 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
	0306    60  PUSH1 0x01
	0308    02  MUL
	0309    33  CALLER
	030A    60  PUSH1 0x40
	030C    51  MLOAD
	030D    60  PUSH1 0x20
	030F    01  ADD
	0310    80  DUP1
	0311    82  DUP3
	0312    73  PUSH20 0xffffffffffffffffffffffffffffffffffffffff
	0327    16  AND
	0328    73  PUSH20 0xffffffffffffffffffffffffffffffffffffffff
	033D    16  AND
	033E    81  DUP2
	033F    52  MSTORE
	0340    60  PUSH1 0x20
	0342    01  ADD
	0343    91  SWAP2
	0344    50  POP
	0345    50  POP
	0346    60  PUSH1 0x40
	0348    51  MLOAD
	0349    60  PUSH1 0x20
	034B    81  DUP2
	034C    83  DUP4
	034D    03  SUB
	034E    03  SUB
	034F    81  DUP2
	0350    52  MSTORE
	0351    90  SWAP1
	0352    60  PUSH1 0x40
	0354    52  MSTORE
	0355    60  PUSH1 0x40
	0357    51  MLOAD
	0358    80  DUP1
	0359    82  DUP3
	035A    80  DUP1
	035B    51  MLOAD
	035C    90  SWAP1
	035D    60  PUSH1 0x20
	035F    01  ADD
	0360    90  SWAP1
	0361    80  DUP1
	0362    83  DUP4
	0363    83  DUP4
	0364    5B  JUMPDEST
	0365    60  PUSH1 0x20
	0367    83  DUP4
	0368    10  LT
	0369    15  ISZERO
	036A    15  ISZERO
	036B    61  PUSH2 0x0389
	036E    57  *JUMPI
	// Stack delta = +9
	// Outputs[12]
	// {
	//     @0308  stack[0] = 0x01 * 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
	//     @033F  memory[0x20 + memory[0x40:0x60]:0x20 + memory[0x40:0x60] + 0x20] = 0xffffffffffffffffffffffffffffffffffffffff & 0xffffffffffffffffffffffffffffffffffffffff & msg.sender
	//     @0350  memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20] = (0x20 + 0x20 + memory[0x40:0x60]) - memory[0x40:0x60] - 0x20
	//     @0351  stack[1] = memory[0x40:0x60]
	//     @0354  memory[0x40:0x60] = 0x20 + 0x20 + memory[0x40:0x60]
	//     @0357  stack[2] = memory[0x40:0x60]
	//     @0358  stack[3] = memory[0x40:0x60]
	//     @0360  stack[4] = 0x20 + memory[0x40:0x60]
	//     @0360  stack[5] = memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20]
	//     @0361  stack[6] = memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20]
	//     @0362  stack[7] = memory[0x40:0x60]
	//     @0363  stack[8] = 0x20 + memory[0x40:0x60]
	// }
	// Block ends with conditional jump to 0x0389, if !!(memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20] < 0x20)

label_036F:
	// Incoming jump from 0x036E, if not !!(memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20] < 0x20)
	// Incoming jump from 0x036E, if not !!(stack[-3] < 0x20)
	// Inputs[4]
	// {
	//     @036F  stack[-1]
	//     @0370  memory[stack[-1]:stack[-1] + 0x20]
	//     @0371  stack[-2]
	//     @0381  stack[-3]
	// }
	036F    80  DUP1
	0370    51  MLOAD
	0371    82  DUP3
	0372    52  MSTORE
	0373    60  PUSH1 0x20
	0375    82  DUP3
	0376    01  ADD
	0377    91  SWAP2
	0378    50  POP
	0379    60  PUSH1 0x20
	037B    81  DUP2
	037C    01  ADD
	037D    90  SWAP1
	037E    50  POP
	037F    60  PUSH1 0x20
	0381    83  DUP4
	0382    03  SUB
	0383    92  SWAP3
	0384    50  POP
	0385    61  PUSH2 0x0364
	0388    56  *JUMP
	// Stack delta = +0
	// Outputs[4]
	// {
	//     @0372  memory[stack[-2]:stack[-2] + 0x20] = memory[stack[-1]:stack[-1] + 0x20]
	//     @0377  stack[-2] = stack[-2] + 0x20
	//     @037D  stack[-1] = stack[-1] + 0x20
	//     @0383  stack[-3] = stack[-3] - 0x20
	// }
	// Block ends with unconditional jump to 0x0364

label_0389:
	// Incoming jump from 0x036E, if !!(memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20] < 0x20)
	// Incoming jump from 0x036E, if !!(stack[-3] < 0x20)
	// Inputs[12]
	// {
	//     @038C  stack[-3]
	//     @0397  stack[-1]
	//     @0398  memory[stack[-1]:stack[-1] + 0x20]
	//     @039B  stack[-2]
	//     @039C  memory[stack[-2]:stack[-2] + 0x20]
	//     @03A9  stack[-4]
	//     @03A9  stack[-5]
	//     @03AB  stack[-6]
	//     @03AC  stack[-8]
	//     @03B1  memory[0x40:0x60]
	//     @03B6  memory[memory[0x40:0x60]:memory[0x40:0x60] + (stack[-4] + stack[-6]) - memory[0x40:0x60]]
	//     @03BB  stack[-9]
	// }
	0389    5B  JUMPDEST
	038A    60  PUSH1 0x01
	038C    83  DUP4
	038D    60  PUSH1 0x20
	038F    03  SUB
	0390    61  PUSH2 0x0100
	0393    0A  EXP
	0394    03  SUB
	0395    80  DUP1
	0396    19  NOT
	0397    82  DUP3
	0398    51  MLOAD
	0399    16  AND
	039A    81  DUP2
	039B    84  DUP5
	039C    51  MLOAD
	039D    16  AND
	039E    80  DUP1
	039F    82  DUP3
	03A0    17  OR
	03A1    85  DUP6
	03A2    52  MSTORE
	03A3    50  POP
	03A4    50  POP
	03A5    50  POP
	03A6    50  POP
	03A7    50  POP
	03A8    50  POP
	03A9    90  SWAP1
	03AA    50  POP
	03AB    01  ADD
	03AC    91  SWAP2
	03AD    50  POP
	03AE    50  POP
	03AF    60  PUSH1 0x40
	03B1    51  MLOAD
	03B2    80  DUP1
	03B3    91  SWAP2
	03B4    03  SUB
	03B5    90  SWAP1
	03B6    20  SHA3
	03B7    60  PUSH1 0x00
	03B9    19  NOT
	03BA    16  AND
	03BB    14  EQ
	03BC    15  ISZERO
	03BD    15  ISZERO
	03BE    61  PUSH2 0x03c6
	03C1    57  *JUMPI
	// Stack delta = -9
	// Outputs[1] { @03A2  memory[stack[-2]:stack[-2] + 0x20] = (memory[stack[-1]:stack[-1] + 0x20] & ~(0x0100 ** (0x20 - stack[-3]) - 0x01)) | (memory[stack[-2]:stack[-2] + 0x20] & 0x0100 ** (0x20 - stack[-3]) - 0x01) }
	// Block ends with conditional jump to 0x03c6, if !!(~0x00 & keccak256(memory[memory[0x40:0x60]:memory[0x40:0x60] + (stack[-4] + stack[-6]) - memory[0x40:0x60]]) == stack[-9])

label_03C2:
	// Incoming jump from 0x03C1, if not !!(~0x00 & keccak256(memory[memory[0x40:0x60]:memory[0x40:0x60] + (stack[-4] + stack[-6]) - memory[0x40:0x60]]) == stack[-9])
	// Inputs[1] { @03C5  memory[0x00:0x00] }
	03C2    60  PUSH1 0x00
	03C4    80  DUP1
	03C5    FD  *REVERT
	// Stack delta = +0
	// Outputs[1] { @03C5  revert(memory[0x00:0x00]); }
	// Block terminates

label_03C6:
	// Incoming jump from 0x03C1, if !!(~0x00 & keccak256(memory[memory[0x40:0x60]:memory[0x40:0x60] + (stack[-4] + stack[-6]) - memory[0x40:0x60]]) == stack[-9])
	// Inputs[2]
	// {
	//     @03CA  address(this)
	//     @03E1  address(0xffffffffffffffffffffffffffffffffffffffff & address(this)).balance
	// }
	03C6    5B  JUMPDEST
	03C7    61  PUSH2 0x03e8
	03CA    30  ADDRESS
	03CB    73  PUSH20 0xffffffffffffffffffffffffffffffffffffffff
	03E0    16  AND
	03E1    31  BALANCE
	03E2    11  GT
	03E3    15  ISZERO
	03E4    61  PUSH2 0x044f
	03E7    57  *JUMPI
	// Stack delta = +0
	// Block ends with conditional jump to 0x044f, if !(address(0xffffffffffffffffffffffffffffffffffffffff & address(this)).balance > 0x03e8)

label_03E8:
	// Incoming jump from 0x03E7, if not !(address(0xffffffffffffffffffffffffffffffffffffffff & address(this)).balance > 0x03e8)
	// Inputs[4]
	// {
	//     @0409  msg.sender
	//     @040C  memory[0x40:0x60]
	//     @0445  memory[0x40:0x60]
	//     @044A  memory[memory[0x40:0x60]:memory[0x40:0x60] + (0x20 + memory[0x40:0x60]) - memory[0x40:0x60]]
	// }
	03E8    7F  PUSH32 0x89814845d4f005a4059f76ea572f39df73fbe3d1c9b20f12b3b03d09f999b9e2
	0409    33  CALLER
	040A    60  PUSH1 0x40
	040C    51  MLOAD
	040D    80  DUP1
	040E    82  DUP3
	040F    73  PUSH20 0xffffffffffffffffffffffffffffffffffffffff
	0424    16  AND
	0425    73  PUSH20 0xffffffffffffffffffffffffffffffffffffffff
	043A    16  AND
	043B    81  DUP2
	043C    52  MSTORE
	043D    60  PUSH1 0x20
	043F    01  ADD
	0440    91  SWAP2
	0441    50  POP
	0442    50  POP
	0443    60  PUSH1 0x40
	0445    51  MLOAD
	0446    80  DUP1
	0447    91  SWAP2
	0448    03  SUB
	0449    90  SWAP1
	044A    A1  LOG1
	044B    61  PUSH2 0x04b3
	044E    56  *JUMP
	// Stack delta = +0
	// Outputs[2]
	// {
	//     @043C  memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20] = 0xffffffffffffffffffffffffffffffffffffffff & 0xffffffffffffffffffffffffffffffffffffffff & msg.sender
	//     @044A  log(memory[memory[0x40:0x60]:memory[0x40:0x60] + (0x20 + memory[0x40:0x60]) - memory[0x40:0x60]], [0x89814845d4f005a4059f76ea572f39df73fbe3d1c9b20f12b3b03d09f999b9e2]);
	// }
	// Block ends with unconditional jump to 0x04b3

label_044F:
	// Incoming jump from 0x03E7, if !(address(0xffffffffffffffffffffffffffffffffffffffff & address(this)).balance > 0x03e8)
	// Inputs[5]
	// {
	//     @0471  msg.sender
	//     @0474  memory[0x40:0x60]
	//     @04AD  memory[0x40:0x60]
	//     @04B2  memory[memory[0x40:0x60]:memory[0x40:0x60] + (0x20 + memory[0x40:0x60]) - memory[0x40:0x60]]
	//     @04B4  stack[-1]
	// }
	044F    5B  JUMPDEST
	0450    7F  PUSH32 0x21d0324cd6cce67ffe52c8955137310671bcef292844385858e00841a18d60c0
	0471    33  CALLER
	0472    60  PUSH1 0x40
	0474    51  MLOAD
	0475    80  DUP1
	0476    82  DUP3
	0477    73  PUSH20 0xffffffffffffffffffffffffffffffffffffffff
	048C    16  AND
	048D    73  PUSH20 0xffffffffffffffffffffffffffffffffffffffff
	04A2    16  AND
	04A3    81  DUP2
	04A4    52  MSTORE
	04A5    60  PUSH1 0x20
	04A7    01  ADD
	04A8    91  SWAP2
	04A9    50  POP
	04AA    50  POP
	04AB    60  PUSH1 0x40
	04AD    51  MLOAD
	04AE    80  DUP1
	04AF    91  SWAP2
	04B0    03  SUB
	04B1    90  SWAP1
	04B2    A1  LOG1
	04B3    5B  JUMPDEST
	04B4    56  *JUMP
	// Stack delta = -1
	// Outputs[2]
	// {
	//     @04A4  memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20] = 0xffffffffffffffffffffffffffffffffffffffff & 0xffffffffffffffffffffffffffffffffffffffff & msg.sender
	//     @04B2  log(memory[memory[0x40:0x60]:memory[0x40:0x60] + (0x20 + memory[0x40:0x60]) - memory[0x40:0x60]], [0x21d0324cd6cce67ffe52c8955137310671bcef292844385858e00841a18d60c0]);
	// }
	// Block ends with unconditional jump to stack[-1]

label_04B5:
	// Incoming call from 0x0219, returns to 0x021A
	// Inputs[1] { @04BB  returndata.length }
	04B5    5B  JUMPDEST
	04B6    60  PUSH1 0x00
	04B8    80  DUP1
	04B9    60  PUSH1 0x24
	04BB    3D  RETURNDATASIZE
	04BC    14  EQ
	04BD    15  ISZERO
	04BE    15  ISZERO
	04BF    61  PUSH2 0x04c7
	04C2    57  *JUMPI
	// Stack delta = +2
	// Outputs[2]
	// {
	//     @04B6  stack[0] = 0x00
	//     @04B8  stack[1] = 0x00
	// }
	// Block ends with conditional jump to 0x04c7, if !!(returndata.length == 0x24)

label_04C3:
	// Incoming jump from 0x04C2, if not !!(returndata.length == 0x24)
	// Inputs[1] { @04C6  memory[0x00:0x00] }
	04C3    60  PUSH1 0x00
	04C5    80  DUP1
	04C6    FD  *REVERT
	// Stack delta = +0
	// Outputs[1] { @04C6  revert(memory[0x00:0x00]); }
	// Block terminates

label_04C7:
	// Incoming jump from 0x04C2, if !!(returndata.length == 0x24)
	// Inputs[7]
	// {
	//     @04CA  memory[0x40:0x60]
	//     @04D0  returndata[0x00:0x24]
	//     @04F3  memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20]
	//     @04F5  stack[-2]
	//     @04FB  memory[0x04 + memory[0x40:0x60]:0x04 + memory[0x40:0x60] + 0x20]
	//     @04FC  stack[-1]
	//     @0500  stack[-3]
	// }
	04C7    5B  JUMPDEST
	04C8    60  PUSH1 0x40
	04CA    51  MLOAD
	04CB    60  PUSH1 0x24
	04CD    60  PUSH1 0x00
	04CF    82  DUP3
	04D0    3E  RETURNDATACOPY
	04D1    7F  PUSH32 0xffffffff00000000000000000000000000000000000000000000000000000000
	04F2    81  DUP2
	04F3    51  MLOAD
	04F4    16  AND
	04F5    92  SWAP3
	04F6    50  POP
	04F7    80  DUP1
	04F8    60  PUSH1 0x04
	04FA    01  ADD
	04FB    51  MLOAD
	04FC    91  SWAP2
	04FD    50  POP
	04FE    50  POP
	04FF    90  SWAP1
	0500    91  SWAP2
	0501    56  *JUMP
	// Stack delta = -1
	// Outputs[3]
	// {
	//     @04D0  memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x24] = returndata[0x00:0x24]
	//     @04FF  stack[-2] = memory[0x04 + memory[0x40:0x60]:0x04 + memory[0x40:0x60] + 0x20]
	//     @0500  stack[-3] = memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20] & 0xffffffff00000000000000000000000000000000000000000000000000000000
	// }
	// Block ends with unconditional jump to stack[-3]

label_0502:
	// Incoming call from 0x00B5, returns to 0x00B6
	// Inputs[2]
	// {
	//     @0507  memory[0x40:0x60]
	//     @0515  stack[-1]
	// }
	0502    5B  JUMPDEST
	0503    60  PUSH1 0x20
	0505    60  PUSH1 0x40
	0507    51  MLOAD
	0508    90  SWAP1
	0509    81  DUP2
	050A    01  ADD
	050B    60  PUSH1 0x40
	050D    52  MSTORE
	050E    80  DUP1
	050F    61  PUSH2 0x0517
	0512    81  DUP2
	0513    52  MSTORE
	0514    50  POP
	0515    90  SWAP1
	0516    56  *JUMP
	// Stack delta = +0
	// Outputs[3]
	// {
	//     @050D  memory[0x40:0x60] = memory[0x40:0x60] + 0x20
	//     @0513  memory[memory[0x40:0x60]:memory[0x40:0x60] + 0x20] = 0x0517
	//     @0515  stack[-1] = memory[0x40:0x60]
	// }
	// Block ends with unconditional jump to stack[-1]

	0517    5B    JUMPDEST
	0518    FE    *ASSERT
	0519    00    *STOP
	051A    A1    LOG1
	051B    65    PUSH6 0x627a7a723058
	0522    20    SHA3
	0523    DF    DF
	0524    59    MSIZE
	0525    F2    CALLCODE
	0526    83    DUP4
	0527    71    PUSH18 0xb1cd310dd48ca7844b4e76df0305a7a600c6
	053A    69    PUSH10 0xb8838e40fe90eb0c0029
