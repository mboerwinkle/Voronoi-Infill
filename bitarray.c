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
void printBitarray(bitarray in, int size){
	for(int x = 0; x < size; x++){
		if(getBit(in, x)) printf("1");
		else printf("0");
	}
	printf("\n");
}
