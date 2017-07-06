#pragma once

#include <SDL.h>

class SDL_WindowWrapper
{
public:
	SDL_WindowWrapper(SDL_Window*);
	~SDL_WindowWrapper();

	bool SetColor(int r, int g, int b, int a = SDL_ALPHA_OPAQUE);
	bool DrawLine(int x1, int y1, int x2, int y2);
	bool Clear();
	void Present();

	static SDL_WindowWrapper* GetWindow(int index);
	int GetIndex() { return m_windowIndex; }

	const static int MAX_WINDOW_COUNT;

private:
	static SDL_WindowWrapper** m_lWindows;
	static int m_windowCount;

	int m_windowIndex;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
};

