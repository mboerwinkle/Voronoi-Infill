#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "globals.h"
point3d *pointList;
int maxx, maxy, maxz, points;
extern void testSuite();
int main(int argc, char *argv[]){
	if(argc == 2 && 0 == strcmp("-t", argv[1])){
		testSuite();
		return 0;
	}
	if(argc != 5){
		puts("invalid format: \"./run maxx maxy maxz points\"");
		return 1;
	}
	maxx = atoi(argv[1]);
	maxy = atoi(argv[2]);
	maxz = atoi(argv[3]);
	points = atoi(argv[4]);
	printf(" maxx:%d\n maxy:%d\n maxz:%d\n points:%d\n", maxx, maxy, maxz, points);
	srandom(time(NULL));
//cool! how nice! this code is nicely divided into three parts:
//generate the starting points
//go through and generate the voronoi diagram
//and do whatever you want to do with the voronoi diagram! (in this case, display it!)
	genPoints();
	calcCenter();	
	display();
	return 0;
}
