#include "SDL_WindowWrapper.h"

const int SDL_WindowWrapper::MAX_WINDOW_COUNT = 10;
SDL_WindowWrapper** SDL_WindowWrapper::m_lWindows = NULL;
int SDL_WindowWrapper::m_windowCount = 0;

SDL_WindowWrapper::SDL_WindowWrapper(SDL_Window* window)
{
	/*m_windowIndex = -1;

	if (SDL_WindowWrapper::m_lWindows == NULL) {
		SDL_WindowWrapper::m_lWindows = (SDL_WindowWrapper**) calloc(sizeof(SDL_WindowWrapper*), SDL_WindowWrapper::MAX_WINDOW_COUNT);
		SDL_WindowWrapper::m_windowCount = 0;
	}

	m_windowIndex = SDL_WindowWrapper::m_windowCount++;

	SDL_WindowWrapper::m_pWindow = window;
	SDL_WindowWrapper::m_lWindows[m_windowIndex] = this;

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);*/
}

SDL_WindowWrapper::~SDL_WindowWrapper()
{
	SDL_DestroyWindow(m_pWindow);
}


bool SDL_WindowWrapper::SetColor(int r, int g, int b, int a)
{
	int result = SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a);
	return result == 0;
}

bool SDL_WindowWrapper::DrawLine(int x1, int y1, int x2, int y2)
{
	int result = SDL_RenderDrawLine(m_pRenderer, x1, y1, x2, y2);
	return result == 0;
}

bool SDL_WindowWrapper::Clear()
{
	int result = SDL_RenderClear(m_pRenderer);
	return result == 0;
}

void SDL_WindowWrapper::Present()
{
	SDL_RenderPresent(m_pRenderer);
}

SDL_WindowWrapper * SDL_WindowWrapper::GetWindow(int index)
{
	if (index >= MAX_WINDOW_COUNT)
		return NULL;

	return SDL_WindowWrapper::m_lWindows[index];
}
