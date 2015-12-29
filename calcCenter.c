#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

vertex **vertexList;
int *vertexCount;
bitarray *pointsPresent;
//returns the index of the step 'count' in a binary separation of [0, max)
extern int sequencer(int count, int max);

void calcCenter(){
	vertexList = calloc(maxz, sizeof(vertex*));
	vertexCount = calloc(maxz, sizeof(int));
	pointsPresent = calloc(maxz, sizeof(bitarray));
	for(int x = 0; x < maxz; x++){
		pointsPresent[x] = genBitarray(points);
	}

//unused for now, will be used once I optimize a bit.	int min, max;//the nearest already generated layers
	vertex *test;
	scalar radiussq;
	int good;
	point3d vertex3deq;
	for(int count = 0; count < maxz; count++){
		int layer = sequencer(count, maxz);
		vertexList[layer] = malloc(sizeof(vertex));
		vertexCount[layer] = 0;
		for(int p1 = 0; p1 < points; p1++){
			for(int p2 = p1+1; p2 < points; p2++){
				for(int p3 = p2+1; p3 < points; p3++){
					test = &vertexList[layer][vertexCount[layer]];
					int ret = setVertex(layer, p1, p2, p3, test);
					puts("got here!");
					if(ret == 0) continue;
					puts("got through!");
					good = 1;
					vertex3deq[0] = test->loc[0];
					vertex3deq[1] = test->loc[1];
					vertex3deq[2] = layer;
					radiussq = distance3dsq(pointList[p1], vertex3deq);
					for(int temp = 0; temp < points; temp++){
						if(temp == p1||temp == p2||temp == p3) continue;
						if(distance3dsq(pointList[temp], vertex3deq) < radiussq){
							good = 0;
							break;
						}
					}
					if(good){
						puts("found a good one!");
						vertexCount[layer]++;
						vertexList[layer] = realloc(vertexList[layer], sizeof(vertex)*(vertexCount[layer]+1));
					}
				}
			}
		}
		vertexList[layer] = realloc(vertexList[layer], sizeof(vertex)*vertexCount[layer]);

		printf("%d vertices\n", vertexCount[layer]);
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
