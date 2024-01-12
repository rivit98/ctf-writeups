#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void hexdump(const void* data, size_t size) {
	char ascii[17];
	size_t i, j;
	ascii[16] = '\0';
	for (i = 0; i < size; ++i) {
		printf("%02X ", ((unsigned char*)data)[i]);
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)data)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == size) {
			printf(" ");
			if ((i+1) % 16 == 0) {
				printf("|  %s \n", ascii);
			} else if (i+1 == size) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					printf(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j) {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}

void decode(char *data_ptr, int data_len, uint8_t* table)
{
  char v3; // al
  int idx; // ecx

  for ( idx = 0; idx < data_len; idx++ )
  {
    v3 = idx + table[idx % 16] - 10 * ((char)idx / 10) + 0x30;
    data_ptr[idx] ^= v3;
  }
}

int main() {
    uint8_t t[] = {0x95, 0xfb, 0xa3, 0xd2, 0xef, 0x76, 0x42, 0xd9, 0x33, 0x44, 0x48, 0x83, 0xbe, 0x22, 0x13, 0x37};
    uint8_t d[] = {0x07, 0x66, 0xd4, 0x05, 0x11, 0xa3, 0x78, 0x10};

    // decode(d, sizeof(d), t);
    // hexdump(d, sizeof(d));


    FILE *f = fopen("data_between_deadbeef", "rb");
    if(!f){
        perror("fopen");
        return;
    }

    fseek(f, 0, SEEK_END);
    int32_t size = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *buffer = malloc(size);
    fread(buffer, 1, size, f);
    fclose(f);

    decode(buffer, size, t);
    hexdump(buffer, size);



    free(buffer);
}
