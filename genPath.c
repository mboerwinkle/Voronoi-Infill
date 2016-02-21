#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#define HEIGHT 750//these either
#define WIDTH 750
#define SCALE 0.25
#define EXTRUSION_CONSTANT 0.0282//mm filament extruded per mm moved
#define HEAD_STEP 0.2//amount to raise head every layer
extern int getNextClosest(int layer, point2d currPos, int *closest);//returns 1 if connections still need to be made, puts index of closest node to currPos into closest
long int E = 0;

typedef struct pathLoc{
	struct pathLoc *prev;
	int index;
}pathLoc;
pathLoc *locStack;//this is a stack of locations, useful for retracing your steps as you complete things

void addToLocStack(int val){
	pathLoc *temp = locStack;
	locStack = malloc(sizeof(pathLoc));
	locStack->index = val;
	locStack->prev = temp;
}
int regressLocStack(){
	pathLoc *old = locStack;
	locStack = locStack->prev;
	free(old);
	if(locStack != NULL)return locStack->index;
	return -1;
}
int locStackHasNoBranches(int layer){
	pathLoc *temp = locStack;
	while(temp != NULL){
		if(nodeList[layer][temp->index].sibCount > 0) return 0;
		temp = temp->prev;
	}
	return 1;
}
void freeLocStack(){
	pathLoc *temp = locStack;
	while(locStack != NULL){
		temp = locStack->prev;
		free(locStack);
		locStack = temp;
	}
}

void genPath(){
	point2d head = {0, 0};
	node* nodeLayer;
	double headHeight = 0;
	FILE *wfp = fopen("output.gcode", "w");//write file pointer
	int index, oldIndex, connectionIndex;
	for(int layer = 0; layer < maxz; layer+=step){
		nodeLayer = nodeList[layer];
		headHeight+=HEAD_STEP;
		while(getNextClosest(layer, head, &index)){
			locStack = NULL;
			//print out gcode to move to new location without extruding


			fprintf(wfp, "G01 F6000\nG01 X%.3lf Y%.3lf Z%.3lf\nG01 F1800\n", ((double)nodeLayer[index].loc[0])/100*SCALE, ((double)nodeLayer[index].loc[1])/100*SCALE, headHeight);

			addToLocStack(index);
			while(1){
				if(nodeLayer[index].sibCount < 1){//regress to last position
					if(locStackHasNoBranches(layer)){//if there's nothing more to print, then don't bother bringing the nozzle back to the beginning
						freeLocStack();
						head[0] = nodeLayer[index].loc[0];//record the current pos so that a closest point can be found
						head[1] = nodeLayer[index].loc[1];
						break;
					}else{
						index = regressLocStack();
						//print out gcode to move to new location without extruding
						fprintf(wfp, "G01 F6000\nG01 X%.3lf Y%.3lf Z%.3lf\nG01 F1800\n", ((double)nodeLayer[index].loc[0])/100*SCALE, ((double)nodeLayer[index].loc[1])/100*SCALE, headHeight);
					}
				}else{
					oldIndex = index;
					//print out gcode to move to new location while extruding

					//deleting connection between nodes
					index = nodeLayer[index].sibs[nodeLayer[index].sibCount-1];
					nodeLayer[oldIndex].sibs[nodeLayer[oldIndex].sibCount-1] = -1;
					nodeLayer[oldIndex].sibCount--;
					connectionIndex = findNodePointer(oldIndex, &(nodeLayer[index]));
					if(connectionIndex == -1){
						printf("invalid connections. layer: %d\nTag <here> inserted in gcode\n", layer);
						fprintf(wfp, "<here>\n");
					}
					nodeLayer[index].sibs[connectionIndex] = nodeLayer[index].sibs[nodeLayer[index].sibCount-1];
					nodeLayer[index].sibs[nodeLayer[index].sibCount-1] = -1;
					nodeLayer[index].sibCount--;
					if(oldIndex == index) puts("well, it is referencing itself!");
					addToLocStack(index);
					//
					//FIXME here, I am checking for any repeat references between these two nodes and destroying them. this should be avoided in combineNodes
					while(1){
						connectionIndex = findNodePointer(oldIndex, &(nodeLayer[index]));
						if(connectionIndex == -1) break;
						puts("avoided");
						nodeLayer[index].sibs[connectionIndex] = nodeLayer[index].sibs[nodeLayer[index].sibCount-1];
						nodeLayer[index].sibs[nodeLayer[index].sibCount-1] = -1;
						nodeLayer[index].sibCount--;
					}
					while(1){
						connectionIndex = findNodePointer(index, &(nodeLayer[oldIndex]));
						if(connectionIndex == -1) break;
						puts("avoided");
						nodeLayer[oldIndex].sibs[connectionIndex] = nodeLayer[oldIndex].sibs[nodeLayer[oldIndex].sibCount-1];
						nodeLayer[oldIndex].sibs[nodeLayer[oldIndex].sibCount-1] = -1;
						nodeLayer[oldIndex].sibCount--;
					}
					//
					head[0] = nodeLayer[index].loc[0];
					head[1] = nodeLayer[index].loc[1];

					E += distance2d(head, nodeLayer[oldIndex].loc);
					fprintf(wfp, "G01 X%.3lf Y%.3lf Z%.3lf E%.4lf\n", ((double)head[0])/100*SCALE, ((double)head[1])/100*SCALE, headHeight, ((double)E)/100*EXTRUSION_CONSTANT*SCALE);
				}
			}
		}
	}
	fclose(wfp);
}

int getNextClosest(int layer, point2d currPos, int *closest){//I use a point2d instead of an index because I want this to work across layers
	int foundYet = 0;
	scalar minDist = 0;
	scalar newDist;
	node *testNode;
	for(int count = 0; count < nodeCount[layer]; count++){
		testNode = &nodeList[layer][count];
		if(testNode->sibCount < 1) continue;
		newDist = distance2dsq(nodeList[layer][count].loc, currPos);
		if(newDist < minDist || !foundYet){
			foundYet = 1;
			minDist = newDist;
			*closest = count;
		}
	}
	return foundYet;
}

/*
void genPathLayer(int layer){
	node* nodeLayer = nodeList[layer];
	int head;//printing head, the current node index that the head is situated at
	int oldHead;
	int count;
	int index;
	for(count = 0; count < vertexCount[layer]; count++){
		while(nodeLayer[count].sibCount > 0){
			printf("G01 E%.3lf F6000\n", (((double)E)/100*EXTRUSION_CONSTANT)-2);
			printf("G01 X%.2lf Y%.2lf Z%.2lf\n", ((double)nodeLayer[count].loc[0]-2000)/100, ((double)nodeLayer[count].loc[1]-2000)/100, (((double)layer)/100));
			E+=2000;
			printf("G01 E%.3lf\n", (((double)E)/100*EXTRUSION_CONSTANT));
			printf("G01 F1800\n");
			head = count;
			while(nodeLayer[head].sibCount > 0){
				oldHead = head;
				head = nodeLayer[head].sibs[nodeLayer[head].sibCount-1];
				nodeLayer[oldHead].sibs[nodeLayer[oldHead].sibCount-1] = -1;
				nodeLayer[oldHead].sibCount--;
				index = findNodePointer(oldHead, &(nodeLayer[head]));
				nodeLayer[head].sibs[index] = nodeLayer[head].sibs[nodeLayer[head].sibCount-1];
				nodeLayer[head].sibs[nodeLayer[head].sibCount-1] = -1;
				nodeLayer[head].sibCount--;
				if(oldHead == head) puts("well, it is referencing itself!");
				E+= distance2d(nodeLayer[head].loc, nodeLayer[oldHead].loc);
				printf("G01 X%.2lf Y%.2lf Z%.2lf E%.3lf\n", ((double)nodeLayer[head].loc[0]-2000)/100, ((double)nodeLayer[head].loc[1]-2000)/100, (((double)layer)/100), ((double)E)/100*EXTRUSION_CONSTANT);
				drawLine(nodeLayer[head].loc[0]*WIDTH/maxx, nodeLayer[head].loc[1]*HEIGHT/maxy, nodeLayer[oldHead].loc[0]*WIDTH/maxx, nodeLayer[oldHead].loc[1]*HEIGHT/maxy);
			}
		}
	}
}*/
