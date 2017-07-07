#include <string>
#include <vector>
#include <memory>
#include <Windows.h>
#include <dart_api.h>
#include <dart_native_api.h>
#include <SDL.h>
#include "SDL_WindowWrapper.h"
#include "sdl_method_map.h"
#include "sdl_misc.h"


Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool * auto_setup_scope)
{
	// If we fail, we return NULL, and Dart throws an exception.
	if (!Dart_IsString(name)) return NULL;
	Dart_NativeFunction result = NULL;
	const char* cname;
	HandleError(Dart_StringToCString(name, &cname));

	result = GetMethod(cname);

	return result;
}

DART_EXPORT Dart_Handle sdl_extension_Init(Dart_Handle parent_library) {
	if (Dart_IsError(parent_library)) return parent_library;

	Dart_Handle result_code =
		Dart_SetNativeResolver(parent_library, ResolveName, NULL);
	if (Dart_IsError(result_code)) return result_code;

	return Dart_Null();
}
