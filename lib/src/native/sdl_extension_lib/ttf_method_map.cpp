#include <string>
#include "SDL_ttf.h"
#include "sdl_misc.h"
#include "ttf_method_map.h"
#include "sdl_ptrlist.h"

void _TTF_Init(Dart_NativeArguments args) 
{
	bool result = !TTF_WasInit() && TTF_Init() == 0;
	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(result)));
}

void _TTF_OpenFont(Dart_NativeArguments args)
{
	const char* filePath = NULL;
	int64_t ptsize = 0;

	void* peer = NULL;
	Dart_Handle filePathString = HandleError(Dart_GetNativeStringArgument(args, 0, &peer));
	HandleError(Dart_StringToCString(filePathString, &filePath));

	HandleError(Dart_GetNativeIntegerArgument(args, 1, &ptsize));
	
	bool result = TTF_WasInit() == 1;
	if (result) {
		TTF_Font* font = TTF_OpenFont(filePath, ptsize);

		if (font) {
			uint64_t fontPtr = reinterpret_cast<uint64_t>(font);
			Dart_SetReturnValue(args, HandleError(Dart_NewInteger(fontPtr)));

			return;
		}
	}

	Dart_SetReturnValue(args, HandleError(Dart_NewInteger(-1)));
}

void _TTF_RenderText(Dart_NativeArguments args) {
	int64_t fontPtr = 0;
	const char* text = NULL;
	int64_t r, g, b, a;

	HandleError(Dart_GetNativeIntegerArgument(args, 0, &fontPtr));

	void* peer = NULL;
	Dart_Handle filePathString = HandleError(Dart_GetNativeStringArgument(args, 1, &peer));
	HandleError(Dart_StringToCString(filePathString, &text));

	HandleError(Dart_GetNativeIntegerArgument(args, 2, &r));
	HandleError(Dart_GetNativeIntegerArgument(args, 3, &g));
	HandleError(Dart_GetNativeIntegerArgument(args, 4, &b));
	HandleError(Dart_GetNativeIntegerArgument(args, 5, &a));

	SDL_Color color = { r, g, b, a };

	TTF_Font* font = reinterpret_cast<TTF_Font*>(fontPtr);
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);

	uint64_t surfacePtr = reinterpret_cast<uint64_t>(surface);
	Dart_SetReturnValue(args, HandleError(Dart_NewInteger(surfacePtr)));
}


////////////////////////////////////////////////////////////////////////////////////

Dart_NativeFunction TTF_GetMethod(const char * title)
{
	Dart_NativeFunction result;

	if (strcmp("TTF_Init", title) == 0) result = _TTF_Init;
	if (strcmp("TTF_OpenFont", title) == 0) result = _TTF_OpenFont;
	if (strcmp("TTF_RenderText", title) == 0) result = _TTF_RenderText;

	return result;
}
