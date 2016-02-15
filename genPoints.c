#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "globals.h"
//#define MINDIST 200000//completely arbitrary
//extern int placementConflicts(int placedIndex, int testIndex);
/*void genPoints(){//a simple way for simulating what this function really should do (to be replaced with settling method)
	pointList = (point3d*)calloc(points, sizeof(point3d));
	int quantity[maxz];//how many points on each layer
	int pindex = 0;//which point we are setting
	memset(quantity, 0, sizeof(quantity));
	for(int count = 0; count < points; count++){
		quantity[random()%maxz]++;
	}
	for(int layer = 0; layer < maxz; layer++){
		for(int tempcount = 0; tempcount < quantity[layer]; tempcount++){
			int good = 0;
			while(!good){
				good = 1;
				pointList[pindex][0] = random()%maxx;
				pointList[pindex][1] = random()%maxy;
				pointList[pindex][2] = layer;
				for(int testIndex = 0; testIndex < pindex; testIndex++){
					if(placementConflicts(pindex, testIndex)){
						good = 0;
		//				break;
					}
				}
			}
			pindex++;
		}
	}
}
int placementConflicts(int placedIndex, int testIndex){
	scalar x = pointList[placedIndex][0]-pointList[testIndex][0];
	scalar y = pointList[placedIndex][1]-pointList[testIndex][1];
	if(x*x+y*y < MINDIST) return 1;
	return 0;
}*/
/*
#include <time.h>
void genPoints(){//random point placement
	srandom(time(NULL));
	points = 150;
	pointList = (point3d*)calloc(points, sizeof(point3d));
	for(int count = 0; count < points; count++){
		pointList[count][0] = random()%maxx;
		pointList[count][1] = random()%maxy;
		pointList[count][2] = random()%maxz;
	}
}
*/
extern void pushPoints(scalar x, scalar y, double strength);
#define UP 0.577//ratio of distpoints to height to go up each z step rn for 45 degree angle
#define SIN 0.866//height of a triangle
void genPoints(){
	points = 0;
	scalar x, y, z;
	int yoffsetStart = 0, yoffset = 0;
	pointList = (point3d*)calloc(1, sizeof(point3d));
	for(z = 0; z < maxz; z+=UP*distpoints){
		if(yoffsetStart == 0){
			yoffsetStart = (int)(distpoints*UP);
		}else yoffsetStart = 0;
		yoffset = yoffsetStart;
		for(x = 0; x < maxx; x+=distpoints/2){
			for(y = yoffset; y < maxy; y+=2*distpoints*SIN){
				points++;
				pointList = (point3d*)realloc(pointList, points*sizeof(point3d));
				pointList[points-1][0] = x;
				pointList[points-1][1] = y;
				pointList[points-1][2] = z;
			}
			if(yoffset == yoffsetStart){
			yoffset = yoffsetStart+(int)(SIN*distpoints);
			}else yoffset = yoffsetStart;
		}
	}
	pushPoints(maxx/2, maxy/2, 250);
	printf("points: %d\n", points);
}
void pushPoints(scalar x, scalar y, double strength){
	scalar vx, vy;
	point2d center = {x, y};
	point2d pnt;
	double newDist;
	double distMult;
	double oldDist;
	for(int temp = 0; temp < points; temp++){
		pnt[0] = pointList[temp][0];
		pnt[1] = pointList[temp][1];
		oldDist = distance2d(pnt, center);
		distMult = -1/((oldDist/strength)+1)+1;
		newDist = distMult*oldDist;
		vx = (newDist*(pnt[0]-x))/oldDist;
		vy = (newDist*(pnt[1]-y))/oldDist;
		pointList[temp][0] = x+vx;
		pointList[temp][1] = y+vy;
	}
}
