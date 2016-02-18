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
	bitarray isInUnion = genBitarray(nodeCount[layer]);
	for(int x = 0; x < nodeCount[layer]; x++){
		if(getBit(isInUnion, x)) continue;
		setBit(isInUnion, x, 1);
		uniMem = 1;
		uni = malloc(sizeof(int));
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
		int sibIndex;
		//getting rid of node references within a union.
		node *node1, *node2;
		node *newNode = &(nodeList[layer][uni[0]]);
		for(int node1Index = 0; node1Index < uniMem; node1Index++){
			node1 = &(nodeList[layer][uni[node1Index]]);
			for(int node2Index = node1Index+1; node2Index < uniMem; node2Index++){
				node2 = &(nodeList[layer][uni[node2Index]]);
				for(int testSib = 0; testSib < node1->sibCount; testSib++){
					if(node1->sibs[testSib] != uni[node2Index]) continue;//thus we will execute the rest of the code in this loop only if the two nodes point at each other.
					sibIndex = findNodePointer(uni[node1Index], node2);
					if(sibIndex == -1) puts("bad connection");
					node1->sibs[testSib] = node1->sibs[node1->sibCount-1];
					node1->sibCount--;
					testSib--;
					node2->sibs[sibIndex] = node2->sibs[node2->sibCount-1];
					node2->sibCount--;
				}
			}
		}//
		
		//getting position of new Node (will be stored in nodeList[layer][uni[0]])
		for(int nodeIndex = 1; nodeIndex < uniMem; nodeIndex++){
			newNode->loc[0] += nodeList[layer][uni[nodeIndex]].loc[0];
			newNode->loc[1] += nodeList[layer][uni[nodeIndex]].loc[1];
		}
		newNode->loc[0] /= uniMem;
		newNode->loc[1] /= uniMem;
		//
		//put node references from the union into nodeList[layer][uni[0]]//FIXME if starting node has an index to two nodes that later merge into one, then the node will end up with two references to another node causing a fatal bad connection. Im just pretending that wont happen, as all of my starting nodes are connected to only one node.
		for(int nodeIndex = 1; nodeIndex < uniMem; nodeIndex++){
			node1 = &(nodeList[layer][uni[nodeIndex]]);
			for(int testSib = 0; testSib < node1->sibCount; testSib++){
				if(findNodePointer(node1->sibs[testSib], newNode) == -1){//is not already in union
					newNode->sibCount++;
					newNode->sibs = realloc(newNode->sibs, sizeof(int)*newNode->sibCount);
					newNode->sibs[newNode->sibCount-1] = node1->sibs[testSib];
				}else{
					puts("This should not happen normally");
				}
			//	if(!getBit(isInUnion, node1->sibs[testSib])){//set all 
					node2 = &(nodeList[layer][node1->sibs[testSib]]);
					sibIndex = findNodePointer(uni[nodeIndex], node2);
					if(sibIndex == -1) puts("fatal error");
					node2->sibs[sibIndex] = uni[0];
			//	}
			}
			node1->sibCount = 0;
			free(node1->sibs);
		}
		//
		free(uni);
		
	}
	for(int x = 0; x < nodeCount[layer]; x++){
		for(int sibI = 0; sibI < nodeList[layer][x].sibCount; sibI++){
			if(findNodePointer(x, &(nodeList[layer][nodeList[layer][x].sibs[sibI]])) == -1){
				printf("error at %d - %d\nlayer %d\n", x, nodeList[layer][x].sibs[sibI], layer);
			}
		}
	}
	free(isInUnion);
}
int isWithinUnionRadius(int nodeIndex, int layer){
	for(int x = 0; x < uniMem; x++){
		if(distance2d(nodeList[layer][uni[x]].loc, nodeList[layer][nodeIndex].loc) < RADIUS){
//			printf("%ld\n", distance2d(nodeList[layer][uni[x]].loc, nodeList[layer][nodeIndex].loc));
			return 1;
		}
	}
	return 0;
}
