#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "globals.h"

#define WIDTH 750
#define HEIGHT 750

SDL_Rect pt = {.w = 2, .h = 2};
SDL_Window* window;
SDL_Renderer* render;

extern void drawLine(int x1, int y1, int x2, int y2);
extern void drawPoint(int x, int y, int color);
extern void clearScreen();
extern void paint();

void paint(){
	SDL_RenderPresent(render);
}
void clearScreen(){
	SDL_SetRenderDrawColor(render, 0,0,0,255);
	SDL_RenderClear(render);
}
void openSDLwindow(){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	window = SDL_CreateWindow("Voronoi Infill", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
	if(window == NULL){
		SDL_Quit();
	}
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	clearScreen();
	paint();
	SDL_SetRenderDrawColor(render, 255,5,5,255);
}

void closeSDLwindow(){
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void layer_to_SDL(int layer){
	for(int pnt = 0; pnt < points; pnt++){
		drawPoint(pointList[pnt][0]*WIDTH/maxx, pointList[pnt][1]*HEIGHT/maxy, 1);
	}
	for(int count = 0; count+1<bPcount; count+=2){
		SDL_SetRenderDrawColor(render, 255,255,255,255);
		drawLine(bP[count][0]*WIDTH/maxx, bP[count][1]*HEIGHT/maxy, bP[count+1][0]*WIDTH/maxx, bP[count+1][1]*HEIGHT/maxy);
	}
/*	SDL_SetRenderDrawColor(render, 255,255,255,255);
	vertex *A, *B;
	for(int temp = 0; temp < vertexCount[layer]; temp++){
		A = &vertexList[layer][temp];
		for(int test = temp+1; test < vertexCount[layer]; test++){
			B = &vertexList[layer][test];
			if(getSharedParentCount(*A, *B) == 2){
				drawLine(A->loc[0]*WIDTH/maxx, A->loc[1]*HEIGHT/maxy, B->loc[0]*WIDTH/maxx, B->loc[1]*HEIGHT/maxy);
			}
		}
	}*/
	SDL_SetRenderDrawColor(render, 255,0,255,255);
//	genPathLayer(layer);
	SDL_SetRenderDrawColor(render, 0,0,255,255);
	node *An, *Bn;
	for(int temp = 0; temp < vertexCount[layer]; temp++){
		An = &nodeList[layer][temp];
		for(int test = temp+1; test < vertexCount[layer]; test++){
			Bn = &nodeList[layer][test];
			if(findNodePointer(test, An)!=-1&&findNodePointer(temp, Bn)!=-1){
				drawLine(An->loc[0]*WIDTH/maxx, An->loc[1]*HEIGHT/maxy, Bn->loc[0]*WIDTH/maxx, Bn->loc[1]*HEIGHT/maxy);
			}
		}
	}
	paint();
	clearScreen();
}
void drawLine(int x1, int y1, int x2, int y2){
//	SDL_SetRenderDrawColor(render, 200, 0, 255, 255);
	SDL_RenderDrawLine(render, x1, y1, x2, y2);
}
void drawPoint(int x, int y, int color){
	if(color == 0) SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	if(color == 1) SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
	if(color == 2) SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
	pt.x = x;
	pt.y = y;
	SDL_RenderFillRect(render, &pt);
}
