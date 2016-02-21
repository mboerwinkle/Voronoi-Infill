#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
line2d **lineList;
int *lineCount;
//taking line defined by a and b, sets ret equal to a line segment that follows the line and is inside of max. returns 0 on success, returns 1 if ray does not intersect valid field.
extern int genLineInBounds(line2d* ret, point2d orig, scalar x, scalar y);
bitarray closedPoints;
bitarray currentPoints;
void calcLines(){
	closedPoints = genBitarray(points);
	bitarray lastLayer = NULL;
	lineList = calloc(maxz, sizeof(line2d*));
	lineCount = calloc(maxz, sizeof(int));
	int layer = 0;
	int i1, i2;
	point3d *p1, *p2;
	point2d mid;
	scalar vx, vy;
	for(int count = 0; count < maxz; count+=step){
		progressBar(count, maxz);
		layer = count;
		lineList[layer] = malloc(sizeof(line2d));
		lineCount[layer] = 0;
		for(i1 = 0; i1 < points; i1++){//getting combinations of indeces.
			if(getBit(closedPoints, i1)) continue;
			for(i2 = i1+1; i2 < points; i2++){
				if(getBit(closedPoints, i2)) continue;
				p1 = &(pointList[i1]);
				p2 = &(pointList[i2]);
				if(planeIntersect(layer, *p1, *p2, mid)){//the two points are on top of each other
					continue;
				}
				lineList[layer][lineCount[layer]].parents[0] = i1;
				lineList[layer][lineCount[layer]].parents[1] = i2;
				vx = -((*p1)[1]-(*p2)[1]);
				vy = (*p1)[0]-(*p2)[0];
				if(genLineInBounds(&(lineList[layer][lineCount[layer]]), mid, vx, vy)){
					continue;
				}
				lineCount[layer]++;
//				printf("%d lines\n", lineCount[layer]);
				lineList[layer] = realloc(lineList[layer], sizeof(line2d)*(lineCount[layer]+1));
			}
		}
		lineList[layer] = realloc(lineList[layer], sizeof(line2d)*lineCount[layer]);
		cropLines(layer);
		if(lastLayer != NULL){
			for(int x = 0; x < points; x++){
				if(getBit(lastLayer, x) && !getBit(currentPoints, x)){
					setBit(closedPoints, x, 1);
				}
			}
			free(lastLayer);
		}
		lastLayer = currentPoints;
	}
	printf("\n");//needed after the progress bar
}
int genLineInBounds(line2d* ret, point2d orig, scalar x, scalar y){
	scalar leftY, rightY;
	if(abs(x) < abs(y)){//angle too steep, rotate everything! 90deg clockwise
		scalar temp;
		temp = orig[0];//rotate origin
		orig[0] = orig[1];
		orig[1] = -temp;

		temp = x;//rotate direction
		x = y;
		y = -temp;

		leftY = orig[1]+((y*(-orig[0]))/x);
		rightY = orig[1]+((y*((maxy-1)-orig[0]))/x);
		if((leftY > 0 && rightY > 0) || (leftY <= -maxx && rightY <= -maxx)){//line is completely too low or high
			return 1;
		}

		//Find left side intersection
		if(leftY <= -maxx){//line intersects with bottom on left side
			ret->end[0][0] = orig[0]+((x*((-maxx+1)-orig[1]))/y);
			ret->end[0][1] = -maxx+1;
		}else if(leftY > 0){//line intersects with top on left side
			ret->end[0][0] = orig[0]+((x*(-orig[1]))/y);
			ret->end[0][1] = 0;
		}else{//line intersects on left wall, like it's supposed to!
			ret->end[0][0] = 0;
			ret->end[0][1] = leftY;
		}
		//Find right side intersection
		if(rightY <= -maxx){//line intersects with bottom on right side
			ret->end[1][0] = orig[0]+((x*((-maxy+1)-orig[1]))/y);
			ret->end[1][1] = -maxx+1;
		}else if(rightY > 0){//line intersects with top on right side
			ret->end[1][0] = orig[0]+((x*(-orig[1]))/y);
			ret->end[1][1] = 0;
		}else{//line intersects on right wall, like it's supposed to!
			ret->end[1][0] = maxy-1;
			ret->end[1][1] = rightY;
		}
		temp = ret->end[0][1];//rotating back coords
		ret->end[0][1] = ret->end[0][0];
		ret->end[0][0] = -temp;
		temp = ret->end[1][1];//rotating back coords
		ret->end[1][1] = ret->end[1][0];
		ret->end[1][0] = -temp;
	}else{//this case is much easier to understand than the rotated case.
		leftY = orig[1]+((y*(-orig[0]))/x);
		rightY = orig[1]+((y*((maxx-1)-orig[0]))/x);
		if((leftY < 0 && rightY < 0) || (leftY >= maxy && rightY >= maxy)){//line is completely too low or high
			return 1;
		}
		//Find left side intersection
		if(leftY >= maxy){//line intersects with top on left side
			ret->end[0][0] = orig[0]+((x*((maxy-1)-orig[1]))/y);
			ret->end[0][1] = maxy-1;
		}else if(leftY < 0){//line intersects with bottom on left side
			ret->end[0][0] = orig[0]+((x*(-orig[1]))/y);
			ret->end[0][1] = 0;
		}else{//line intersects on left wall, like it's supposed to!
			ret->end[0][0] = 0;
			ret->end[0][1] = leftY;
		}
		//Find right side intersection
		if(rightY >= maxy){//line intersects with top on right side
			ret->end[1][0] = orig[0]+((x*((maxy-1)-orig[1]))/y);
			ret->end[1][1] = maxy-1;
		}else if(rightY < 0){//line intersects with bottom on right side
			ret->end[1][0] = orig[0]+((x*(-orig[1]))/y);
			ret->end[1][1] = 0;
		}else{//line intersects on right wall, like it's supposed to!
			ret->end[1][0] = maxx-1;
			ret->end[1][1] = rightY;
		}
	}
	return 0;
}
