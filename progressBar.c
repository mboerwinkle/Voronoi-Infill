#include <stdio.h>
#include <stdlib.h>
void progressBar(int count, int max){
/*	char out[max+3];//plus two for the endcaps, plus one for null byte
	out[0] = '[';
	for(int pos = 1; pos < count; pos++){
		out[pos] = '=';
	}
	if(count > 0){
		if(count < max) out[count] = '>';
		else out[count] = '=';
	}
	for(int pos = count+1; pos <= max; pos++){
		out[pos] = ' ';
	}
	out[max+1] = ']';
	out[max+2] = '\0';*/
	printf("\rCalculating: %d/%d", count, max);
	fflush(stdout);
}
