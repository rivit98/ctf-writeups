#include "unistd.h"
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *int2bin(uint8_t n)
{
	char *buf = calloc(0x20, 1);
	int i;

	for (i = sizeof(n) * 8 - 1; i >= 0; --i)
	{
		buf[i] = (n & 1) ? '1' : '0';
		n >>= 1;
	}

	return buf;
}

uint64_t step(uint8_t *my_data, unsigned int data_len)
{
	char v3;		// [rsp+15h] [rbp-1Bh]
	uint8_t is_odd; // [rsp+16h] [rbp-1Ah]
	char v5;		// [rsp+17h] [rbp-19h]
	unsigned int i; // [rsp+18h] [rbp-18h]
	signed int j;	// [rsp+1Ch] [rbp-14h]
	uint64_t carry; // [rsp+20h] [rbp-10h]
	uint64_t v9;	// [rsp+28h] [rbp-8h]

	is_odd = *my_data & 1;
	if (is_odd)
	{
		// printf("shuffle\n");
		carry = 1LL;
		for (i = 0; i < data_len; ++i)
		{
			// v9 has to be less than 256
			v9 = carry + 3LL * (uint8_t)my_data[i];
			carry = v9 >> 8;
			// printf("%d %d\n", v9, carry);
			my_data[i] = v9;
		}
		if (carry)
		{
			puts("Error.");
			exit(99);
		}
	}
	v3 = 0;
	for (j = data_len - 1; j >= 0; --j)
	{
		v5 = my_data[j] & 1;
		my_data[j] >>= 1;
		my_data[j] |= v3 << 7;
		v3 = v5;
	}
	if (v3)
	{
		puts("extra == 0");
		exit(1);
	}
	return is_odd;
}

int pos(uint8_t data[])
{
	for (int i = 0; i < 0x4009; i++)
	{
		if (data[i])
			return i;
	}

	return -1;
}

int main(int argc, char *argv[])
{
	// uint8_t d[2] = {0b11001010, 0b00101001};
	// step(d, 2);
	// printf("%s %s\n", int2bin(d[0]), int2bin(d[1]));

	char *my_input = calloc(0x4009, 1);

	for (int i = 0; i < 0x4009; i++)
	{
		my_input[i] = 0b00000001;
	}

	for (int i = 0; i < 0x4000; i++)
	{
		my_input[i] = 0;
	}

	// my_input[123] = 0b1;

	for (int j = 0; j <= 0x2003F; ++j)
	{
		if (step(my_input, 0x4009))
		{
			printf("%x ", j);
		}
	}

	// for (int i = 0; i < 3; i++)
	// {
	// 	my_input[i] = 0xa1;
	// }

	// for (int j = 0; j < 3; j++)
	// {
	// 	printf("%s ", int2bin(my_input[j]));
	// }
	// puts("");

	// for (int i = 0; i < 2; i++)
	// {
	// 	step(my_input, 3);
	// 	for (int j = 0; j < 3; j++)
	// 	{
	// 		printf("%s ", int2bin(my_input[j]));
	// 	}
	// 	puts("");
	// }
}
