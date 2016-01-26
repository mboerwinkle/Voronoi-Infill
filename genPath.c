#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#define HEIGHT 750//these either
#define WIDTH 750
#define EXTRUSION_CONSTANT 0.1//approx
extern void drawLine(int x1, int y1, int x2, int y2);//this should not be here
extern void genPathLayer(int layer);
long int E = 0;
//FILE *gcode;

void genPath(){
//	gcode = fopen("output.txt", "w");
	for(int layer = 0; layer < maxz; layer+=step){
		genPathLayer(layer);
	}
}

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
}
