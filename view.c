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
}

void closeSDLwindow(){
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void layer_to_SDL(int layer){
	for(int temp = 0; temp < vertexCount[layer]; temp++){
		
	}
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
