#ifndef _sdl_windowwrapper_h
#define _sdl_windowwrapper_h

#include <SDL.h>

#define MAX_WINDOW_COUNT 10

struct SDL_WindowWrapper2 {
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool SetColor(int r, int g, int b, int a)
	{
		int result = SDL_SetRenderDrawColor(renderer, r, g, b, a);
		return result == 0;
	}

	bool DrawLine(int x1, int y1, int x2, int y2)
	{
		int result = SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
		return result == 0;
	}

	bool Clear()
	{
		int result = SDL_RenderClear(renderer);
		return result == 0;
	}

	void Present()
	{
		SDL_RenderPresent(renderer);
	}

	void SetWindowTitle(const char* title) 
	{
		SDL_SetWindowTitle(window, title);
	}
};

#endif // _sdl_windowwrapper_h