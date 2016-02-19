//THANKS: line "y--;" used to say "y = 0;", caused problems when y was already equal to 0. bug detected by Simon Boerwinkle
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

point2d *bP;
long int bPcount = 16;
point2d insideBounds;
extern void cropNodesLayer(int layer);
extern void insertNodesAtIntersections(int ind1, int ind2, int layer);
extern int isOutside(node *A, node *B);
//extern int findNodePointer(int targ, node *orig);
extern int lineSegIntersect2dNoRet(point2d a1, point2d a2, point2d b1, point2d b2);
extern point2d* intersectsBound(point2d A, point2d B, int* howmany);
extern void sortPointList(point2d start, point2d* inter, int size);
void cropNodes(){
	insideBounds[0] = 6000;
	insideBounds[1] = 7100;
	bP = calloc(bPcount, sizeof(point2d));
	bP[0][0] = 12000;
	bP[0][1] = 7000;

	bP[1][0] = 10536;
	bP[1][1] = 3464;
	bP[2][0] = 10536;
	bP[2][1] = 3464;

	bP[3][0] = 7000;
	bP[3][1] = 2000;
	bP[4][0] = 7000;
	bP[4][1] = 2000;

	bP[5][0] = 3464;
	bP[5][1] = 3464;
	bP[6][0] = 3464;
	bP[6][1] = 3464;

	bP[7][0] = 2000;
	bP[7][1] = 7000;
	bP[8][0] = 2000;
	bP[8][1] = 7000;

	bP[9][0] = 3464;
	bP[9][1] = 10536;
	bP[10][0] = 3464;
	bP[10][1] = 10536;

	bP[11][0] = 7000;
	bP[11][1] = 12000;
	bP[12][0] = 7000;
	bP[12][1] = 12000;

	bP[13][0] = 10536;
	bP[13][1] = 10536;
	bP[14][0] = 10536;
	bP[14][1] = 10536;

	bP[15][0] = 12000;
	bP[15][1] = 7000;
/*triangle
	bP[8][0] = 8000;
	bP[8][1] = 2000;
	bP[9][0] = 8000;
	bP[9][1] = 12000;
	bP[10][0] = 8000;
	bP[10][1] = 12000;
	bP[11][0] = 12000;
	bP[11][1] = 7000;
	bP[12][0] = 12000;
	bP[12][1] = 7000;
	bP[13][0] = 8000;
	bP[13][1] = 2000;
*/
	for(int count = 0; count < maxz; count+=step){
		cropNodesLayer(count);
	}
}
void cropNodesLayer(int layer){
	int ind1, ind2;
	int vertexCountOrig = vertexCount[layer];
	for(int x = 0; x < vertexCountOrig; x++){
//		printf("lel %d %d\n", x, vertexCount[layer]);
		ind1 = x;//FIXME
		for(int y = x+1; y < vertexCountOrig; y++){
			ind2 = y;
			if(findNodePointer(ind2, &(nodeList[layer][ind1])) == -1 || findNodePointer(ind1, &(nodeList[layer][ind2])) == -1) continue;
			insertNodesAtIntersections(ind1, ind2, layer);
		}
	}
	node *other, *this;
	for(int x = 0; x < vertexCount[layer]; x++){
		for(int y = 0; y < nodeList[layer][x].sibCount; y++){
			this = &(nodeList[layer][x]);
			other = &(nodeList[layer][this->sibs[y]]);
			if(isOutside(this, other)){
				int index = findNodePointer(x, other);
				if(index == -1) puts("fatal error");
				other->sibs[index] = other->sibs[(other->sibCount)-1];
				other->sibs[(other->sibCount)-1] = -1;
				other->sibCount--;
				this->sibs[y] = this->sibs[(this->sibCount)-1];
				this->sibs[(this->sibCount)-1] = -1;
				this->sibCount--;
				y--;//this is because while rearranging the pointers, some would be skipped maybe
			}
		}
	}
}
void insertNodesAtIntersections(int ind1, int ind2, int layer){
//	puts("begun insert func");
	node *new;
	point2d* inter;
	int index;
	node *A, *B;
	int howmany;
	inter = intersectsBound(nodeList[layer][ind1].loc, nodeList[layer][ind2].loc, &howmany);
//	puts("first step done!");
	nodeList[layer] = realloc(nodeList[layer], (vertexCount[layer]+howmany)*sizeof(node));//note that node *A and *B are defined after the realloc. I had a bug for a while due to defining before the realloc.
	for(int which = 0; which < howmany; which++){
		vertexCount[layer]++;
		A = &(nodeList[layer][ind1]);
		B = &(nodeList[layer][ind2]);
		new = &(nodeList[layer][vertexCount[layer]-1]);
		new->loc[0] = inter[which][0];
		new->loc[1] = inter[which][1];
		new->sibCount = 2;
		new->sibs[0] = ind1;
		new->sibs[1] = ind2;
		new->sibs[2] = -1;
		index = findNodePointer(ind2, A);
		if(index == -1) puts("warning 1!");//warning 1 never occurs
		A->sibs[index] = vertexCount[layer]-1;
		index = findNodePointer(ind1, B);
		if(index == -1)	puts("warning 2!");
		B->sibs[index] = vertexCount[layer]-1;
		ind2 = vertexCount[layer]-1;
	}
	free(inter);
//	puts("ended insert func");
}
point2d* intersectsBound(point2d A, point2d B, int* howmany){
	point2d* ret = malloc(sizeof(point2d));
	*howmany = 0;
	for(int count = 0; count+1<bPcount; count+=2){
		//puts("realloced once");
		if(lineSegIntersect2d(A, B, bP[count], bP[count+1], &(ret[(*howmany)]))){
			(*howmany)++;
			ret = realloc(ret, ((*howmany)+1)*sizeof(point2d));
		}
	}
	sortPointList(B, ret, *howmany);
	return ret;
}
int isOutside(node *A, node *B){
	point2d mid;
	int outside = 0;
	midpoint2d(A->loc, B->loc, &mid);
	for(int count = 0; count+1 < bPcount; count+=2){
		if(lineSegIntersect2dNoRet(insideBounds, mid, bP[count], bP[count+1])){
			outside |= 1;//FIXME changed to or instead of xor (^) to temporarily work around the problem of intersecting twice when the line segment crosses a vertex of the border
		}
	}
	return outside;
}
void sortPointList(point2d start, point2d* inter, int size){//sorts list of points in order of distance away from current first point.
	//insertion (old way)
	for(int temp = 1; temp < size; temp++){
		for(int loc = temp; loc > 0; loc--){
			if(distance2d(start, inter[loc]) < distance2d(start, inter[loc-1])){
				scalar x = inter[loc][0];
				scalar y = inter[loc][1];
				inter[loc][0] = inter[loc-1][0];
				inter[loc][1] = inter[loc-1][1];
				inter[loc-1][0] = x;
				inter[loc-1][1] = y;
			}else break;
		}
	}
	//sorted by coordinate with the most difference (new way)
/*	int loc, temp;
	scalar x, y;
	int w = 0;//specifies which dimension to use for comparisons (x by default
	//if(abs(start[0]-inter[0][0]) < abs(start[1]-inter[0][1])){//y coord difference is more important, sort by that
	if(abs(start[0]-inter[size-1][0]) < abs(start[1]-inter[size-1][1])){//y coord difference is more important, sort by that
		w = 1;
	}
	for(temp = 1; temp < size; temp++){
		for(loc = temp; loc > 0; loc--){
			if(abs(start[w] - inter[loc][w]) < abs(start[w] - inter[loc-1][w])){
				x = inter[loc][0];
				y = inter[loc][1];
				inter[loc][0] = inter[loc-1][0];
				inter[loc][1] = inter[loc-1][1];
				inter[loc-1][0] = x;
				inter[loc-1][1] = y;
			}else break;
		}
	}*/
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
	for(int x = 0; x < orig->sibCount; x++){
		if(orig->sibs[x] == targ) return x;
	}
	return -1;
}
void midpoint2d(point2d A, point2d B, point2d* ret){
	(*ret)[0] = (A[0]+B[0])/2;
	(*ret)[1] = (A[1]+B[1])/2;
}
