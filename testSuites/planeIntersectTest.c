#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../globals.h"

int planeIntersectTest(){
	maxz = 10000;
	point3d one = {100, 200, 40};
	point3d two = {200, 400, 20};
	point2d ret;
	planeIntersect(30, one, two, ret);
	if(ret[0] != 150||ret[1] != 300) return 1;
	
	point3d three = {100, 200, 40};
	point3d four = {100, 100, 20};
	planeIntersect(20, three, four, ret);
	printf("%ld %ld\n", ret[0], ret[1]);
	return 0;
}
