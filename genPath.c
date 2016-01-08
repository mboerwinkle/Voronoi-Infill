#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#define HEIGHT 750//these either
#define WIDTH 750
extern void drawLine(int x1, int y1, int x2, int y2);//this should not be here
extern void genPathLayer(int layer);
void genPath(){
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
			printf("%ld, %ld, %d, 0\n", nodeLayer[count].loc[0], nodeLayer[count].loc[1], layer);
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
				printf("%ld, %ld, %d, 1\n", nodeLayer[head].loc[0], nodeLayer[head].loc[1], layer);
				drawLine(nodeLayer[head].loc[0]*WIDTH/maxx, nodeLayer[head].loc[1]*HEIGHT/maxy, nodeLayer[oldHead].loc[0]*WIDTH/maxx, nodeLayer[oldHead].loc[1]*HEIGHT/maxy);
			}
		}
	}
}
