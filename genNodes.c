#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
node **nodeList;
int *nodeCount;
/*void genNodes(){
	node *thisnode, *testnode;
	vertex* thisvertex;
	nodeList = calloc(maxz, sizeof(node*));
	int temp, test;
	int tooFar = 0;
	for(int layer = 0; layer < maxz; layer+=step){
		nodeList[layer] = (node*)calloc(vertexCount[layer], sizeof(node));
		for(temp = 0; temp < vertexCount[layer]; temp++){
			thisnode = &nodeList[layer][temp];
			thisvertex = &vertexList[layer][temp];
			thisnode->loc[0] = thisvertex->loc[0];
			thisnode->loc[1] = thisvertex->loc[1];
			for(test = temp+1; test < vertexCount[layer]; test++){
				if(getSharedParentCount(vertexList[layer][test], *thisvertex) == 2){
					testnode = &(nodeList[layer][test]);
					if(thisnode->sibCount == 3 || testnode->sibCount == 3){
						tooFar++;
						continue;
					}
					thisnode->sibs[thisnode->sibCount] = test;
					testnode->sibs[testnode->sibCount] = temp;
					thisnode->sibCount++;
					testnode->sibCount++;
				}
			}
		}
	}
	printf("Node overload: %d\n", tooFar);
}*/
void genNodes(){
	int layer, temp;
	nodeCount = calloc(maxz, sizeof(int));
	nodeList = calloc(maxz, sizeof(node*));
	for(layer = 0; layer < maxz; layer+=step){
		nodeCount[layer] = 2*lineCount[layer];//we are going to start out with a unique node for each end, then we will combine close nodes.
		nodeList[layer] = calloc(nodeCount[layer], sizeof(node));
		for(temp = 0; temp < lineCount[layer]; temp++){
			nodeList[layer][temp*2].sibCount = 1;
			nodeList[layer][temp*2].sibs = malloc(sizeof(int));
			nodeList[layer][temp*2].sibs[0] = temp*2+1;
			nodeList[layer][temp*2].loc[0] = lineList[layer][temp].end[0][0];
			nodeList[layer][temp*2].loc[1] = lineList[layer][temp].end[0][1];
			nodeList[layer][temp*2+1].sibCount = 1;
			nodeList[layer][temp*2+1].sibs = malloc(sizeof(int));
			nodeList[layer][temp*2+1].sibs[0] = temp*2;
			nodeList[layer][temp*2+1].loc[0] = lineList[layer][temp].end[1][0];
			nodeList[layer][temp*2+1].loc[1] = lineList[layer][temp].end[1][1];
		}
		combineNodes(layer);
	}
}
