#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#define RADIUS 10

extern int isWithinUnionRadius(int nodeIndex, int layer);

//list of union members
int *uni;
//list of size in members of union
int uniMem;

void combineNodes(int layer){
	int pot;//index of node to be tested to see if it should be added
	int newNodeCount = 0;
	node *newNode;
	bitarray isInUnion = genBitarray(nodeCount[layer]);
	node *newNodeList = malloc(sizeof(node));
	for(int x = 0; x < nodeCount[layer]; x++){
		if(getBit(isInUnion, x)) continue;
		setBit(isInUnion, x, 1);
		uniMem = 1;
		uni = malloc(sizeof(int));
		newNodeCount++;
		uni[0] = x;
		pot = 0;
		while(pot < nodeCount[layer]){
			//in order to add into the union, it has to be not in any union already, and it has to be within the area covered by the union
			if((!getBit(isInUnion, pot)) && isWithinUnionRadius(pot, layer)){
				uniMem++;
				setBit(isInUnion, pot, 1);
				uni = realloc(uni, sizeof(int)*uniMem);
				uni[uniMem-1] = pot;
				pot = 0;
			}else{
				pot++;
			}
		}
		newNodeList = realloc(newNodeList, sizeof(node)*newNodeCount);
		newNode = &(newNodeList[newNodeCount-1]);
		newNode->loc[0] = 0;
		newNode->loc[1] = 0;
		int sibIndex;//getting rid of node references within a union.
		node *node1, *node2;
		for(int node1Index = 0; node1Index < uniMem; node1Index++){
			node1 = &(nodeList[layer][uni[node1Index]]);
			for(int node2Index = node1Index+1; node2Index < uniMem; node2Index++){
				node2 = &(nodeList[layer][uni[node2Index]]);
				for(int testSib = 0; testSib < node1->sibCount; testSib++){
					sibIndex = findNodePointer(uni[node1Index], node2);
					if(sibIndex == -1) continue;
					node1->sibs[testSib] = node1->sibs[node1->sibCount-1];
					node1->sibCount--;
					testSib--;
					node2->sibs[sibIndex] = node2->sibs[node2->sibCount-1];
					node2->sibCount--;
				}
			}
		}//
		//getting position of newNode
		for(int nodeIndex = 0; nodeIndex < uniMem; nodeIndex++){
			newNode->loc[0] += nodeList[layer][uni[nodeIndex]].loc[0];
			newNode->loc[1] += nodeList[layer][uni[nodeIndex]].loc[1];
		}
		newNode->loc[0] /= uniMem;
		newNode->loc[1] /= uniMem;
		//
		free(uni);
		
	}
	free(isInUnion);
	printf("%d initial nodes, %d final nodes\n", nodeCount[layer], newNodeCount);
}
int isWithinUnionRadius(int nodeIndex, int layer){
	for(int x = 0; x < uniMem; x++){
		if(distance2d(nodeList[layer][uni[x]].loc, nodeList[layer][nodeIndex].loc) < RADIUS){
			printf("%ld\n", distance2d(nodeList[layer][uni[x]].loc, nodeList[layer][nodeIndex].loc));
			return 1;
		}
	}
	return 0;
}
