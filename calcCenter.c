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

	for(int count = 0; count < MAXZ; count++){
		int layer = sequencer(count, MAXZ);

		vertexCount[layer]++;
		vertexList[layer] = realloc(vertexList[layer], vertexCount[layer]);

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
