//
//  nano_engine.c
//
//  Created by william herrera
//  Copyright © 2019 william herrera. All rights reserved.
//

#include "nano_engine.h"

SDL_Window *win;
SDL_Renderer *ren;

int Nano_Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s",SDL_GetError());
        return -1;
    }
    return 0;
}

int Nano_CreateRenderer(const char *title,
                         int x, int y, int width,
                         int height) {
    win = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_SHOWN);
    if (win == NULL){
        printf("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL){
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    return 0;
}

int Nano_PollEvent(Nano_Event *event) {
	return SDL_PollEvent((SDL_Event *)event);
}

int Nano_QuitEvent(Nano_Event *event) {
	SDL_Event *sdl_event = (SDL_Event *)event;
	if (sdl_event->type == SDL_QUIT) {
		return 1;
	}
	return 0;
}

int Nano_KeyDownEvent(Nano_Event *event, int *scancode) {
	SDL_Event *sdl_event = (SDL_Event *)event;
	if (sdl_event->type == SDL_KEYDOWN) {		
		*scancode = sdl_event->key.keysym.scancode;
		return 1;
	}
	return 0;
}

Nano_Texture* Nano_LoadTexture(const char *file_path) {
    SDL_Surface *bmp = SDL_LoadBMP(file_path);
    if (bmp == NULL){
        printf("SDL_LoadBMP Error: %s",SDL_GetError());
        return NULL;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == NULL){
        printf("SDL_CreateTextureFromSurface Error: %s",SDL_GetError());
        return NULL;
    }
    return (Nano_Texture*)tex;
}

void Nano_DestroyTexture(Nano_Texture *texture) {
	SDL_DestroyTexture((SDL_Texture *)texture);
}

void Nano_RenderClear() {
    SDL_RenderClear(ren);
}

void Nano_RenderCopy(Nano_Texture * texture,
                    const Nano_Rect * srcrect,
                    const Nano_Rect * dstrect) {
    SDL_RenderCopy(ren, (SDL_Texture *)texture, (SDL_Rect *)srcrect, (SDL_Rect *)dstrect);
}

void Nano_RenderPresent() {
    SDL_RenderPresent(ren);
}

void Nano_Sleep(unsigned int ms) {
	SDL_Delay(ms);
}

void Nano_Shutdown() {
    if(ren != NULL) {
        SDL_DestroyRenderer(ren);
    }
    if(win != NULL) {
        SDL_DestroyWindow(win);
    }
    SDL_Quit();
}
