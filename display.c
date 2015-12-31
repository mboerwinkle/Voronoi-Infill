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
	scalar x, y, origx, origy;
	for(int temp = 0; temp < vertexCount[layer]; temp++){
		origx = vertexList[layer][temp].loc[0];
		origy = vertexList[layer][temp].loc[1];
		if(origx < 0 || origx >= maxx || origy < 0 || origy >= maxy) continue;
		x = (origx*(ASCIIX-1))/maxx;
		y = (origy*(ASCIIY-1))/maxy;
		int index = x+y*ASCIIX;
		if(index >= ASCIIX*ASCIIY) puts("goteem");
		setBit(loc, index, 1);
	}
	for(int ycycle = 0; ycycle < ASCIIY; ycycle++){
		for(int xcycle = 0; xcycle < ASCIIX; xcycle++){
			if(getBit(loc, xcycle+ycycle*ASCIIX)){
				printf("O");
			}else printf("-");
		}
		printf("\n");
	}
	free(loc);
}
