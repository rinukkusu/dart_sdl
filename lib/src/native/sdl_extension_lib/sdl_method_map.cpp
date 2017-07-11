#include <Windows.h>
#include <dart_api.h>
#include "sdl_event_map.h"
#include "sdl_misc.h"
#include "SDL_WindowWrapper.h"
#include "sdl_method_map.h"
#include "ttf_method_map.h"
#include "img_method_map.h"
#include "json.h"

SDL_WindowWrapper2* g_wrapperArray;
struct SDL_WindowWrapper2 SDL_WindowWrapper2_t;


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

	bool success = RunOnGuiThread([](TaskValue val) {
		bool result = SDL_Init(val.integer_1) == 0;

		return TaskValue(result);
	}, TaskValue(flags)).bool_1;
	

	g_wrapperArray = (SDL_WindowWrapper2*)SDL_calloc(10, sizeof(SDL_WindowWrapper2));

	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(success)));
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

	auto val = TaskValue(x, y, w, h, flags);
	val.string_1 = title;

	auto result = RunOnGuiThread([](TaskValue val) {
		SDL_Window* window = SDL_CreateWindow(
			val.string_1, 
			val.integer_1, 
			val.integer_2, 
			val.integer_3, 
			val.integer_4, 
			val.integer_5);

		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		return TaskValue(window, renderer);
	}, TaskValue(x, y, w, h, flags));

	bool success = result.ptr_1 != NULL;

	if (success) {
		SDL_Window* window = (SDL_Window*)result.ptr_1;
		SDL_Renderer* renderer = (SDL_Renderer*)result.ptr_2;

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

	bool success = RunOnGuiThread([](TaskValue val) {
		SDL_WindowWrapper2* window = (SDL_WindowWrapper2*)val.ptr_1;

		bool result = window->Clear();

		return TaskValue(result);
	}, TaskValue(&window)).bool_1;

	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(success)));
}

void _SDL_RenderPresent(Dart_NativeArguments args) {
	SDL_WindowWrapper2 window = GetWindowFromArgs(args);

	RunOnGuiThread([](TaskValue val) {
		SDL_WindowWrapper2* window = (SDL_WindowWrapper2*)val.ptr_1;

		window->Present();

		return TaskValue();
	}, TaskValue(&window));
}

void _SDL_SetRenderDrawColor(Dart_NativeArguments args) {
	int64_t r, g, b, a = 0;
	HandleError(Dart_GetNativeIntegerArgument(args, 1, &r));
	HandleError(Dart_GetNativeIntegerArgument(args, 2, &g));
	HandleError(Dart_GetNativeIntegerArgument(args, 3, &b));
	HandleError(Dart_GetNativeIntegerArgument(args, 4, &a));

	SDL_WindowWrapper2 window = GetWindowFromArgs(args);

	bool success = RunOnGuiThread([](TaskValue val) {
		SDL_WindowWrapper2* window = (SDL_WindowWrapper2*)val.ptr_1;

		bool result = window->SetColor(val.integer_1, val.integer_2, val.integer_3, val.integer_4);

		return TaskValue(result);
	}, TaskValue(&window)).bool_1;

	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(success)));
}

void _SDL_PollEvent(Dart_NativeArguments args) {
	const char* json = RunOnGuiThread([](TaskValue val) {
		SDL_Event event;
		TaskValue retVal = TaskValue();

		if (SDL_PollEvent(&event)) {
			const char* json = EncodeEvent(&event);

			retVal.string_1 = json;
		}

		return retVal;
	}, TaskValue()).string_1;

	if (json) {
		Dart_SetReturnValue(args, HandleError(Dart_NewStringFromCString(json)));

		SDL_free((void*)json);
	}
}

void _SDL_Delay(Dart_NativeArguments args) {
	int64_t ms = 1;

	HandleError(Dart_GetNativeIntegerArgument(args, 0, &ms));
	if (ms < 0)
		ms = 0;

	RunOnGuiThread([](TaskValue val) {
		SDL_Delay(val.integer_1);

		return TaskValue();
	}, TaskValue(ms));
}

void _SDL_SetWindowTitle(Dart_NativeArguments args) {
	const char* title;

	void* peer = NULL;
	Dart_Handle titleString = HandleError(Dart_GetNativeStringArgument(args, 1, &peer));
	HandleError(Dart_StringToCString(titleString, &title));

	SDL_WindowWrapper2 window = GetWindowFromArgs(args);
	auto val = TaskValue(&window);
	val.string_1 = title;

	RunOnGuiThread([](TaskValue val) {
		SDL_WindowWrapper2* window = (SDL_WindowWrapper2*)val.ptr_1;

		window->SetWindowTitle(val.string_1);

		return TaskValue();
	}, val);
}

void _SDL_RenderDrawPoint(Dart_NativeArguments args) {
	int64_t x, y = 0;

	HandleError(Dart_GetNativeIntegerArgument(args, 1, &x));
	HandleError(Dart_GetNativeIntegerArgument(args, 2, &y));

	SDL_WindowWrapper2 window = GetWindowFromArgs(args);

	bool result = RunOnGuiThread([](TaskValue val) {
		SDL_WindowWrapper2* window = (SDL_WindowWrapper2*)val.ptr_1;

		bool result = window->DrawPoint(val.integer_1, val.integer_2);

		return TaskValue(result);
	}, TaskValue(x, y)).bool_1;

	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(result)));
}

void _SDL_RenderDrawLine(Dart_NativeArguments args) {
	int64_t x1, y1, x2, y2 = 0;

	HandleError(Dart_GetNativeIntegerArgument(args, 1, &x1));
	HandleError(Dart_GetNativeIntegerArgument(args, 2, &y1));
	HandleError(Dart_GetNativeIntegerArgument(args, 3, &x2));
	HandleError(Dart_GetNativeIntegerArgument(args, 4, &y2));

	SDL_WindowWrapper2 window = GetWindowFromArgs(args);

	bool result = RunOnGuiThread([](TaskValue val) {
		SDL_WindowWrapper2* window = (SDL_WindowWrapper2*)val.ptr_1;

		bool result = window->DrawLine(val.integer_1, val.integer_2, val.integer_3, val.integer_4);

		return TaskValue(result);
	}, TaskValue(x1, y1, x2, y2)).bool_1;

	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(result)));
}

void _SDL_ShowCursor(Dart_NativeArguments args) {
	int64_t toggle = 0;

	HandleError(Dart_GetNativeIntegerArgument(args, 0, &toggle));

	bool result = RunOnGuiThread([](TaskValue val) {
		bool result = SDL_ShowCursor(val.integer_1) == SDL_ENABLE;

		return TaskValue(result);
	}, TaskValue(toggle)).bool_1;

	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(result)));
}

void _SDL_CreateTextureFromSurface(Dart_NativeArguments args) {
	int64_t surfacePtr = 0;

	HandleError(Dart_GetNativeIntegerArgument(args, 1, &surfacePtr));

	SDL_Surface* surface = reinterpret_cast<SDL_Surface*>(surfacePtr);

	SDL_WindowWrapper2 window = GetWindowFromArgs(args);

	auto result = RunOnGuiThread([](TaskValue val) {
		SDL_WindowWrapper2* window = (SDL_WindowWrapper2*)val.ptr_1;
		SDL_Surface* surface = (SDL_Surface*)val.ptr_2;
		SDL_Texture* texture = window->CreateTextureFromSurface(surface);

		int width; int height;
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);

		uint64_t texturePtr = reinterpret_cast<uint64_t>(texture);

		return TaskValue(texturePtr, width, height);
	}, TaskValue(&window, surface));

	std::string ptrString = std::to_string(result.integer_1);

	// render to json
	json_object o = {};
	o.init();

	o.add("data", ptrString.c_str());
	o.add("width", result.integer_2);
	o.add("height", result.integer_3);

	const char* json = o.serialize();

	Dart_SetReturnValue(args, HandleError(Dart_NewStringFromCString(json)));

	o.free();
	SDL_free((void*)json);
}

void _SDL_RenderCopy(Dart_NativeArguments args) {
	int64_t texturePtr = 0;

	int64_t src_x, src_y, src_w, src_h;
	int64_t dst_x, dst_y, dst_w, dst_h;

	HandleError(Dart_GetNativeIntegerArgument(args, 1, &texturePtr));
	HandleError(Dart_GetNativeIntegerArgument(args, 2, &src_x));
	HandleError(Dart_GetNativeIntegerArgument(args, 3, &src_y));
	HandleError(Dart_GetNativeIntegerArgument(args, 4, &src_w));
	HandleError(Dart_GetNativeIntegerArgument(args, 5, &src_h));
	HandleError(Dart_GetNativeIntegerArgument(args, 6, &dst_x));
	HandleError(Dart_GetNativeIntegerArgument(args, 7, &dst_y));
	HandleError(Dart_GetNativeIntegerArgument(args, 8, &dst_w));
	HandleError(Dart_GetNativeIntegerArgument(args, 9, &dst_h));

	SDL_Rect* src = NULL;
	if (src_x || src_y || src_w || src_h) {
		SDL_Rect srcRect;
		srcRect.x = src_x;
		srcRect.y = src_y;
		srcRect.w = src_w;
		srcRect.h = src_h;

		src = &srcRect;
	}

	SDL_Rect dst;
	dst.x = dst_x;
	dst.y = dst_y;
	dst.w = dst_w;
	dst.h = dst_h;

	SDL_WindowWrapper2 window = GetWindowFromArgs(args);

	TaskValue val = TaskValue(&window, src, &dst);
	val.integer_1 = texturePtr;

	bool result = RunOnGuiThread([](TaskValue val) {
		SDL_WindowWrapper2* window = (SDL_WindowWrapper2*)val.ptr_1;
		SDL_Texture* texture = reinterpret_cast<SDL_Texture*>(val.integer_1);
		SDL_Rect* src = (SDL_Rect*)val.ptr_2;
		SDL_Rect* dst = (SDL_Rect*)val.ptr_3;

		bool result = window->RenderCopy(texture, src, dst);

		return TaskValue(result);
	}, val).bool_1;

	Dart_SetReturnValue(args, HandleError(Dart_NewBoolean(result)));
}

void _SDL_FreeSurface(Dart_NativeArguments args) {
	int64_t surfacePtr = 0;

	HandleError(Dart_GetNativeIntegerArgument(args, 0, &surfacePtr));

	RunOnGuiThread([](TaskValue val) {
		SDL_Surface* surface = reinterpret_cast<SDL_Surface*>(val.integer_1);
		SDL_FreeSurface(surface);

		return TaskValue();
	}, TaskValue(surfacePtr));
}

void _GetCurrentThreadId_2(Dart_NativeArguments args) {
	auto threadId = RunOnGuiThread([](TaskValue a) {
		auto threadId = GetCurrentThreadId();
		return TaskValue((int64_t)threadId);
	}, TaskValue());

	Dart_SetReturnValue(args, HandleError(Dart_NewIntegerFromUint64(threadId.integer_1)));
}

////////////////////////////////////////////////////////////////////////////////////

Dart_NativeFunction GetMethod(const char * title)
{
	Dart_NativeFunction result = NULL;

	if (strcmp("GetCurrentThreadId", title) == 0) result = _GetCurrentThreadId;
	if (strcmp("GetCurrentThreadId_2", title) == 0) result = _GetCurrentThreadId_2;

	if (strcmp("SDL_Init", title) == 0) result = _SDL_Init;
	if (strcmp("SDL_CreateWindow", title) == 0) result = _SDL_CreateWindow;
	if (strcmp("SDL_RenderClear", title) == 0) result = _SDL_RenderClear;
	if (strcmp("SDL_SetRenderDrawColor", title) == 0) result = _SDL_SetRenderDrawColor;
	if (strcmp("SDL_RenderPresent", title) == 0) result = _SDL_RenderPresent;
	if (strcmp("SDL_PollEvent", title) == 0) result = _SDL_PollEvent;
	if (strcmp("SDL_Delay", title) == 0) result = _SDL_Delay;
	if (strcmp("SDL_SetWindowTitle", title) == 0) result = _SDL_SetWindowTitle;
	if (strcmp("SDL_RenderDrawPoint", title) == 0) result = _SDL_RenderDrawPoint;
	if (strcmp("SDL_RenderDrawLine", title) == 0) result = _SDL_RenderDrawLine;
	if (strcmp("SDL_ShowCursor", title) == 0) result = _SDL_ShowCursor;
	if (strcmp("SDL_CreateTextureFromSurface", title) == 0) result = _SDL_CreateTextureFromSurface;
	if (strcmp("SDL_RenderCopy", title) == 0) result = _SDL_RenderCopy;
	if (strcmp("SDL_FreeSurface", title) == 0) result = _SDL_FreeSurface;

	// search in ttf library for method
	if (result == NULL) {
		result = TTF_GetMethod(title);
	}

	// search in img library for method
	if (result == NULL) {
		result = IMG_GetMethod(title);
	}

	return result;
}