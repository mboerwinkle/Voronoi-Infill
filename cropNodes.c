#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

point2d *bP;
long int bPcount = 8;
point2d insideBounds;
extern void cropNodesLayer(int layer);
extern void insertNodesAtIntersections(int ind1, int ind2, int layer);
extern int isOutside(node *A, node *B);
extern void midpoint2d(point2d A, point2d B, point2d* ret);
extern int findNodePointer(int targ, node *orig);
extern int lineSegIntersect2dNoRet(point2d a1, point2d a2, point2d b1, point2d b2);
extern int lineSegIntersect2d(point2d a1, point2d a2, point2d b1, point2d b2, point2d* sect/*for inter'sect*/);
void cropNodes(){
	insideBounds[0] = 3000;
	insideBounds[1] = 3000;
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
	int ind1, ind2;
	for(int x = 0; x < vertexCount[layer]; x++){
		printf("lel %d %d\n", x, vertexCount[layer]);
		ind1 = x;//FIXME
		for(int y = 0; y < nodeList[layer][x].sibCount; y++){
			ind2 = nodeList[layer][x].sibs[y];
			if(/*ive never seen this section error... findNodePointer(ind2, &(nodeList[layer][ind1])) == -1 ||*/ findNodePointer(ind1, &(nodeList[layer][ind2])) == -1){
				puts("this is freel");
			};
			insertNodesAtIntersections(ind1, ind2, layer);
		}
	}
	node *other, *this;
	for(int x = 0; x < vertexCount[layer]; x++){
		for(int y = 0; y < nodeList[layer][x].sibCount; y++){
			this = &(nodeList[layer][x]);
			other = &(nodeList[layer][nodeList[layer][x].sibs[y]]);
			if(isOutside(this, other)){
				int index = findNodePointer(x, other);
				if(index == -1) puts("fatal error");
				other->sibs[index] = other->sibs[(other->sibCount)-1];
				other->sibs[(other->sibCount)-1] = -1;
				other->sibCount--;
				this->sibs[y] = this->sibs[(this->sibCount)-1];
				this->sibs[(this->sibCount)-1] = -1;
				this->sibCount--;
				y = 0;//this is because while rearranging the pointers, some would be skipped maybe FIXME
			}
		}
	}
}
void insertNodesAtIntersections(int ind1, int ind2, int layer){
	point2d inter;
	node *new;
	int index;
	for(int count = 0; count+1<bPcount; count+=2){	
		if(lineSegIntersect2d(nodeList[layer][ind1].loc, nodeList[layer][ind2].loc, bP[count], bP[count+1], &inter)){
			vertexCount[layer]++;
			nodeList[layer] = realloc(nodeList[layer], vertexCount[layer]*sizeof(node));//note that node *A and *B are defined after the realloc. I had a bug for a while due to defining before the realloc.
			node* A = &(nodeList[layer][ind1]);
			node* B = &(nodeList[layer][ind2]);
			new = &(nodeList[layer][vertexCount[layer]-1]);
			new->loc[0] = inter[0];
			new->loc[1] = inter[1];
			new->sibCount = 2;
			new->sibs[0] = ind1;
			new->sibs[1] = ind2;
			new->sibs[2] = -1;
			index = findNodePointer(ind2, A);
			if(index == -1) puts("warning 1!");//warning 1 never occurs
			A->sibs[index] = vertexCount[layer]-1;
			index = findNodePointer(ind1, B);
			if(index == -1){
				puts("warning 2!");
			}else{
			//	puts("all good!");
			}
			B->sibs[index] = vertexCount[layer]-1;
			break;
		}
	}
}
int isOutside(node *A, node *B){
	point2d mid;
	int outside = 0;
	midpoint2d(A->loc, B->loc, &mid);
	for(int count = 0; count+1 < bPcount; count+=2){
		if(lineSegIntersect2dNoRet(insideBounds, mid, bP[count], bP[count+1])){
			outside ^= 1;
		}
	}
	return outside;
}
int lineSegIntersect2d(point2d a1, point2d a2, point2d b1, point2d b2, point2d* sect/*for inter'sect*/){
	point2d reta, retb;
	if(!lineIntersect2d(a1, a2, b1, b2, &((*sect)[0]), &((*sect)[1]))) return 0;
	midpoint2d(a1, a2, &reta);
	midpoint2d(b1, b2, &retb);
	if(distance2d(a1, a2)/2<distance2d(reta, *sect)) return 0;
	if(distance2d(b1, b2)/2<distance2d(retb, *sect)) return 0;
	return 1;
}
int lineSegIntersect2dNoRet(point2d a1, point2d a2, point2d b1, point2d b2){
	point2d sect;
	point2d reta, retb;
	if(!lineIntersect2d(a1, a2, b1, b2, &(sect[0]), &(sect[1]))) return 0;
	midpoint2d(a1, a2, &reta);
	midpoint2d(b1, b2, &retb);
	if(distance2d(a1, a2)/2<distance2d(reta, sect)) return 0;
	if(distance2d(b1, b2)/2<distance2d(retb, sect)) return 0;
	return 1;
}
int findNodePointer(int targ, node *orig){
	if(orig->sibs[0] == targ) return 0;
	if(orig->sibs[1] == targ) return 1;
	if(orig->sibs[2] == targ) return 2;
	return -1;
}
void midpoint2d(point2d A, point2d B, point2d* ret){
	(*ret)[0] = (A[0]+B[0])/2;
	(*ret)[1] = (A[1]+B[1])/2;
}
