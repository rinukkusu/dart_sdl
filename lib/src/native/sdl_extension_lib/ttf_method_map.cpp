#include <string>
#include "SDL_ttf.h"
#include "sdl_misc.h"
#include "ttf_method_map.h"
#include "sdl_ptrlist.h"

void _TTF_Init(Dart_NativeArguments args) 
{
	bool result = RunOnGuiThread([](TaskValue val) {
		bool result = !TTF_WasInit() && TTF_Init() == 0;

		return TaskValue(result);
	}, TaskValue()).bool_1;

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

	TaskValue val = TaskValue(filePath);
	val.integer_1 = ptsize;
	
	uint64_t fontPtr = RunOnGuiThread([](TaskValue val) {
		bool result = TTF_WasInit() == 1;
		if (result) {
			TTF_Font* font = TTF_OpenFont(val.string_1, val.integer_1);

			if (font) {
				int64_t fontPtr = reinterpret_cast<int64_t>(font);
				return TaskValue(fontPtr);
			}
		}

		return TaskValue((int64_t)-1);
	}, val).integer_1;

	if (fontPtr > 0) {
		Dart_SetReturnValue(args, HandleError(Dart_NewInteger(fontPtr)));
	}
}

void RenderText_Internal(Dart_NativeArguments args, bool blended) {
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

	TaskValue val = TaskValue((void*)font, (void*)text, (void*)&color);
	val.bool_1 = blended;

	uint64_t surfacePtr = RunOnGuiThread([](TaskValue val) {
		TTF_Font* font = (TTF_Font*)val.ptr_1;
		const char* text = (const char*)val.ptr_2;
		SDL_Color* color = (SDL_Color*)val.ptr_3;

		SDL_Surface* surface = val.bool_1
			? TTF_RenderText_Blended(font, text, *color)
			: TTF_RenderText_Solid(font, text, *color);

		int64_t surfacePtr = reinterpret_cast<int64_t>(surface);

		return TaskValue(surfacePtr);
	}, val).integer_1;

	Dart_SetReturnValue(args, HandleError(Dart_NewInteger(surfacePtr)));
}

void _TTF_RenderText(Dart_NativeArguments args) {
	RenderText_Internal(args, false);
}

void _TTF_RenderText_Blended(Dart_NativeArguments args) {
	RenderText_Internal(args, true);
}



////////////////////////////////////////////////////////////////////////////////////

Dart_NativeFunction TTF_GetMethod(const char * title)
{
	Dart_NativeFunction result = NULL;

	if (strcmp("TTF_Init", title) == 0) result = _TTF_Init;
	if (strcmp("TTF_OpenFont", title) == 0) result = _TTF_OpenFont;
	if (strcmp("TTF_RenderText", title) == 0) result = _TTF_RenderText;
	if (strcmp("TTF_RenderText_Blended", title) == 0) result = _TTF_RenderText_Blended;

	return result;
}
