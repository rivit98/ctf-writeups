#include<stdio.h>
#include <stdint.h>

typedef uint32_t uint;
typedef uint8_t byte;

byte first_scramble[] = { 0x55, 0x8b, 0xec, 0x83, 0xec, 0x20, 0xeb, 0xfe };
byte second_scramble[] = { 0x3e, 0x39, 0x51, 0xfb, 0xa2, 0x11, 0xf7, 0xb9, 0x2c };
byte flag[] = { 0xe1, 0x60, 0xa1, 0x18, 0x93, 0x2e, 0x96, 0xad, 0x73, 0xbb, 0x4a, 0x92, 0xde, 0x18, 0x0a, 0xaa, 0x41, 0x74, 0xad, 0xc0, 0x1d, 0x9f, 0x3f, 0x19, 0xff, 0x2b, 0x02, 0xdb, 0xd1, 0xcd, 0x1a, 0x00 };
void FUN_100011ef(uint *param_1, const byte *param_2, int param_3)
{
	int iVar1;
	int *piVar2;
	int iVar3;
	int iVar4;
	uint uVar5;
	int idx;

	iVar4 = 0x0;
	idx = 0x0;
	*param_1 = 0x0;
	param_1[0x1] = 0x0;
	do {
		piVar2 = param_1 + idx + 0x2;
		*piVar2 = idx;
		piVar2[0x1] = idx + 0x1;
		piVar2[0x2] = idx + 0x2;
		piVar2[0x3] = idx + 0x3;
		idx = idx + 0x4;
	} while (idx < 0x100);
	uVar5 = 0x0;
	idx = 0x0;
	do {
		iVar3 = param_1[idx + 0x2];
		uVar5 = (uint)(byte)(param_2[iVar4] + (char)uVar5 + (char)iVar3);
		param_1[idx + 0x2] = param_1[uVar5 + 0x2];
		iVar1 = iVar4 + 0x1;
		param_1[uVar5 + 0x2] = iVar3;
		idx = idx + 0x1;
		iVar4 = 0x0;
		if (iVar1 < param_3) {
			iVar4 = iVar1;
		}
	} while (idx < 0x100);
}

void FUN_10001187(uint *param_1,byte *param_2,int param_3)
{
	uint uVar1;
	uint uVar2;
	char cVar3;
	uint uVar4;
	int iVar5;
	uint local_4;

	iVar5 = 0x0;
	local_4 = param_1[0x1];
	uVar4 = *param_1;
	if (0x0 < param_3) {
		do {
			uVar4 = (uint)(byte)((char)uVar4 + 0x1);
			uVar1 = param_1[uVar4 + 0x2];
			cVar3 = (char)uVar1;
			local_4 = (uint)(byte)(cVar3 + (char)local_4);
			uVar2 = param_1[local_4 + 0x2];
			param_1[uVar4 + 0x2] = uVar2;
			param_1[local_4 + 0x2] = uVar1;
			param_2[iVar5] = param_2[iVar5] ^ *(byte *)(param_1 + (byte)(cVar3 + (char)uVar2) + 0x2);
			printf("%c", param_2[iVar5]);
			iVar5 = iVar5 + 0x1;
		} while (iVar5 < param_3);
		puts("");
	}
	*param_1 = uVar4;
	param_1[0x1] = local_4;
}


int main(void)
{
	uint local_40c [0x100] = {0};
	FUN_100011ef(local_40c, first_scramble,0x8);
	FUN_10001187(local_40c, second_scramble,0x9);
	FUN_10001187(local_40c, flag, 0x1f);
}