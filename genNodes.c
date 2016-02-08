#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
node **nodeList;
void genNodes(){
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
}
