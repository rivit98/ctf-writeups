#include <stdio.h>
#include <stdint.h>

int8_t data[] = {
0x0A, 0x9B, 0xF7, 0xFF, 0xBB, 0x7A, 0x89, 0xBC, 0xB3, 0x67,
  0x18, 0xAE, 0x64, 0x40, 0x68, 0xD8, 0x89, 0x06, 0x91, 0x79,
  0x91, 0x5D, 0x80, 0xA1, 0x13, 0x56, 0xC4, 0x46, 0xF5, 0x84,
  0x6D, 0x62, 0xC6, 0x28, 0x93, 0x1F, 0xFC, 0xE9, 0xD6, 0xA4,
  0x2F, 0x96, 0x98, 0x40, 0x44, 0x52, 0x85, 0x7E, 0x2F, 0xE5,
  0x7D, 0x33, 0xDF, 0x06, 0x75, 0x51, 0xD1, 0x2B, 0x41, 0x2D,
  0xFC, 0x4A, 0x3B, 0xAE, 0x20, 0x8D, 0x11, 0x93, 0x4E, 0x3B,
  0x2D, 0x60, 0xC3, 0x31, 0xB9, 0xCA, 0x6C, 0xCC, 0x00, 0x00,
  0x00, 0xB9, 0xA7, 0x29, 0x06, 0xFA, 0x30, 0x6E, 0xF0
};

int main() {
	for(int i = 0; i < 0x27; i++){
		printf("%c", data[i]-data[i+0x27]);	
	}

	return 0;
}
