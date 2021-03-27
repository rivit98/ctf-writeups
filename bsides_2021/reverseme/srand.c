#include <stdio.h>
#include <stdlib.h>


int main(){

	srand(0x13371337u);
	for(int i = 0; i < 1024; i++){
		printf("%d ", rand() >> 3);
	}

}
