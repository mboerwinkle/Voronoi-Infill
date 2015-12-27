#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

int bitarrayTest(){
	bitarray test = genBitarray(40);
	for(int x = 0; x < 40; x++){
		if(getBit(test, x)) return 1;
	}
	for(int x = 0; x < 40; x+=2){
		setBit(test, x, 2);
	}
	printBitarray(test, 40);
	printf("should be equal to:\n1010101010101010101010101010101010101010\n");
	return 0;
}
