#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

point2d *bP;
long int bPcount = 8;
point2d insideBounds;
extern void cropNodesLayer(int layer);
extern void insertNodesAtIntersections(node* A, node* B);
extern int isOutside(node *A, node *B);
extern void midpoint2d(point2d A, point2d B, point2d* ret);
extern int findNodePointer(node *targ, node *orig);
extern int lineSegIntersect2d(point2d a1, point2d a2, point2d b1, point2d b2);
void cropNodes(){
	insideBounds[0] = 7000;
	insideBounds[1] = 7000;
	bP = calloc(bPcount, sizeof(point2d));
	bP[0][0] = 2000;
	bP[0][1] = 2000;
	bP[1][0] = 12000;
	bP[1][1] = 2000;
	bP[2][0] = 12000;
	bP[2][1] = 2000;
	bP[3][0] = 12000;
	bP[3][1] = 12000;
	bP[4][0] = 12000;
	bP[4][1] = 12000;
	bP[5][0] = 2000;
	bP[5][1] = 12000;
	bP[6][0] = 2000;
	bP[6][1] = 12000;
	bP[7][0] = 2000;
	bP[7][1] = 2000;
	for(int count = 0; count < maxz; count+=step){
		cropNodesLayer(count);
	}
}
void cropNodesLayer(int layer){
	for(int x = 0; x < vertexCount[layer]; x++){
		for(int y = 0; y < nodeList[layer][x].sibCount; y++){
			insertNodesAtIntersections(&nodeList[layer][x], nodeList[layer][x].sibs[y]);
		}
	}
	node *other, *this;
	for(int x = 0; x < vertexCount[layer]; x++){
		this = &nodeList[layer][x];
		for(int y = 0; y < nodeList[layer][x].sibCount; y++){
			other = nodeList[layer][x].sibs[y];
			if(isOutside(this, other)){
				int index = findNodePointer(this, other);
				if(index == -1) puts("fatal error");
				other->sibs[index] = other->sibs[(other->sibCount)-1];
				other->sibs[(other->sibCount)-1] = NULL;
				other->sibCount--;
				this->sibs[y] = this->sibs[(this->sibCount)-1];
				this->sibs[(this->sibCount)-1] = NULL;
				this->sibCount--;
			}
		}
	}
}
void insertNodesAtIntersections(node* A, node* B){

	return;
}
int isOutside(node *A, node *B){
	point2d mid;
	int outside = 0;
	midpoint2d(A->loc, B->loc, &mid);
	for(int count = 0; count+1 < bPcount; count+=2){
		if(lineSegIntersect2d(insideBounds, mid, bP[count], bP[count+1])){
			outside ^= 1;
		}
	}
	return outside;
}
int lineSegIntersect2d(point2d a1, point2d a2, point2d b1, point2d b2){
	point2d sect;
	point2d reta, retb;
	if(!lineIntersect2d(a1, a2, b1, b2, &(sect[0]), &(sect[1]))) return 0;
	midpoint2d(a1, a2, &reta);
	midpoint2d(b1, b2, &retb);
	if(distance2d(a1, a2)/2<distance2d(reta, sect)) return 0;
	if(distance2d(b1, b2)/2<distance2d(retb, sect)) return 0;
	return 1;
}
int findNodePointer(node *targ, node *orig){
	if(orig->sibs[0] == targ) return 0;
	if(orig->sibs[1] == targ) return 1;
	if(orig->sibs[2] == targ) return 2;
	return -1;
}
void midpoint2d(point2d A, point2d B, point2d* ret){
	(*ret)[0] = (A[0]+B[0])/2;
	(*ret)[1] = (A[1]+B[1])/2;
}
