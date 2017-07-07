#include "sdl_misc.h"

Dart_Handle HandleError(Dart_Handle handle) {
	if (Dart_IsError(handle)) Dart_PropagateError(handle);
	return handle;
}