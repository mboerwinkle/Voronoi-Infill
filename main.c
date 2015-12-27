#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "globals.h"
point3d *pointList;
extern void testSuite();
int main(int argc, char *argv[]){
	if(argc == 2 && 0 == strcmp("-t", argv[1])){
		testSuite();
		return 0;
	}
	srandom(time(NULL));
	genPoints();
	calcCenter();	
	return 0;
}
