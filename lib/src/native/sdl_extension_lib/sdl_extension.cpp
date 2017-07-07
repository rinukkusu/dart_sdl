#include <string>
#include <vector>
#include <memory>
#include <Windows.h>
#include <dart_api.h>
#include <dart_native_api.h>
#include <SDL.h>
#include "SDL_WindowWrapper.h"

// Forward declaration of ResolveName function.
Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool* auto_setup_scope);

void _GetCurrentThreadId(Dart_NativeArguments args);
void _SDL_Init(Dart_NativeArguments args);
void _SDL_CreateWindow(Dart_NativeArguments args);
void _SDL_RenderClear(Dart_NativeArguments args);
void _SDL_SetRenderDrawColor(Dart_NativeArguments args);
void _SDL_RenderPresent(Dart_NativeArguments args);
void _SDL_PollEvent(Dart_NativeArguments args);
void _SDL_Delay(Dart_NativeArguments args);

// The name of the initialization function is the extension name followed
// by _Init.
DART_EXPORT Dart_Handle sdl_extension_Init(Dart_Handle parent_library) {
	if (Dart_IsError(parent_library)) return parent_library;

	Dart_Handle result_code =
		Dart_SetNativeResolver(parent_library, ResolveName, NULL);
	if (Dart_IsError(result_code)) return result_code;

	return Dart_Null();
}

Dart_Handle HandleError(Dart_Handle handle) {
	if (Dart_IsError(handle)) Dart_PropagateError(handle);
	return handle;
}

Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool * auto_setup_scope)
{
	// If we fail, we return NULL, and Dart throws an exception.
	if (!Dart_IsString(name)) return NULL;
	Dart_NativeFunction result = NULL;
	const char* cname;
	HandleError(Dart_StringToCString(name, &cname));

	if (strcmp("GetCurrentThreadId", cname) == 0) result = _GetCurrentThreadId;

	if (strcmp("SDL_Init", cname) == 0) result = _SDL_Init;
	if (strcmp("SDL_CreateWindow", cname) == 0) result = _SDL_CreateWindow;
	if (strcmp("SDL_RenderClear", cname) == 0) result = _SDL_RenderClear;
	if (strcmp("SDL_SetRenderDrawColor", cname) == 0) result = _SDL_SetRenderDrawColor;
	if (strcmp("SDL_RenderPresent", cname) == 0) result = _SDL_RenderPresent;
	if (strcmp("SDL_PollEvent", cname) == 0) result = _SDL_PollEvent;
	if (strcmp("SDL_Delay", cname) == 0) result = _SDL_Delay;

	return result;
}

//////////////////////////////////////////////////////////////////////////////////////////


void _GetCurrentThreadId(Dart_NativeArguments args) {
	uint64_t threadId = GetCurrentThreadId();
	Dart_SetReturnValue(args, HandleError(Dart_NewIntegerFromUint64(threadId)));
}

SDL_WindowWrapper2 GetWindowFromArgs(Dart_NativeArguments args) {
	int64_t index = 0;

	HandleError(Dart_GetNativeIntegerArgument(args, 0, &index));

	return g_wrapperArray[index];
}

void _SDL_Init(Dart_NativeArguments args) {
	int64_t flags = 0;
	HandleError(Dart_GetNativeIntegerArgument(args, 0, &flags));
	SDL_Init(flags);

	g_wrapperArray = (SDL_WindowWrapper2*)SDL_calloc(10, sizeof(SDL_WindowWrapper2));

	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(true)));
}

void _SDL_CreateWindow(Dart_NativeArguments args) {
	const char* title = NULL;
	int64_t x, y, w, h, flags = 0;

	void* peer = NULL;
	Dart_Handle titleString = HandleError(Dart_GetNativeStringArgument(args, 0, &peer));
	HandleError(Dart_StringToCString(titleString, &title));

	HandleError(Dart_GetNativeIntegerArgument(args, 1, &x));
	HandleError(Dart_GetNativeIntegerArgument(args, 2, &y));
	HandleError(Dart_GetNativeIntegerArgument(args, 3, &w));
	HandleError(Dart_GetNativeIntegerArgument(args, 4, &h));
	HandleError(Dart_GetNativeIntegerArgument(args, 5, &flags));

	SDL_Window* window = SDL_CreateWindow(title, x, y, w, h, flags);
	
	bool success = window != NULL;

	if (success) {
		//auto wrapper = std::make_shared<SDL_WindowWrapper>(window);
		//Dart_SetReturnValue(args, HandleError(Dart_NewInteger(wrapper->GetIndex())));
		struct SDL_WindowWrapper2 w = SDL_WindowWrapper2_t;
		w.window = window;
		w.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		g_wrapperArray[0] = w;
		Dart_SetReturnValue(args, HandleError(Dart_NewInteger(0)));
	}
	else {
		Dart_SetReturnValue(args, HandleError(Dart_NewApiError("Couldn't create SDL window.")));
	}
}

void _SDL_RenderClear(Dart_NativeArguments args) {
	SDL_WindowWrapper2 window = GetWindowFromArgs(args);
	bool result = window.Clear();

	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(result)));
}

void _SDL_RenderPresent(Dart_NativeArguments args) {
	SDL_WindowWrapper2 window = GetWindowFromArgs(args);
	window.Present();
}

void _SDL_SetRenderDrawColor(Dart_NativeArguments args) {
	int64_t r, g, b, a = 0;
	HandleError(Dart_GetNativeIntegerArgument(args, 1, &r));
	HandleError(Dart_GetNativeIntegerArgument(args, 2, &g));
	HandleError(Dart_GetNativeIntegerArgument(args, 3, &b));
	HandleError(Dart_GetNativeIntegerArgument(args, 4, &a));

	SDL_WindowWrapper2 window = GetWindowFromArgs(args);
	bool result = window.SetColor(r, g, b, a);

	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(result)));
}

void _SDL_PollEvent(Dart_NativeArguments args) {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_WINDOWEVENT:
			break;
		case SDL_MOUSEMOTION:
			break;
		}

		Dart_SetReturnValue(args, HandleError(Dart_NewInteger(event.type)));
	}
}

void _SDL_Delay(Dart_NativeArguments args) {
	int64_t ms = 1;

	HandleError(Dart_GetNativeIntegerArgument(args, 0, &ms));
	if (ms <= 0)
		ms = 1;

	SDL_Delay(ms);
}