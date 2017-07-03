// console-test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SDL.h"

#undef main
int main()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("test", 0, 0, 100, 100, SDL_VIDEO_OPENGL);

    return 0;
}

