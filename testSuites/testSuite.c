#include <stdio.h>
#include <stdlib.h>
#include "../globals.h"
extern int bitarrayTest();
extern int distance3dsqTest();
void testSuite(){
	if(bitarrayTest()) puts("bitarrayTest failed.");
	if(distance3dsqTest()) puts("distance3dsqTest failed");
}
