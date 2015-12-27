#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
extern int bitarrayTest();
void testSuite(){
	if(bitarrayTest()) puts("bitarrayTest failed.");
}
