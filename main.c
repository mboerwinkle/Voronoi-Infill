#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"
point3d *pointList;
int main(){
	srandom(time(NULL));
	genPoints();
	calcCenter();	
	return 0;
}
