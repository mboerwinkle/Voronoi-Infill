#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "globals.h"
point3d *pointList;
int maxx, maxy, maxz, points, step, distpoints;
extern void testSuite();
int main(int argc, char *argv[]){
	if(argc == 2 && 0 == strcmp("-t", argv[1])){
		testSuite();
		return 0;
	}
	if(argc != 6){
		puts("invalid format: \"./run maxx maxy maxz distpoints step\"");
		return 1;
	}
	maxx = atoi(argv[1]);
	maxy = atoi(argv[2]);
	maxz = atoi(argv[3]);
	distpoints = atoi(argv[4]);
	step = atoi(argv[5]);
	printf(" maxx:%d\n maxy:%d\n maxz:%d\n distpoints:%d\n", maxx, maxy, maxz, distpoints);
//	puts("use epoch seed? y/n");
//	char resp;
//	int seed;
//	scanf("%c", &resp);
//	if(resp == 'n'){
//		puts("specify seed");
//		scanf("%d", &seed);
//	}else{
//		seed = time(NULL);
//	}
//	srandom(seed);
//	printf("seed: %d\n", seed);	//not needed if deterministic!
	genPoints();//initial point placement
	calcLines();//generate lines between all possible points
	genNodes();//generate the nodes based on line endpoints
//	cropNodes();//cut out nodes that are out of bounds
	genPath();//make gcode for the print
	display();
	return 0;
}
