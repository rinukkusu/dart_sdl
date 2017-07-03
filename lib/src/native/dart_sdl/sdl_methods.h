#pragma once
#include <string>
#include <SDL.h>
#include <dart_api.h>

class SDL {
private:
	static SDL_Window *m_pWindow;

public:
	static void Init(Dart_NativeArguments args) { 
		int64_t flags = 0;
		Dart_GetNativeIntegerArgument(args, 0, &flags);
		SDL_Init(flags);
	}

	static void CreateWindow(Dart_NativeArguments args) {
		const char* title = NULL;
		int64_t x, y, w, h, flags = 0;

		void* peer;
		Dart_Handle titleString = Dart_GetNativeStringArgument(args, 0, &peer);
		Dart_StringToCString(titleString, &title);

		Dart_GetNativeIntegerArgument(args, 1, &x);
		Dart_GetNativeIntegerArgument(args, 2, &y);
		Dart_GetNativeIntegerArgument(args, 3, &w);
		Dart_GetNativeIntegerArgument(args, 4, &h);
		Dart_GetNativeIntegerArgument(args, 5, &flags);

		m_pWindow = SDL_CreateWindow(title, x, y, w, h, flags); 
	}
};