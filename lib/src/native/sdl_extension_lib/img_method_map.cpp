#include "sdl_misc.h"
#include "img_method_map.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>

void _IMG_Init(Dart_NativeArguments args) {
	int64_t flags = 0;

	HandleError(Dart_GetNativeIntegerArgument(args, 0, &flags));

	bool result = IMG_Init(flags) != 0;

	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(result)));
}

Dart_NativeFunction IMG_GetMethod(const char * title)
{
	Dart_NativeFunction result = NULL;

	if (strcmp("IMG_Init", title) == 0) result = _IMG_Init;


	return result;
}
