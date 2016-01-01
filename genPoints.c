#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#define MINDIST 50//completely arbitrary
extern int placementConflicts(int placedIndex, int testIndex);
void genPoints(){//a simple way for simulating what this function really should do (to be replaced with settling method)
	pointList = (point3d*)calloc(points, sizeof(point3d));
	int quantity[maxz];//how many points on each layer
	int pindex = 0;//which point we are setting
	memset(quantity, 0, sizeof(quantity));
	for(int count = 0; count < points; count++){
		quantity[random()%maxz]++;
	}
	for(int layer = 0; layer < maxz; layer++){
		for(int tempcount = 0; tempcount < quantity[layer]; tempcount++){
/*			pointList[pindex][0] = (pindex%3)*1000;
			pointList[pindex][1] = (pindex/3)*1000;
			pointList[pindex][2] = 0;*/
			int good = 0;
			while(!good){
				good = 1;
				pointList[pindex][0] = random()%maxx;
				pointList[pindex][1] = random()%maxy;
				pointList[pindex][2] = layer;
				for(int testIndex = 0; testIndex < pindex; testIndex++){
					if(placementConflicts(pindex, testIndex)){
						good = 0;
						break;
					}
				}
			}
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
