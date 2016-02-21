#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
//determines if the two line segments can intersect in the square. designed in order to avoid problems with near-parallel lines overflowing scalars when their intersection point was calculated.
int sideRay(point2d targ, line2d ray);

extern bitarray closedPoints;
extern bitarray currentPoints;


void cropLines(int layer){
	currentPoints = genBitarray(points);
	int i1, i2;
	int count = lineCount[layer];
	point2d* interList;//this is the list of all intersections by lines that share a parent 
	int interCount;
	int temp;
	int segValid1, segValid2;
	point2d mid;
	point3d mid3d;
	scalar pdistsq;
	line2d *layerlist = lineList[layer];
	line2d *newlayerlist = malloc(sizeof(line2d));
	int newCount = 0;
	for(i1 = 0; i1 < count; i1++){
		interList = calloc(2, sizeof(point2d));
		interCount = 1;
		interList[0][0] = layerlist[i1].end[0][0];
		interList[0][1] = layerlist[i1].end[0][1];
		for(i2 = 0; i2 < count; i2++){
			if(i1 == i2) continue;
//this is to check if it shares a parent. Ima go one step further and make it have parents[0].			if(!lineSharesParent(&(layerlist[i2]), &(layerlist[i1]))) continue;
			if(!(layerlist[i1].parents[0] == layerlist[i2].parents[0] || layerlist[i1].parents[0] == layerlist[i2].parents[1])) continue;
			int res1 = sideRay(layerlist[i2].end[0], layerlist[i1]);
			int res2 = sideRay(layerlist[i2].end[1], layerlist[i1]);
			if(res1!=res2){
				if(lineSegIntersect2d(layerlist[i1].end[0], layerlist[i1].end[1], layerlist[i2].end[0], layerlist[i2].end[1], &(interList[interCount]))){
					interCount++;
					interList = realloc(interList, sizeof(point2d)*(interCount+1));
				}//else puts("Yo ni**a, come see this!");//if canIntersect in square, then it should be able to intersect....
			}
		}
		sortPointList(interList[0], &(interList[1]), interCount-1);//-2 because I don't need to sort the ends, since they are the original ends
		interList[interCount][0] = layerlist[i1].end[1][0];//I set the beginning and end intersections to the original ends of the line
		interList[interCount][1] = layerlist[i1].end[1][1];
		interCount++;
		//valid = 0;//this will be set to one if it finds a line segment where it is closest to its parents
		for(temp = 0; temp < interCount-1; temp++){
			midpoint2d(interList[temp], interList[temp+1], &mid);
			mid3d[0] = mid[0];
			mid3d[1] = mid[1];
			mid3d[2] = layer;
			pdistsq = distance3dsq(mid3d, pointList[layerlist[i1].parents[0]]);
			segValid1 = 1;
			
			for(int test = 0; test < points; test++){
				if(test == layerlist[i1].parents[0] || test == layerlist[i1].parents[1]) continue;
				if(pdistsq > distance3dsq(mid3d, pointList[test])){
					segValid1 = 0;
					break;
				}
			}
			if(segValid1 == 1){
				newlayerlist[newCount].end[0][0] = interList[temp][0];
				newlayerlist[newCount].end[0][1] = interList[temp][1];
				break;
			}
		}
		for(temp = interCount-1; temp > 0; temp--){
			midpoint2d(interList[temp], interList[temp-1], &mid);
			mid3d[0] = mid[0];
			mid3d[1] = mid[1];
			mid3d[2] = layer;
			pdistsq = distance3dsq(mid3d, pointList[layerlist[i1].parents[0]]);
			segValid2 = 1;
			for(int test = 0; test < points; test++){
				if(test == layerlist[i1].parents[0] || test == layerlist[i1].parents[1]) continue;
				if(pdistsq > distance3dsq(mid3d, pointList[test])){
					segValid2 = 0;
					break;
				}
			}
			if(segValid2 == 1){
				newlayerlist[newCount].end[1][0] = interList[temp][0];
				newlayerlist[newCount].end[1][1] = interList[temp][1];
				newlayerlist[newCount].parents[0] = layerlist[i1].parents[0];
				newlayerlist[newCount].parents[1] = layerlist[i1].parents[1];
				newCount++;
				newlayerlist = realloc(newlayerlist, sizeof(line2d)*(newCount+1));
				setBit(currentPoints, layerlist[i1].parents[0], 1);
				setBit(currentPoints, layerlist[i1].parents[1], 1);
				break;
			}
		}
		if(segValid1^segValid2) puts("Much error, Very Bad, Wow!");
		
		free(interList);
	}
	newlayerlist = realloc(newlayerlist, sizeof(line2d)*newCount);
	free(lineList[layer]);
	lineList[layer] = newlayerlist;
	lineCount[layer] = newCount;
}

int lineSharesParent(line2d *A, line2d *B){
	return (A->parents[0] == B->parents[0] || A->parents[0] == B->parents[1] || A->parents[1] == B->parents[0] || A->parents[1] == B->parents[1]);
}

//  public-domain code by Darel Rex Finley,
//  2010.  See diagrams at http://
//  alienryderflex.com/point_left_of_ray

int sideRay(point2d targ, line2d ray){
  if((targ[1]-ray.end[0][1])*(ray.end[1][0]-ray.end[0][0]) == (targ[0]-ray.end[0][0])*(ray.end[1][1]-ray.end[0][1])) return -1;
  return (targ[1]-ray.end[0][1])*(ray.end[1][0]-ray.end[0][0]) < (targ[0]-ray.end[0][0])*(ray.end[1][1]-ray.end[0][1]);
}
