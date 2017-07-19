#include "sdl_misc.h"
#include "img_method_map.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>

void _IMG_Init(Dart_NativeArguments args) {
	int64_t flags = 0;

	HandleError(Dart_GetNativeIntegerArgument(args, 0, &flags));

	bool result = RunOnGuiThread([](TaskValue val) {
		bool result = IMG_Init(flags) != 0;

		return TaskValue(result);
	}, TaskValue(flags)).bool_1;

	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(result)));
}

void _IMG_Load(Dart_NativeArguments args) {
	const char* filename = NULL;
	
	void* peer = NULL;
	Dart_Handle fileString = HandleError(Dart_GetNativeStringArgument(args, 1, &peer));
	HandleError(Dart_StringToCString(fileString, &filename));

	int64_t surfacePtr = RunOnGuiThread([](TaskValue val) {
		SDL_Surface* surface = IMG_Load(val.string_1);

		if (!surface)
			return new TaskValue((int64_t)-1);

		int64_t ptr = reinterpret_cast<int64_t>(surface);

		return TaskValue(ptr);
	}, TaskValue(filename)).integer_1;

	Dart_SetReturnValue(args, HandleError(Dart_NewInteger(surfacePtr)));
}

Dart_NativeFunction IMG_GetMethod(const char * title)
{
	Dart_NativeFunction result = NULL;

	if (strcmp("IMG_Init", title) == 0) result = _IMG_Init;


	return result;
}
