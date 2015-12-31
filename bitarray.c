#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#define BITS 32

bitarray genBitarray(int size){
	return (bitarray) calloc((size+BITS-1)/BITS, sizeof(int));
}
void setBit(bitarray in, int index, int value){
	in[index/BITS] |= 1<<(index%BITS);
}
int getBit(bitarray in, int index){
	return ((in[index/BITS])>>(index%BITS))&1;
}
bitarray ORBitarray(bitarray one, bitarray two, int size){
	bitarray ret = genBitarray(size);
	for(int loc = size/(BITS+1); loc >= 0; loc--){
		ret[loc] = one[loc]|two[loc];
	}
	return ret;
}
char* printBitarray(bitarray in, int size){
	char * ret = calloc(size, sizeof(char));
	for(int x = 0; x < size; x++){
		if(getBit(in, x)) ret[x] = '1';
		else ret[x] = '0';
	}
	return ret;
}
