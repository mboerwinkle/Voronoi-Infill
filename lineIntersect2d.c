#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
int lineIntersect2d(point2d A, point2d B, point2d C, point2d D, scalar *X, scalar *Y){//from wikipedia article on line-line intersections
	scalar den = (A[0]-B[0])*(C[1]-D[1])-(A[1]-B[1])*(C[0]-D[0]);
	if(den == 0){
//		puts("den is 0");
		return 0;
	}
	if(X!=NULL) *X = ((A[0]*B[1]-A[1]*B[0])*(C[0]-D[0])-(A[0]-B[0])*(C[0]*D[1]-C[1]*D[0]))/den;
	if(Y!=NULL) *Y = ((A[0]*B[1]-A[1]*B[0])*(C[1]-D[1])-(A[1]-B[1])*(C[0]*D[1]-C[1]*D[0]))/den;
	return 1;
}
