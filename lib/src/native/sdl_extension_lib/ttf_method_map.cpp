#include <string>
#include "SDL_ttf.h"
#include "sdl_misc.h"
#include "ttf_method_map.h"

TTF_Font** g_fonts = NULL;
short g_fontCount = 0;

void _TTF_Init(Dart_NativeArguments args) 
{
	bool result = TTF_Init() == 0;
	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(result)));

	if (result) {
		g_fonts = (TTF_Font**)SDL_calloc(sizeof(TTF_Font*), 100);
	}
}

void _TTF_OpenFont(Dart_NativeArguments args)
{
	const char* filePath = NULL;
	int64_t ptsize = 0;

	void* peer = NULL;
	Dart_Handle filePathString = HandleError(Dart_GetNativeStringArgument(args, 0, &peer));
	HandleError(Dart_StringToCString(filePathString, &filePath));

	HandleError(Dart_GetNativeIntegerArgument(args, 1, &ptsize));

	TTF_Font* font = TTF_OpenFont(filePath, ptsize);

	if (font) {
		short fontIndex = g_fontCount++;
		g_fonts[fontIndex] = font;

		Dart_SetReturnValue(args, HandleError(Dart_NewInteger(fontIndex)));
	}
	else {
		Dart_SetReturnValue(args, HandleError(Dart_NewInteger(-1)));
	}
}


////////////////////////////////////////////////////////////////////////////////////

Dart_NativeFunction TTF_GetMethod(const char * title)
{
	Dart_NativeFunction result;

	if (strcmp("TTF_Init", title) == 0) result = _TTF_Init;
	if (strcmp("TTF_OpenFont", title) == 0) result = _TTF_OpenFont;

	return result;
}
