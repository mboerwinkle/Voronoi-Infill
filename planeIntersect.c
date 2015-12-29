#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "globals.h"
scalar distance2d(point2d a, point2d b){
	return sqrt((a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1]));
}
scalar distance2dsq(point2d a, point2d b){
	return (a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1]);
}
scalar distance3dsq(point3d a, point3d b){
	return (a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1])+(a[2]-b[2])*(a[2]-b[2]);
//this is to check for overflow. odds are that if overflow is a problem then I would eventually get a distance that was shorter than the difference of one of their coordinates
/*	int xdif = (a[0]-b[0])*(a[0]-b[0]);
	int ydif = (a[1]-b[1])*(a[1]-b[1]);
	int zdif = (a[2]-b[2])*(a[2]-b[2]);
	int ret = xdif+ydif+zdif;
	if(ret < xdif || ret < ydif || ret < zdif) puts("see distance3dsq. Overflow detected");
	return ret;*/
}
scalar radsq(point3d targ, int layer){//cite
	int konstant = maxz+1;
	int zdist = abs(layer-targ[2]);
	return -(zdist-konstant)*(zdist+konstant);//overflow
}
void planeIntersect(int layer, point3d one, point3d two, point2d ret){
	point2d newone = {one[0], one[1]};//thus we gain the 2d projections of our 3d points
	point2d newtwo = {two[0], two[1]};
	
	scalar distABsq = distance2dsq(newone, newtwo);
	scalar unit1 = distABsq+radsq(one, layer)-radsq(two, layer);
	scalar unit2 = 2*distABsq;
	ret[0] = one[0]+((unit1*(two[0]-one[0]))/unit2);
	ret[1] = one[1]+((unit1*(two[1]-one[1]))/unit2);
}

