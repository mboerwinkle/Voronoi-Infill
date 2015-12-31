#include <stdio.h>
#include <stdlib.h>
#include "../globals.h"
extern int bitarrayTest();
extern int planeIntersectTest();
void testSuite(){
	if(bitarrayTest()) puts("bitarrayTest failed.");
	if(planeIntersectTest()) puts("planeIntersectTest failed");
}
