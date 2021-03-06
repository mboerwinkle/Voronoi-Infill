#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

int setVertex(int layer, int ind1, int ind2, int ind3, vertex* target){
	point3d *p1 = &(pointList[ind1]);
	point3d *p2 = &(pointList[ind2]);
	point3d *p3 = &(pointList[ind3]);

	target->parents[0] = p1;
	target->parents[1] = p2;
	target->parents[2] = p3;
	point2d a1, a2, b1, b2;
	if(planeIntersect(layer, *p1, *p2, a1) || planeIntersect(layer, *p2, *p3, b1)) return 0;//two points are on top of each other;
	
	//vectors of bisector
	scalar cvx = -((*p1)[1]-(*p2)[1]);
	scalar cvy = (*p1)[0]-(*p2)[0];

	a2[0] = a1[0]+cvx;
	a2[1] = a1[1]+cvy;

	//vectors of bisector
	cvx = -((*p2)[1]-(*p3)[1]);
	cvy = (*p2)[0]-(*p3)[0];

	b2[0] = b1[0]+cvx;
	b2[1] = b1[1]+cvy;
	//Now, we have four 2d points. these four points express two lines. the intersection of these lines is the vertex of the three 3d points.
	return lineIntersect2d(a1, a2, b1, b2, &(target->loc[0]), &(target->loc[1]));
}
int getSharedParentCount(vertex a, vertex b){
	int ret = 0;
	if(a.parents[0] == b.parents[0] || a.parents[0] == b.parents[1] || a.parents[0] == b.parents[2]) ret++;
	if(a.parents[1] == b.parents[0] || a.parents[1] == b.parents[1] || a.parents[1] == b.parents[2]) ret++;
	if(a.parents[2] == b.parents[0] || a.parents[2] == b.parents[1] || a.parents[2] == b.parents[2]) ret++;
	return ret;
}
