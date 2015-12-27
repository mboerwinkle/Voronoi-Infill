#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#define ASCIIX 200
#define ASCIIY 60
void display(){
	int div;
	puts("print layers divisible by what number?");
	scanf("%d", &div);
	for(int layer = 0; layer < maxz; layer+=div){
		getchar();
		layer_to_ascii(layer);
	}
}
void layer_to_ascii(int layer){
	bitarray loc = genBitarray(ASCIIX*ASCIIY);
	int x, y;
	for(int temp = 0; temp < vertexCount[layer]; temp++){
		puts("hi");
		x = vertexList[layer][temp].loc[0]/(maxx/ASCIIX-1);
		y = vertexList[layer][temp].loc[1]/(maxy/ASCIIY-1);
		setBit(loc, x+y*ASCIIX, 1);
	}
	for(int ycycle = 0; ycycle < ASCIIY; ycycle++){
		for(int xcycle = 0; xcycle < ASCIIX; xcycle++){
			if(getBit(loc, xcycle+ycycle*ASCIIX)){
				printf("0");
			}else printf(".");
		}
		printf("\n");
	}
	free(loc);
}
