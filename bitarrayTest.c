#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"

int bitarrayTest(){
	bitarray test = genBitarray(40);
	for(int x = 0; x < 40; x++){
		if(getBit(test, x)) return 1;
	}
	for(int x = 0; x < 40; x+=2){
		setBit(test, x, 2);
	}
	char * ret = printBitarray(test, 40);
	if(strncmp(ret, "1010101010101010101010101010101010101010", 40) != 0) return 1;
	free(ret);
	return 0;
}
