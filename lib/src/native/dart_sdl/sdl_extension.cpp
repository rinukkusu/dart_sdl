#include <string>
#include <dart_api.h>
#include <SDL.h>

#include "sdl_methods.h"

// Forward declaration of ResolveName function.
Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool* auto_setup_scope);

void _SDL_Init(Dart_NativeArguments args);
void _SDL_CreateWindow(Dart_NativeArguments args);

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

void Test(Dart_NativeArguments arguments) {
	Dart_Handle result = HandleError(Dart_NewInteger(5));
	Dart_SetReturnValue(arguments, result);
}

Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool * auto_setup_scope)
{
	// If we fail, we return NULL, and Dart throws an exception.
	if (!Dart_IsString(name)) return NULL;
	Dart_NativeFunction result = NULL;
	const char* cname;
	HandleError(Dart_StringToCString(name, &cname));

	if (strcmp("SDL_Init", cname) == 0) result = _SDL_Init;
	if (strcmp("SDL_CreateWindow", cname) == 0) result = _SDL_CreateWindow;

	return result;
}

//////////////////////////////////////////////////////////////////////////////////////////

SDL_Window *m_pWindow;

void _SDL_Init(Dart_NativeArguments args) {
	int64_t flags = 0;
	HandleError(Dart_GetNativeIntegerArgument(args, 0, &flags));
	SDL_Init(flags);

	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(true)));
}

void _SDL_CreateWindow(Dart_NativeArguments args) {
	const char* title = NULL;
	int64_t x, y, w, h, flags = 0;

	void* peer;
	Dart_Handle titleString = HandleError(Dart_GetNativeStringArgument(args, 0, &peer));
	HandleError(Dart_StringToCString(titleString, &title));

	HandleError(Dart_GetNativeIntegerArgument(args, 1, &x));
	HandleError(Dart_GetNativeIntegerArgument(args, 2, &y));
	HandleError(Dart_GetNativeIntegerArgument(args, 3, &w));
	HandleError(Dart_GetNativeIntegerArgument(args, 4, &h));
	HandleError(Dart_GetNativeIntegerArgument(args, 5, &flags));

	m_pWindow = SDL_CreateWindow(title, x, y, w, h, flags);

	bool success = m_pWindow != NULL;

	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(success)));
}