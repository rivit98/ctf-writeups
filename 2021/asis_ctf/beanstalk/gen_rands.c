#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	
	srand(0x00000000F5F38A17);
	printf("rands = [");
	for (int i = 0; i < 32; ++i)
	{
		printf("0x%x, ", rand() & 0xFFFF);
	}
	puts("]");

	return 0;
}