#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

vertex **vertexList;
int *vertexCount;
bitarray *pointsPresent;
//returns the index of the step 'count' in a binary separation of [0, max)
extern int sequencer(int count, int max);

void calcCenter(){
	vertexList = calloc(MAXZ, sizeof(vertex*));
	vertexCount = calloc(MAXZ, sizeof(int));
	pointsPresent = calloc(MAXZ, sizeof(bitarray));
	for(int x = 0; x < MAXZ; x++){
		pointsPresent[x] = genBitarray(POINTS);
	}

//unused for now, will be used once I optimize a bit.	int min, max;//the nearest already generated layers
	vertex *test;
	for(int count = 0; count < MAXZ; count++){
		int layer = sequencer(count, MAXZ);
		vertexList[layer] = malloc(sizeof(vertex));
		vertexCount[layer] = 1;
		for(int p1 = 0; p1 < POINTS; p1++){
			for(int p2 = p1+1; p2 < POINTS; p2++){
				for(int p3 = p2+1; p3 < POINTS; p3++){
					test = &vertexList[layer][vertexCount[layer]-1];
					setVertex(layer, p1, p2, p3, test);
					if(isGoodVertex(layer, *test)){
						vertexCount[layer]++;
						vertexList[layer] = realloc(vertexList[layer], sizeof(vertex)*vertexCount[layer]);
					}
				}
			}
		}
		vertexCount[layer]--;
		vertexList[layer] = realloc(vertexList[layer], sizeof(vertex)*vertexCount[layer]);

	}
}

int sequencer(int count, int max){
/*	for(int pow = 1; pow*2 <= max; pow*=2);//should later do the binary stuff. for now just progresses.
	if(count < pow){
		
	}else{
	}
*/
return count;
}
