#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

void cropLines(int layer){
	int i1, i2;
	int count = lineCount[layer];
	point2d* interList;
	int interCount;
	int temp;
	int valid;
	int segValid;
	point2d mid;
	point3d mid3d;
	scalar pdistsq;
	line2d *layerlist = lineList[layer];
	for(i1 = 0; i1 < count; i1++){
		interList = calloc(2, sizeof(point2d));
		interCount = 1;
		interList[0][0] = layerlist[i1].end[0][0];
		interList[0][1] = layerlist[i1].end[0][1];
		for(i2 = 0; i2 < count; i2++){
			if(i1 == i2) continue;
			if(!lineSharesParent(&(layerlist[i2]), &(layerlist[i1]))) continue;
			if(lineSegIntersect2d(layerlist[i1].end[0], layerlist[i1].end[1], layerlist[i2].end[0], layerlist[i2].end[1], &(interList[interCount]))){
				interCount++;
				interList = realloc(interList, sizeof(point2d)*(interCount+1));
			}
		}
		interList[interCount][0] = layerlist[i1].end[1][0];//I set the beginning and end intersections to the original ends of the line
		interList[interCount][1] = layerlist[i1].end[1][1];
		interCount++;
		sortPointList(interList[0], interList, interCount);//-2 because I don't need to sort the ends, since they are the original ends
		valid = 0;//this will be set to one if it finds a line segment where it is closest to its parents
		for(temp = 0; temp < interCount-1; temp++){
			midpoint2d(interList[temp], interList[temp+1], &mid);
			mid3d[0] = mid[0];
			mid3d[1] = mid[1];
			mid3d[2] = layer;
			pdistsq = distance3dsq(mid3d, pointList[layerlist[i1].parents[0]]);
			segValid = 1;
			for(int test = 0; test < points; test++){
				if(test == layerlist[i1].parents[0] || test == layerlist[i1].parents[1]) continue;
				if(pdistsq > distance3dsq(mid3d, pointList[test])){
					segValid = 0;
					break;
				}
			}
			if(segValid == 1){
				valid = 1;
				layerlist[i1].end[0][0] = interList[temp][0];
				layerlist[i1].end[0][1] = interList[temp][1];
			}
		}
		if(!valid){//line is, in fact, never valid. So we need to remove all traces of it, move the last one into its spot, and shrink the array size by one.
			layerlist[i1].end[0][0] = layerlist[count-1].end[0][0];
			layerlist[i1].end[0][1] = layerlist[count-1].end[0][1];
			layerlist[i1].end[1][0] = layerlist[count-1].end[1][0];
			layerlist[i1].end[1][1] = layerlist[count-1].end[1][1];
			layerlist[i1].parents[0] = layerlist[count-1].parents[0];
			layerlist[i1].parents[1] = layerlist[count-1].parents[1];
			lineCount[layer]--;
//lets leave this out for now...			lineList[layer] = realloc(lineList[layer], sizeof(line2d)*lineCount[layer]);
			layerlist = lineList[layer];
			count = lineCount[layer];
			i1--;
			free(interList);
			continue;
		}
		for(temp = interCount-1; temp > 0; temp--){
			midpoint2d(interList[temp], interList[temp-1], &mid);
			mid3d[0] = mid[0];
			mid3d[1] = mid[1];
			mid3d[2] = layer;
			pdistsq = distance3dsq(mid3d, pointList[layerlist[i1].parents[0]]);
			segValid = 1;
			for(int test = 0; test < points; test++){

				if(pdistsq > distance3dsq(mid3d, pointList[test])){
					segValid = 0;
					break;
				}
			}
			if(segValid == 1){
				valid = 1;
				layerlist[i1].end[1][0] = interList[temp][0];
				layerlist[i1].end[1][1] = interList[temp][1];
			}
		}
		free(interList);
		
	}
}

int lineSharesParent(line2d *A, line2d *B){
	return (A->parents[0] == B->parents[0] || A->parents[0] == B->parents[1] || A->parents[1] == B->parents[0] || A->parents[1] == B->parents[1]);
}
