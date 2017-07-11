// example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SDL.h>
#include <SDL_ttf.h>

#undef main
int main()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("test", 10, 10, 100, 100, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	TTF_Init();
	TTF_Font* font = TTF_OpenFont("C:\\Users\\mriegler\\Documents\\Visual Studio 2015\\Projects\\dart_sdl\\example\\arial.ttf", 12);

	SDL_Texture* renderedText = NULL;
	if (font != NULL) {
		SDL_Color color;
		color.a = 255;
		color.r = 0;
		color.b = 0;
		color.g = 0;

		SDL_Surface* surface = TTF_RenderText_Blended(font, "test", color);
		renderedText = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}

	while (true) {
		SDL_Event* event = (SDL_Event*) SDL_calloc(sizeof(*event), 1);
		SDL_PollEvent(event);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		if (renderedText != NULL) {
			int w, h;
			SDL_QueryTexture(renderedText, NULL, NULL, &w, &h);
			SDL_Rect rect;
			rect.w = w;
			rect.h = h;
			//SDL_RenderCopy(renderer, renderedText, NULL, &rect);
		}

		SDL_RenderPresent(renderer);


		SDL_Delay(1);
	}

    return 0;
}

