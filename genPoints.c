#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#define MINDIST 5000//completely arbitrary
extern int placementConflicts(int placedIndex, int testIndex);
void genPoints(){//a simple way for simulating what this function really should do (to be replaced with settling method)
	pointList = calloc(POINTS, sizeof(point3d));
	int quantity[MAXZ];//how many points on each layer
	int pindex = 0;//which point we are setting
	memset(quantity, 0, sizeof(quantity));
	for(int count = 0; count < POINTS; count++){
		quantity[random()%MAXZ]++;
	}
	for(int layer = 0; layer < MAXZ; layer++){
		for(; quantity[layer] > 0; quantity[layer]--){
			int good = 0;
			while(!good){
				good = 1;
				pointList[pindex][0] = random()%MAXX;
				pointList[pindex][1] = random()%MAXY;
				pointList[pindex][2] = layer;
				for(int testIndex = 0; testIndex < pindex; testIndex++){
					if(placementConflicts(pindex, testIndex)){
						good = 0;
						break;
					}
				}
			}
			printf("%d %d %d\n", pointList[pindex][0], pointList[pindex][1], pointList[pindex][2]);
			pindex++;
		}
	}
}
int placementConflicts(int placedIndex, int testIndex){
	int x = pointList[placedIndex][0]-pointList[testIndex][0];
	int y = pointList[placedIndex][1]-pointList[testIndex][1];
	if(x*x+y*y < MINDIST) return 1;
	return 0;
}
