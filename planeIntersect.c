#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "globals.h"
#define KONSTANT (MAXZ+1)
scalar distance2d(point2d a, point2d b){
	return sqrt((a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1]));
}
scalar distance3dsq(point3d a, point3d b){
	return (a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1])+(a[2]-b[2])*(a[2]-b[2]);
}
scalar radsq(point3d targ, int layer){//cite
	int zdist = abs(layer-targ[2]);
	return -(zdist-KONSTANT)*(zdist+KONSTANT);//overflow
}
void planeIntersect(int layer, point3d one, point3d two, point2d ret){
	point2d newone = {one[0], one[1]};//thus we gain the 2d projections of our 3d points
	point2d newtwo = {two[0], two[1]};
	
	scalar dist = distance2d(newone, newtwo);
	scalar len = (dist*dist+radsq(one, layer)-radsq(two, layer))/(2*dist);
	ret[0] = one[0]+((len/dist)*(two[0]-one[0]));
	ret[1] = one[1]+((len/dist)*(two[1]-one[1]));
}

