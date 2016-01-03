#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

point2d *bP;
long int bPcount = 8;
point2d insideBounds;
extern void cropNodesLayer(int layer);
extern void insertNodesAtIntersections(node* A, node* B);
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
	for(int x = 0; x < vertexCount[layer]; x++){
		for(int y = 0; y < nodeList[layer][x].sibCount; y++){
			if(isOutside(&nodeList[layer][x], nodeList[layer][x].sibs[y])){
				//dereference each other
			}
		}
	}
}
void insertNodesAtIntersections(node* A, node* B){

	return;
}
int lineSegIntersect2d(point2d a1, point2d a2, point2d b1, point2d b2, scalar* x, scalar* y){

}
