#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
line2d **lineList;
int *lineCount;
//taking ray defined by x, y, and orig, sets ret equal to a line segment that follows the ray and is inside of max. returns 0 on success, returns 1 if ray does not intersect valid field.
int genLineInBounds(line2d* ret, point2d* orig, scalar x, scalar y);
void calcLines(){
	lineList = calloc(maxz, sizeof(line2d*));
	lineCount = calloc(maxz, sizeof(int));
	int layer = 0;
	int i1, i2;
	point3d *p1, *p2;
	point2d mid;
	int ret;
	scalar vx, vy;//the vector direction for the midline
	for(int count = 0; count < maxz; count+=step){
		progressBar(((count+step)*50)/(maxz), 50);
		layer = count;
		lineList[layer] = malloc(sizeof(line2d));
		lineCount[layer] = 0;
		for(i1 = 0; i1 < points; i1++){//getting combinations of indeces.
			for(i2 = i1+1; i2 < points; i2++){
				p1 = &(pointList[i1]);
				p2 = &(pointList[i2]);
				if(planeIntersect(layer, *p1, *p2, mid)){//the two points are on top of each other
					continue;
				}
				vx = -((*p1)[1]-(*p2)[1]);
				vy = (*p1)[0]-(*p2)[0];
				if(genLineInBounds(&(lineList[layer][lineCount]), &mid, vx, vy)){
					continue;
				}
			}
		}
	}
}
int genLineInBounds(line2d* ret, point2d* orig, scalar x, scalar y){
}
