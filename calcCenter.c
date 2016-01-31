#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

vertex **vertexList;
int *vertexCount;
bitarray *pointsPresent;
//returns the index of the step 'count' in a binary separation of [0, max)
extern int sequencer(int count, int max);
//returns the median of the three scalars
extern scalar scalarmed(scalar A, scalar B, scalar C);

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
	for(int count = 0; count < maxz; count+=step){
		//progressBar(((count+1)*20)/(maxz), 20);
		int layer = sequencer(count, maxz);
		vertexList[layer] = (vertex*)malloc(sizeof(vertex));
		vertexCount[layer] = 0;
		int p1, p2, p3, ret;
		for(p1 = 0; p1 < points; p1++){
			for(p2 = p1+1; p2 < points; p2++){
				for(p3 = p2+1; p3 < points; p3++){
					test = &vertexList[layer][vertexCount[layer]];
					ret = setVertex(layer, p1, p2, p3, test);
					if(ret == 0) continue;
					good = 1;
					vertex3deq[0] = test->loc[0];
					vertex3deq[1] = test->loc[1];
					vertex3deq[2] = layer;
					radiussq = scalarmed(distance3dsq(pointList[p1], vertex3deq), distance3dsq(pointList[p2], vertex3deq), distance3dsq(pointList[p3], vertex3deq));
					for(int temp = 0; temp < points; temp++){
						if(temp == p1||temp == p2||temp == p3) continue;
						if(distance3dsq(pointList[temp], vertex3deq) < radiussq){
							good = 0;
							break;
						}
					}
					if(good){
					//	printf("%ld, %ld, %ld\n", distance3dsq(vertex3deq, *test->parents[0]), distance3dsq(vertex3deq, *test->parents[1]), distance3dsq(vertex3deq, *test->parents[2]));
						vertexCount[layer]++;
						vertexList[layer] = (vertex*)realloc(vertexList[layer], sizeof(vertex)*(vertexCount[layer]+1));
					}
				}
			}
		}
		vertexList[layer] = realloc(vertexList[layer], sizeof(vertex)*vertexCount[layer]);

//		printf("%d vertices\n", vertexCount[layer]);
	}
	printf("\n");//for making a newline after the progress bar
}

scalar scalarmed(scalar A, scalar B, scalar C){
	if (A < B) {
		if (B < C) return B;
		return A>C?A:C;
	}
	if (A <= C) return A;
	return B>C?B:C;
}

int sequencer(int count, int max){
/*	for(int pow = 1; pow*2 <= max; pow*=2);//should later do the binary stuff. for now just progresses.
	if(count < pow){
		
	}else{
	}
*/
	return count;
}
