#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "globals.h"
scalar distance2d(point2d a, point2d b){
	//return sqrt((a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1]));
	scalar ret = (a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1]);

	if(ret < abs(a[0]-b[0]) || ret < abs(a[1]-b[1])){
		printf("overflow in distance2d %ld %ld, %ld %ld\n", a[0], a[1], b[0], b[1]);//overflow detected
		
	}
	return sqrt(ret);
}
scalar distance2dsq(point2d a, point2d b){
//	return (a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1]);
	scalar ret = (a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1]);

	if(ret < abs(a[0]-b[0]) || ret < abs(a[1]-b[1])) puts("overflow in distance2d (planeintersect.c)");//overflow detected
	return ret;
}
scalar distance3dsq(point3d a, point3d b){
	//return (a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1])+(a[2]-b[2])*(a[2]-b[2]);
//this is to check for overflow. odds are that if overflow is a problem then I would eventually get a distance that was shorter than the difference of one of their coordinates
	scalar ret = (a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1])+(a[2]-b[2])*(a[2]-b[2]);

	if(ret < abs(a[0]-b[0]) || ret < abs(a[1]-b[1]) || ret < abs(a[2]-b[2])){
		printf("overflow in distance3dsq %ld %ld %ld, %ld %ld %ld\n", a[0], a[1], a[2], b[0], b[1], b[2]);//overflow detected
	}
	return ret;
}
scalar radsq(point3d targ, int layer){//cite
	int konstant = maxz+1;
	int zdist = abs(layer-targ[2]);
	return -(zdist-konstant)*(zdist+konstant);//overflow
}
int planeIntersect(int layer, point3d one, point3d two, point2d ret){
	point2d newone = {one[0], one[1]};//thus we gain the 2d projections of our 3d points
	point2d newtwo = {two[0], two[1]};
	
	scalar distABsq = distance2dsq(newone, newtwo);
	if(distABsq == 0) return 1; //the points are on top of each other (error)
	scalar unit1 = distABsq+radsq(one, layer)-radsq(two, layer);
	scalar unit2 = 2*distABsq;
	ret[0] = one[0]+((unit1*(two[0]-one[0]))/unit2);
	ret[1] = one[1]+((unit1*(two[1]-one[1]))/unit2);
	return 0;
}
